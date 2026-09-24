#ifndef UINT_POD_H_
#define UINT_POD_H_

#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <type_traits>

namespace {
  std::mt19937_64 rng64(14);
  uint64_t rng_leftover;
  uint64_t rng_bits_left = 0;
}

template<int w_> struct SInt;

constexpr int _pod_cmin(int a, int b) { return a < b ? a : b; }
constexpr int _pod_cmax(int a, int b) { return a > b ? a : b; }

template<int w_>
struct UInt {
  static constexpr bool kWide = (w_ > 64);
  static constexpr int kWords = kWide ? (w_ + 63) / 64 : 1;

  using scalar_t =
    std::conditional_t<(w_ <= 8), uint8_t,
    std::conditional_t<(w_ <= 16), uint16_t,
    std::conditional_t<(w_ <= 32), uint32_t, uint64_t>>>;

  using storage_t = std::conditional_t<kWide, std::array<uint64_t, kWords>, scalar_t>;

  static constexpr int kTopBits = kWide ? (w_ % 64 == 0 ? 64 : w_ % 64)
                                        : (w_ % (sizeof(scalar_t)*8) == 0 ? (int)(sizeof(scalar_t)*8) : w_ % (int)(sizeof(scalar_t)*8));
  static constexpr auto kMask = []() -> storage_t {
    if constexpr (!kWide) {
      if constexpr (w_ >= (int)(sizeof(scalar_t)*8)) return ~scalar_t(0);
      else return static_cast<scalar_t>((scalar_t(1) << w_) - 1);
    } else {
      return storage_t{};
    }
  }();

  storage_t val;

  UInt() : val{} {}

  template<int ow>
  UInt& operator=(const UInt<ow>& o) {
    if constexpr (!kWide && !UInt<ow>::kWide) {
      val = static_cast<scalar_t>(o.val);
    } else if constexpr (!kWide && UInt<ow>::kWide) {
      val = static_cast<scalar_t>(o.val[0]);
    } else if constexpr (kWide && !UInt<ow>::kWide) {
      val[0] = static_cast<uint64_t>(o.val);
      for (int i = 1; i < kWords; i++) val[i] = 0;
    } else {
      constexpr int mn = _pod_cmin(kWords, UInt<ow>::kWords);
      for (int i = 0; i < mn; i++) val[i] = o.val[i];
      for (int i = mn; i < kWords; i++) val[i] = 0;
    }
    mask_top();
    return *this;
  }

  template<int ow>
  UInt& operator=(const SInt<ow>& o) {
    return *this = o.asUInt();
  }

  UInt(uint64_t v) : val{} {
    if constexpr (!kWide) val = static_cast<scalar_t>(v);
    else val[0] = v;
    mask_top();
  }

  UInt(std::string initial) : val{} {
    if (initial.substr(0,2) != "0x") { std::cerr << "UInt: string must start with 0x\n"; std::exit(-17); }
    initial.erase(0,2);
    if constexpr (!kWide) {
      val = static_cast<scalar_t>(std::stoull(initial, nullptr, 16));
    } else {
      int last = initial.length();
      for (int i = 0; i < kWords && last > 0; i++) {
        int start = std::max(0, last - 16);
        val[i] = std::stoull(initial.substr(start, last - start), nullptr, 16);
        last = start;
      }
    }
    mask_top();
  }

  UInt(std::array<uint64_t, kWords> raw) : val{} {
    if constexpr (!kWide) val = static_cast<scalar_t>(raw[kWords - 1]);
    else { for (int i = 0; i < kWords; i++) val[i] = raw[kWords - 1 - i]; }
    mask_top();
  }

  template<int ow, std::enable_if_t<(ow < w_), int> = 0>
  UInt(const UInt<ow>& o) : val{} {
    if constexpr (!kWide && !UInt<ow>::kWide) {
      val = static_cast<scalar_t>(o.val);
    } else if constexpr (kWide && !UInt<ow>::kWide) {
      val[0] = static_cast<uint64_t>(o.val);
    } else if constexpr (!kWide && UInt<ow>::kWide) {
      val = static_cast<scalar_t>(o.val[0]);
    } else {
      for (int i = 0; i < _pod_cmin(kWords, UInt<ow>::kWords); i++) val[i] = o.val[i];
    }
  }

  void mask_top() {
    if constexpr (!kWide) {
      if constexpr (w_ < (int)(sizeof(scalar_t)*8)) val &= kMask;
    } else {
      constexpr int top = w_ % 64;
      if constexpr (top != 0) val[kWords-1] &= (1ULL << top) - 1;
    }
  }

  void rand_init() {
    if constexpr (!kWide) {
      if (w_ > (int)rng_bits_left) { rng_leftover = rng64(); rng_bits_left = 64; }
      val = static_cast<scalar_t>(rng_leftover);
      rng_leftover >>= (w_ < 64 ? w_ : 0);
      rng_bits_left -= w_;
    } else {
      for (int i = 0; i < kWords; i++) val[i] = rng64();
    }
    mask_top();
  }

  uint64_t as_single_word() const {
    static_assert(w_ <= 64, "UInt too wide for as_single_word");
    return static_cast<uint64_t>(val);
  }

  template<int ow>
  UInt<_pod_cmax(w_,ow)> pad() const { return UInt<_pod_cmax(w_,ow)>(*this); }

  template<int ow>
  UInt<w_ + ow> cat(const UInt<ow>& o) const {
    constexpr int rw = w_ + ow;
    if constexpr (rw <= 64 && !kWide && !UInt<ow>::kWide) {
      using rt = typename UInt<rw>::scalar_t;
      return UInt<rw>(static_cast<rt>((static_cast<uint64_t>(val) << ow) | static_cast<uint64_t>(o.val)));
    } else {
      UInt<rw> r(o);
      constexpr int off_word = ow / 64, off_bit = ow % 64;
      uint64_t hi;
      if constexpr (kWide) hi = val[0]; else hi = static_cast<uint64_t>(val);
      if constexpr (off_bit == 0) r.val[off_word] = hi;
      else {
        r.val[off_word] |= hi << off_bit;
        if constexpr (off_word + 1 < UInt<rw>::kWords)
          r.val[off_word + 1] = hi >> (64 - off_bit);
      }
      if constexpr (kWide) {
        for (int i = 1; i < kWords; i++) {
          int dw = off_word + i;
          if constexpr (off_bit == 0) { if (dw < UInt<rw>::kWords) r.val[dw] = val[i]; }
          else {
            if (dw < UInt<rw>::kWords) r.val[dw] |= val[i] << off_bit;
            if (dw + 1 < UInt<rw>::kWords) r.val[dw + 1] = val[i] >> (64 - off_bit);
          }
        }
      }
      return r;
    }
  }

  template<int hi, int lo>
  UInt<hi - lo + 1> bits() const {
    static_assert(hi >= lo && hi < w_ && lo >= 0);
    constexpr int rw = hi - lo + 1;
    if constexpr (!kWide) {
      return UInt<rw>(static_cast<uint64_t>(val) >> lo);
    } else if constexpr (rw <= 64) {
      constexpr int lo_w = lo / 64, lo_b = lo % 64;
      uint64_t v = val[lo_w] >> lo_b;
      if constexpr (lo_b > 0 && lo_w + 1 < kWords)
        v |= val[lo_w + 1] << (64 - lo_b);
      return UInt<rw>(v);
    } else {
      // Wide result: assemble each output word from one or two source words.
      constexpr int lo_w = lo / 64, lo_b = lo % 64;
      UInt<rw> r{};
      for (int i = 0; i < UInt<rw>::kWords; i++) {
        const int si = lo_w + i;
        uint64_t v = (si < kWords) ? (val[si] >> lo_b) : 0;
        // lo_b is compile-time constant.  A normal `if (lo_b > 0)` still
        // instantiates `<< 64` when lo is word-aligned, which is undefined C++
        // and rejected by Clang under -Werror even though the branch is never
        // taken.  Do not instantiate that expression at all in the aligned
        // specialization.
        if constexpr (lo_b > 0) {
          if (si + 1 < kWords) v |= val[si + 1] << (64 - lo_b);
        }
        r.val[i] = v;
      }
      r.mask_top();
      return r;
    }
  }

  template<int n> UInt<n> head() const { return bits<w_-1, w_-n>(); }
  template<int n> UInt<w_-n> tail() const { return bits<w_-n-1, 0>(); }

  template<int sh>
  UInt<w_ + sh> shl() const {
    static_assert(sh >= 0);
    return cat(UInt<sh>(0));
  }

  template<int sh>
  UInt<w_> shlw() const { return shl<sh>().template tail<sh>(); }

  template<int sh>
  UInt<_pod_cmax(w_-sh,1)> shr() const {
    static_assert(sh >= 0);
    if constexpr (sh >= w_) return UInt<_pod_cmax(w_-sh,1)>(0);
    else return bits<w_-1, sh>();
  }

  template<int ow>
  UInt<w_> operator>>(const UInt<ow>& o) const {
    if constexpr (!kWide) {
      uint64_t s = o.as_single_word();
      return s >= (unsigned)w_ ? UInt<w_>(0) : UInt<w_>(static_cast<scalar_t>(val >> s));
    } else {
      uint64_t s = o.as_single_word();
      UInt<w_> r;
      int wdown = s / 64, bdown = s % 64;
      for (int i = 0; i < kWords; i++) {
        int si = i + wdown;
        r.val[i] = (si < kWords) ? val[si] >> bdown : 0;
        if (bdown && si + 1 < kWords) r.val[i] |= val[si+1] << (64 - bdown);
      }
      return r;
    }
  }

  template<int ow>
  UInt<w_ + (1<<ow) - 1> operator<<(const UInt<ow>& o) const {
    constexpr int rw = w_ + (1<<ow) - 1;
    if constexpr (rw <= 64 && !kWide) {
      using rt = typename UInt<rw>::scalar_t;
      return UInt<rw>(static_cast<rt>(static_cast<uint64_t>(val) << o.as_single_word()));
    } else {
      UInt<rw> r{};
      uint64_t s = o.as_single_word();
      if (s >= (unsigned)rw) return r;
      int wordOff = s / 64;
      int bitOff  = s % 64;
      auto getWord = [&](int i) -> uint64_t {
        if (i < 0 || i >= kWords) return 0;
        if constexpr (kWide) return val[i];
        else return (i == 0) ? static_cast<uint64_t>(val) : 0;
      };
      for (int i = UInt<rw>::kWords - 1; i >= wordOff; i--) {
        uint64_t w = getWord(i - wordOff);
        r.val[i] = (bitOff == 0) ? w : (w << bitOff);
        if (bitOff > 0 && i > wordOff) {
          r.val[i] |= getWord(i - wordOff - 1) >> (64 - bitOff);
        }
      }
      r.mask_top();
      return r;
    }
  }

  template<int ow>
  UInt<w_> dshlw(const UInt<ow>& o) const {
    if constexpr (!kWide) {
      uint64_t s = o.as_single_word();
      scalar_t r = (s >= 64) ? 0 : static_cast<scalar_t>((static_cast<uint64_t>(val) << s));
      if constexpr (w_ < (int)(sizeof(scalar_t)*8)) r &= kMask;
      return UInt<w_>(r);
    } else {
      uint64_t s = o.as_single_word();
      UInt<w_> r;
      int wup = s / 64, bup = s % 64;
      for (int i = kWords - 1; i >= 0; i--) {
        int si = i - wup;
        r.val[i] = (si >= 0) ? val[si] << bup : 0;
        if (bup && si - 1 >= 0) r.val[i] |= val[si-1] >> (64 - bup);
      }
      r.mask_top();
      return r;
    }
  }

  UInt<w_> addw(const UInt<w_>& o) const {
    if constexpr (!kWide) return UInt<w_>(static_cast<scalar_t>((val + o.val) & kMask));
    else {
      UInt<w_> r;
      uint64_t carry = 0;
      for (int i = 0; i < kWords; i++) {
        __uint128_t s = (__uint128_t)val[i] + o.val[i] + carry;
        r.val[i] = (uint64_t)s; carry = (uint64_t)(s >> 64);
      }
      r.mask_top(); return r;
    }
  }
  UInt<w_> subw(const UInt<w_>& o) const {
    if constexpr (!kWide) return UInt<w_>(static_cast<scalar_t>((val - o.val) & kMask));
    else {
      UInt<w_> r;
      uint64_t borrow = 0;
      for (int i = 0; i < kWords; i++) {
        __uint128_t s = (__uint128_t)val[i] - o.val[i] - borrow;
        r.val[i] = (uint64_t)s; borrow = (s >> 127) & 1;
      }
      r.mask_top(); return r;
    }
  }

  template<int ow>
  UInt<_pod_cmax(w_,ow)+1> operator+(const UInt<ow>& o) const {
    constexpr int rw = _pod_cmax(w_,ow) + 1;
    if constexpr (rw <= 64 && !kWide && !UInt<ow>::kWide) {
      return UInt<rw>(static_cast<uint64_t>(val) + static_cast<uint64_t>(o.val));
    } else {
      auto a = pad<rw>(); auto b = o.template pad<rw>();
      return a.addw(b);
    }
  }

  template<int ow>
  UInt<_pod_cmax(w_,ow)+1> operator-(const UInt<ow>& o) const {
    constexpr int rw = _pod_cmax(w_,ow) + 1;
    if constexpr (rw <= 64 && !kWide && !UInt<ow>::kWide) {
      return UInt<rw>(static_cast<uint64_t>(val) - static_cast<uint64_t>(o.val));
    } else {
      auto a = pad<rw>(); auto b = o.template pad<rw>();
      return a.subw(b);
    }
  }

  SInt<w_+1> operator-() const;

  template<int ow>
  UInt<w_+ow> operator*(const UInt<ow>& o) const {
    if constexpr (w_ <= 32 && ow <= 32) {
      return UInt<w_+ow>(static_cast<uint64_t>(val) * static_cast<uint64_t>(o.val));
    } else if constexpr (w_ <= 64 && ow <= 64) {
      __uint128_t a = as_single_word(), b = o.as_single_word();
      __uint128_t p = a * b;
      UInt<w_+ow> r;
      if constexpr (w_+ow <= 64) { r = UInt<w_+ow>(static_cast<uint64_t>(p)); }
      else {
        r.val[0] = static_cast<uint64_t>(p);
        if constexpr (UInt<w_+ow>::kWords > 1) r.val[1] = static_cast<uint64_t>(p >> 64);
        for (int i = 2; i < UInt<w_+ow>::kWords; i++) r.val[i] = 0;
        r.mask_top();
      }
      return r;
    } else {
      // Wide multiply: schoolbook over 64-bit words with 128-bit partial
      // products. Result width w_+ow always covers na+nb words, so no
      // partial product is ever dropped; mask_top() trims the top word.
      constexpr int rww = UInt<w_+ow>::kWords;
      auto word_of = [](const auto& u, int i) -> uint64_t {
        using T = std::decay_t<decltype(u)>;
        if constexpr (T::kWide) return u.val[i];
        else return i == 0 ? static_cast<uint64_t>(u.val) : 0;
      };
      constexpr int na = kWide ? kWords : 1;
      constexpr int nb = UInt<ow>::kWide ? UInt<ow>::kWords : 1;
      UInt<w_+ow> r{};
      for (int i = 0; i < na; i++) {
        const uint64_t a = word_of(*this, i);
        if (a == 0) continue;
        uint64_t carry = 0;
        for (int j = 0; j < nb; j++) {
          __uint128_t p = (__uint128_t)a * word_of(o, j) + r.val[i + j] + carry;
          r.val[i + j] = (uint64_t)p;
          carry = (uint64_t)(p >> 64);
        }
        for (int k = i + nb; carry != 0 && k < rww; k++) {
          __uint128_t s = (__uint128_t)r.val[k] + carry;
          r.val[k] = (uint64_t)s;
          carry = (uint64_t)(s >> 64);
        }
      }
      r.mask_top();
      return r;
    }
  }

  template<int ow>
  UInt<w_> operator/(const UInt<ow>& o) const {
    static_assert(w_ <= 64 && ow <= 64);
    return UInt<w_>(as_single_word() / o.as_single_word());
  }

  template<int ow>
  UInt<_pod_cmin(w_,ow)> operator%(const UInt<ow>& o) const {
    static_assert(w_ <= 64 && ow <= 64);
    return UInt<_pod_cmin(w_,ow)>(as_single_word() % o.as_single_word());
  }

  UInt<w_> operator~() const {
    if constexpr (!kWide) return UInt<w_>(static_cast<scalar_t>(~val & kMask));
    else { UInt<w_> r; for (int i=0;i<kWords;i++) r.val[i]=~val[i]; r.mask_top(); return r; }
  }
  UInt<w_> operator&(const UInt<w_>& o) const {
    if constexpr (!kWide) return UInt<w_>(val & o.val);
    else { UInt<w_> r; for (int i=0;i<kWords;i++) r.val[i]=val[i]&o.val[i]; return r; }
  }
  UInt<w_> operator|(const UInt<w_>& o) const {
    if constexpr (!kWide) return UInt<w_>(val | o.val);
    else { UInt<w_> r; for (int i=0;i<kWords;i++) r.val[i]=val[i]|o.val[i]; return r; }
  }
  UInt<w_> operator^(const UInt<w_>& o) const {
    if constexpr (!kWide) return UInt<w_>(val ^ o.val);
    else { UInt<w_> r; for (int i=0;i<kWords;i++) r.val[i]=val[i]^o.val[i]; return r; }
  }

  UInt<1> andr() const { return *this == ~UInt<w_>(0); }
  UInt<1> orr()  const { return *this != UInt<w_>(0); }
  UInt<1> xorr() const {
    uint64_t v = 0;
    if constexpr (!kWide) v = static_cast<uint64_t>(val);
    else { for (int i=0;i<kWords;i++) v ^= val[i]; }
    v ^= v >> 1; v ^= v >> 2; v ^= v >> 4;
    v ^= v >> 8; v ^= v >> 16; v ^= v >> 32;
    return UInt<1>(v & 1);
  }

  UInt<1> operator==(const UInt<w_>& o) const {
    if constexpr (!kWide) return UInt<1>(val == o.val);
    else { for (int i=0;i<kWords;i++) if (val[i]!=o.val[i]) return UInt<1>(0); return UInt<1>(1); }
  }
  UInt<1> operator!=(const UInt<w_>& o) const {
    if constexpr (!kWide) return UInt<1>(val != o.val);
    else { return ~(*this == o); }
  }
  UInt<1> operator<=(const UInt<w_>& o) const {
    if constexpr (!kWide) return UInt<1>(val <= o.val);
    else { for (int i=kWords-1;i>=0;i--) { if (val[i]<o.val[i]) return UInt<1>(1); if (val[i]>o.val[i]) return UInt<1>(0); } return UInt<1>(1); }
  }
  template<int ow> UInt<1> operator>=(const UInt<ow>& o) const { return pad<_pod_cmax(w_,ow)>() >= o.template pad<_pod_cmax(w_,ow)>(); }
  template<int ow> UInt<1> operator<(const UInt<ow>& o) const { return pad<_pod_cmax(w_,ow)>() < o.template pad<_pod_cmax(w_,ow)>(); }
  UInt<1> operator>=(const UInt<w_>& o) const {
    if constexpr (!kWide) return UInt<1>(val >= o.val);
    else { for (int i=kWords-1;i>=0;i--) { if (val[i]>o.val[i]) return UInt<1>(1); if (val[i]<o.val[i]) return UInt<1>(0); } return UInt<1>(1); }
  }
  UInt<1> operator<(const UInt<w_>& o) const {
    if constexpr (!kWide) return UInt<1>(val < o.val);
    else return ~(*this >= o);
  }
  UInt<1> operator>(const UInt<w_>& o) const {
    if constexpr (!kWide) return UInt<1>(val > o.val);
    else return ~(*this <= o);
  }

  explicit operator bool() const {
    if constexpr (!kWide) return val != 0;
    else { for (auto w : val) if (w) return true; return false; }
  }

  SInt<w_> asSInt() const;
  UInt<w_> asUInt() const { return *this; }
  SInt<w_+1> cvt() const;

  __attribute__((noinline))
  std::string to_bin_str() const {
    std::string s; s.reserve(w_);
    if constexpr (!kWide) {
      uint64_t m = static_cast<uint64_t>(val);
      for (int i=w_-1;i>=0;i--) s += (m & (1ULL<<i)) ? '1' : '0';
    } else {
      for (int wi=kWords-1;wi>=0;wi--) {
        int top = (wi==kWords-1) ? ((w_-1)%64) : 63;
        for (int j=top;j>=0;j--) s += (val[wi] & (1ULL<<j)) ? '1' : '0';
      }
    }
    return s;
  }

  __attribute__((noinline))
  char* write_char_buf(char* buf) const {
    int idx = 0;
    if constexpr (!kWide) {
      uint64_t m = static_cast<uint64_t>(val);
      for (int i=w_-1;i>=0;i--) buf[idx++] = (m & (1ULL<<i)) ? '1' : '0';
    } else {
      for (int wi=kWords-1;wi>=0;wi--) {
        int top = (wi==kWords-1) ? ((w_-1)%64) : 63;
        for (int j=top;j>=0;j--) buf[idx++] = (val[wi] & (1ULL<<j)) ? '1' : '0';
      }
    }
    buf[w_] = '\0'; return buf;
  }

protected:
  void raw_copy_in(uint64_t* src) {
    if constexpr (!kWide) val = static_cast<scalar_t>(*src);
    else { for (int i=0;i<kWords;i++) val[i]=src[i]; }
  }
  void raw_copy_out(uint64_t* dst) {
    if constexpr (!kWide) *dst = static_cast<uint64_t>(val);
    else { for (int i=0;i<kWords;i++) dst[i]=val[i]; }
  }

  template<int> friend struct UInt;
  template<int> friend struct SInt;
};

template<int w>
std::ostream& operator<<(std::ostream& os, const UInt<w>& u) {
  os << "0x" << std::hex;
  if constexpr (!UInt<w>::kWide) os << static_cast<uint64_t>(u.val);
  else { for (int i=UInt<w>::kWords-1;i>=0;i--) os << u.val[i]; }
  os << std::dec << "<U" << w << ">";
  return os;
}

#endif

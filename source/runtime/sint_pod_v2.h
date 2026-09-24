#ifndef SINT_POD_H_
#define SINT_POD_H_

#include "uint_pod_v2.h"

template<int w_>
struct SInt {
  UInt<w_> ui;

  SInt() : ui() {}
  SInt(int64_t v) : ui(static_cast<uint64_t>(v)) { sign_extend(); }
  SInt(std::string s) : ui(s) { sign_extend(); }
  SInt(std::array<uint64_t, UInt<w_>::kWords> r) : ui(r) { sign_extend(); }
  SInt(const UInt<w_>& u) : ui(u) {}

  template<int ow>
  SInt& operator=(const SInt<ow>& o) {
    ui = o.ui;
    sign_extend();
    return *this;
  }

  template<int ow>
  explicit SInt(const SInt<ow>& o) : ui() {
    static_assert(ow <= w_);
    ui = UInt<w_>(o.ui);
    if constexpr (ow < w_) sign_extend(ow - 1);
  }

  void rand_init() { ui.rand_init(); sign_extend(); }

  template<int ow> SInt<_pod_cmax(w_,ow)> pad() const { return SInt<_pod_cmax(w_,ow)>(*this); }

  template<int ow>
  SInt<w_+ow> cat(const SInt<ow>& o) const {
    UInt<ow> o_clean = o.ui; o_clean.mask_top();
    SInt<w_+ow> r(ui.cat(o_clean));
    r.sign_extend();
    return r;
  }

  template<int ow>
  SInt<_pod_cmax(w_,ow)+1> operator+(const SInt<ow>& o) const {
    constexpr int rw = _pod_cmax(w_,ow)+1;
    auto a = pad<rw>(); auto b = o.template pad<rw>();
    return a.addw(b);
  }
  SInt<w_> addw(const SInt<w_>& o) const { SInt<w_> r(ui.addw(o.ui)); r.sign_extend(); return r; }
  SInt<w_> subw(const SInt<w_>& o) const { SInt<w_> r(ui.subw(o.ui)); r.sign_extend(); return r; }

  SInt<w_+1> operator-() const { return SInt<w_>(0) - *this; }

  template<int ow>
  SInt<_pod_cmax(w_,ow)+1> operator-(const SInt<ow>& o) const {
    constexpr int rw = _pod_cmax(w_,ow)+1;
    auto a = pad<rw>(); auto b = o.template pad<rw>();
    return a.subw(b);
  }

  template<int ow>
  SInt<w_+ow> operator*(const SInt<ow>& o) const {
    constexpr int rw = w_ + ow;
    auto ap = pad<rw>(); auto bp = o.template pad<rw>();
    SInt<2*rw> prod(ap.ui * bp.ui);
    SInt<rw> r = prod.template tail<rw>().asSInt();
    r.sign_extend();
    return r;
  }

  template<int ow>
  SInt<w_+1> operator/(const SInt<ow>& o) const {
    static_assert(w_ <= 64 && ow <= 64);
    return SInt<w_+1>(as_single_word() / o.as_single_word());
  }

  template<int ow>
  SInt<_pod_cmin(w_,ow)> operator%(const SInt<ow>& o) const {
    static_assert(w_ <= 64 && ow <= 64);
    return SInt<_pod_cmin(w_,ow)>(as_single_word() % o.as_single_word());
  }

  UInt<w_> operator~() const { return ~ui; }
  UInt<w_> operator&(const SInt<w_>& o) const { auto r = ui & o.ui; r.mask_top(); return r; }
  UInt<w_> operator|(const SInt<w_>& o) const { auto r = ui | o.ui; r.mask_top(); return r; }
  UInt<w_> operator^(const SInt<w_>& o) const { auto r = ui ^ o.ui; r.mask_top(); return r; }

  UInt<1> andr() const { auto c = ui; c.mask_top(); return c.andr(); }
  UInt<1> orr()  const { auto c = ui; c.mask_top(); return c.orr(); }
  UInt<1> xorr() const { auto c = ui; c.mask_top(); return c.xorr(); }

  template<int hi, int lo> UInt<hi-lo+1> bits() const { return ui.template bits<hi,lo>(); }
  template<int n> UInt<n> head() const { return bits<w_-1, w_-n>(); }
  template<int n> UInt<w_-n> tail() const { return bits<w_-n-1, 0>(); }

  template<int sh> SInt<w_+sh> shl() const { return cat(SInt<sh>(0)); }
  template<int sh> SInt<w_> shlw() const { SInt<w_> r(ui.template shlw<sh>()); r.sign_extend(); return r; }

  template<int sh>
  SInt<_pod_cmax(w_-sh,1)> shr() const {
    static_assert(sh >= 0);
    constexpr int rw = _pod_cmax(w_-sh,1);
    SInt<rw> r;
    if constexpr (sh >= w_) r = SInt<rw>(ui.template bits<w_-1,w_-1>());
    else r = SInt<rw>(ui.template bits<w_-1,sh>());
    r.sign_extend(_pod_cmax(w_-sh-1,0));
    return r;
  }

  template<int ow>
  SInt<w_> operator>>(const UInt<ow>& o) const {
    // Arithmetic shift: for sh >= w_ every result bit is the sign bit, which
    // equals shifting by w_-1 and extending from bit 0.
    uint64_t sh = o.as_single_word();
    if (sh >= (unsigned)w_) sh = w_ - 1;
    UInt<ow> sh_clamped((uint64_t)sh);
    SInt<w_> r(ui >> sh_clamped);
    r.sign_extend(w_ - 1 - sh);
    return r;
  }

  template<int ow>
  SInt<w_+(1<<ow)-1> operator<<(const UInt<ow>& o) const {
    SInt<w_+(1<<ow)-1> r(ui << o);
    r.sign_extend(w_ + o.as_single_word() - 1);
    return r;
  }

  template<int ow>
  SInt<w_> dshlw(const UInt<ow>& o) const {
    SInt<w_> r(ui.dshlw(o)); r.sign_extend(); return r;
  }

  // With the sign-filled storage invariant, two's-complement ordering matches
  // unsigned ordering whenever both operands have the same sign.
  UInt<1> operator<=(const SInt<w_>& o) const {
    if (negative()) { return o.negative() ? (ui <= o.ui) : UInt<1>(1); }
    else { return o.negative() ? UInt<1>(0) : (ui <= o.ui); }
  }
  UInt<1> operator>=(const SInt<w_>& o) const {
    if (negative()) { return o.negative() ? (ui >= o.ui) : UInt<1>(0); }
    else { return o.negative() ? UInt<1>(1) : (ui >= o.ui); }
  }
  UInt<1> operator<(const SInt<w_>& o) const { return ~(*this >= o); }
  UInt<1> operator>(const SInt<w_>& o) const { return ~(*this <= o); }
  UInt<1> operator==(const SInt<w_>& o) const { return ui == o.ui; }
  UInt<1> operator!=(const SInt<w_>& o) const { return ~(*this == o); }

  UInt<w_> asUInt() const { auto r = ui; r.mask_top(); return r; }
  SInt<w_> asSInt() const { return *this; }
  SInt<w_> cvt() const { return *this; }

  int64_t as_single_word() const {
    static_assert(w_ <= 64);
    return static_cast<int64_t>(ui.val);
  }

  std::string to_bin_str() const { return ui.to_bin_str(); }
  char* write_char_buf(char* b) const { return ui.write_char_buf(b); }

private:
  bool negative() const {
    if constexpr (!UInt<w_>::kWide) {
      return (static_cast<uint64_t>(ui.val) >> (w_ - 1)) & 1;
    } else {
      int word = (w_ - 1) / 64, bit = (w_ - 1) % 64;
      return (ui.val[word] >> bit) & 1;
    }
  }

  void sign_extend(int sign_index = w_ - 1) {
    if constexpr (!UInt<w_>::kWide) {
      int so = sign_index % 64;
      int64_t sv = static_cast<int64_t>(ui.val);
      ui.val = static_cast<typename UInt<w_>::scalar_t>(
        (sv << (63 - so)) >> (63 - so));
    } else {
      int sw = sign_index / 64, sb = sign_index % 64;
      bool neg = (ui.val[sw] >> sb) & 1;
      ui.val[sw] = (static_cast<int64_t>(ui.val[sw]) << (63 - sb)) >> (63 - sb);
      for (int i = sw + 1; i < UInt<w_>::kWords; i++)
        ui.val[i] = neg ? ~uint64_t(0) : 0;
    }
  }

  template<int> friend struct UInt;
  template<int> friend struct SInt;
};

template<int w_>
SInt<w_> UInt<w_>::asSInt() const {
  SInt<w_> r(*this);
  r.sign_extend();  // establish the sign-filled storage invariant
  return r;
}

template<int w_>
SInt<w_+1> UInt<w_>::cvt() const { return pad<w_+1>().asSInt(); }

template<int w_>
SInt<w_+1> UInt<w_>::operator-() const {
  return SInt<w_+1>(0).subw(SInt<w_+1>(pad<w_+1>()));
}

template<int w>
std::ostream& operator<<(std::ostream& os, const SInt<w>& s) {
  s.ui.to_bin_str(); os << "<S" << w << ">"; return os;
}

#endif

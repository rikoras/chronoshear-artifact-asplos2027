// Read-only result observer for the fixed Rocket Dhrystone ELF (SHA256
// c1588a509e757aed52867603957949390d99ee7aa227f84214ebf898e56c17fa).
// Call PCs select actual result-report arguments, never adjacent "should be"
// constants. Readers must obtain values from the observed implementation.
#pragma once
#include <cstdint>
#include <cstdio>
#include <cstring>
struct DhrystoneFunctional {
  const char* side;
  unsigned numeric_seen = 0, string_seen = 0, pointer_seen = 0, failures = 0;
  struct Numeric { uint64_t pc, value; const char* name; };
  static constexpr Numeric numeric[] = {
    {0x80001d30,5,"Int_Glob"}, {0x80001d58,1,"Bool_Glob"},
    {0x80001d7a,65,"Ch_1_Glob"}, {0x80001d9e,66,"Ch_2_Glob"},
    {0x80001dc0,7,"Arr_1_Glob[8]"}, {0x80001de6,510,"Arr_2_Glob[8][7]"},
    {0x80001e2e,0,"Ptr.Discr"}, {0x80001e4e,2,"Ptr.Enum"}, {0x80001e6e,17,"Ptr.Int"},
    {0x80001ed2,0,"Next.Discr"}, {0x80001ef0,1,"Next.Enum"}, {0x80001f0e,18,"Next.Int"},
    {0x80001f48,5,"Int_1_Loc"}, {0x80001f72,13,"Int_2_Loc"},
    {0x80001f90,7,"Int_3_Loc"}, {0x80001fae,1,"Enum_Loc"}};
  template<class Read> static uint64_t read_n(Read read, uint64_t address, unsigned bytes) {
    uint64_t value = 0;
    for (unsigned byte = 0; byte < bytes; ++byte)
      value |= ((read((address+byte) & ~UINT64_C(7)) >> (8*((address+byte)&7))) & 255) << (8*byte);
    return value;
  }
  template<class Read> static bool string_equal(Read read, uint64_t address, const char* text) {
    for (size_t i = 0; i <= std::strlen(text); ++i)
      if (read_n(read, address+i, 1) != static_cast<unsigned char>(text[i])) return false;
    return true;
  }
  template<class Read> void observe(uint64_t pc, uint64_t argument, Read read) {
    for (unsigned i = 0; i < 16; ++i) if (pc == numeric[i].pc) {
      const bool okay = argument == numeric[i].value && !(numeric_seen & (1u<<i));
      failures += !okay; numeric_seen |= 1u<<i;
      std::printf("DHRYSTONE_ARGUMENT side=%s name=%s actual=%llu expected=%llu status=%s\n", side,
                  numeric[i].name, (unsigned long long)argument, (unsigned long long)numeric[i].value, okay?"pass":"FAIL");
    }
    const uint64_t pcs[] = {0x80001e8e,0x80001f2c,0x80001fcc,0x80001fe8};
    const char* strings[] = {"DHRYSTONE PROGRAM, SOME STRING", "DHRYSTONE PROGRAM, SOME STRING",
                            "DHRYSTONE PROGRAM, 1'ST STRING", "DHRYSTONE PROGRAM, 2'ND STRING"};
    for (unsigned i = 0; i < 4; ++i) if (pc == pcs[i]) {
      const bool okay = string_equal(read, argument, strings[i]) && !(string_seen & (1u<<i));
      failures += !okay; string_seen |= 1u<<i;
      std::printf("DHRYSTONE_STRING side=%s index=%u status=%s\n", side, i, okay?"pass":"FAIL");
    }
    if (pc == 0x80001e10 || pc == 0x80001eb6) {
      const unsigned index = pc == 0x80001e10 ? 0 : 1;
      const auto next = read(0x800028e8);
      const bool okay = argument != 0 && argument == next && !(pointer_seen & (1u<<index));
      pointer_seen |= 1u<<index; failures += !okay;
      std::printf("DHRYSTONE_POINTER side=%s index=%u actual=0x%llx expected=0x%llx status=%s\n", side,
                  index, (unsigned long long)argument, (unsigned long long)next, okay?"pass":"FAIL");
    }
  }
  template<class Read> bool finish(Read read) {
    struct Mem { uint64_t address, value; unsigned bytes; const char* name; };
    const Mem checks[] = {{0x800028e0,5,4,"Int_Glob"}, {0x800028dc,1,4,"Bool_Glob"},
      {0x800028d9,65,1,"Ch_1_Glob"}, {0x800028d8,66,1,"Ch_2_Glob"},
      {0x80002918,7,4,"Arr_1_Glob[8]"}, {0x8000301c,510,4,"Arr_2_Glob[8][7]"}, {0x800028d0,1,4,"Done"}};
    for (const auto& c : checks) {
      const auto actual = read_n(read, c.address, c.bytes);
      failures += actual != c.value;
      std::printf("DHRYSTONE_MEMORY side=%s name=%s actual=%llu expected=%llu status=%s\n", side,
                  c.name, (unsigned long long)actual, (unsigned long long)c.value, actual==c.value?"pass":"FAIL");
    }
    const bool okay = numeric_seen == 0xffff && string_seen == 15 && pointer_seen == 3 && failures == 0;
    std::printf("DHRYSTONE_FUNCTIONAL side=%s status=%s numeric_seen=0x%x strings_seen=0x%x pointers_seen=0x%x memory_checks=7 failures=%u iterations=500\n",
                side, okay?"pass":"FAIL", numeric_seen, string_seen, pointer_seen, failures);
    return okay;
  }
};

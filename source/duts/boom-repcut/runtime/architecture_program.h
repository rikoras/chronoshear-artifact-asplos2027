#pragma once
#include <elf.h>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <vector>

namespace chisa::boom_repcut {
struct ArchitecturalProgram { std::uint64_t entry = 0, tohost = 0, initial_tohost = 0; };
inline ArchitecturalProgram read_architectural_program(const char* path) {
  std::ifstream input(path, std::ios::binary);
  if (!input) throw std::runtime_error("cannot open architecture target ELF");
  const std::vector<char> data{std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
  const auto bytes = [&](std::uint64_t offset, std::uint64_t size) {
    if (offset > data.size() || size > data.size() - offset)
      throw std::runtime_error("truncated architecture target ELF");
    return data.data() + offset;
  };
  Elf64_Ehdr header;
  std::memcpy(&header, bytes(0, sizeof(header)), sizeof(header));
  if (std::memcmp(header.e_ident, ELFMAG, SELFMAG) ||
      header.e_ident[EI_CLASS] != ELFCLASS64 || header.e_ident[EI_DATA] != ELFDATA2LSB ||
      header.e_machine != EM_RISCV || header.e_shentsize != sizeof(Elf64_Shdr))
    throw std::runtime_error("architecture checker requires a little-endian RV64 ELF with symbols");
  const auto section = [&](unsigned index) {
    if (index >= header.e_shnum) throw std::runtime_error("invalid ELF section link");
    Elf64_Shdr result;
    std::memcpy(&result, bytes(header.e_shoff + std::uint64_t(index) * sizeof(result), sizeof(result)), sizeof(result));
    return result;
  };
  ArchitecturalProgram result{header.e_entry, 0, 0};
  for (unsigned i = 0; i < header.e_shnum; ++i) {
    const auto symbols = section(i);
    if (symbols.sh_type != SHT_SYMTAB && symbols.sh_type != SHT_DYNSYM) continue;
    if (symbols.sh_entsize != sizeof(Elf64_Sym) || symbols.sh_size % sizeof(Elf64_Sym))
      throw std::runtime_error("invalid ELF symbol table");
    const auto strings = section(symbols.sh_link);
    const char* names = bytes(strings.sh_offset, strings.sh_size);
    const char* table = bytes(symbols.sh_offset, symbols.sh_size);
    for (std::uint64_t at = 0; at < symbols.sh_size; at += sizeof(Elf64_Sym)) {
      Elf64_Sym symbol;
      std::memcpy(&symbol, table + at, sizeof(symbol));
      if (symbol.st_name >= strings.sh_size ||
          !std::memchr(names + symbol.st_name, 0, strings.sh_size - symbol.st_name))
        throw std::runtime_error("invalid ELF symbol name");
      if (std::strcmp(names + symbol.st_name, "tohost") == 0 && symbol.st_shndx != SHN_UNDEF) {
        if (result.tohost && result.tohost != symbol.st_value)
          throw std::runtime_error("ambiguous ELF tohost symbol");
        result.tohost = symbol.st_value;
        const auto storage = section(symbol.st_shndx);
        if (symbol.st_value < storage.sh_addr || symbol.st_value - storage.sh_addr > storage.sh_size ||
            storage.sh_size - (symbol.st_value - storage.sh_addr) < 8)
          throw std::runtime_error("ELF does not define the full initial tohost word");
        if (storage.sh_type == SHT_NOBITS) result.initial_tohost = 0;
        else if (storage.sh_type == SHT_PROGBITS)
          std::memcpy(&result.initial_tohost,
                      bytes(storage.sh_offset + symbol.st_value - storage.sh_addr, 8), 8);
        else throw std::runtime_error("unsupported initial tohost storage");
      }
    }
  }
  if (!result.entry || !result.tohost) throw std::runtime_error("ELF entry/tohost boundary is unavailable");
  return result;
}


} // namespace chisa::boom_repcut

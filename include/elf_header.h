/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#ifndef XORG_ELF_HEADER_H_
#define XORG_ELF_HEADER_H_

#include <cstdint>
#include <string>

#include "common.h"
#include "elf_spec.h"

namespace xorg {

class ElfHeader : private Elf64_Ehdr {
 public:
  ElfHeader() = default;
  ~ElfHeader() = default;

  void Print() const;

  std::uint64_t GetPhOff() const { return e_phoff; }
  std::uint16_t GetPhSize() const { return e_phentsize; }
  std::uint16_t GetPhNum() const { return e_phnum; }

  std::uint64_t GetShOff() const { return e_shoff; }
  std::uint16_t GetShSize() const { return e_shentsize; }
  std::uint16_t GetShNum() const { return e_shnum; }

  std::uint16_t GetShStrndx() const { return e_shstrndx; }

 private:
  void PrintMagic() const;
  void PrintClass() const;
  void PrintData() const;
  void PrintVersion() const;
  void PrintOsABI() const;
  void PrintType() const;
  void PrintMachine() const;

  void PrintDec(const std::string& key,
                const std::uint64_t& value,
                const std::string& suffix = "") const;
  void PrintHex(const std::string& key, const std::uint64_t& value) const;
  void PrintCommon(const std::string& key, const std::string& value) const;

  DISALLOW_COPY_AND_ASSIGN(ElfHeader);
};

}  // namespace xorg

#endif  // XORG_ELF_HEADER_H_

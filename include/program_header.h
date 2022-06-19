/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#ifndef XORG_PROGRAM_HEADER_H_
#define XORG_PROGRAM_HEADER_H_

#include <cstdint>
#include <string>

#include "elf_spec.h"

namespace xorg {

class ProgramHeader : private Elf64_Phdr {
 public:
  ProgramHeader() = default;
  ~ProgramHeader() = default;

  static void PrintHeader();
  void Print() const;

 private:
  std::string GetHex(std::uint64_t value, bool isAddr = true) const;
  std::string GetFlags(std::uint32_t flag) const;
};

}  // namespace xorg

#endif  // XORG_PROGRAM_HEADER_H_

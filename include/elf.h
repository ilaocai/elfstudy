/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#ifndef XORG_ELF_H_
#define XORG_ELF_H_

#include <cstdint>
#include <fstream>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "common.h"
#include "elf_header.h"
#include "program_header.h"
#include "section_header.h"
#include "string_tab.h"
#include "symbol_tab.h"

namespace xorg {

class Elf {
 public:
  Elf(const std::string& filename);
  ~Elf();

  void Parse();
  void Print() const;

  const ElfHeader& Header() const { return m_header_; }

 private:
  void ParseStrTab(std::uint16_t idx);
  void ParseSymbolTab(std::uint16_t idx);
  void ParseSymbolTabName();

  ElfHeader m_header_;
  std::vector<ProgramHeader> m_program_headers_;
  std::vector<SectionHeader> m_section_headers_;

  std::map<std::uint16_t, StringTab> m_str_sections_;
  std::vector<SymbolTab> m_symbols_;

  std::ifstream m_ifs_;

  std::map<SHType, std::function<void(std::uint16_t)>> m_sht_parse_map_;

  std::uint16_t m_symbol_idx_;

  DISALLOW_COPY_AND_ASSIGN(Elf);
};

}  // namespace xorg

#endif  // XORG_ELF_H_

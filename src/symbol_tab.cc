/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#include "symbol_tab.h"

#include <spdlog/spdlog.h>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <map>
#include <sstream>
#include <string>

#include "common.h"
#include "elf_spec.h"

namespace xorg {

void SymbolTab::PrintHeader(std::uint32_t size) {
  spdlog::info("Symbol table '.symtab' contains {} entries:", size);
  std::stringstream ss;
  ss << std::right << std::setw(6) << std::setfill(' ') << "Num"
     << ":    "
     << "Value" << std::setw(14) << std::setfill(' ') << "Size"
     << " " << std::left << std::setw(8) << std::setfill(' ') << "Type"
     << std::setw(7) << "Bind" << std::setw(9) << "Vis"
     << "Ndx Name";

  spdlog::info("{}", ss.str());
}

void SymbolTab::Print() const {
  std::stringstream ss;

  ss << std::right << std::setw(6) << std::setfill(' ') << std::dec << m_num_
     << ": " << std::setw(16) << std::setfill('0') << std::hex << st_value
     << " " << std::setw(5) << std::setfill(' ') << std::dec << st_size << " "
     << std::left << std::setw(7) << GetType() << " " << std::setw(6)
     << GetBind() << " " << std::setw(8) << GetVisible() << " " << std::right
     << std::setw(3) << GetShndx() << " " << m_name_.substr(0, 25);
  spdlog::info("{}", ss.str());
}

void SymbolTab::Parse() {
  m_type_ = static_cast<STType>(st_info & 0xf);
  m_bind_ = static_cast<STBind>(st_info >> 4);
  m_visible_ = static_cast<STVisable>(st_other & 0x03);
}

const std::string& SymbolTab::GetType() const {
  static const std::map<STType, std::string> typeMap{
      {STType::STT_NOTYPE, "NOTYPE"}, {STType::STT_OBJECT, "OBJECT"},
      {STType::STT_FUNC, "FUNC"},     {STType::STT_SECTION, "SECTION"},
      {STType::STT_FILE, "FILE"},     {STType::STT_COMMON, "COMMON"},
      {STType::STT_TLS, "TLS"},
  };

  return GetMapValWithDef(typeMap, m_type_, std::string("UKN"));
}

const std::string& SymbolTab::GetBind() const {
  static const std::map<STBind, std::string> bindMap{
      {STBind::STB_LOCAL, "LOCAL"},
      {STBind::STB_GLOBAL, "GLOBAL"},
      {STBind::STB_WEAK, "WEAK"},
  };
  return GetMapValWithDef(bindMap, m_bind_, std::string("UKN"));
}

const std::string& SymbolTab::GetVisible() const {
  static const std::map<STVisable, std::string> visibleMap{
      {STVisable::STV_DEFAULT, "DEFAULT"},
      {STVisable::STV_INTERNAL, "INTERNAL"},
      {STVisable::STV_HIDDEN, "HIDDEN"},
      {STVisable::STV_PROTECTED, "PROTECT"},
  };
  return GetMapValWithDef(visibleMap, m_visible_, std::string("UKN"));
}

const std::string SymbolTab::GetShndx() const {
  std::stringstream ss;

  switch (static_cast<SHNdx>(st_shndx)) {
    case SHNdx::SHN_UNDEF:
      ss << "UND";
      break;
    case SHNdx::SHN_ABS:
      ss << "ABS";
      break;
    case SHNdx::SHN_COMMON:
      ss << "CMN";
      break;
    case SHNdx::SHN_XINDEX:
    default:
      ss << st_shndx;
      break;
  }

  return ss.str();
}

}  // namespace xorg

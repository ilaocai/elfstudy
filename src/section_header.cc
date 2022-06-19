/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#include "section_header.h"

#include <bits/stdint-uintn.h>
#include <spdlog/spdlog.h>
#include <iomanip>
#include <ios>
#include <map>
#include <sstream>
#include <string>
#include "common.h"
#include "elf_spec.h"

namespace xorg {

void SectionHeader::PrintHeader() {
  spdlog::info("Section Headers:");

  std::stringstream ss;
  ss << std::right << std::setw(6) << std::setfill(' ') << "[Nr]"
     << " " << std::left << std::setw(17) << std::setfill(' ') << "Name"
     << " " << std::setw(16) << std::setfill(' ') << "Type"
     << " " << std::setw(16) << std::setfill(' ') << "Address"
     << "  "
     << "Offset";
  spdlog::info("{}", ss.str());

  ss.str("");
  ss << std::left << std::setw(6) << std::setfill(' ') << " "
     << " " << std::setw(16) << std::setfill(' ') << "Size"
     << "  " << std::setw(16) << std::setfill(' ') << "EntSize"
     << " " << std::setw(5) << std::setfill(' ') << "Flags"
     << "  " << std::setw(4) << std::setfill(' ') << "Link"
     << "  " << std::setw(4) << std::setfill(' ') << "Info"
     << "  "
     << "Align";
  spdlog::info("{}", ss.str());
}

void SectionHeader::Print() const {
  std::stringstream ss;
  ss << "  [" << std::right << std::setw(2) << std::setfill(' ') << m_idx_
     << "]"
     << " " << std::left << std::setw(17) << std::setfill(' ') << m_name_ << " "
     << std::setw(16) << std::setfill(' ') << m_type_str_ << " " << std::right
     << std::setw(16) << std::setfill('0') << std::hex << sh_addr << "  "
     << std::setw(8) << std::setfill('0') << std::hex << sh_offset;
  spdlog::info("{}", ss.str());

  ss.str("");
  ss << std::setw(6) << std::setfill(' ') << " "
     << " " << std::right << std::setw(16) << std::setfill('0') << std::hex
     << sh_size << "  " << std::setw(16) << std::setfill('0') << std::hex
     << sh_entsize << " " << std::setw(3) << std::setfill(' ') << GetFlags()
     << "    " << std::setw(4) << std::setfill(' ') << std::dec << sh_link
     << "  " << std::setw(4) << std::setfill(' ') << sh_info << "     "
     << sh_addralign;
  spdlog::info("{}", ss.str());
}

void SectionHeader::ParseType() {
  static const std::map<SHType, std::string> typeMap{
      {SHType::SHT_NULL, "NULL"},
      {SHType::SHT_PROGBITS, "PROGBITS"},
      {SHType::SHT_SYMTAB, "SYMTAB"},
      {SHType::SHT_STRTAB, "STRTAB"},
      {SHType::SHT_RELA, "RELA"},
      {SHType::SHT_HASH, "HASH"},
      {SHType::SHT_DYNAMIC, "DYNAMIC"},
      {SHType::SHT_NOTE, "NOTE"},
      {SHType::SHT_NOBITS, "NOBITS"},
      {SHType::SHT_REL, "RELA"},
      {SHType::SHT_SHLIB, "SHLIB"},
      {SHType::SHT_DYNSYM, "DYNSYM"},
      {SHType::SHT_INIT_ARRAY, "INIT_ARRAY"},
      {SHType::SHT_FINI_ARRAY, "FINI_ARRAY"},
      {SHType::SHT_PREINIT_ARRAY, "PREINIT_ARRAY"},
      {SHType::SHT_GROUP, "GROUP"},
      {SHType::SHT_SYMTAB_SHNDX, "SYMTAB_SHNDX"},
      {SHType::SHT_GNU_ATTRIBUTES, "GNU_ATTRIBUTES"},
      {SHType::SHT_GNU_HASH, "GNU_HASH"},
      {SHType::SHT_GNU_LIBLIST, "GNU_LIBLIST"},
      {SHType::SHT_CHECKSUM, "CHECKSUM"},
      {SHType::SHT_GNU_VERDEF, "GNU_VERDEF"},
      {SHType::SHT_GNU_VERNEED, "GNU_VERNEED"},
      {SHType::SHT_GNU_VERSYM, "GNU_VERSYM"},
  };

  m_type_str_ = GetMapValWithDef(typeMap, static_cast<SHType>(sh_type),
                                 std::string("Unknown Type"));
}

const std::string SectionHeader::GetFlags() const {
  std::stringstream ss;
  if (sh_flags & static_cast<uint64_t>(SHFlags::SHF_WRITE))
    ss << "W";
  if (sh_flags & static_cast<uint64_t>(SHFlags::SHF_ALLOC))
    ss << "A";
  if (sh_flags & static_cast<uint64_t>(SHFlags::SHF_EXECINSTR))
    ss << "X";
  if (sh_flags & static_cast<uint64_t>(SHFlags::SHF_MERGE))
    ss << "M";
  if (sh_flags & static_cast<uint64_t>(SHFlags::SHF_STRINGS))
    ss << "S";
  if (sh_flags & static_cast<uint64_t>(SHFlags::SHF_INFO_LINK))
    ss << "I";
  if (sh_flags & static_cast<uint64_t>(SHFlags::SHF_LINK_ORDER))
    ss << "L";
  if (sh_flags & static_cast<uint64_t>(SHFlags::SHF_OS_NONCONFORMING))
    ss << "O";
  if (sh_flags & static_cast<uint64_t>(SHFlags::SHF_GROUP))
    ss << "G";
  if (sh_flags & static_cast<uint64_t>(SHFlags::SHF_TLS))
    ss << "T";
  if (sh_flags & static_cast<uint64_t>(SHFlags::SHF_COMPRESSED))
    ss << "C";
  if (sh_flags & static_cast<uint64_t>(SHFlags::SHF_EXCLUDE))
    ss << "E";

  return ss.str();
}
}  // namespace xorg

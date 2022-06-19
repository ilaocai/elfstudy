/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#include <spdlog/spdlog.h>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <map>
#include <sstream>
#include <string>

#include "common.h"
#include "elf.h"
#include "elf_header.h"
#include "elf_spec.h"
#include "program_header.h"

namespace xorg {

void ProgramHeader::PrintHeader() {
  spdlog::info("Program Headers:");

  std::stringstream ss;
  ss << "  " << std::left << std::setw(15) << std::setfill(' ') << "Type"
     << std::setw(19) << std::setfill(' ') << "Offset" << std::setw(19)
     << std::setfill(' ') << "VirtAddr" << std::setw(19) << std::setfill(' ')
     << "PhysAddr";
  spdlog::info("{}", ss.str());

  ss.str("");
  ss << "  " << std::left << std::setw(15) << std::setfill(' ') << " "
     << std::setw(19) << std::setfill(' ') << "FileSiz" << std::setw(20)
     << std::setfill(' ') << "MemSiz" << std::setw(7) << std::setfill(' ')
     << "Flags"
     << "Align";
  spdlog::info("{}", ss.str());
}

void ProgramHeader::Print() const {
  static const std::map<PHType, std::string> typeMap{
      {PHType::PT_NULL, "NULL"},
      {PHType::PT_LOAD, "LOAD"},
      {PHType::PT_DYNAMIC, "DYNAMIC"},
      {PHType::PT_INTERP, "INTERP"},
      {PHType::PT_NOTE, "NOTE"},
      {PHType::PT_SHLIB, "SHLIB"},
      {PHType::PT_PHDR, "PHDR"},
      {PHType::PT_TLS, "TLS"},
      {PHType::PT_GNU_EH_FRAME, "GNU_EH_FRAME"},
      {PHType::PT_GNU_STACK, "GNU_STACK"},
      {PHType::PT_GNU_RELRO, "GNU_RELRO"},
  };

  std::stringstream ss;
  ss << "  " << std::left << std::setw(15) << std::setfill(' ')
     << GetMapValWithDef(typeMap, static_cast<PHType>(p_type),
                         std::string("Unknown"))
     << std::setw(19) << std::setfill(' ') << GetHex(p_offset) << std::setw(19)
     << std::setfill(' ') << GetHex(p_vaddr) << std::setw(18)
     << std::setfill(' ') << GetHex(p_paddr);
  spdlog::info("{}", ss.str());

  ss.str("");
  ss << "  " << std::left << std::setw(15) << std::setfill(' ') << " "
     << std::setw(19) << std::setfill(' ') << GetHex(p_filesz) << std::setw(20)
     << std::setfill(' ') << GetHex(p_memsz) << std::setw(7)
     << std::setfill(' ') << GetFlags(p_flags) << GetHex(p_align, false);
  spdlog::info("{}", ss.str());
}

std::string ProgramHeader::GetFlags(std::uint32_t flag) const {
  std::stringstream ss;
#define CHECKFLAG(f) (flag & static_cast<std::uint32_t>(PHFlag::f))

  ss << (CHECKFLAG(PF_R) ? 'R' : ' ');
  ss << (CHECKFLAG(PF_W) ? 'W' : ' ');
  ss << (CHECKFLAG(PF_X) ? 'E' : ' ');

  return ss.str();
}

std::string ProgramHeader::GetHex(std::uint64_t value, bool isAddr) const {
  std::stringstream ss;

  ss << "0x";
  if (isAddr) {
    ss << std::right << std::setw(16) << std::setfill('0');
  }
  ss << std::hex << value;

  return ss.str();
}

}  // namespace xorg

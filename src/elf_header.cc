/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#include <spdlog/spdlog.h>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>

#include "common.h"
#include "elf_header.h"
#include "elf_spec.h"

namespace xorg {

void ElfHeader::Print() const {
  spdlog::info("ELF Header:");

  PrintMagic();
  PrintType();
  PrintMachine();

  // print file version
  PrintHex("Version", e_version);

  // print entry point address
  PrintHex("Entry point address", e_entry);

  PrintDec("Start of program headers", e_phoff, " (bytes into file)");
  PrintDec("Start of section headers", e_shoff, " (bytes into file)");
  // print flags
  PrintHex("Flags", e_flags);
  PrintDec("Size of this header", e_ehsize, " (bytes)");
  PrintDec("Size of program headers", e_phentsize, " (bytes)");
  PrintDec("Number of program headers", e_phnum);
  PrintDec("Size of section headers", e_shentsize, " (bytes)");
  PrintDec("Number of section headers", e_shnum);
  PrintDec("Section header string table index", e_shstrndx);
}

void ElfHeader::PrintMachine() const {
  static const std::map<EMachine, std::string> machineMap{
      {EMachine::EM_NONE, "No machine"},
      {EMachine::EM_ARM, "ARM"},
      {EMachine::EM_X86_64, "Advanced Micro Devices X86-64"},
      {EMachine::EM_AARCH64, "AARCH64"},
      {EMachine::EM_RISCV, "RISC-V"},
      {EMachine::EM_LOONGARCH, "LoongArch"},
  };

  PrintCommon("Machine",
              GetMapValWithDef(machineMap, static_cast<EMachine>(e_machine),
                               std::string("Unknown Machine")));
}

void ElfHeader::PrintType() const {
  static const std::map<EType, std::string> typeMap{
      {EType::ET_NONE, "No file type"},
      {EType::ET_REL, "REL (Relocatable file)"},
      {EType::ET_EXEC, "EXEC (Executable file)"},
      {EType::ET_DYN, "DYN (Shared object file)"},
      {EType::ET_CORE, "Core (Core file)"},
  };

  PrintCommon("Type", GetMapValWithDef(typeMap, static_cast<EType>(e_type),
                                       std::string("Unknown file type")));
}

void ElfHeader::PrintMagic() const {
  std::stringstream ss;

  // print magic
  ss << "  " << std::left << std::setw(9) << std::setfill(' ') << "Magic:";
  for (auto i = 0; i < EI_NIDENT; i++) {
    ss << std::right << std::setw(2) << std::setfill('0') << std::hex
       << (int)(e_ident[i]) << " ";
  }
  spdlog::info("{}", ss.str());

  PrintClass();
  PrintData();
  PrintVersion();
  PrintOsABI();

  PrintDec("ABI Version", e_ident[static_cast<int>(EIdent::EI_ABIVERSION)]);
}

void ElfHeader::PrintClass() const {
  static const std::map<EIClass, std::string> classMap{
      {EIClass::ELFCLASSNONE, "Invalid Class"},
      {EIClass::ELFCLASS32, "ELF32"},
      {EIClass::ELFCLASS64, "ELF64"},
  };

  auto classIdx = e_ident[static_cast<int>(EIdent::EI_CLASS)];
  PrintCommon("Class",
              GetMapValWithDef(classMap, static_cast<EIClass>(classIdx),
                               std::string("Unknown Class")));
}

void ElfHeader::PrintData() const {
  static const std::map<EIdata, std::string> dataMap{
      {EIdata::ELFDATANONE, "Invalid data encoding"},
      {EIdata::ELFDATA2LSB, "2's complement, little endian"},
      {EIdata::ELFDATA2MSB, "2's complement, big endian"},
  };

  auto dataIdx = e_ident[static_cast<int>(EIdent::EI_DATA)];
  PrintCommon("Data", GetMapValWithDef(dataMap, static_cast<EIdata>(dataIdx),
                                       std::string("Unknown data encoding")));
}

void ElfHeader::PrintVersion() const {
  static const std::map<EVersion, std::string> versionMap{
      {EVersion::EV_NONE, "Invalid ELF version"},
      {EVersion::EV_CURRENT, "1 (current)"},
  };

  auto versionIdx = e_ident[static_cast<int>(EIdent::EI_VERSION)];
  PrintCommon("Version",
              GetMapValWithDef(versionMap, static_cast<EVersion>(versionIdx),
                               std::string("Unknown ELF Version")));
}

void ElfHeader::PrintOsABI() const {
  static const std::map<EIOsabi, std::string> osabiMap{
      {EIOsabi::ELFOSABI_SYSV, "UNIX - System V"},
      {EIOsabi::ELFOSABI_ARM, "ARM"},
  };

  auto osabiIdx = e_ident[static_cast<int>(EIdent::EI_OSABI)];
  PrintCommon("OS/ABI",
              GetMapValWithDef(osabiMap, static_cast<EIOsabi>(osabiIdx),
                               std::string("Unknown OS ABI")));
}

void ElfHeader::PrintDec(const std::string& key,
                         const std::uint64_t& value,
                         const std::string& suffix) const {
  std::stringstream ss;

  ss << value << suffix;
  PrintCommon(key, ss.str());
}

void ElfHeader::PrintHex(const std::string& key,
                         const std::uint64_t& value) const {
  std::stringstream ss;

  ss << "0x" << std::hex << value;
  PrintCommon(key, ss.str());
}

void ElfHeader::PrintCommon(const std::string& key,
                            const std::string& value) const {
  std::stringstream ss;

  ss << "  " << std::left << std::setw(35) << std::setfill(' ') << (key + ":")
     << value;
  spdlog::info("{}", ss.str());
}

}  // namespace xorg

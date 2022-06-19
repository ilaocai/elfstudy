/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#ifndef XORG_SECTION_HEADER_H_
#define XORG_SECTION_HEADER_H_

#include <cstdint>
#include <string>
#include "elf_spec.h"

namespace xorg {

class SectionHeader : private Elf64_Shdr {
 public:
  SectionHeader() = default;
  ~SectionHeader() = default;

  static void PrintHeader();
  void Print() const;

  void SetIdx(std::uint16_t idx) { m_idx_ = idx; }
  void SetName(const std::string& name) { m_name_ = name; }
  void ParseType();

  const std::string& Name() const { return m_name_; }
  std::uint32_t NameValue() const { return sh_name; }

  std::uint64_t Size() const { return sh_size; }
  std::uint64_t EntSize() const { return sh_entsize; }
  std::uint64_t Offset() const { return sh_offset; }
  std::uint32_t Type() const { return sh_type; }
  std::uint32_t Link() const { return sh_link; }

 private:
  const std::string GetFlags() const;

  std::uint16_t m_idx_;
  std::string m_name_;
  std::string m_type_str_;
};

}  // namespace xorg

#endif  // XORG_SECTION_HEADER_H_

/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#ifndef XORG_SYMBOL_TAB_H_
#define XORG_SYMBOL_TAB_H_

#include <cstdint>
#include "common.h"
#include "elf_spec.h"

namespace xorg {

class SymbolTab : private Elf64_Sym {
 public:
  SymbolTab() = default;
  ~SymbolTab() = default;

  static void PrintHeader(std::uint32_t size);
  void Print() const;

  void SetNum(std::uint32_t num) { m_num_ = num; }
  void SetName(const std::string& name) { m_name_ = name; }
  void Parse();

  std::uint32_t Name() const { return st_name; }

 private:
  const std::string& GetType() const;
  const std::string& GetBind() const;
  const std::string& GetVisible() const;
  const std::string GetShndx() const;

  std::uint32_t m_num_;
  std::string m_name_;
  STType m_type_;
  STBind m_bind_;
  STVisable m_visible_;
};

}  // namespace xorg

#endif  // XORG_SYMBOL_TAB_H_

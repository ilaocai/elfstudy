/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#include "elf.h"
#include <spdlog/spdlog.h>
#include <algorithm>
#include <ios>
#include <string>

#include "elf_spec.h"
#include "section_header.h"
#include "string_tab.h"
#include "symbol_tab.h"

namespace xorg {

Elf::Elf(const std::string& filename)
    : m_ifs_(filename, std::ios::in | std::ios::binary) {
  m_sht_parse_map_ = {
      {SHType::SHT_STRTAB, [&](std::uint16_t idx) { ParseStrTab(idx); }},
      {SHType::SHT_SYMTAB, [&](std::uint16_t idx) { ParseSymbolTab(idx); }},
  };
}

Elf::~Elf() {
  m_ifs_.close();
}

void Elf::Parse() {
  m_ifs_.seekg(0, m_ifs_.beg);
  m_ifs_.read((char*)((Elf64_Ehdr*)&m_header_), sizeof(Elf64_Ehdr));

  // parse program headers
  if (m_header_.GetPhNum() > 0) {
    m_program_headers_.resize(m_header_.GetPhNum());
    m_ifs_.seekg(m_header_.GetPhOff(), m_ifs_.beg);
    for (auto i = 0; i < m_program_headers_.size(); i++) {
      m_ifs_.read((char*)((Elf64_Phdr*)&m_program_headers_[i]),
                  sizeof(Elf64_Phdr));
    }
  }

  // parse section headers
  m_section_headers_.resize(m_header_.GetShNum());
  m_ifs_.seekg(m_header_.GetShOff(), m_ifs_.beg);
  for (auto i = 0; i < m_section_headers_.size(); i++) {
    m_ifs_.read((char*)((Elf64_Shdr*)&m_section_headers_[i]),
                sizeof(Elf64_Shdr));
    m_section_headers_[i].SetIdx(i);
    m_section_headers_[i].ParseType();

    auto length = m_ifs_.tellg();

    const auto& it = m_sht_parse_map_.find(
        static_cast<SHType>(m_section_headers_[i].Type()));
    if (it != m_sht_parse_map_.end()) {
      it->second(i);
    }
    m_ifs_.seekg(length, m_ifs_.beg);
  }

  // parse section header name
  const auto& st = m_str_sections_[m_header_.GetShStrndx()];
  for (auto& sh : m_section_headers_) {
    sh.SetName(&st[sh.NameValue()]);
  }

  // parse symbol table name
  ParseSymbolTabName();
}

void Elf::ParseStrTab(std::uint16_t idx) {
  StringTab st;
  st.resize(m_section_headers_[idx].Size());
  m_ifs_.seekg(m_section_headers_[idx].Offset());
  m_ifs_.read(&st[0], st.size());
  st.SetIdx(idx);

  m_str_sections_[idx] = std::move(st);
}

void Elf::ParseSymbolTab(std::uint16_t idx) {
  auto& sh = m_section_headers_[idx];
  m_symbols_.resize(sh.Size() / sh.EntSize());
  m_ifs_.seekg(sh.Offset());
  for (auto i = 0; i < m_symbols_.size(); i++) {
    m_ifs_.read((char*)((Elf64_Sym*)&m_symbols_[i]), sh.EntSize());
    m_symbols_[i].SetNum(i);
    m_symbols_[i].Parse();
  }
  m_symbol_idx_ = idx;
}

void Elf::ParseSymbolTabName() {
  const auto& sts = m_str_sections_[m_section_headers_[m_symbol_idx_].Link()];
  for (auto& symbol : m_symbols_) {
    symbol.SetName(&sts[symbol.Name()]);
  }
}

void Elf::Print() const {
  // m_header_.Print();

  // ProgramHeader::PrintHeader();
  // for (const auto& ph : m_program_headers_) {
  //   ph.Print();
  // }

  // SectionHeader::PrintHeader();
  // for (const auto& sh : m_section_headers_) {
  //   sh.Print();
  // }

  // print string table
  // for (const auto& st : m_str_sections_) {
  //   st.second.Print();
  // }

  SymbolTab::PrintHeader(m_symbols_.size());
  for (const auto& st : m_symbols_) {
    st.Print();
  }
}

}  // namespace xorg

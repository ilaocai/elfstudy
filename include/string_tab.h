/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#ifndef XORG_STRING_TAB_H_
#define XORG_STRING_TAB_H_

#include <cstdint>
#include <vector>

#include "common.h"

namespace xorg {

class StringTab : public std::vector<char> {
 public:
  StringTab() = default;
  ~StringTab() = default;

  void Print() const;

  void SetIdx(std::uint16_t idx) { m_idx_ = idx; }
  const std::uint16_t GetIdx() const { return m_idx_; }

 private:
  std::uint16_t m_idx_;
};

}  // namespace xorg

#endif  // XORG_STRING_TAB_H_

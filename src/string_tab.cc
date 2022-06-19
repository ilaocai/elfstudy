/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#include "string_tab.h"

#include <spdlog/spdlog.h>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <sstream>
#include <string>

namespace xorg {

void StringTab::Print() const {
  spdlog::info("String dump of section :");

  std::stringstream ss;
  auto idx = 0;
  while (idx < size()) {
    std::string str((char*)&((*this)[idx]));
    ss.str("");
    ss << "  [" << std::right << std::setw(6) << std::setfill(' ') << std::hex
       << idx << "]  " << str;
    spdlog::info("{}", ss.str());
    idx += (str.length() + 1);
  }
}

}  // namespace xorg

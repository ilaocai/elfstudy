/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#include <spdlog/spdlog.h>
#include <fstream>
#include <ios>
#include <memory>

#include "elf.h"

int main(int argc, char* argv[]) {
  // spdlog::set_level(spdlog::level::debug);
  spdlog::set_pattern("%v");

  spdlog::debug("argc: {}", argc);
  for (auto i = 0; i < argc; i++) {
    spdlog::debug("argv[{}]: {}", i, argv[i]);
  }

  // use current file
  auto elf = std::make_unique<xorg::Elf>(argv[0]);
  elf->Parse();
  elf->Print();

  return 0;
}

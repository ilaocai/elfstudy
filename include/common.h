/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#ifndef XORG_COMMON_H_
#define XORG_COMMON_H_

#include <map>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(TypeName&) = delete;            \
  void operator=(TypeName) = delete;

template <class K, class V>
const V& GetMapValWithDef(const std::map<K, V>& map,
                          const K& key,
                          const V& defval) {
  const auto& it = map.find(key);
  if (it == map.end())
    return defval;

  return it->second;
}

#endif  // XORG_COMMON_H_

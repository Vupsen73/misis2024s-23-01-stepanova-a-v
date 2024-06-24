#pragma once
#ifndef PRJ_TEST_UTILS_HPP_20240418
#define PRJ_TEST_UTILS_HPP_20240418

#include <vector>
#include <string>

template<class T>
void FillData(const int n, std::vector<T>& data) {
  data.clear();
  data.reserve(n);
  for (int i = 0; i < n; i += 1) {
    data.emplace_back(i);
  }
}

template<>
void FillData(const int n, std::vector<std::string>& data) {
  data.clear();
  data.reserve(n);
  for (int i = 0; i < n; i += 1) {
    data.emplace_back(std::to_string(i));
  }
}

template<class T>
void FillEl(const int n, T &el) {
  el = n;
}

template<>
void FillEl(const int n, std::string &el) {
  el = std::to_string(n);
}

#endif
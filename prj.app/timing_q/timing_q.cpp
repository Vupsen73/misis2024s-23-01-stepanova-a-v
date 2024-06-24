#include <chrono>
#include <iostream>
#include <queuelst/queuelst.hpp>
#include <queuearr/queuearr.hpp>

int main() {
  //default ctor test
  const auto start_default_lst{ std::chrono::steady_clock::now() };
  QueueLst test;
  const auto end_default_lst{ std::chrono::steady_clock::now() };
  std::cout << "Default ctor lst: " << (end_default_lst - start_default_lst) << std::endl;

  const auto start_default_arr{ std::chrono::steady_clock::now() };
  QueueArr test1;
  const auto end_default_arr{ std::chrono::steady_clock::now() };
  std::cout << "Default ctor arr: " << (end_default_arr - start_default_arr) << std::endl;
}
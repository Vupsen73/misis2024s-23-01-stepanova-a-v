#pragma once
#ifndef STACKARR_STACKARR_HPP
#define STACKARR_STACKARR_HPP

#include <complex/complex.hpp>

#include <cstddef>

class StackArr {
public:
  StackArr();
  StackArr(const StackArr&);
  StackArr(StackArr&&) noexcept;
  ~StackArr();

  StackArr& operator=(const StackArr& rhs) noexcept;
  StackArr& operator=(StackArr&& rhs) noexcept;

  void Push(const Complex&);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  const Complex& Top() const;
  Complex& Top();
  void Clear() noexcept;

  std::ptrdiff_t Size() const noexcept { return head_ + 1; };

  bool operator==(const StackArr& rhs) const noexcept;
  bool operator!=(const StackArr& rhs) const noexcept { return !operator==(rhs); }

private:
  std::ptrdiff_t capacity_ = 1;
  std::ptrdiff_t head_ = -1;
  Complex* data_ = nullptr;

  void ChangeCapacity(const std::ptrdiff_t new_capacity) noexcept;
};


#endif // !STACKARR_STACKARR_HPP
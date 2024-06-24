#pragma once
#ifndef STACKLST_STACKLST_HPP
#define STACKLST_STACKLST_HPP

#include <complex/complex.hpp>

#include <cstddef>

class StackLst {
public:
  StackLst() = default;
  StackLst(const StackLst&);
  StackLst(StackLst&&) noexcept;
  ~StackLst();

  StackLst& operator=(const StackLst& rhs) noexcept;
  StackLst& operator=(StackLst&& rhs) noexcept;

  void Push(const Complex& new_val);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  const Complex& Top() const;
  Complex& Top();
  void Clear() noexcept;

  std::ptrdiff_t Size() const noexcept { return size_; };

  bool operator==(const StackLst& rhs) const noexcept;
  bool operator!=(const StackLst& rhs) const noexcept { return !operator==(rhs); }

private:
  struct Node {
    Complex value = Complex();
    Node* next = nullptr;
  };

  std::ptrdiff_t size_ = 0; //!< число элементов в стеке
  Node* head_ = nullptr; //!< указатель на голову стека

};


#endif // !STACKLST_STACKLST_HPP
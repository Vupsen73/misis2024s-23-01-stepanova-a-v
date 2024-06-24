#pragma once
#ifndef QUEUELST_QUEUELST_HPP
#define QUEUELST_QUEUELST_HPP

#include <complex/complex.hpp>

#include <cstddef>

class QueueLst {
public:
  QueueLst() = default;
  QueueLst(const QueueLst&);
  QueueLst(QueueLst&&) noexcept;
  ~QueueLst();

  QueueLst& operator=(const QueueLst& rhs) noexcept;
  QueueLst& operator=(QueueLst&& rhs) noexcept;

  void Push(const Complex& new_val);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  const Complex& Top() const;
  Complex& Top();
  void Clear() noexcept;

  std::ptrdiff_t Size() const noexcept { return size_; };

  bool operator==(const QueueLst& rhs) const noexcept;
  bool operator!=(const QueueLst& rhs) const noexcept { return !operator==(rhs); }

private:
  struct Node {
    Complex value = Complex();
    Node* next = nullptr;
  };

  std::ptrdiff_t size_ = 0; //!< the number of items in the queue
  Node* head_ = nullptr; //!< pointer to the head of the queue
  Node* tail_ = nullptr; //!< pointer to the tail of the queue
};


#endif // !QUEUELST_QUEUELST_HPP
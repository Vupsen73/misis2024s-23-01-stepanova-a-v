#pragma once
#ifndef STACKLSTT_STACKLSTT_HPP
#define STACKLSTT_STACKLSTT_HPP

#include <cstddef>
#include <algorithm>
#include <stdexcept>


template<class T>
class StackLstT {
public:
  StackLstT() = default;
  StackLstT(const StackLstT<T>&);
  StackLstT(StackLstT<T>&&) noexcept;
  ~StackLstT();

  StackLstT<T>& operator=(const StackLstT<T>& rhs) noexcept;
  StackLstT<T>& operator=(StackLstT<T>&& rhs) noexcept;

  void Push(const T& new_val);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  const T& Top() const;
  T& Top();
  void Clear() noexcept;

  std::ptrdiff_t Size() const noexcept { return size_; };

  bool operator==(const StackLstT<T>& rhs) const noexcept;
  bool operator!=(const StackLstT<T>& rhs) const noexcept { return !operator==(rhs); }

private:
  struct Node {
    T value = T();
    Node* next = nullptr;
  };

  std::ptrdiff_t size_ = 0; //!< число элементов в стеке
  Node* head_ = nullptr; //!< указатель на голову стека

};


template<class T>
StackLstT<T>::StackLstT(const StackLstT<T>& stack)
{
  *this = stack;
}

template<class T>
StackLstT<T>::StackLstT(StackLstT<T>&& rhs) noexcept
{
  if (!rhs.IsEmpty()) {
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
  }
}

template<class T>
StackLstT<T>::~StackLstT()
{
  Clear();
}

template<class T>
StackLstT<T>& StackLstT<T>::operator=(const StackLstT<T>& rhs) noexcept
{
  if (this != &rhs) {
    StackLstT<T> time;
    Node* head = rhs.head_;
    for (int i = 0; i < rhs.size_; i++) {
      time.Push(head->value);
      head = head->next;
    }
    head = time.head_;
    Clear();
    for (int i = 0; i < rhs.size_; i++) {
      Push(head->value);
      head = head->next;
    }

    return *this;
  }
}

template<class T>
StackLstT<T>& StackLstT<T>::operator=(StackLstT<T>&& rhs) noexcept
{
  if (this != &rhs) {
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
  }

  return *this;
}

template<class T>
void StackLstT<T>::Push(const T& new_val)
{
  StackLstT<T>::Node* new_node = new StackLstT<T>::Node;
  new_node->value = new_val;
  new_node->next = head_;
  head_ = new_node;
  size_++;
}

template<class T>
void StackLstT<T>::Pop() noexcept
{
  if (!IsEmpty()) {
    auto del_node = head_;
    head_ = head_->next;
    delete del_node;
    del_node = nullptr;
    size_--;
  }
}

template<class T>
bool StackLstT<T>::IsEmpty() const noexcept
{
  return size_ == 0;
}

template<class T>
const T& StackLstT<T>::Top() const
{
  if (!IsEmpty()) {
    return head_->value;
  }
  else {
    throw std::logic_error("StackLstT - try get top form empty stack.");
  }
}

template<class T>
T& StackLstT<T>::Top()
{
  if (!IsEmpty()) {
    return head_->value;
  }
  else {
    throw std::logic_error("StackLstT - try get top form empty stack.");
  }
}

template<class T>
void StackLstT<T>::Clear() noexcept
{
  while (!IsEmpty()) {
    Pop();
  }
}

template<class T>
bool StackLstT<T>::operator==(const StackLstT<T>& rhs) const noexcept
{
  if (size_ != rhs.size_) {
    return false;
  }

  for (auto cur_node_lhs = head_, cur_node_rhs = rhs.head_; cur_node_lhs != nullptr; cur_node_lhs = cur_node_lhs->next, cur_node_rhs = cur_node_rhs->next) {
    if (cur_node_lhs->value != cur_node_rhs->value) {
      return false;
    }
  }

  return true;
}


#endif // !STACKLSTT_STACKLSTT_HPP
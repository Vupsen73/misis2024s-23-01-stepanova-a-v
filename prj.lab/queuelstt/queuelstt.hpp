#pragma once
#ifndef QUEUELSTT_QUEUELSTT_HPP
#define QUEUELSTT_QUEUELSTT_HPP

#include <cstddef>
#include <stdexcept>


template<class T>
class QueueLstT {
public:
  QueueLstT() = default;
  QueueLstT(const QueueLstT<T>&);
  QueueLstT(QueueLstT<T>&&) noexcept;
  ~QueueLstT();

  QueueLstT<T>& operator=(const QueueLstT<T>& rhs) noexcept;
  QueueLstT<T>& operator=(QueueLstT<T>&& rhs) noexcept;

  void Push(const T& new_val);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  const T& Top() const;
  T& Top();
  void Clear() noexcept;

  std::ptrdiff_t Size() const noexcept { return size_; };

  bool operator==(const QueueLstT<T>& rhs) const noexcept;
  bool operator!=(const QueueLstT<T>& rhs) const noexcept { return !operator==(rhs); }

private:
  struct Node {
    T value = T();
    Node* next = nullptr;
  };

  std::ptrdiff_t size_ = 0; //!< the number of items in the queue
  Node* head_ = nullptr; //!< pointer to the head of the queue
  Node* tail_ = nullptr; //!< pointer to the tail of the queue
};

template<class T>
QueueLstT<T>::QueueLstT(const QueueLstT<T>& queue)
{
  *this = queue;
}

template<class T>
QueueLstT<T>::QueueLstT(QueueLstT<T>&& rhs) noexcept
{
  if (!rhs.IsEmpty()) {
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
    std::swap(tail_, rhs.tail_);
  }
}

template<class T>
QueueLstT<T>::~QueueLstT()
{
  Clear();
}

template<class T>
QueueLstT<T>& QueueLstT<T>::operator=(const QueueLstT<T>& rhs) noexcept
{
  if (this != &rhs) {
    Clear();
    Node* head = rhs.head_;
    for (int i = 0; i < rhs.size_; i++) {
      Push(head->value);
      head = head->next;
    }
  }

  return *this;
}

template<class T>
QueueLstT<T>& QueueLstT<T>::operator=(QueueLstT<T>&& rhs) noexcept
{
  if (this != &rhs) {
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
    std::swap(tail_, rhs.tail_);
  }

  return *this;
}

template<class T>
void QueueLstT<T>::Push(const T& new_val)
{
  QueueLstT<T>::Node* new_node = new QueueLstT<T>::Node{ new_val };

  if (IsEmpty()) {
    tail_ = new_node;
    head_ = tail_;
  }
  else {
    tail_->next = new_node;
    tail_ = new_node;
  }

  size_++;
}

template<class T>
void QueueLstT<T>::Pop() noexcept
{
  if (!IsEmpty()) {
    auto del_node = head_;
    head_ = head_->next;
    delete del_node;
    del_node = nullptr;
    size_--;
  }
  else {
    tail_ = nullptr;
  }
}

template<class T>
bool QueueLstT<T>::IsEmpty() const noexcept
{
  return size_ == 0;
}

template<class T>
const T& QueueLstT<T>::Top() const
{
  if (!IsEmpty()) {
    return head_->value;
  }
  else {
    throw std::logic_error("QueueLstT - try get top form empty queue.");
  }
}

template<class T>
T& QueueLstT<T>::Top()
{
  if (!IsEmpty()) {
    return head_->value;
  }
  else {
    throw std::logic_error("QueueLstT - try get top form empty queue.");
  }
}

template<class T>
void QueueLstT<T>::Clear() noexcept
{
  while (!IsEmpty()) {
    Pop();
  }
}

template<class T>
bool QueueLstT<T>::operator==(const QueueLstT<T>& rhs) const noexcept
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


#endif // !QUEUELSTT_QUEUELSTT_HPP
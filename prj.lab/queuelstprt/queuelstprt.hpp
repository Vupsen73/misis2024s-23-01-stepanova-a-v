#pragma once
#ifndef QUEUELSTPRT_QUEUELSTPRT_HPP
#define QUEUELSTPRT_QUEUELSTPRT_HPP

#include <cstddef>
#include <stdexcept>


template<class T>
class QueueLstPrT {
public:
  QueueLstPrT() = default;
  QueueLstPrT(const QueueLstPrT<T>&);
  QueueLstPrT(QueueLstPrT<T>&&) noexcept;
  ~QueueLstPrT();

  QueueLstPrT<T>& operator=(const QueueLstPrT<T>& rhs);
  QueueLstPrT<T>& operator=(QueueLstPrT<T>&& rhs) noexcept;

  void Push(const T& new_val);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  const T& Top() const;
  void Clear() noexcept;

  std::ptrdiff_t Size() const noexcept { return size_; };

  bool operator==(const QueueLstPrT<T>& rhs) const noexcept;
  bool operator!=(const QueueLstPrT<T>& rhs) const noexcept { return !operator==(rhs); }

private:
  struct Node {
    T value = T();
    Node* next = nullptr;
  };

  std::ptrdiff_t size_ = 0; //!< the number of items in the queue
  Node* head_ = nullptr; //!< pointer to the head of the queue

  void Copy(const QueueLstPrT<T>& rhs);
};


template<class T>
QueueLstPrT<T>::QueueLstPrT(const QueueLstPrT<T>& rhs)
{
  if (!rhs.IsEmpty()) {
    Copy(rhs);
  }
}

template<class T>
QueueLstPrT<T>::QueueLstPrT(QueueLstPrT<T>&& rhs) noexcept
{
  if (!rhs.IsEmpty()) {
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
  }
}

template<class T>
QueueLstPrT<T>::~QueueLstPrT()
{
  Clear();
}

template<class T>
QueueLstPrT<T>& QueueLstPrT<T>::operator=(const QueueLstPrT<T>& rhs)
{
  if (this != &rhs) {
    Clear();
    if (!rhs.IsEmpty()) {
      Copy(rhs);
    }
  }

  return *this;
}

template<class T>
QueueLstPrT<T>& QueueLstPrT<T>::operator=(QueueLstPrT<T>&& rhs) noexcept
{
  if (this != &rhs) {
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
  }

  return *this;
}

template<class T>
void QueueLstPrT<T>::Push(const T& new_val)
{
  QueueLstPrT<T>::Node* new_node = new QueueLstPrT<T>::Node{ new_val };

  if (IsEmpty()) {
    head_ = new_node;
  }
  else {
    if (head_->value > new_node->value) {
      new_node->next = head_;
      head_ = new_node;
    }
    else {
      auto cur = head_;
      while (cur->next != nullptr && (cur->next)->value <= new_node->value) {
        cur = cur->next;
      }
      if (cur->next == nullptr) {
        cur->next = new_node;
      }
      else {
        auto temp = cur->next;
        cur->next = new_node;
        new_node->next = temp;
      }
    }
  }

  size_++;
}

template<class T>
void QueueLstPrT<T>::Pop() noexcept
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
bool QueueLstPrT<T>::IsEmpty() const noexcept
{
  return size_ == 0;
}

template<class T>
const T& QueueLstPrT<T>::Top() const
{
  if (!IsEmpty()) {
    return head_->value;
  }
  else {
    throw std::logic_error("QueueLstPrT - try get top form empty queue.");
  }
}

template<class T>
void QueueLstPrT<T>::Clear() noexcept
{
  while (!IsEmpty()) {
    Pop();
  }
}

template<class T>
bool QueueLstPrT<T>::operator==(const QueueLstPrT<T>& rhs) const noexcept
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

template<class T>
void QueueLstPrT<T>::Copy(const QueueLstPrT<T>& rhs)
{
  Node* head = rhs.head_;
  for (int i = 0; i < rhs.size_; i++) {
    Push(head->value);
    head = head->next;
  }
}

#endif // !QUEUELSTPRT_QUEUELSTPRT_HPP
#pragma once
#ifndef QUEUEARRT_QUEUEARRT_HPP
#define QUEUEARRT_QUEUEARRT_HPP

#include <algorithm>
#include <cstddef>
#include <stdexcept>


template<class T>
class QueueArrT {
public:
  QueueArrT() = default;
  QueueArrT(const QueueArrT<T>&);
  QueueArrT(QueueArrT<T>&&) noexcept;
  ~QueueArrT();

  QueueArrT<T>& operator=(const QueueArrT<T>& queue);
  QueueArrT<T>& operator=(QueueArrT<T>&&) noexcept;

  void Push(const T& val);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  const T& Top() const;
  T& Top();
  void Clear() noexcept;

  std::ptrdiff_t Size() const noexcept { return size_; };

  bool operator==(const QueueArrT<T>& rhs) const noexcept;
  bool operator!=(const QueueArrT<T>& rhs) const noexcept { return !operator==(rhs); }

private:
  std::ptrdiff_t size_ = 0;       //!< the number of items in the queue
  std::ptrdiff_t capacity_ = 0;   //!< queue capacity
  std::ptrdiff_t head_ = -1;      //!< index head of the queue
  std::ptrdiff_t tail_ = -1;      //!< index tail of the queue
  T* data_ = nullptr;       //!< pointer to the data

  void ChangeCapacity(std::ptrdiff_t new_capacity);

  void Copy(const QueueArrT<T>& queue);
};


template<class T>
QueueArrT<T>::QueueArrT(const QueueArrT<T>& queue)
{
  if (!queue.IsEmpty()) {
    Copy(queue);
  }
}

template<class T>
QueueArrT<T>::QueueArrT(QueueArrT<T>&& queue) noexcept
{
  if (!queue.IsEmpty()) {
    std::swap(size_, queue.size_);
    std::swap(capacity_, queue.capacity_);
    std::swap(head_, queue.head_);
    std::swap(tail_, queue.tail_);
    std::swap(data_, queue.data_);
  }
}

template<class T>
QueueArrT<T>::~QueueArrT()
{
  if (data_ != nullptr) {
    delete[] data_;
    data_ = nullptr;
  }
}

template<class T>
QueueArrT<T>& QueueArrT<T>::operator=(const QueueArrT<T>& queue)
{
  if (this != &queue) {
    Clear();
    if (!queue.IsEmpty()) {
      Copy(queue);
    }
  }

  return *this;
}

template<class T>
QueueArrT<T>& QueueArrT<T>::operator=(QueueArrT<T>&& queue) noexcept
{
  if (this != &queue) {
    std::swap(size_, queue.size_);
    std::swap(capacity_, queue.capacity_);
    std::swap(head_, queue.head_);
    std::swap(tail_, queue.tail_);
    std::swap(data_, queue.data_);
  }

  return *this;
}

template<class T>
void QueueArrT<T>::Push(const T& val)
{
  if (data_ == nullptr) {
    capacity_ = 1;
    data_ = new T[capacity_]();
  }
  if (IsEmpty()) {
    head_ = 0;
    tail_ = 0;
  }
  else {
    if (head_ == (tail_ + 1) % capacity_) {
      ChangeCapacity(capacity_ * 2);
    }

    tail_ = (tail_ + 1) % capacity_;
  }

  data_[tail_] = val;
  size_++;
}

template<class T>
void QueueArrT<T>::Pop() noexcept
{
  if (!IsEmpty()) {
    if (head_ != tail_) {
      head_ = (head_ + 1) % capacity_;
    }
    else {
      head_ = -1;
      tail_ = -1;
    }

    size_--;
  }
}

template<class T>
bool QueueArrT<T>::IsEmpty() const noexcept
{
  return size_ == 0;
}

template<class T>
const T& QueueArrT<T>::Top() const
{
  if (IsEmpty()) {
    throw std::logic_error("QueueArrT - try get top form empty queue.");
  }
  return data_[head_];
}

template<class T>
T& QueueArrT<T>::Top()
{
  if (IsEmpty()) {
    throw std::logic_error("QueueArrT - try get top form empty queue.");
  }
  return data_[head_];
}

template<class T>
void QueueArrT<T>::Clear() noexcept
{
  head_ = -1;
  tail_ = -1;
  size_ = 0;
}

template<class T>
bool QueueArrT<T>::operator==(const QueueArrT<T>& rhs) const noexcept
{
  if (size_ != rhs.size_) {
    return false;
  }
  else if (IsEmpty() || rhs.IsEmpty()) {
    return IsEmpty() && rhs.IsEmpty();
  }
  else {
    auto i = head_, j = rhs.head_;
    for (; i != tail_; i = (i + 1) % capacity_, j = (j + 1) % rhs.capacity_) {
      if (data_[i] != rhs.data_[j]) {
        return false;
      }
    }
    if (data_[i] != rhs.data_[j]) {
      return false;
    }

    return true;
  }
}

template<class T>
void QueueArrT<T>::ChangeCapacity(std::ptrdiff_t new_capacity)
{
  T* new_data = new T[new_capacity]();

  if (head_ <= tail_) {
    std::copy(data_ + head_, data_ + tail_ + 1, new_data);
  }
  else {
    std::copy(data_ + head_, data_ + capacity_, new_data);
    std::copy(data_, data_ + tail_ + 1, data_ + (capacity_ - head_ + 1));
  }

  std::swap(data_, new_data);
  head_ = 0;
  tail_ = size_ - 1;
  capacity_ = new_capacity;
}

template<class T>
void QueueArrT<T>::Copy(const QueueArrT<T>& queue)
{
  capacity_ = queue.capacity_;
  head_ = 0;
  tail_ = queue.size_ - 1;
  data_ = new T[capacity_]();
  size_ = queue.size_;

  if (queue.head_ <= queue.tail_) {
    std::copy(queue.data_ + queue.head_, queue.data_ + queue.tail_ + 1, data_);
  }
  else {
    std::copy(queue.data_ + queue.head_, queue.data_ + queue.capacity_, data_);
    std::copy(queue.data_, queue.data_ + queue.tail_ + 1, data_ + (queue.capacity_ - queue.head_ + 1));
  }
}


#endif // !QUEUEARRT_QUEUEARRT_HPP
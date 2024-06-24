#pragma once
#ifndef STACKARRT_STACKARRT_HPP
#define STACKARRT_STACKARRT_HPP

#include <cstddef>
#include <algorithm>
#include <stdexcept>


template<class T>
class StackArrT {
public:
  StackArrT();
  StackArrT(const StackArrT<T>&);
  StackArrT(StackArrT<T>&&) noexcept;
  ~StackArrT();

  StackArrT<T>& operator=(const StackArrT<T>& rhs) noexcept;
  StackArrT<T>& operator=(StackArrT<T>&& rhs) noexcept;

  void Push(const T&);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  const T& Top() const;
  T& Top();
  void Clear() noexcept;

  std::ptrdiff_t Size() const noexcept { return head_ + 1; };

  bool operator==(const StackArrT<T>& rhs) const noexcept;
  bool operator!=(const StackArrT<T>& rhs) const noexcept { return !operator==(rhs); }

private:
  std::ptrdiff_t capacity_ = 1;
  std::ptrdiff_t head_ = -1;
  T* data_ = nullptr;

  void ChangeCapacity(const std::ptrdiff_t new_capacity) noexcept;
};

template<class T>
StackArrT<T>::StackArrT()
  : data_(new T[capacity_]())
{
}

template<class T>
StackArrT<T>::StackArrT(const StackArrT<T>& stack)
  : capacity_(stack.capacity_), head_(stack.head_), data_(new T[stack.capacity_]())
{
  std::copy(stack.data_, stack.data_ + stack.capacity_, data_);
}

template<class T>
StackArrT<T>::StackArrT(StackArrT<T>&& rhs) noexcept
{
  if (!rhs.IsEmpty()) {
    std::swap(data_, rhs.data_);
    std::swap(head_, rhs.head_);
    std::swap(capacity_, rhs.capacity_);
  }
}

template<class T>
StackArrT<T>::~StackArrT()
{
  if (data_ != nullptr) {
    delete[] data_;
    data_ = nullptr;
  }
}

template<class T>
StackArrT<T>& StackArrT<T>::operator=(StackArrT<T>&& rhs) noexcept
{
  if (this != &rhs) {
    std::swap(data_, rhs.data_);
    std::swap(head_, rhs.head_);
    std::swap(capacity_, rhs.capacity_);
  }

  return *this;
}

template<class T>
void StackArrT<T>::Push(const T& new_el)
{
  if (Size() == capacity_) {
    ChangeCapacity(capacity_ * 2);
  }
  head_++;
  data_[head_] = new_el;
}

template<class T>
void StackArrT<T>::Pop() noexcept
{
  if (!IsEmpty()) {
    data_[head_] = T();
    head_--;
  }
}

template<class T>
bool StackArrT<T>::IsEmpty() const noexcept
{
  return head_ == -1;
}

template<class T>
const T& StackArrT<T>::Top() const
{
  if (!IsEmpty()) {
    return data_[head_];
  }
  else {
    throw std::logic_error("StackArrT - try get top form empty stack.");
  }
}

template<class T>
T& StackArrT<T>::Top()
{
  if (!IsEmpty()) {
    return data_[head_];
  }
  else {
    throw std::logic_error("StackArrT - try get top form empty stack.");
  }
}

template<class T>
void StackArrT<T>::Clear() noexcept
{
  head_ = -1;
}

template<class T>
void StackArrT<T>::ChangeCapacity(const std::ptrdiff_t new_capacity) noexcept
{
  if (new_capacity > capacity_) {
    auto buf = new T[new_capacity]();
    std::copy(data_, data_ + capacity_, buf);
    std::swap(data_, buf);
    capacity_ = new_capacity;
  }
}

template<class T>
bool StackArrT<T>::operator==(const StackArrT<T>& rhs) const noexcept
{
  if (Size() != rhs.Size()) {
    return false;
  }

  for (std::ptrdiff_t i = 0; i < Size(); i++) {
    if (data_[i] != rhs.data_[i]) {
      return false;
    }
  }

  return true;
}

template<class T>
StackArrT<T>& StackArrT<T>::operator=(const StackArrT& rhs) noexcept
{
  if (this != &rhs) {
    if (capacity_ < rhs.capacity_) {
      ChangeCapacity(rhs.capacity_);
      capacity_ = rhs.capacity_;
    }
    head_ = rhs.head_;

    std::copy(rhs.data_, rhs.data_ + rhs.capacity_, data_);

    return *this;
  }
}


#endif // !STACKARRT_STACKARRT_HPP
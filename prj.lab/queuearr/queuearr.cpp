#include "queuearr/queuearr.hpp"

#include <algorithm>
#include <stdexcept>

QueueArr::QueueArr(const QueueArr& queue)
{
  if (!queue.IsEmpty()) {
    Copy(queue);
  }
}

QueueArr::QueueArr(QueueArr&& queue) noexcept
{
  if (!queue.IsEmpty()) {
    std::swap(size_, queue.size_);
    std::swap(capacity_, queue.capacity_);
    std::swap(head_, queue.head_);
    std::swap(tail_, queue.tail_);
    std::swap(data_, queue.data_);
  }
}

QueueArr::~QueueArr()
{
  if (data_ != nullptr) {
    delete[] data_;
    data_ = nullptr;
  }
}

QueueArr& QueueArr::operator=(const QueueArr& queue)
{
  if (this != &queue) {
    Clear();
    if (!queue.IsEmpty()) {
      Copy(queue);
    }
  }

  return *this;
}

QueueArr& QueueArr::operator=(QueueArr&& queue) noexcept
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

void QueueArr::Push(const Complex& val)
{
  if (data_ == nullptr) {
    capacity_ = 1;
    data_ = new Complex[capacity_]();
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

void QueueArr::Pop() noexcept
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

bool QueueArr::IsEmpty() const noexcept
{
  return size_ == 0;
}

const Complex& QueueArr::Top() const
{
  if (IsEmpty()) {
    throw std::logic_error("QueueArr - try get top form empty queue.");
  }
  return data_[head_];
}

Complex& QueueArr::Top()
{
  if (IsEmpty()) {
    throw std::logic_error("QueueArr - try get top form empty queue.");
  }
  return data_[head_];
}

void QueueArr::Clear() noexcept
{
  head_ = -1;
  tail_ = -1;
  size_ = 0;
}

bool QueueArr::operator==(const QueueArr& rhs) const noexcept
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

void QueueArr::ChangeCapacity(std::ptrdiff_t new_capacity)
{
  Complex* new_data = new Complex[new_capacity]();

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

void QueueArr::Copy(const QueueArr& queue)
{
  capacity_ = queue.capacity_;
  head_ = 0;
  tail_ = queue.size_ - 1;
  data_ = new Complex[capacity_]();
  size_ = queue.size_;

  if (queue.head_ <= queue.tail_) {
    std::copy(queue.data_ + queue.head_, queue.data_ + queue.tail_ + 1, data_);
  }
  else {
    std::copy(queue.data_ + queue.head_, queue.data_ + queue.capacity_, data_);
    std::copy(queue.data_, queue.data_ + queue.tail_ + 1, data_ + (queue.capacity_ - queue.head_ + 1));
  }
}

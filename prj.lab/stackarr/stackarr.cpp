#include <stackarr/stackarr.hpp>
#include <algorithm>
#include <stdexcept>

StackArr::StackArr()
  : data_(new Complex[capacity_]())
{
}

StackArr::StackArr(const StackArr& stack)
  : capacity_(stack.capacity_), head_(stack.head_), data_(new Complex[stack.capacity_]())
{
  std::copy(stack.data_, stack.data_ + stack.capacity_, data_);
}

StackArr::StackArr(StackArr&& rhs) noexcept
{
  if (!rhs.IsEmpty()) {
    std::swap(data_, rhs.data_);
    std::swap(head_, rhs.head_);
    std::swap(capacity_, rhs.capacity_);
  }
}

StackArr::~StackArr()
{
  if (data_ != nullptr) {
    delete[] data_;
    data_ = nullptr;
  }
}

StackArr& StackArr::operator=(StackArr&& rhs) noexcept
{
  if (this != &rhs) {
    std::swap(data_, rhs.data_);
    std::swap(head_, rhs.head_);
    std::swap(capacity_, rhs.capacity_);
  }

  return *this;
}

void StackArr::Push(const Complex& new_el)
{
  if (Size() == capacity_) {
    ChangeCapacity(capacity_ * 2);
  }
  head_++;
  data_[head_] = new_el;
}

void StackArr::Pop() noexcept
{
  if (!IsEmpty()) {
    data_[head_] = Complex();
    head_--;
  }
}

bool StackArr::IsEmpty() const noexcept
{
  return head_ == -1;
}

const Complex& StackArr::Top() const
{
  if (!IsEmpty()) {
    return data_[head_];
  }
  else {
    throw std::logic_error("StackArr - try get top form empty stack.");
  }
}

Complex& StackArr::Top()
{
  if (!IsEmpty()) {
    return data_[head_];
  }
  else {
    throw std::logic_error("StackArr - try get top form empty stack.");
  }
}

void StackArr::Clear() noexcept
{
  head_ = -1;
}

void StackArr::ChangeCapacity(const std::ptrdiff_t new_capacity) noexcept
{
  if (new_capacity > capacity_) {
    auto buf = new Complex[new_capacity]();
    std::copy(data_, data_ + capacity_, buf);
    std::swap(data_, buf);
    capacity_ = new_capacity;
  }
}

bool StackArr::operator==(const StackArr& rhs) const noexcept
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

StackArr& StackArr::operator=(const StackArr& rhs) noexcept
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
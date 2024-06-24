#include <dynarr/dynarr.hpp>

DynArr::DynArr()
  : data_(new float[capacity_]())
{
}

DynArr::~DynArr()
{
  if (data_ != nullptr) {
    delete[] data_;
    data_ = nullptr;
  }
}

DynArr::DynArr(const DynArr& new_d)
{
  *this = new_d;
}

DynArr::DynArr(const std::ptrdiff_t size) : size_(size), capacity_(size * 2), data_(new float[capacity_]()) {
  if (size_ > 0) {
    Resize(size);
  }
  else {
    throw("size <= 0");
  }

}

DynArr::DynArr(DynArr&& rhs) noexcept
{
  if (rhs.Size() != 0) {
    std::swap(data_, rhs.data_);
    std::swap(size_, rhs.size_);
    std::swap(capacity_, rhs.capacity_);
  }
}

void DynArr::Resize(const std::ptrdiff_t& new_size)
{
  if (new_size > 0) {
    if (new_size > capacity_) { ChangeCapacity(new_size); }
    else {
      for (std::ptrdiff_t i = new_size; i < capacity_; i++)
      {
        data_[i] = 0;
      }
    }
    size_ = new_size;
  }
  else {
    throw("new size <= 0");
  }
}

void DynArr::PushBack(const float& obj)
{
  if (size_ == capacity_) { ChangeCapacity(capacity_ * 2); }

  data_[size_] = obj;
  ++size_;
}

void DynArr::PopBack()
{
  if (size_ > 0) {
    --size_;
  }
  else {
    throw("empty array pop");
  }
}

void DynArr::Erase(const std::ptrdiff_t& index)
{
  if (index >= 0 && index < size_)
  {
    for (std::ptrdiff_t i = index; i < size_; i++)
    {
      data_[i] = data_[i + 1];
    }
    size_--;
  }
  else
  {
    throw("uncorrect index");
  }
}

DynArr& DynArr::operator=(const DynArr& rhs)
{
  if (rhs.capacity_ > capacity_) {
    ChangeCapacity(rhs.capacity_);
  }

  for (std::ptrdiff_t i = 0; i < rhs.size_; i++)
  {
    data_[i] = rhs.data_[i];
  }

  size_ = rhs.size_;

  return *this;
}

DynArr& DynArr::operator=(DynArr&& rhs) noexcept
{
  if (this != &rhs) {
    std::swap(data_, rhs.data_);
    std::swap(size_, rhs.size_);
    std::swap(capacity_, rhs.capacity_);
  }

  return *this;
}

const float& DynArr::operator[](const std::ptrdiff_t& index) const
{
  if (index >= size_ || index < 0) {
    throw("index out of range");
  }

  return data_[index];
}

float& DynArr::operator[](const std::ptrdiff_t& index)
{
  if (index >= size_ || index < 0) {
    throw("index out of range");
  }

  return data_[index];
}

bool DynArr::operator==(const DynArr& rhs) const noexcept
{
  if (size_ != rhs.size_) { return false; }

  for (std::ptrdiff_t i = 0; i < size_; i++)
  {
    if (data_[i] != rhs.data_[i]) { return false; }
  }

  return true;
}

void DynArr::ChangeCapacity(const std::ptrdiff_t& new_capacity)
{
  if (new_capacity > capacity_) {
    float* new_data = new float[new_capacity]();
    for (std::ptrdiff_t i = 0; i < size_; i++)
    {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }
}

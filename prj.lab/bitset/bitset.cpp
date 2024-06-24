#include "bitset/bitset.hpp"

#include <stdexcept>


BitSet::BitSet(const BitSet& rhs)
  : data_(rhs.data_), size_(rhs.size_)
{
}

BitSet::BitSet(const int32_t size)
  : size_(size)
{
  if (size > 0) {
    data_.resize((size / 32) + 1);
  }
  else {
    throw std::logic_error("BitSet - size must be positive.");
  }
}

BitSet::BitSet(BitSet&& rhs) noexcept
{
  if (this != &rhs) {
    std::swap(size_, rhs.size_);
    std::swap(data_, rhs.data_);
  }
}

BitSet& BitSet::operator=(const BitSet& rhs) noexcept
{
  if (this != &rhs) {
    size_ = rhs.size_;
    data_ = rhs.data_;
  }

  return *this;
}

BitSet& BitSet::operator=(BitSet&& rhs) noexcept
{
  if (this != &rhs) {
    std::swap(size_, rhs.size_);
    std::swap(data_, rhs.data_);
  }

  return *this;
}

void BitSet::Resize(const int32_t& size)
{
  if (size > 0) {
    data_.resize((size / 32) + 1);
    size_ = size;
  }
  else {
    throw std::logic_error("BitSet - size must be positive.");
  }
}

bool BitSet::Get(const int32_t& idx) const
{
  if (idx >= 0 && idx < size_) {
    int32_t vec_pos = idx % 32;
    return (data_[idx / 32] >> vec_pos) & 1;
  }
  else {
    throw std::logic_error("BitSet - idx must be >= 0.");
  }
}

void BitSet::Set(const int32_t& idx, const bool v)
{
  if (idx >= 0 && idx < size_) {
    auto vec_pos = idx % 32;
    if (v == true) {
      data_[idx / 32] |= (1 << vec_pos);
    }
    else {
      data_[idx / 32] &= ~(1 << vec_pos);
    }
  }
  else {
    throw std::logic_error("BitSet - idx must be >= 0.");
  }
}

void BitSet::Fill(const bool val) noexcept {
  for (int i = 0; i < size_; i++) {
    Set(i, val);
  }
}

BitSet::BiA BitSet::operator[](const int32_t i) {
  if (i >= 0 && i < size_) {
    return BiA(*this, i);
  }
  else {
    throw std::logic_error("BitSet - i must be >= 0.");
  }
}

BitSet BitSet::operator~() const noexcept
{
  BitSet res(*this);
  for (int i = 0; i < size_ / 32; i++) {
    res.data_[i] = ~res.data_[i];
  }
  for (int i = size_ - (size_ % 32); i < size_; i++) {
    res.Set(i, !res.Get(i));
  }
  return res;
}

bool BitSet::operator==(const BitSet& rhs) const
{
  if (size_ == rhs.size_) {
    return data_ == rhs.data_;
  }
  else {
    throw std::logic_error("BitSet - size must be equal.");
  }
}

BitSet& BitSet::operator&=(const BitSet& rhs)
{
  if (Size() == rhs.Size()) {
    BitSet res(Size());
    for (int i = 0; i < res.Size(); i++) {
      res.Set(i, Get(i) && rhs.Get(i));
    }
    *this = res;
    return *this;
  }
  else {
    throw std::logic_error("BitSet - size must be equal.");
  }
}

BitSet& BitSet::operator^=(const BitSet& rhs)
{
  if (Size() == rhs.Size()) {
    BitSet res(Size());
    for (int i = 0; i < res.Size(); i++) {
      res.Set(i, Get(i) ^ rhs.Get(i));
    }
    *this = res;
    return *this;
  }
  else {
    throw std::logic_error("BitSet - size must be equal.");
  }
}

BitSet& BitSet::operator|=(const BitSet& rhs)
{
  if (Size() == rhs.Size()) {
    BitSet res(Size());
    for (int i = 0; i < res.Size(); i++) {
      res.Set(i, Get(i) || rhs.Get(i));
    }
    *this = res;
    return *this;
  }
  else {
    throw std::logic_error("BitSet - size must be equal.");
  }
}

BitSet operator&(const BitSet& lhs, const BitSet& rhs) { return BitSet(lhs) &= rhs; }

BitSet operator^(const BitSet& lhs, const BitSet& rhs) { return BitSet(lhs) ^= rhs; }

BitSet operator|(const BitSet& lhs, const BitSet& rhs) { return BitSet(lhs) |= rhs; }

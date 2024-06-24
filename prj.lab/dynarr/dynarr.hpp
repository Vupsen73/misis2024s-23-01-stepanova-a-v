#ifndef DYNARR_DYNARR_HPP
#define DYNARR_DYNARR_HPP

#include <iostream>
#include <cstddef>

class DynArr {
public:
  DynArr();
  DynArr(const DynArr& new_d);
  DynArr(const std::ptrdiff_t size);
  DynArr(DynArr&&) noexcept;
  ~DynArr();

  std::ptrdiff_t Size() const noexcept { return size_; }
  void Resize(const std::ptrdiff_t& new_size);
  void PushBack(const float& obj);
  void PopBack();
  void Erase(const std::ptrdiff_t& index);

  DynArr& operator=(const DynArr& rhs);
  DynArr& operator=(DynArr&& rhs) noexcept;

  const float& operator[](const std::ptrdiff_t& index) const;
  float& operator[](const std::ptrdiff_t& index);

  bool operator==(const DynArr& rhs) const noexcept;
  bool operator!=(const DynArr& rhs) const noexcept { return !operator==(rhs); }


private:
  void ChangeCapacity(const std::ptrdiff_t& new_capacity);
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t capacity_ = 2;
  float* data_ = nullptr;
};

#endif

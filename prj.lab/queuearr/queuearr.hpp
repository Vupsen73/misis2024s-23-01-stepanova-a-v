#pragma once
#ifndef QUEUEARR_QUEUEARR_HPP
#define QUEUEARR_QUEUEARR_HPP

#include <complex/complex.hpp>

#include <cstddef>

class QueueArr {
public:
  QueueArr() = default;
  QueueArr(const QueueArr&);
  QueueArr(QueueArr&&) noexcept;
  ~QueueArr();

  QueueArr& operator=(const QueueArr& queue);
  QueueArr& operator=(QueueArr&&) noexcept;

  void Push(const Complex& val);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  const Complex& Top() const;
  Complex& Top();
  void Clear() noexcept;

  std::ptrdiff_t Size() const noexcept { return size_; };

  bool operator==(const QueueArr& rhs) const noexcept;
  bool operator!=(const QueueArr& rhs) const noexcept { return !operator==(rhs); }

private:
  std::ptrdiff_t size_ = 0;       //!< the number of items in the queue
  std::ptrdiff_t capacity_ = 0;   //!< queue capacity
  std::ptrdiff_t head_ = -1;      //!< index head of the queue
  std::ptrdiff_t tail_ = -1;      //!< index tail of the queue
  Complex* data_ = nullptr;       //!< pointer to the data

  void ChangeCapacity(std::ptrdiff_t new_capacity);

  void Copy(const QueueArr& queue);
};


#endif // !QUEUEARR_QUEUEARR_HPP
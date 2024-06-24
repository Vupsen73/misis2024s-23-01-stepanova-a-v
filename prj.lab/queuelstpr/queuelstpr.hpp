#pragma once
#ifndef QUEUELSTPR_QUEUELSTPR_HPP
#define QUEUELSTPR_QUEUELSTPR_HPP

#include <cstddef>

class QueueLstPr {
public:
  QueueLstPr() = default;
  QueueLstPr(const QueueLstPr&);
  QueueLstPr(QueueLstPr&&) noexcept;
  ~QueueLstPr();

  QueueLstPr& operator=(const QueueLstPr& rhs);
  QueueLstPr& operator=(QueueLstPr&& rhs) noexcept;

  void Push(const float& new_val);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  const float& Top() const;
  void Clear() noexcept;

  std::ptrdiff_t Size() const noexcept { return size_; };

  bool operator==(const QueueLstPr& rhs) const noexcept;
  bool operator!=(const QueueLstPr& rhs) const noexcept { return !operator==(rhs); }

private:
  struct Node {
    float value = 0.0;
    Node* next = nullptr;
  };

  std::ptrdiff_t size_ = 0; //!< the number of items in the queue
  Node* head_ = nullptr; //!< pointer to the head of the queue

  void Copy(const QueueLstPr& rhs);
};


#endif // !QUEUELSTPR_QUEUELSTPR_HPP
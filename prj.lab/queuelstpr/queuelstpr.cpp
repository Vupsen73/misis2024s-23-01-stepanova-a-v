#include <queuelstpr/queuelstpr.hpp>

#include <stdexcept>

QueueLstPr::QueueLstPr(const QueueLstPr& rhs)
{
  if (!rhs.IsEmpty()) {
    Copy(rhs);
  }
}

QueueLstPr::QueueLstPr(QueueLstPr&& rhs) noexcept
{
  if (!rhs.IsEmpty()) {
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
  }
}

QueueLstPr::~QueueLstPr()
{
  Clear();
}

QueueLstPr& QueueLstPr::operator=(const QueueLstPr& rhs)
{
  if (this != &rhs) {
    Clear();
    if (!rhs.IsEmpty()) {
      Copy(rhs);
    }
  }

  return *this;
}

QueueLstPr& QueueLstPr::operator=(QueueLstPr&& rhs) noexcept
{
  if (this != &rhs) {
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
  }

  return *this;
}

void QueueLstPr::Push(const float& new_val)
{
  QueueLstPr::Node* new_node = new QueueLstPr::Node{ new_val };

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

void QueueLstPr::Pop() noexcept
{
  if (!IsEmpty()) {
    auto del_node = head_;
    head_ = head_->next;
    delete del_node;
    del_node = nullptr;
    size_--;
  }
}

bool QueueLstPr::IsEmpty() const noexcept
{
  return size_ == 0;
}

const float& QueueLstPr::Top() const
{
  if (!IsEmpty()) {
    return head_->value;
  }
  else {
    throw std::logic_error("QueueLstPr - try get top form empty queue.");
  }
}

void QueueLstPr::Clear() noexcept
{
  while (!IsEmpty()) {
    Pop();
  }
}

bool QueueLstPr::operator==(const QueueLstPr& rhs) const noexcept
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

void QueueLstPr::Copy(const QueueLstPr& rhs)
{
  Node* head = rhs.head_;
  for (int i = 0; i < rhs.size_; i++) {
    Push(head->value);
    head = head->next;
  }
}

#include <queuelst/queuelst.hpp>

#include <stdexcept>

QueueLst::QueueLst(const QueueLst& queue)
{
  *this = queue;
}

QueueLst::QueueLst(QueueLst&& rhs) noexcept
{
  if (!rhs.IsEmpty()) {
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
    std::swap(tail_, rhs.tail_);
  }
}

QueueLst::~QueueLst()
{
  Clear();
}

QueueLst& QueueLst::operator=(const QueueLst& rhs) noexcept
{
  if (this != &rhs) {
    Clear();
    Node* head = rhs.head_;
    for (int i = 0; i < rhs.size_; i++) {
      Push(head->value);
      head = head->next;
    }
  }

  return *this;
}

QueueLst& QueueLst::operator=(QueueLst&& rhs) noexcept
{
  if (this != &rhs) {
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
    std::swap(tail_, rhs.tail_);
  }

  return *this;
}

void QueueLst::Push(const Complex& new_val)
{
  QueueLst::Node* new_node = new QueueLst::Node{ new_val };

  if (IsEmpty()) {
    tail_ = new_node;
    head_ = tail_;
  }
  else {
    tail_->next = new_node;
    tail_ = new_node;
  }

  size_++;
}

void QueueLst::Pop() noexcept
{
  if (!IsEmpty()) {
    auto del_node = head_;
    head_ = head_->next;
    delete del_node;
    del_node = nullptr;
    size_--;
  }
  else {
    tail_ = nullptr;
  }
}

bool QueueLst::IsEmpty() const noexcept
{
  return size_ == 0;
}

const Complex& QueueLst::Top() const
{
  if (!IsEmpty()) {
    return head_->value;
  }
  else {
    throw std::logic_error("QueueLst - try get top form empty queue.");
  }
}

Complex& QueueLst::Top()
{
  if (!IsEmpty()) {
    return head_->value;
  }
  else {
    throw std::logic_error("QueueLst - try get top form empty queue.");
  }
}

void QueueLst::Clear() noexcept
{
  while (!IsEmpty()) {
    Pop();
  }
}

bool QueueLst::operator==(const QueueLst& rhs) const noexcept
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
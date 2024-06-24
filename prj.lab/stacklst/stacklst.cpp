#include <stacklst/stacklst.hpp>
#include <algorithm>
#include <stdexcept>

StackLst::StackLst(const StackLst& stack)
{
  *this = stack;
}

StackLst::StackLst(StackLst&& rhs) noexcept
{
  if (!rhs.IsEmpty()) {
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
  }
}

StackLst::~StackLst()
{
  Clear();
}

StackLst& StackLst::operator=(const StackLst& rhs) noexcept
{
  if (this != &rhs) {
    StackLst time;
    Node* head = rhs.head_;
    for (int i = 0; i < rhs.size_; i++) {
      time.Push(head->value);
      head = head->next;
    }
    head = time.head_;
    Clear();
    for (int i = 0; i < rhs.size_; i++) {
      Push(head->value);
      head = head->next;
    }

    return *this;
  }
}

StackLst& StackLst::operator=(StackLst&& rhs) noexcept
{
  if (this != &rhs) {
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
  }

  return *this;
}

void StackLst::Push(const Complex& new_val)
{
  StackLst::Node* new_node = new StackLst::Node;
  new_node->value = new_val;
  new_node->next = head_;
  head_ = new_node;
  size_++;
}

void StackLst::Pop() noexcept
{
  if (!IsEmpty()) {
    auto del_node = head_;
    head_ = head_->next;
    delete del_node;
    del_node = nullptr;
    size_--;
  }
}

bool StackLst::IsEmpty() const noexcept
{
  return size_ == 0;
}

const Complex& StackLst::Top() const
{
  if (!IsEmpty()) {
    return head_->value;
  }
  else {
    throw std::logic_error("StackLst - try get top form empty stack.");
  }
}

Complex& StackLst::Top()
{
  if (!IsEmpty()) {
    return head_->value;
  }
  else {
    throw std::logic_error("StackLst - try get top form empty stack.");
  }
}

void StackLst::Clear() noexcept
{
  while (!IsEmpty()) {
    Pop();
  }
}

bool StackLst::operator==(const StackLst& rhs) const noexcept
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


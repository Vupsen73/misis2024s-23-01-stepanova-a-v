#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stacklstt/stacklstt.hpp>

#include "utils.hpp"

#include <string>
#include <vector>


#define TYPES int, double, std::string


TEST_CASE_TEMPLATE("stacklstt ctor", T, TYPES) {
  StackLstT<T> stack_def;
  CHECK_EQ(stack_def.Size(), 0);

  StackLstT<T> stack(stack_def);
  CHECK_EQ(stack, stack_def);

  T value;
  FillEl(1, value);
  stack.Push(value);
  StackLstT<T> stack2(stack);
  CHECK_EQ(stack, stack2);
}

template<class T>
double MeasureTimeCtorMove(const int pushed_count, StackLstT<T> qu_src) {
  std::vector<T> data;
  FillData(pushed_count, data);
  for (int i = 0; i < pushed_count; i++) {
    qu_src.Push(data[i]);
  }
  const auto t_beg = std::chrono::steady_clock::now();
  StackLstT<T> qu_tgt = std::move(qu_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE_TEMPLATE("stacklstt ctor move", T, TYPES) {
  StackLstT<T> qu_src;
  StackLstT<T> qu_tgt = std::move(qu_src);
  if (!qu_src.IsEmpty() && !qu_tgt.IsEmpty()) {
    CHECK(qu_src.Top() != qu_tgt.Top());
  }
  const auto t_0099 = MeasureTimeCtorMove(99, qu_src);
  qu_src.Clear();
  const auto t_9999 = MeasureTimeCtorMove(9999, qu_src);
  CHECK(t_0099 == t_9999);
}

template<class T>
double MeasureTimeEqMove(const int pushed_count, StackLstT<T> qu_src) {
  std::vector<T> data;
  FillData(pushed_count, data);
  for (int i = 0; i < pushed_count; i++) {
    qu_src.Push(data[i]);
  }
  const auto t_beg = std::chrono::steady_clock::now();
  StackLstT<T> qu_tgt;
  qu_tgt = std::move(qu_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE_TEMPLATE("stacklstt operator= move", T, TYPES) {
  StackLstT<T> qu_src;
  StackLstT<T> qu_tgt;
  qu_tgt = std::move(qu_src);
  if (!qu_src.IsEmpty() && !qu_tgt.IsEmpty()) {
    CHECK(qu_src.Top() != qu_tgt.Top());
  }
  const auto t_0099 = MeasureTimeEqMove(99, qu_src);
  const auto t_9999 = MeasureTimeEqMove(9999, qu_src);
  CHECK(t_0099 == t_9999);
}

TEST_CASE_TEMPLATE("stacklstt copy constructor", T, TYPES) {
  StackLstT<T> stack1;
  T value1;
  FillEl(1, value1);
  T value2;
  FillEl(2, value2);
  stack1.Push(value1);
  stack1.Push(value2);

  StackLstT<T> stack2(stack1);
  CHECK_EQ(stack1, stack2);

  stack2.Pop();

  CHECK_NE(stack1, stack2);

  CHECK_EQ(stack2.Size(), 1);
  CHECK_EQ(stack2.Top(), value1);

  CHECK_EQ(stack1.Size(), 2);
  CHECK_EQ(stack1.Top(), value2);

  stack1.Pop();

  CHECK_EQ(stack1, stack2);
  CHECK_EQ(stack1.Size(), 1);
  CHECK_EQ(stack1.Top(), value1);
}

TEST_CASE_TEMPLATE("stacklstt Push, Pop, Top, IsEmpty, Size, Clear", T, TYPES) {
  StackLstT<T> stack;

  T value1;
  FillEl(1, value1);
  T value2;
  FillEl(2, value2);
  stack.Push(value1);

  CHECK_EQ(stack.Top(), value1);

  stack.Pop();

  CHECK_THROWS(stack.Top());

  stack.Pop();

  CHECK(stack.IsEmpty());

  stack.Push(value1);
  stack.Push(value2);

  CHECK_EQ(stack.Top(), value2);
  CHECK_EQ(stack.Size(), 2);

  stack.Top() = value1;
  CHECK_EQ(stack.Top(), value1);
  CHECK_EQ(stack.Size(), 2);

  stack.Clear();
  StackLstT<T> stack_void;
  CHECK_EQ(stack, stack_void);

  stack.Push(value1);
  stack.Push(value2);

  CHECK_EQ(stack.Top(), value2);
  CHECK_EQ(stack.Size(), 2);

  StackLstT<T> new_stack(stack);

  new_stack.Clear();
  CHECK_EQ(new_stack, stack_void);
  CHECK_EQ(stack.Top(), value2);
  CHECK_EQ(stack.Size(), 2);

  int n = 100;
  StackLstT<T> st;
  std::vector<T> data;
  FillData(n, data);
  for (int i = 0; i < n; i += 1) {
    st.Push(data[i]);
  }
  bool correct_fifo = true;
  for (int i = n - 1; correct_fifo && (i >= 0); i--) {
    correct_fifo = (data[i] == st.Top());
    st.Pop();
  }
  CHECK(correct_fifo);
}

TEST_CASE_TEMPLATE("stacklstt operator =, ==, !=", T, TYPES) {
  StackLstT<T> stack1;
  StackLstT<T> stack2;

  T value1;
  FillEl(1, value1);
  T value2;
  FillEl(2, value2);

  stack2.Push(value1);
  stack2.Push(value2);

  CHECK(stack1 != stack2);

  stack1 = stack2;

  CHECK(stack1 == stack2);

  stack1.Pop();

  CHECK(stack1 != stack2);

  CHECK_EQ(stack1.Top(), value1);
  CHECK_EQ(stack2.Top(), value2);

  stack2.Pop();
  CHECK(stack1 == stack2);

  stack1.Push(value2);
  stack2.Push(value2);
  CHECK(stack1 == stack2);
}
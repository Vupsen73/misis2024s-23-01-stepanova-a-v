#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stackarrt/stackarrt.hpp>

#include "utils.hpp"

#include <string>
#include <vector>


#define TYPES int, double, std::string


TEST_CASE_TEMPLATE("stackarrt ctor", T, TYPES) {
  StackArrT<T> stack_def;
  CHECK_EQ(stack_def.Size(), 0);

  StackArrT<T> stack(stack_def);
  CHECK_EQ(stack, stack_def);

  T value;
  FillEl(1, value);
  stack.Push(value);
  StackArrT<T> stack2(stack);
  CHECK_EQ(stack, stack2);
}

template<class T>
double MeasureTimeCtorMove(const int pushed_count, StackArrT<T> qu_src) {
  std::vector<T> data;
  FillData(pushed_count, data);
  for (int i = 0; i < pushed_count; i++) {
    qu_src.Push(data[i]);
  }
  const auto t_beg = std::chrono::steady_clock::now();
  StackArrT<T> qu_tgt = std::move(qu_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE_TEMPLATE("queuelstpr ctor move", T, TYPES) {
  StackArrT<T> qu_src;
  StackArrT<T> qu_tgt = std::move(qu_src);
  if (!qu_src.IsEmpty() && !qu_tgt.IsEmpty()) {
    CHECK(qu_src.Top() != qu_tgt.Top());
  }
  const auto t_0099 = MeasureTimeCtorMove(99, qu_src);
  const auto t_9999 = MeasureTimeCtorMove(9999, qu_src);
  CHECK(t_0099 == t_9999);
}

template<class T>
double MeasureTimeEqMove(const int pushed_count, StackArrT<T> qu_src) {
  std::vector<T> data;
  FillData(pushed_count, data);
  for (int i = 0; i < pushed_count; i++) {
    qu_src.Push(data[i]);
  }
  const auto t_beg = std::chrono::steady_clock::now();
  StackArrT<T> qu_tgt;
  qu_tgt = std::move(qu_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE_TEMPLATE("queuelstpr operator= move", T, TYPES) {
  StackArrT<T> qu_src;
  StackArrT<T> qu_tgt;
  qu_tgt = std::move(qu_src);
  if (!qu_src.IsEmpty() && !qu_tgt.IsEmpty()) {
    CHECK(qu_src.Top() != qu_tgt.Top());
  }
  const auto t_0099 = MeasureTimeEqMove(99, qu_src);
  const auto t_9999 = MeasureTimeEqMove(9999, qu_src);
  CHECK(t_0099 == t_9999);
}

TEST_CASE_TEMPLATE("stackarrt copy constructor", T, TYPES) {
  StackArrT<T> stack1;
  T value1;
  FillEl(1, value1);
  T value2;
  FillEl(2, value2);
  stack1.Push(value1);
  stack1.Push(value2);

  StackArrT<T> stack2(stack1);
  CHECK_EQ(stack1, stack2);

  stack2.Pop();

  CHECK_NE(stack1, stack2);

  CHECK_EQ(stack2.Size(), 1);
  CHECK_EQ(stack2.Top(), value1);

  CHECK_EQ(stack1.Size(), 2);
  CHECK_EQ(stack1.Top(), value2);
}

TEST_CASE_TEMPLATE("stackarrt Push, Pop, Top, IsEmpty, Size, Clear", T, TYPES) {
  StackArrT<T> stack;

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
  StackArrT<T> stack_void;
  CHECK_EQ(stack, stack_void);

  stack.Push(value1);
  stack.Push(value2);

  CHECK_EQ(stack.Top(), value2);
  CHECK_EQ(stack.Size(), 2);

  int n = 100;
  StackArrT<T> st;
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

TEST_CASE_TEMPLATE("stackarrt operator =, ==, !=", T, TYPES) {
  StackArrT<T> stack1;
  StackArrT<T> stack2;

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
}
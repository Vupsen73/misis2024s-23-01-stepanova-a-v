#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stacklst/stacklst.hpp>


TEST_CASE("stacklst ctor") {
  StackLst stack_def;
  CHECK_EQ(stack_def.Size(), 0);

  StackLst stack(stack_def);
  CHECK_EQ(stack, stack_def);

  const Complex value(1.0);
  stack.Push(value);
  StackLst stack2(stack);
  CHECK_EQ(stack, stack2);
}

inline double MeasureTimeCtorMove(const int pushed_count) {
  StackLst qu_src;
  for (double v = 0.0; v < pushed_count; v += 1.0) {
    qu_src.Push(Complex(v, v));
  }
  const auto t_beg = std::chrono::steady_clock::now();
  StackLst qu_tgt = std::move(qu_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE("queuelstpr ctor move") {
  StackLst qu_src;
  StackLst qu_tgt = std::move(qu_src);
  if (!qu_src.IsEmpty() && !qu_tgt.IsEmpty()) {
    CHECK(qu_src.Top() != qu_tgt.Top());
  }
  const auto t_0099 = MeasureTimeCtorMove(99);
  const auto t_9999 = MeasureTimeCtorMove(9999);
  CHECK(t_0099 == t_9999);
}

inline double MeasureTimeEqMove(const int pushed_count) {
  StackLst qu_src;
  for (double v = 0.0; v < pushed_count; v += 1.0) {
    qu_src.Push(Complex(v, v));
  }
  const auto t_beg = std::chrono::steady_clock::now();
  StackLst qu_tgt;
  qu_tgt = std::move(qu_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE("queuelstpr operator= move") {
  StackLst qu_src;
  StackLst qu_tgt;
  qu_tgt = std::move(qu_src);
  if (!qu_src.IsEmpty() && !qu_tgt.IsEmpty()) {
    CHECK(qu_src.Top() != qu_tgt.Top());
  }
  const auto t_0099 = MeasureTimeEqMove(99);
  const auto t_9999 = MeasureTimeEqMove(9999);
  CHECK(t_0099 == t_9999);
}

TEST_CASE("stacklst copy constructor") {
  StackLst stack1;
  const Complex value1(1.0, 1.0);
  const Complex value2(2.0, 2.0);
  stack1.Push(value1);
  stack1.Push(value2);

  StackLst stack2(stack1);
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

TEST_CASE("stacklst Push, Pop, Top, IsEmpty, Size, Clear") {
  StackLst stack;

  const Complex value1(1.0, 1.0);
  const Complex value2(2.0, 2.0);
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
  StackLst stack_void;
  CHECK_EQ(stack, stack_void);

  stack.Push(value1);
  stack.Push(value2);

  CHECK_EQ(stack.Top(), value2);
  CHECK_EQ(stack.Size(), 2);

  StackLst new_stack(stack);

  new_stack.Clear();
  CHECK_EQ(new_stack, stack_void);
  CHECK_EQ(stack.Top(), value2);
  CHECK_EQ(stack.Size(), 2);
}

TEST_CASE("stacklst operator =, ==, !=") {
  StackLst stack1;
  StackLst stack2;

  const Complex value1(1.0, 1.0);
  const Complex value2(2.0, 2.0);

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
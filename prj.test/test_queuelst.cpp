﻿#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <queuelst/queuelst.hpp>


TEST_CASE("queuelst ctor") {
  QueueLst queue_def;
  CHECK_EQ(queue_def.Size(), 0);

  QueueLst queue(queue_def);
  CHECK_EQ(queue, queue_def);

  const Complex value(1.0);
  queue.Push(value);
  QueueLst queue2(queue);
  CHECK_EQ(queue, queue2);
}

inline double MeasureTimeCtorMove(const int pushed_count) {
  QueueLst qu_src;
  for (double v = 0.0; v < pushed_count; v += 1.0) {
    qu_src.Push(Complex(v, v));
  }
  const auto t_beg = std::chrono::steady_clock::now();
  QueueLst qu_tgt = std::move(qu_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE("queuelstpr ctor move") {
  QueueLst qu_src;
  QueueLst qu_tgt = std::move(qu_src);
  if (!qu_src.IsEmpty() && !qu_tgt.IsEmpty()) {
    CHECK(qu_src.Top() != qu_tgt.Top());
  }
  const auto t_0099 = MeasureTimeCtorMove(99);
  const auto t_9999 = MeasureTimeCtorMove(9999);
  CHECK(t_0099 == t_9999);
}

inline double MeasureTimeEqMove(const int pushed_count) {
  QueueLst qu_src;
  for (double v = 0.0; v < pushed_count; v += 1.0) {
    qu_src.Push(Complex(v, v));
  }
  const auto t_beg = std::chrono::steady_clock::now();
  QueueLst qu_tgt;
  qu_tgt = std::move(qu_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE("queuelstpr operator= move") {
  QueueLst qu_src;
  QueueLst qu_tgt;
  qu_tgt = std::move(qu_src);
  if (!qu_src.IsEmpty() && !qu_tgt.IsEmpty()) {
    CHECK(qu_src.Top() != qu_tgt.Top());
  }
  const auto t_0099 = MeasureTimeEqMove(99);
  const auto t_9999 = MeasureTimeEqMove(9999);
  CHECK(t_0099 == t_9999);
}

TEST_CASE("queuelst copy constructor") {
  QueueLst queue1;
  const Complex value1(1.0, 1.0);
  const Complex value2(2.0, 2.0);
  queue1.Push(value2);
  queue1.Push(value1);

  QueueLst queue2(queue1);
  CHECK_EQ(queue1, queue2);

  queue2.Pop();

  CHECK_NE(queue1, queue2);

  CHECK_EQ(queue2.Size(), 1);
  CHECK_EQ(queue2.Top(), value1);

  CHECK_EQ(queue1.Size(), 2);
  CHECK_EQ(queue1.Top(), value2);

  queue1.Pop();

  CHECK_EQ(queue1, queue2);
  CHECK_EQ(queue1.Size(), 1);
  CHECK_EQ(queue1.Top(), value1);

  QueueLst queue4;
  QueueLst queue3;
  queue4.Push(value2);
  queue4.Push(value1);

  queue3 = queue4;
  CHECK_EQ(queue3.Top(), value2);
  queue3.Pop();
  CHECK_EQ(queue3.Top(), value1);
  queue3.Pop();
  CHECK_THROWS(queue3.Top());
  queue4 = queue3;
  CHECK_THROWS(queue4.Top());
}

TEST_CASE("queuelst Push, Pop, Top, IsEmpty, Size, Clear") {
  QueueLst queue;

  const Complex value1(1.0, 1.0);
  const Complex value2(2.0, 2.0);
  queue.Push(value1);

  CHECK_EQ(queue.Top(), value1);

  queue.Pop();

  CHECK_THROWS(queue.Top());

  queue.Pop();

  CHECK(queue.IsEmpty());

  queue.Push(value2);
  queue.Push(value1);

  CHECK_EQ(queue.Top(), value2);
  CHECK_EQ(queue.Size(), 2);

  queue.Top() = value1;
  CHECK_EQ(queue.Top(), value1);
  CHECK_EQ(queue.Size(), 2);

  queue.Clear();
  QueueLst queue_void;
  CHECK_EQ(queue, queue_void);

  queue.Push(value2);
  queue.Push(value1);

  CHECK_EQ(queue.Top(), value2);
  CHECK_EQ(queue.Size(), 2);

  QueueLst new_queue(queue);

  new_queue.Clear();
  CHECK_EQ(new_queue, queue_void);
  CHECK_EQ(queue.Top(), value2);
  CHECK_EQ(queue.Size(), 2);
}

TEST_CASE("queuelst operator =, ==, !=") {
  QueueLst queue1;
  QueueLst queue2;

  const Complex value1(1.0, 1.0);
  const Complex value2(2.0, 2.0);

  queue2.Push(value2);
  queue2.Push(value1);

  CHECK(queue1 != queue2);

  queue1 = queue2;

  CHECK(queue1 == queue2);

  queue1.Pop();

  CHECK(queue1 != queue2);

  CHECK_EQ(queue1.Top(), value1);
  CHECK_EQ(queue2.Top(), value2);

  queue2.Pop();
  CHECK(queue1 == queue2);

  queue1.Push(value2);
  queue2.Push(value2);
  CHECK(queue1 == queue2);

  queue1.Clear();
  queue2.Clear();
  for (int i = 0; i < 100; i++) {
    queue1.Push(value1);
  }
  for (int i = 0; i < 123; i++) {
    queue2.Push(value2);
  }
  queue2 = queue1;
  CHECK(queue1 == queue2);

  queue1.Clear();
  queue2.Clear();
  CHECK(queue1 == queue2);
}
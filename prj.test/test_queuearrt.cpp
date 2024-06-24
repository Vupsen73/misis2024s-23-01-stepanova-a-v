#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <queuearrt/queuearrt.hpp>

#include "utils.hpp"

#include <string>
#include <vector>


#define TYPES int, double, std::string


TEST_CASE_TEMPLATE("queuearrt ctor", T, TYPES) {
  QueueArrT<T> queue_def;
  CHECK_EQ(queue_def.Size(), 0);

  QueueArrT<T> queue(queue_def);
  CHECK_EQ(queue, queue_def);

  T value;
  FillEl(1, value);
  queue.Push(value);
  QueueArrT<T> queue2(queue);
  CHECK_EQ(queue, queue2);
}

template<class T>
double MeasureTimeCtorMove(const int pushed_count, QueueArrT<T> qu_src) {
  std::vector<T> data;
  FillData(pushed_count, data);
  for (int i = 0; i < pushed_count; i++) {
    qu_src.Push(data[i]);
  }
  const auto t_beg = std::chrono::steady_clock::now();
  QueueArrT<T> qu_tgt = std::move(qu_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE_TEMPLATE("queuelstt ctor move", T, TYPES) {
  QueueArrT<T> qu_src;
  QueueArrT<T> qu_tgt = std::move(qu_src);
  if (!qu_src.IsEmpty() && !qu_tgt.IsEmpty()) {
    CHECK(qu_src.Top() != qu_tgt.Top());
  }
  const auto t_0099 = MeasureTimeCtorMove(99, qu_src);
  qu_src.Clear();
  const auto t_9999 = MeasureTimeCtorMove(9999, qu_src);
  CHECK(t_0099 == t_9999);
}

template<class T>
double MeasureTimeEqMove(const int pushed_count, QueueArrT<T> qu_src) {
  std::vector<T> data;
  FillData(pushed_count, data);
  for (int i = 0; i < pushed_count; i++) {
    qu_src.Push(data[i]);
  }
  const auto t_beg = std::chrono::steady_clock::now();
  QueueArrT<T> qu_tgt;
  qu_tgt = std::move(qu_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE_TEMPLATE("queuelstt operator= move", T, TYPES) {
  QueueArrT<T> qu_src;
  QueueArrT<T> qu_tgt;
  qu_tgt = std::move(qu_src);
  if (!qu_src.IsEmpty() && !qu_tgt.IsEmpty()) {
    CHECK(qu_src.Top() != qu_tgt.Top());
  }
  const auto t_0099 = MeasureTimeEqMove(99, qu_src);
  const auto t_9999 = MeasureTimeEqMove(9999, qu_src);
  CHECK(t_0099 == t_9999);
}

TEST_CASE_TEMPLATE("queuearrt copy constructor", T, TYPES) {
  QueueArrT<T> queue1;
  T value1;
  FillEl(1, value1);
  T value2;
  FillEl(2, value2);

  queue1.Push(value2);
  queue1.Push(value1);
  
  QueueArrT<T> queue2(queue1);
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

  QueueArrT<T> queue3(queue1);
  CHECK_EQ(queue1.Top(), value1);
  CHECK_EQ(queue1.Size(), 1);
  CHECK_EQ(queue3.Top(), value1);
  CHECK_EQ(queue3.Size(), 1);
  CHECK_EQ(queue1, queue3);
  
  QueueArrT<T> queue4;
  queue3.Clear();
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

TEST_CASE_TEMPLATE("queuearrt Push, Pop, Top, IsEmpty, Size, Clear", T, TYPES) {
  QueueArrT<T> queue;

  T value1;
  FillEl(1, value1);
  T value2;
  FillEl(2, value2);
  T value3;
  FillEl(3, value3);
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
  QueueArrT<T> queue_void;
  CHECK_EQ(queue, queue_void);

  queue.Push(value2);
  queue.Push(value1);

  CHECK_EQ(queue.Top(), value2);
  CHECK_EQ(queue.Size(), 2);

  QueueArrT<T> new_queue(queue);

  new_queue.Clear();
  CHECK_EQ(new_queue, queue_void);
  CHECK_EQ(queue.Top(), value2);
  CHECK_EQ(queue.Size(), 2);

  queue.Clear();
  queue.Push(value3);
  queue.Push(value2);
  queue.Push(value1);

  CHECK_EQ(queue.Top(), value3);

  queue.Pop();

  CHECK_EQ(queue.Top(), value2);

  queue.Pop();

  CHECK_EQ(queue.Top(), value1);

  queue.Pop();

  CHECK(queue.IsEmpty());

  queue.Push(value1);
  queue.Push(value1);
  queue.Push(value1);
  queue.Push(value1);
  queue.Push(value1);
  queue.Push(value1);
  queue.Push(value1);

  CHECK_EQ(queue.Top(), value1);
  CHECK_EQ(queue.Size(), 7);

  queue.Clear();
  CHECK(queue.IsEmpty());
}

TEST_CASE_TEMPLATE("queuearrt operator =, ==, !=", T, TYPES) {
  QueueArrT<T> queue1;
  QueueArrT<T> queue2;

  T value1;
  FillEl(1, value1);
  T value2;
  FillEl(2, value2);

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
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <dynarr/dynarr.hpp>

TEST_CASE("dynarr ctor") {
  DynArr arr_def;
  CHECK_EQ(arr_def.Size(), 0);

  DynArr arr_arr(arr_def);
  CHECK_EQ(arr_def, arr_arr);

  const int size = 5;
  DynArr arr_s(size);
  CHECK_EQ(arr_s.Size(), size);

  DynArr arr_d(arr_s);
  CHECK_EQ(arr_d, arr_s);

  CHECK_THROWS(void(DynArr(0)));
  CHECK_THROWS(void(DynArr(-size)));
}

inline double MeasureTimeCtorMove(const int pushed_count) {
  DynArr qu_src;
  for (double v = 0.0; v < pushed_count; v += 1.0) {
    qu_src.PushBack(v);
  }
  const auto t_beg = std::chrono::steady_clock::now();
  DynArr qu_tgt = std::move(qu_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE("queuelstpr ctor move") {
  DynArr qu_src;
  DynArr qu_tgt = std::move(qu_src);
  if (!qu_src.Size() == 0 && !qu_tgt.Size() == 0) {
    CHECK(qu_src[0] != qu_tgt[0]);
  }
  const auto t_0099 = MeasureTimeCtorMove(99);
  const auto t_9999 = MeasureTimeCtorMove(9999);
  CHECK(t_0099 == t_9999);
}

inline double MeasureTimeEqMove(const int pushed_count) {
  DynArr qu_src;
  for (double v = 0.0; v < pushed_count; v += 1.0) {
    qu_src.PushBack(v);
  }
  const auto t_beg = std::chrono::steady_clock::now();
  DynArr qu_tgt;
  qu_tgt = std::move(qu_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE("queuelstpr operator= move") {
  DynArr qu_src;
  DynArr qu_tgt;
  qu_tgt = std::move(qu_src);
  if (!qu_src.Size() == 0 && !qu_tgt.Size() == 0) {
    CHECK(qu_src[0] != qu_tgt[0]);
  }
  const auto t_0099 = MeasureTimeEqMove(99);
  const auto t_9999 = MeasureTimeEqMove(9999);
  CHECK(t_0099 == t_9999);
}

TEST_CASE("dynarr op[]") {
  const int size = 5;
  DynArr arr(size);
  CHECK_EQ(arr[0], 0);
  CHECK_EQ(arr[arr.Size() - 1], 0);
  CHECK_THROWS(arr[-1]);
  CHECK_THROWS(arr[arr.Size()]);
  arr[1] = 1;
  CHECK_EQ(arr[1], 1);
}

TEST_CASE("dynarr Resize") {
  const int size = 5;
  DynArr arr(size);
  CHECK_EQ(arr.Size(), size);

  const int new_size_pos = 3;
  arr.Resize(new_size_pos);
  CHECK_EQ(arr.Size(), new_size_pos);

  const int new_size_neg = -3;
  CHECK_THROWS(arr.Resize(new_size_neg));
}

TEST_CASE("dynarr PushBack") {
  DynArr arr;
  arr.PushBack(1);
  CHECK_EQ(arr[0], 1);
}

TEST_CASE("dynarr PopBack") {
  DynArr arr;
  arr.PushBack(1);
  arr.PushBack(2);
  arr.PopBack();
  CHECK_EQ(arr[0], 1);
  CHECK_THROWS(arr[1]);
  arr.PopBack();
  CHECK_THROWS(arr.PopBack());
}


TEST_CASE("dynarr op=") {
  DynArr arr_1;
  arr_1.PushBack(1);
  arr_1.PushBack(2);
  DynArr arr_2;
  arr_2 = arr_1;
  CHECK_EQ(arr_1, arr_2);
}

TEST_CASE("dynarr op== op!=") {
  DynArr arr_1;
  arr_1.PushBack(1);
  arr_1.PushBack(2);
  DynArr arr_2;
  arr_2 = arr_1;
  CHECK_EQ(arr_1 == arr_2, true);
  CHECK_EQ(arr_1 != arr_2, false);

  arr_1.PopBack();
  CHECK_EQ(arr_1 == arr_2, false);
  CHECK_EQ(arr_1 != arr_2, true);
}

TEST_CASE("dynarr Erase") {
  DynArr arr_1;
  arr_1.PushBack(1);
  arr_1.PushBack(2);
  arr_1.PushBack(3);
  arr_1.Erase(1);
  DynArr arr_2;
  arr_2.PushBack(1);
  arr_2.PushBack(3);
  CHECK_EQ(arr_1 == arr_2, true);
}

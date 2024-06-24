#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <bitset/bitset.hpp>

TEST_CASE("bitset ctor") {
  BitSet bs_def;
  CHECK_EQ(bs_def.Size(), 0);

  BitSet bs_bs_def(bs_def);
  CHECK_EQ(bs_bs_def, bs_def);

  const int size = 5;
  BitSet bs_s(size);
  CHECK_EQ(bs_s.Size(), size);

  BitSet bs_bs_s(bs_s);
  CHECK_EQ(bs_bs_s, bs_s);

  CHECK_THROWS(void(BitSet(0)));
  CHECK_THROWS(void(BitSet(-size)));
}

TEST_CASE("bitset Size, Resize") {
  const int size = 5;
  BitSet bs(size);
  CHECK_EQ(bs.Size(), size);

  const int new_size_pos = 34;
  bs.Resize(new_size_pos);
  CHECK_EQ(bs.Size(), new_size_pos);

  CHECK_THROWS(bs.Resize(-3));
  CHECK_THROWS(bs.Resize(0));
}

TEST_CASE("bitset Get, Set, Fill") {
  const int size = 3;
  BitSet bs(size);
  
  bs.Set(0, 1);
  CHECK_EQ(bs.Get(0), 1);
  bs.Set(1, 0);
  CHECK_EQ(bs.Get(1), 0);
  bs.Set(2, 1);
  CHECK_EQ(bs.Get(2), 1);
  bs.Set(0, 0);
  CHECK_EQ(bs.Get(0), 0);
  bs.Set(1, 1);
  CHECK_EQ(bs.Get(1), 1);
  bs.Set(2, 1);
  CHECK_EQ(bs.Get(2), 1);

  const int size2 = 100;
  bs.Resize(size2);

  bs.Set(0, 0);
  CHECK_EQ(bs.Get(0), 0);
  bs.Set(88, 1);
  CHECK_EQ(bs.Get(88), 1);
  bs.Set(33, 1);
  CHECK_EQ(bs.Get(33), 1);
  bs.Set(66, 1);
  CHECK_EQ(bs.Get(66), 1);
  bs.Set(33, 0);
  CHECK_EQ(bs.Get(33), 0);
  bs.Set(10, 1);
  CHECK_EQ(bs.Get(10), 1);

  bs.Fill(true);
  bool all_true = true;
  for (int i = 0; all_true && (i < size2); i++) {
    all_true = (bs.Get(i) == true);
  }
  CHECK(all_true);
}

TEST_CASE("bitset operator=, operator==, operator!=") {
  const int size = 52;
  BitSet bs(size);
  bs.Set(6, 1);
  bs.Set(32, 1);
  bs.Set(41, 1);

  BitSet bs2(3);
  bs.Set(0, 0);
  bs.Set(1, 1);
  bs.Set(2, 0);
  bs2 = bs;
  CHECK_EQ(bs, bs2);

  bs2.Resize(3);
  bs2.Resize(size);
  CHECK_NE(bs, bs2);
  bs2.Set(6, 1);
  bs2.Set(32, 1);
  bs2.Set(41, 1);
  CHECK_EQ(bs, bs2);
}

TEST_CASE("bitset operator~") {
  const int size = 52;
  BitSet bs(size);
  bs.Set(14, 1);
  bs.Set(32, 1);
  bs.Set(47, 1);

  BitSet bs2(size);
  for (int i = 0; i < size; i++) {
    bs2.Set(i, 1);
  }
  bs2.Set(14, 0);
  bs2.Set(32, 0);
  bs2.Set(47, 0);

  CHECK_EQ(bs, ~bs2);
}

TEST_CASE("bitset operator&, operator|, operator^") {
  const int size = 5;
  BitSet bs(size);
  bs.Set(0, 1);
  bs.Set(2, 1);
  bs.Set(4, 1);

  BitSet bs2(size);
  bs2.Set(1, 1);
  bs2.Set(2, 1);
  bs2.Set(3, 1);

  BitSet rs1(size);
  for (int i = 0; i < size; i++) {
    rs1.Set(i, 1);
  }
  BitSet rs2(size);
  rs2.Set(2, 1);
  BitSet rs3(size);
  rs3.Set(0, 1);
  rs3.Set(1, 1);
  rs3.Set(3, 1);
  rs3.Set(4, 1);


  CHECK((bs | bs2) == rs1);
  CHECK((bs & bs2) == rs2);
  CHECK((bs ^ bs2) == rs3);
}

TEST_CASE("bitset operator[]") {
  const int size = 5;
  BitSet bs(size);
  bs[1] = true;
  bs[2] = true;

  CHECK(bs.Get(1) == true);
  CHECK((bs[1] == true));
  CHECK((bs[2] == bs.Get(1)));
  CHECK((bs[2] == bs[1]));

  bs[1] = false;

  CHECK((bs[1] == false));
  CHECK((bs[2] != bs[1]));
  CHECK_THROWS(bs[6]);
  CHECK_THROWS(bs[-1]);

  bs[2] = bs[1];

  CHECK((bs[2] == false));
  CHECK((bs[2] == bs[1]));

  BitSet bs2(size);
  bs2[2] = true;
  bs2[2] = bs[2];
  CHECK((bs2[2] == false));
  CHECK((bs2[2] == bs[2]));
}

inline double MeasureTimeCtorMove(const int pushed_count) {
  BitSet bs_src(pushed_count);
  for (int i = 0; i < pushed_count; i++) {
    bs_src.Set(i, 1);
  }
  const auto t_beg = std::chrono::steady_clock::now();
  BitSet bs_tgt = std::move(bs_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE("bitset ctor move") {
  BitSet bs_src;
  BitSet bs_tgt = std::move(bs_src);
  if (!bs_src.Size() == 0 && !bs_tgt.Size() == 0) {
    CHECK(bs_src.Get(0) != bs_tgt.Get(0));
  }
  const auto t_0099 = MeasureTimeCtorMove(99);
  const auto t_9999 = MeasureTimeCtorMove(9999);
  CHECK(t_0099 == t_9999);
}

inline double MeasureTimeEqMove(const int pushed_count) {
  BitSet bs_src(pushed_count);
  for (int i = 0; i < pushed_count; i++) {
    bs_src.Set(i, 1);
  }
  const auto t_beg = std::chrono::steady_clock::now();
  BitSet bs_tgt;
  bs_tgt = std::move(bs_src);
  const auto t_end = std::chrono::steady_clock::now();
  const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_beg);
  return diff.count();
}

TEST_CASE("bitset operator= move") {
  BitSet bs_src;
  BitSet bs_tgt = std::move(bs_src);
  if (!bs_src.Size() == 0 && !bs_tgt.Size() == 0) {
    CHECK(bs_src.Get(0) != bs_tgt.Get(0));
  }
  const auto t_0099 = MeasureTimeCtorMove(99);
  const auto t_9999 = MeasureTimeCtorMove(9999);
  CHECK(t_0099 == t_9999);
}

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <rational/rational.hpp>

TEST_CASE("Rational ctor") {
  Rational r_def;
  CHECK(0 == r_def.num());
  CHECK(1 == r_def.den());

  Rational r_rat(r_def);
  CHECK(r_rat.num() == r_def.num());
  CHECK(r_rat.den() == r_def.den());

  Rational r_int(3);
  CHECK(3 == r_int.num());
  CHECK(1 == r_int.den());

  Rational r_copy(r_int);
  CHECK(r_int.num() == r_copy.num());
  CHECK(r_int.den() == r_copy.den());

  Rational r(2, -3);
  CHECK(-2 == r.num());
  CHECK(3 == r.den());

  CHECK_THROWS(void(Rational(1, 0)));
}

TEST_CASE("Rational bool operators") {
  Rational r(2, -3);
  CHECK((r == Rational(-2, 3)));
  CHECK((r != Rational(2)));

  CHECK(Rational(1, 2) >= r);
  CHECK(Rational(-2, 3) >= r);
  CHECK(Rational(-3, 4) <= r);
  CHECK(Rational(-2, 3) <= r);

  CHECK(Rational(1, 2) > r);
  CHECK(Rational(-3, 4) < r);
}

TEST_CASE("Rational arithmetic operators Rational and Rational") {
  Rational r1;
  Rational r2;

  r1 = Rational(1, 2);
  r2 = Rational(3, 5);
  r1 += r2;
  CHECK(r1 == Rational(11, 10));
  r1 -= r2;
  CHECK(r1 + r2 == Rational(11, 10));

  r1 = Rational(1, 2);
  r2 = Rational(2, 5);
  r1 -= r2;
  CHECK(r1 == Rational(1, 10));
  r1 += r2;
  CHECK(r1 - r2 == Rational(1, 10));

  r1 = Rational(-8, 15);
  r2 = Rational(9, -4);
  r1 *= r2;
  CHECK(r1 == Rational(6, 5));
  r1 /= r2;
  CHECK(r1 * r2 == Rational(6, 5));

  r1 = Rational(2, 5);
  r2 = Rational(3, 4);
  r1 /= r2;
  CHECK(r1 == Rational(8, 15));
  r1 *= r2;
  CHECK(r1 / r2 == Rational(8, 15));

  CHECK_THROWS(void(r1 / Rational(0, 1)));
}

TEST_CASE("Rational arithmetic operators Rational and int") {
  Rational r1;
  int r2;

  r1 = Rational(1, 2);
  r2 = 1;
  r1 += r2;
  CHECK(r1 == Rational(3, 2));
  r1 -= r2;
  CHECK(r1 + r2 == Rational(3, 2));

  r1 = Rational(1, 2);
  r2 = 2;
  r1 -= r2;
  CHECK(r1 == Rational(-3, 2));
  r1 += r2;
  CHECK(r1 - r2 == Rational(-3, 2));

  r1 = Rational(-8, 15);
  r2 = -5;
  r1 *= r2;
  CHECK(r1 == Rational(8, 3));
  r1 /= r2;
  CHECK(r1 * r2 == Rational(8, 3));

  r1 = Rational(2, 5);
  r2 = 4;
  r1 /= r2;
  CHECK(r1 == Rational(1, 10));
  r1 *= r2;
  CHECK(r1 / r2 == Rational(1, 10));

  CHECK_THROWS(void(r1 / 0));
}

TEST_CASE("Rational arithmetic operators int and Rational") {
  int r1;
  Rational r2;

  r1 = 1;
  r2 = Rational(1, 2);
  CHECK(r1 + r2 == Rational(3, 2));

  r1 = 2;
  r2 = Rational(1, 2);
  CHECK(r1 - r2 == Rational(3, 2));

  r1 = -5;
  r2 = Rational(-8, 15);
  CHECK(r1 * r2 == Rational(8, 3));

  r1 = 4;
  r2 = Rational(2, 5);
  CHECK(r1 / r2 == Rational(10, 1));

  CHECK_THROWS(void(4 / Rational(0, 1)));
}

TEST_CASE("Rational gcd") {
  Rational r(15, 6);
  CHECK(5 == r.num());
  CHECK(2 == r.den());

  Rational r_neg(-15, 6);
  CHECK(-5 == r_neg.num());
  CHECK(2 == r_neg.den());
}

TEST_CASE("IO") {
  std::istringstream istream("2/3 ");
  Rational reading;

  istream >> reading;
  CHECK_FALSE(istream.fail());
  CHECK(reading.num() == 2);
  CHECK(reading.den() == 3);

  std::istringstream istream2("4/5");
  istream2 >> reading;
  CHECK(reading.num() == 4);
  CHECK(reading.den() == 5);

  std::istringstream istream3("7/8");
  istream3 >> reading;
  CHECK(reading.num() == 7);
  CHECK(reading.den() == 8);

  std::istringstream istream4("-712/38");
  istream4 >> reading;
  CHECK(reading.num() == -356);
  CHECK(reading.den() == 19);

  std::istringstream istream5("-123/48");
  istream5 >> reading;
  CHECK(reading.num() == -41);
  CHECK(reading.den() == 16);

  std::istringstream istream6("7/-8");
  istream6 >> reading;
  CHECK(istream6.fail());

  std::istringstream istream7("4|54");
  istream7 >> reading;
  std::ostringstream ostream;
  CHECK(istream7.fail());
  ostream << Rational(2, 3);
  CHECK(ostream.str() == "2/3");

  std::istringstream istream8("7/0");
  istream8 >> reading;
  CHECK(istream8.fail());
};

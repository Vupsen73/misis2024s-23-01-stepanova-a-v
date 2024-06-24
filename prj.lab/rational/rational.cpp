#include <rational/rational.hpp>

#include <stdexcept>
#include <sstream>

static int64_t greatest_common_divisor(const int64_t& a, const int64_t& b) noexcept {
  if (a % b == 0) { return b; }
  if (b % a == 0) { return a; }
  if (a > b) { return greatest_common_divisor(a % b, b); }

  return greatest_common_divisor(a, b % a);
}

static int64_t least_common_multiple(const int64_t& a, const int64_t& b) noexcept {
  return (a * b) / greatest_common_divisor(a, b);
}


Rational::Rational(const int64_t num, const int64_t den)
  : num_(num), den_(den)
{
  if (den_ == 0) {
    throw std::invalid_argument("Zero denumenator in Rational ctor");
  }
  else {
    if (den_ < 0) {
      num_ = -num_;
      den_ = -den_;
    }
    int64_t gcd = greatest_common_divisor(std::abs(num), std::abs(den));
    if (gcd != 1) {
      num_ /= gcd;
      den_ /= gcd;
    }
  }
}

Rational& Rational::operator+=(const Rational& rhs) noexcept {
  if (den_ != rhs.den_) {
    const int64_t temp = least_common_multiple(den_, rhs.den_);
    num_ = temp / den_ * num_ + temp / rhs.den_ * rhs.num_;
    den_ = temp;
  }
  else {
    num_ += rhs.num_;
  }
  return *this;
}

Rational& Rational::operator-=(const Rational& rhs) noexcept {
  if (den_ != rhs.den_) {
    const int64_t temp = least_common_multiple(den_, rhs.den_);
    num_ = temp / den_ * num_ - temp / rhs.den_ * rhs.num_;
    den_ = temp;
  }
  else {
    num_ -= rhs.num_;
  }
  return *this;
}

Rational& Rational::operator*=(const Rational& rhs) noexcept {
  num_ *= rhs.num_;
  den_ *= rhs.den_;
  return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
  if (rhs.num_ == 0) {
    throw std::invalid_argument("division by zero");
  }
  den_ *= rhs.num_;
  num_ *= rhs.den_;
  return *this;
}

std::ostream& Rational::WriteTo(std::ostream& ostrm) const noexcept {
  ostrm << num_ << separator << den_;
  return ostrm;
}

std::istream& Rational::ReadFrom(std::istream& istrm) noexcept {
  int64_t num(0);
  char delimiter(0);
  int64_t den(1);
  istrm >> num;
  istrm.get(delimiter);
  int64_t trash = istrm.peek();
  istrm >> den;
  if (!istrm || trash > '9' || trash < '0') {
    istrm.setstate(std::ios_base::failbit);
    return istrm;
  }
  if (istrm.good() || istrm.eof()) {
    if ('/' == delimiter && den > 0) {
      *this = Rational(num, den);
    }
    else {
      istrm.setstate(std::ios_base::failbit);
    }
  }
  return istrm;
}

Rational operator+(const Rational& lhs, const Rational& rhs) noexcept { return Rational{ lhs } += rhs; }
Rational operator-(const Rational& lhs, const Rational& rhs) noexcept { return Rational{ lhs } -= rhs; }
Rational operator*(const Rational& lhs, const Rational& rhs) noexcept { return Rational{ lhs } *= rhs; }
Rational operator/(const Rational& lhs, const Rational& rhs) { return Rational{ lhs } /= rhs; }

Rational operator+(const Rational& lhs, const int64_t rhs) noexcept { return Rational{ lhs } += rhs; }
Rational operator-(const Rational& lhs, const int64_t rhs) noexcept { return Rational{ lhs } -= rhs; };
Rational operator*(const Rational& lhs, const int64_t rhs) noexcept { return Rational{ lhs } *= rhs; };
Rational operator/(const Rational& lhs, const int64_t rhs) { return Rational{ lhs } /= rhs; }

Rational operator+(const int64_t lhs, const Rational& rhs) noexcept { return Rational{ lhs } += rhs; }
Rational operator-(const int64_t lhs, const Rational& rhs) noexcept { return Rational{ lhs } -= rhs; }
Rational operator*(const int64_t lhs, const Rational& rhs) noexcept { return Rational{ lhs } *= rhs; };
Rational operator/(const int64_t lhs, const Rational& rhs) { return Rational{ lhs } /= rhs; }

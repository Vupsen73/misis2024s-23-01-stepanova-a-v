#ifndef RATIONAL_RATIONAL_HPP
#define RATIONAL_RATIONAL_HPP

#include <cstdint>
#include <iostream>

class Rational {
public:
  Rational() = default;
  Rational(const Rational&) = default;
  explicit Rational(const int64_t num) noexcept : num_(num) { }
  Rational(const int64_t num, const int64_t den);
  ~Rational() = default;

  Rational& operator=(const Rational&) = default;

  int64_t num() const noexcept { return num_; }
  int64_t den() const noexcept { return den_; }

  bool operator==(const Rational& lhs) const noexcept { return num_ * lhs.den_ == lhs.num_ * den_; }
  bool operator!=(const Rational& lhs) const noexcept { return !operator==(lhs); }
  bool operator>(const Rational& lhs) const noexcept { return num_ * lhs.den_ > lhs.num_ * den_; }
  bool operator<(const Rational& lhs) const noexcept { return num_ * lhs.den_ < lhs.num_ * den_; }
  bool operator>=(const Rational& lhs) const noexcept { return operator==(lhs) || operator>(lhs); }
  bool operator<=(const Rational& lhs) const noexcept { return operator==(lhs) || operator<(lhs); }

  Rational operator-() const noexcept { return { -num_, den_ }; }

  Rational& operator+=(const Rational& lhs) noexcept;
  Rational& operator+=(const int64_t lhs) noexcept { return operator+=(Rational(lhs)); }
  Rational& operator-=(const Rational& lhs) noexcept;
  Rational& operator-=(const int64_t lhs) noexcept { return operator-=(Rational(lhs)); }
  Rational& operator*=(const Rational& lhs) noexcept;
  Rational& operator*=(const int64_t lhs) noexcept { return operator*=(Rational(lhs)); }
  Rational& operator/=(const Rational& lhs);
  Rational& operator/=(const int64_t lhs) { return operator/=(Rational(lhs)); }

  std::ostream& WriteTo(std::ostream& ostrm) const noexcept;
  std::istream& ReadFrom(std::istream& istrm) noexcept;

private:
  int64_t num_ = 0;
  int64_t den_ = 1;
  static const char separator = '/';
};

Rational operator+(const Rational& lhs, const Rational& rhs) noexcept;
Rational operator-(const Rational& lhs, const Rational& rhs) noexcept;
Rational operator*(const Rational& lhs, const Rational& rhs) noexcept;
Rational operator/(const Rational& lhs, const Rational& rhs);

Rational operator+(const Rational& lhs, const int64_t rhs) noexcept;
Rational operator-(const Rational& lhs, const int64_t rhs) noexcept;
Rational operator*(const Rational& lhs, const int64_t rhs) noexcept;
Rational operator/(const Rational& lhs, const int64_t rhs);

Rational operator+(const int64_t lhs, const Rational& rhs) noexcept;
Rational operator-(const int64_t lhs, const Rational& rhs) noexcept;
Rational operator*(const int64_t lhs, const Rational& rhs) noexcept;
Rational operator/(const int64_t lhs, const Rational& rhs);

inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept {
  return rhs.WriteTo(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept {
  return rhs.ReadFrom(istrm);
}

#endif

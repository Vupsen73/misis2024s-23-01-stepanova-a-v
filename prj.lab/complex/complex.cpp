#include <complex/complex.hpp>

Complex::Complex(const double real)
  : re(real)
{
}

Complex::Complex(const double real, const double imaginary)
  : re(real), im(imaginary)
{
}

Complex Complex::operator-() const noexcept {
  return Complex(-re, -im);
}

bool Complex::operator==(const Complex& rhs) const noexcept {
  constexpr double eps = 2 * std::numeric_limits<double>::epsilon();
  return std::abs(re - rhs.re) < eps && std::abs(im - rhs.im) < eps;
}

bool Complex::operator!=(const Complex& rhs) const noexcept {
  return !operator==(rhs);
}

Complex& Complex::operator+=(const Complex& rhs) noexcept {
  re += rhs.re;
  im += rhs.im;
  return *this;
}

Complex& Complex::operator+=(const double rhs) noexcept {
  return operator+=(Complex(rhs));
}

Complex& Complex::operator-=(const Complex& rhs) noexcept {
  re -= rhs.re;
  im -= rhs.im;
  return *this;
}

Complex& Complex::operator-=(const double rhs) noexcept {
  return operator-=(Complex(rhs));
}

Complex& Complex::operator*=(const Complex& rhs) noexcept {
  const double temp = re;
  re = temp * rhs.re - im * rhs.im;
  im = temp * rhs.im + im * rhs.re;
  return *this;
}

Complex& Complex::operator*=(const double rhs) noexcept {
  return operator*=(Complex(rhs));
}

Complex& Complex::operator/=(const Complex& rhs) {
  Complex con_z = Complex(rhs.re, -rhs.im);
  const double t = (con_z * rhs).re;
  con_z /= t;
  return operator*=(con_z);
}

Complex& Complex::operator/=(const double rhs) {
  if (rhs == 0.0) {
    throw ("division by zero");
  }
  re /= rhs;
  im /= rhs;
  return *this;
}

std::ostream& Complex::WriteTo(std::ostream& ostrm) const noexcept {
  ostrm << leftBrace << re << separator << im << rightBrace;
  return ostrm;
}

std::istream& Complex::ReadFrom(std::istream& istrm) noexcept {
  char leftBrace(0);
  double real(0.0);
  char comma(0);
  double imaganary(0.0);
  char rightBrace(0);
  istrm >> leftBrace >> real >> comma >> imaganary >> rightBrace;
  if (istrm.good()) {
    if ((Complex::leftBrace == leftBrace) && (Complex::separator == comma) && (Complex::rightBrace == rightBrace)) {
      re = real;
      im = imaganary;
    }
    else {
      istrm.setstate(std::ios_base::failbit);
    }
  }
  return istrm;
}

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept { return Complex(lhs) += rhs; }
Complex operator+(const Complex& lhs, const double rhs) noexcept { return Complex(lhs) += rhs; }
Complex operator+(const double lhs, const Complex& rhs) noexcept { return Complex(lhs) += rhs; }

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept { return Complex(lhs) -= rhs; }
Complex operator-(const Complex& lhs, const double rhs) noexcept { return Complex(lhs) -= rhs; }
Complex operator-(const double lhs, const Complex& rhs) noexcept { return Complex(lhs) -= rhs; }

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept { return Complex(lhs) *= rhs; }
Complex operator*(const Complex& lhs, const double rhs) noexcept { return Complex(lhs) *= rhs; }
Complex operator*(const double lhs, const Complex& rhs) noexcept { return Complex(lhs) *= rhs; }

Complex operator/(const Complex& lhs, const Complex& rhs) { return Complex(lhs) /= rhs; }
Complex operator/(const Complex& lhs, const double rhs) { return Complex(lhs) /= rhs; }
Complex operator/(const double lhs, const Complex& rhs) { return Complex(lhs) /= rhs; }

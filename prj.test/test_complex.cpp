#include <complex/complex.hpp>

#include <sstream>

static bool testParse(const std::string& str) {
  std::istringstream istrm(str);
  Complex z;
  istrm >> z;
  if (istrm.good()) {
    std::cout << "Read success: " << str << " -> " << z << '\n';
  }
  else {
    std::cout << "Read error : " << str << " -> " << z << '\n';
  }
  return istrm.good();
}

int main() {

  Complex z(4.0);
  std::cout << "complex number: " << z << '\n';

  z += Complex(8.0, 3.0);
  std::cout << "complex += complex: " << z << '\n';
  z += 4.0;
  std::cout << "complex += real: " << z << '\n';
  z = Complex(8.0, 3.0) + Complex(4.0, 2.0);
  std::cout << "complex + complex: " << z << '\n';

  z -= Complex(8.0, 3.0);
  std::cout << "complex -= complex: " << z << '\n';
  z -= 4.0;
  std::cout << "complex += real: " << z << '\n';
  z = Complex(8.0, 3.0) - Complex(4.0, 2.0);
  std::cout << "complex - complex: " << z << '\n';

  z *= Complex(8.0, 3.0);
  std::cout << "complex *= complex: " << z << '\n';
  z *= 4.0;
  std::cout << "complex *= real: " << z << '\n';
  z = Complex(8.0, 3.0) * Complex(4.0, 2.0);
  std::cout << "complex * complex: " << z << '\n';

  z /= Complex(8.0, 3.0);
  std::cout << "complex /= complex: " << z << '\n';
  z /= 4.0;
  std::cout << "complex /= real: " << z << '\n';
  z = Complex(8.0, 3.0) / Complex(4.0, 2.0);
  std::cout << "complex / complex: " << z << '\n';

  testParse("{8.9,9}");
  testParse("{8.9, 9}");
  testParse("{8.9,9");

  return 0;
}

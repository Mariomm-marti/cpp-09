#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv) {
  RPN rpn;

  for (int i = 1; i < argc; i++) {
    try {
      std::cout << rpn.calculate(argv[i]) << std::endl;
    } catch (std::invalid_argument const &e) {
      std::cout << "invalid_argument: " << e.what() << " on expression "
                << argv[i] << std::endl;
      rpn.clear();
    }
  }
}

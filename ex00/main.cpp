#include "BitcoinExchange.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char **argv) {
  if (argc != 2 && argc != 3) {
    std::cout << "Expected usage: " << argv[0] << " <input_file> [dbname.csv]"
              << std::endl;
    return 1;
  }
  try {
    BitcoinExchange exchange(argv[1], argv[2] ? argv[2] : "data.csv");

    if (__CPP09_DEBUG_)
      for (BitcoinExchange::db_type::const_iterator it = exchange.begin();
           it != exchange.end(); it++)
        std::cout << "{\"date\": \"" << it->first
                  << "\", \"value\": " << it->second << "}" << std::endl;
  } catch (std::invalid_argument const &except) {
    std::cout << "invalid_argument: " << except.what() << std::endl;
  } catch (std::exception const &except) {
    std::cout << "exception: " << except.what() << std::endl;
  }
}

#include "PmergeMe.hpp"
#include <chrono>
#include <deque>
#include <exception>
#include <iostream>
#include <list>
#include <string>
#include <vector>

typedef std::chrono::steady_clock::time_point time_point;

int main(int argc, char **argv) {
  PmergeMe<std::vector<int> > vector;
  PmergeMe<std::list<int> > list;
  PmergeMe<std::deque<int> > deque;
  time_point chrono_begin;
  time_point chrono_end;

  try {
    for (int i = 1; i < argc; i++) {
      if (std::stoi(*(argv + i)) < 0)
        throw std::exception();
      vector.insert(std::stoi(*(argv + i)));
      list.insert(std::stoi(*(argv + i)));
      deque.insert(std::stoi(*(argv + i)));
    }
  } catch (std::exception const &ex) {
    std::cerr << "Error" << std::endl;
    return 1;
  }

  std::cout << "Before: ";
  vector.stream_numbers(std::cout);
  std::cout << std::endl;
  chrono_begin = std::chrono::high_resolution_clock::now();
  vector.sort();
  chrono_end = std::chrono::high_resolution_clock::now();
  std::cout << "After: ";
  vector.stream_numbers(std::cout);
  std::cout << std::endl;
  std::cout << "Time to process a range of " << argc - 1
            << " elements with std::vector : "
            << std::chrono::duration_cast<std::chrono::microseconds>(
                   chrono_end - chrono_begin)
                   .count()
            << std::endl;

  chrono_begin = std::chrono::high_resolution_clock::now();
  list.sort();
  chrono_end = std::chrono::high_resolution_clock::now();
  std::cout << "Time to process a range of " << argc - 1
            << " elements with std::list: "
            << std::chrono::duration_cast<std::chrono::microseconds>(
                   chrono_end - chrono_begin)
                   .count()
            << std::endl;

  chrono_begin = std::chrono::high_resolution_clock::now();
  deque.sort();
  chrono_end = std::chrono::high_resolution_clock::now();
  std::cout << "Time to process a range of " << argc - 1
            << " elements with std::deque: "
            << std::chrono::duration_cast<std::chrono::microseconds>(
                   chrono_end - chrono_begin)
                   .count()
            << std::endl;
}

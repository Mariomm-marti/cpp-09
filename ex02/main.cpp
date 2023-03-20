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

  for (int i = 1; i < argc; i++)
    try {
      vector.insert(std::stoi(*(argv + i)));
      list.insert(std::stoi(*(argv + i)));
      deque.insert(std::stoi(*(argv + i)));
    } catch (std::exception const &ex) {
      std::cerr << "Invalid argument " << *(argv + i) << ", ignoring..."
                << std::endl;
    }

  vector.stream_numbers(std::cout);
  std::cout << std::endl;
  chrono_begin = std::chrono::high_resolution_clock::now();
  vector.sort();
  chrono_end = std::chrono::high_resolution_clock::now();
  vector.stream_numbers(std::cout);
  std::cout << std::endl;
  std::cout << "Took (vector): "
            << std::chrono::duration_cast<std::chrono::microseconds>(
                   chrono_end - chrono_begin)
                   .count()
            << std::endl;

  list.stream_numbers(std::cout);
  std::cout << std::endl;
  chrono_begin = std::chrono::high_resolution_clock::now();
  list.sort();
  chrono_end = std::chrono::high_resolution_clock::now();
  list.stream_numbers(std::cout);
  std::cout << std::endl;
  std::cout << "Took (list): "
            << std::chrono::duration_cast<std::chrono::microseconds>(
                   chrono_end - chrono_begin)
                   .count()
            << std::endl;

  deque.stream_numbers(std::cout);
  std::cout << std::endl;
  chrono_begin = std::chrono::high_resolution_clock::now();
  deque.sort();
  chrono_end = std::chrono::high_resolution_clock::now();
  deque.stream_numbers(std::cout);
  std::cout << std::endl;
  std::cout << "Took (deque): "
            << std::chrono::duration_cast<std::chrono::microseconds>(
                   chrono_end - chrono_begin)
                   .count()
            << std::endl;
}

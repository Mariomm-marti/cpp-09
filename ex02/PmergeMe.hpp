#ifndef CPP_09_EX02_PMERGE_ME_HPP_
#define CPP_09_EX02_PMERGE_ME_HPP_
#pragma once

#ifndef __CPP09_DEBUG_
#define __CPP09_DEBUG_ false
#endif

#include <iterator>
#include <ostream>
#include <stdexcept>

template <typename Container> class PmergeMe {
public:
  typedef Container container;
  typedef typename container::value_type value_type;
  typedef typename container::size_type size_type;
  typedef typename container::iterator iterator;
  typedef typename container::const_iterator const_iterator;

private:
  container _numbers;

  container sort_insert(container const &left, container const &right) {
    container result;
    const_iterator left_it = left.begin();
    const_iterator right_it = right.begin();

    while (left_it != left.end() && right_it != right.end())
      if (*left_it < *right_it) {
        result.push_back(*left_it);
        left_it++;
      } else {
        result.push_back(*right_it);
        right_it++;
      }
    for (; left_it != left.end(); left_it++)
      result.push_back(*left_it);
    for (; right_it != right.end(); right_it++)
      result.push_back(*right_it);
    return result;
  };

  void sort(container &numbers, std::random_access_iterator_tag) {
    container left;
    container right;
    size_type middle;

    if (numbers.size() < 2)
      return;
    middle = numbers.size() / 2;
    left = container(numbers.begin(), numbers.begin() + middle);
    right = container(numbers.begin() + middle, numbers.end());
    sort(left, std::random_access_iterator_tag());
    sort(right, std::random_access_iterator_tag());
    numbers = sort_insert(left, right);
  };

  template <class Iterator> void sort(container &numbers, Iterator) {
    container left;
    container right;
    iterator middle_it;
    size_type middle;

    if (numbers.size() < 2)
      return;
    middle = numbers.size() / 2;
    middle_it = numbers.begin();
    for (size_type i = 0; i < middle; i++)
      middle_it++;
    left = container(numbers.begin(), middle_it);
    right = container(middle_it, numbers.end());
    sort(left, Iterator());
    sort(right, Iterator());
    numbers = sort_insert(left, right);
  };

public:
  PmergeMe(void){};
  PmergeMe(PmergeMe const &copy) : _numbers(copy._numbers){};
  ~PmergeMe(void){};

  PmergeMe &operator=(PmergeMe const &copy) { _numbers = copy._numbers; };

  const_iterator begin(void) const { return _numbers.cbegin(); };
  const_iterator end(void) const { return _numbers.cend(); };
  void stream_numbers(std::ostream &stream,
                      std::string const &separator = " ") const {
    for (const_iterator it = begin(); it != end(); it++)
      stream << *it << separator;
  };
  void insert(value_type const &element) { _numbers.push_back(element); };
  void sort(void) {
    typename std::iterator_traits<iterator>::iterator_category cat;
    sort(_numbers, cat);
  };
};

#endif

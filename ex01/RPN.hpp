#ifndef CPP_09_EX01_RPN_HPP_
#define CPP_09_EX01_RPN_HPP_
#pragma once

#ifndef __CPP09_DEBUG_
#define __CPP09_DEBUG_ false
#endif

#include <stack>
#include <string>

/*
** class RPN
**  A simple Reverse Polish Notation calculator
**
** Usage:
**  RPN x();
**  x.calculate("995+/") => 0.642857
**
** Exception safety:
**  If the expression is not valid, std::invalid_argument is thrown
**  When an exception is thrown, a call to RPN#clear MUST be used or
**  consecutive calls will have the remnants of the previous expression
*/
class RPN {
public:
  typedef double number;

private:
  std::stack<number> _numbers;

  number process_expression(std::string::const_iterator begin,
                            std::string::const_iterator end);

public:
  RPN(void);
  RPN(RPN const &copy);
  ~RPN(void);

  RPN &operator=(RPN const &copy);

  number calculate(std::string const expression);
  void clear(void);
};

#endif

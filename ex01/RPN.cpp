#include "RPN.hpp"
#include <cctype>
#include <stack>
#include <stdexcept>

RPN::RPN(void){};
RPN::RPN(RPN const &copy) : _numbers(copy._numbers){};
RPN::~RPN(void){};

RPN &RPN::operator=(RPN const &copy) {
  _numbers = copy._numbers;
  return *this;
};

RPN::number RPN::process_expression(std::string::const_iterator begin,
                                    std::string::const_iterator end) {
  number first;
  number second;

  if (begin == end && _numbers.size() != 1)
    throw std::invalid_argument("final result is not one number");
  if (begin == end)
    return _numbers.top();
  if (std::isdigit(*begin))
    _numbers.push(*begin - '0');
  if (std::isspace(*begin) || std::isdigit(*begin))
    return process_expression(begin + 1, end);
  if (_numbers.size() < 2)
    throw std::invalid_argument("not enough numbers to operate");
  if (std::string("*/-+").find(std::string(1, *begin)) == std::string::npos)
    throw std::invalid_argument("token error");
  first = _numbers.top();
  _numbers.pop();
  second = _numbers.top();
  _numbers.pop();
  if (*begin == '-')
    _numbers.push(second - first);
  if (*begin == '+')
    _numbers.push(second + first);
  if (*begin == '*')
    _numbers.push(second * first);
  if (*begin == '/')
    _numbers.push(second / first);
  return process_expression(begin + 1, end);
};

RPN::number RPN::calculate(std::string const expression) {
  return process_expression(expression.cbegin(), expression.cend());
};

void RPN::clear(void) {
  while (!_numbers.empty())
    _numbers.pop();
}

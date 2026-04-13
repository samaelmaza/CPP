#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &src) : _stack(src._stack) {}

RPN &RPN::operator=(const RPN &rhs)
{
	if (this != &rhs)
		this->_stack = rhs._stack;
	return *this;
}

RPN::~RPN() {}

void RPN::evaluate(const std::string &expression)
{
	std::stringstream ss(expression);
	std::string token;

	while (ss >> token)
	{
		if (token.size() != 1)
			throw std::runtime_error("Error: invalid expression");
		if (isdigit(token[0]))
			_stack.push(token[0] - '0');
		else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Error: invalid expression");
			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			_stack.pop();
			if (token[0] == '+')
				_stack.push(a + b);
			else if (token[0] == '-')
				_stack.push(a - b);
			else if (token[0] == '*')
				_stack.push(a * b);
			else if (token[0] == '/')
			{
				if (b == 0)
					throw std::runtime_error("Error: division by zero");
				_stack.push(a / b);
			}
		}
		else
			throw std::runtime_error("Error: invalid expression");
	}
	if (_stack.size() != 1)
		throw std::runtime_error("Error");
	std::cout << _stack.top() << std::endl;
}

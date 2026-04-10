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
		else
			throw std::runtime_error("Error: invalid expression");
	}


	// TODO: Loop through each character of the expression
	// - Skip spaces
	// - If it's a digit (0-9): push it onto _stack
	// - If it's an operator (+, -, *, /):
	//     1. Check that _stack has at least 2 elements, otherwise error
	//     2. Pop the top 2 values (attention: first pop = second operand!)
	//     3. Perform the operation
	//     4. Push the result back onto _stack
	//     5. Don't forget: division by 0 = error
	// - Anything else = error
	//
	// After the loop: _stack should have exactly 1 element = the result
	// If more or less: error

	(void)expression; // remove this when you start
}

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>

class RPN
{
	private:
		std::stack<double> _stack;

	public:
		RPN();
		RPN(const RPN &src);
		RPN &operator=(const RPN &rhs);
		~RPN();

		// Evaluate an RPN expression and print the result
		void evaluate(const std::string &expression);
};

#endif

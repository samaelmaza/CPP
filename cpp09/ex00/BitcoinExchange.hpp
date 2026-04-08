#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

class BitcoinExchange
{
	private:
		// Map storing our Bitcoin database. Key = YYYY-MM-DD, Value = Exchange rate
		std::map<std::string, double> _db;

		bool	isValidDate(const std::string &date) const;
		bool	isValidValue(const std::string &valueStr, double &value) const;
		double	getExchangeRate(const std::string &date) const;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange &operator=(const BitcoinExchange &rhs);
		~BitcoinExchange();

		// Load the database (data.csv)
		void	loadDatabase(const std::string &filename);

		// Process the user's input file
		void	processInput(const std::string &filename);
};

#endif

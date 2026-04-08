#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) : _db(src._db) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	if (this != &rhs)
		this->_db = rhs._db;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// TODO: Load the CSV database
void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database file.");

	std::string line;
	// TODO: Read the first line to skip the header ("date,exchange_rate")
	// TODO: Read the file line by line
	// TODO: Split the line using the comma ',' delimiter
	// TODO: Convert the second part to a double using std::strtod or atof
	// TODO: Store it in _db using _db[date] = value;
	
	file.close();
}

// TODO: Process the input file
void BitcoinExchange::processInput(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	// Skip the header part ("date | value")
	std::getline(file, line);

	while (std::getline(file, line))
	{
		// TODO: Split the line using the " | " delimiter
		// Check that the delimiter exists
		size_t pos = line.find(" | ");
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, pos);
		std::string valueStr = line.substr(pos + 3);

		// TODO: Implement isValidDate
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		double value;
		// TODO: Implement isValidValue (value must be >= 0 and <= 1000)
		if (!isValidValue(valueStr, value))
			continue; // isValidValue will print exactly what error happened

		// TODO: Fetch the correct exchange rate using getExchangeRate()
		double rate = getExchangeRate(date);
		std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
	}
	file.close();
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	// TODO: Check if date format is strictly YYYY-MM-DD
	// - Validate year, month (1-12) and days (1-31)
	return true; // replace this
}

bool BitcoinExchange::isValidValue(const std::string &valueStr, double &value) const
{
	// TODO: Convert valueStr to double
	// - If it's not a valid number or negative: std::cerr << "Error: not a positive number.\n"; return false;
	// - If it's > 1000: std::cerr << "Error: too large a number.\n"; return false;
	
	// Example logic:
	value = std::strtod(valueStr.c_str(), NULL);
	return true; // replace this
}

double BitcoinExchange::getExchangeRate(const std::string &date) const
{
	// TODO: Use _db.lower_bound(date) to find the closest date.
	// 1. If lower_bound returns exactly the date we want, return its value.
	// 2. If it returns the beginning of the map (and not the exact date), the date is older than our database! Return 0 or closest.
	// 3. Otherwise, because lower_bound returns the first element that is NOT LESS than the date, 
	//    you must decrement the iterator (it--) to get the closest date IN THE PAST.

	return 0.0; // replace this
}

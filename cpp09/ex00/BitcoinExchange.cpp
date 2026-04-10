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
	std::getline(file, line);
	while (std::getline(file, line))
	{
		size_t pos = line.find(',');
		if (pos == std::string::npos)
			continue;
		std::string date = line.substr(0, pos);
		std::string valueStr = line.substr(pos + 1);
		double value = std::strtod(valueStr.c_str(), NULL);
		_db[date] = value;
	}
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
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date[i]))
			return false;
	}
	std::string year = date.substr(0, 4);
	std::string month = date.substr(5, 2);
	std::string day = date.substr(8, 2);
	if (year.length() != 4 || month.length() != 2 || day.length() != 2)
		return false;
	int y = std::atoi(year.c_str());
	int m = std::atoi(month.c_str());
	int d = std::atoi(day.c_str());
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
		daysInMonth[1] = 29;
	if (y < 1 || m < 1 || m > 12 || d < 1)
		return false;
	if (d > daysInMonth[m - 1])
		return false;
	return true;
}

bool BitcoinExchange::isValidValue(const std::string &valueStr, double &value) const
{
	// TODO: Convert valueStr to double
	// - If it's not a valid number or negative: std::cerr << "Error: not a positive number.\n"; return false;
	// - If it's > 1000: std::cerr << "Error: too large a number.\n"; return false;

	// Example logic:
	char *endptr;
	value = std::strtod(valueStr.c_str(), &endptr);
	if (endptr == valueStr.c_str() || *endptr != '\0')
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (value < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (value > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
}

double BitcoinExchange::getExchangeRate(const std::string &date) const
{
	// TODO: Use _db.lower_bound(date) to find the closest date.
	// 1. If lower_bound returns exactly the date we want, return its value.
	// 2. If it returns the beginning of the map (and not the exact date), the date is older than our database! Return 0 or closest.
	// 3. Otherwise, because lower_bound returns the first element that is NOT LESS than the date,
	//    you must decrement the iterator (it--) to get the closest date IN THE PAST.
	std::map<std::string, double>::const_iterator it = _db.lower_bound(date);
	if (it != _db.end()	 && it->first == date)
		return it->second;
	if (it == _db.begin())
		return 0.0;
	--it;
	return it->second;
}

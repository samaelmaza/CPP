#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		std::cerr << "Usage: ./btc <input.txt>" << std::endl;
		return 1;
	}

	try
	{
		BitcoinExchange btc;
		
		// 1. Load the database into our std::map
		btc.loadDatabase("data.csv");
		
		// 2. Evaluate the user's input with the database
		btc.processInput(argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

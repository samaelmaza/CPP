#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
	if(argc != 4)
		return 1;
	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];
	if(s1.empty())
		return 1;
	std::ifstream infile(filename.c_str());
	if(!infile.is_open())
	{
		std::cerr << "Error: cannot open the file" << std::endl;
		return 1;
	}
	std::ofstream outfile((filename + ".replace").c_str());
	std::string line;
	while(std::getline(infile, line))
	{
		std::string result;
		size_t pos = 0;
		size_t found = line.find(s1, pos);
		while(found != std::string::npos)
		{
			result += line.substr(pos, found - pos);
			result += s2;
			pos = found + s1.length();
			found = line.find(s1, pos);
		}
		result += line.substr(pos);
		outfile << result << std::endl;
	}
	return 0;
}

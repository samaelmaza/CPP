#include <iostream>
#include <cctype>


int	main(int ac, char **av)
{
	if(ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	int i = 1;
	while(i < ac)
	{
		int j = 0;
		while(av[i][j])
		{
			std::cout << char(std::toupper(av[i][j]));
			j++;
		}
		if(av[i + 1])
			std::cout << " ";
		i++;
	}
	std::cout << std::endl;
	return (0);
}

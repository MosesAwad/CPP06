
#include <sstream>
#include <iostream>
#include <exception>

int main()
{
	std::cout << "--------------- MAIN 1 ---------------" << std::endl;
	{
		std::stringstream	sso;
		std::string			target = "125454x";
		int					int_result;
		
		sso << target;
		sso >> int_result;

		/*
			sso.fail(): This checks if the stream operation failed, 
			which can occur if the input value is out of range for 
			int or if there was an invalid input.
			
			!sso.eof(): This checks if the entire input string was 
			successfully processed. If there are remaining characters 
			in the stream after attempting to extract the integer, it 
			indicates an issue with the conversion.
		*/
		if (sso.fail() || !sso.eof()) {
			std::cerr << "Value not representable as int" << std::endl;
		}
		else {
			std::cout << "Int -> " << int_result << std::endl;
		}
	}

	std::cout << "--------------- MAIN 2 ---------------" << std::endl;
	{
		float lol = 98.2;

		std::cout << "In char form -> " << static_cast<char>(lol) << std::endl;
	}
	return (0);
}

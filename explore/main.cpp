
#include <sstream>
#include <iostream>
#include <exception>
#include <iomanip>

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

	std::cout << "\n";

	std::cout << "--------------- MAIN 2 ---------------" << std::endl;
	{
		float lol = 98.2;

		std::cout << "In char form -> " << static_cast<char>(lol) << std::endl;
	}

	std::cout << "\n";

	std::cout << "--------------- MAIN 3 ---------------" << std::endl;
	{
		float lol = 2147483650.0f;

		std::cout << "In int form -> " << static_cast<int>(lol) << std::endl;
	}

	std::cout << "\n";

	std::cout << "--------------- MAIN 4 ---------------" << std::endl;
	/*
		The difference in outputs is due to precision losz in floats compared to doubles:
			
			Floats:
				When you assign 2147483647.0 (which is 2^31 - 1, the maximum value for 
				a 32-bit signed integer) to a float, the precision loss occurs because a
				float cannot exactly represent this value due to its limited precision.
			
			Doubles:
				On the other hand, a double can represent 2147483647.0 exactly because of
				its higher precision.
	*/
	{
		float 	lol = 2147483647.0;
		double	lol2 = 2147483647.0;
		std::cout << "In int form -> " << static_cast<int>(lol) << std::endl;
		std::cout << "In int form -> " << static_cast<int>(lol2) << std::endl;
	
		std::cout << "\n";

		int 	lol3 = 2147483647;
		std::cout << "In float form -> " << static_cast<float>(lol3) << std::endl;
		std::cout << "In double form -> " << static_cast<double>(lol3) << std::endl;

		double	lol4 =  214748.12 ;
		std::cout << "In float form -> " << static_cast<float>(lol4) << std::endl;
		std::cout << "In double form -> " << lol4 << std::endl;

		double	lol5 =  2147483;
		std::cout << "In ~float form -> " << lol5 << std::endl;
		std::cout << "In ~double form -> " << static_cast<double>(lol5) << std::endl;

		/*
			For a double, std::cout will generally switch to scientific notation when the 
			number of digits before the decimal point exceeds 6, or if the number is smaller 
			than 1e-6 or larger than 1e+6.
		*/
		double lol6 = 123456.89;
		double lol7 = 1234567.89;
		std::cout << "In float form -> " << lol6 << std::endl;
		std::cout << "In double form -> " << static_cast<double>(lol6) << std::endl;

		std::cout << "In float form -> " << lol7 << std::endl;
		std::cout << "In double form -> " << static_cast<double>(lol7) << std::endl;

		double lol8 = 214748.47;
		std::cout << "In double form -> " << std::fixed << std::setprecision(1) << static_cast<float>(lol8) << std::endl;
		std::cout << "In double form -> " << std::fixed << std::setprecision(1) << static_cast<double>(lol8) << std::endl;

	}
	return (0);
}

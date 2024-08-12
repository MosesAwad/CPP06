
# include "Serializer.hpp"

int main()
{
	Data		sample;
	uintptr_t	raw;

	std::cout << std::endl;
	std::cout << "--------------------------------------------------------------------" << std::endl;
	std::cout << "Serializing the address of the struct in decimal form and storing it" << std::endl;
	std::cout << "--------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	raw = Serializer::serialize(&sample);
	std::cout << "Serialized address of the struct is -> " << raw << " (" << &sample << ")\n" << std::endl;

	std::cout << "----------------------------------------------" << std::endl;
	std::cout << "Directly assigning a grade of 92 to the struct" << std::endl;
	std::cout << "----------------------------------------------" << std::endl;
	sample.grade = 92;
	std::cout << std::endl;

	std::cout << "------------------------------------------------------------------------------" << std::endl;
	std::cout << "Deserializing the raw stored address of the struct to a pointer of that struct" << std::endl;
	std::cout << "------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	Data*	address = Serializer::deserialize(raw);
	std::cout << "Dereferencing grade on the pointer to the deserialized stored address -> " << address->grade << std::endl;
	std::cout << std::endl;

	std::cout << "The grade matches and thus, the serialization and deserialization processes on the struct's address were successful" << std::endl;
	std::cout << std::endl;

	return (0);
}

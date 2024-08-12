
# include "Serializer.hpp"

int main()
{
	Data		sample;
	uintptr_t	raw;

	sample.grade = 69;

	raw = Serializer::serialize(&sample);
	std::cout << "Result is -> " << raw << std::endl;
	
	Data*	address = Serializer::deserialize(raw);
	std::cout << "Result is -> " << address->grade << std::endl;
}

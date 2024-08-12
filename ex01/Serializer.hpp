
#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

#include <cstdint>
#include <iterator>
#include <string>
#include <iostream>

typedef struct Data
{
	int			grade;
	std::string	name;
	long		student_id;
} Data;

class Serializer
{
	private:
		Serializer();
		Serializer(const Serializer& other);
		Serializer&	operator=(const Serializer& other);
		~Serializer();
	public:
		static uintptr_t	serialize(Data *ptr);
		static Data*		deserialize(uintptr_t raw);
};

#endif

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base() {};

Base*	generate(void)
{
	srand(static_cast<unsigned>(time(0)));

	int	choice = std::rand() % 3;

	switch (choice) {
		case (0):
			return (new A());

		case (1):
			return (new B());

		case (2):
			return (new C());
	}
	return (NULL);
}

void	identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "Object is of class A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "Object is of class B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "Object is of class C" << std::endl;
};

void	identify(Base& p)
{
	try
	{
		A& ref = dynamic_cast<A&>(p);
		(void) ref;
		return (std::cout << "Object is of class A" << std::endl, void());
	}
	catch (const std::bad_cast& e) {
	}

	try
	{
		B& ref = dynamic_cast<B&>(p);
		(void) ref;
		return (std::cout << "Object is of class B" << std::endl, void());
	}
	catch(const std::bad_cast& e) {
	}

	try
	{
		C& ref = dynamic_cast<C&>(p);
		(void) ref;
		return (std::cout << "Object is of class C" << std::endl, void());
	}
	catch(const std::bad_cast& e) {
	}
};

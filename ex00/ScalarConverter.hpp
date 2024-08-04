
#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <iostream>
#include <string>

class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter& other);
        ScalarConverter& operator=(const ScalarConverter& other);
    public:
        ~ScalarConverter();
        static void convert(const std::string& target);
        
        static int  char_version;
        static int  int_version;
        static int  float_version;
        static int  double_version;

        static bool char_overflow;
        static bool int_overflow;
        static bool float_overflow;
        static bool double_overflow;

        static const int    MAX_INT;
        static const int    MIN_INT;
        static const float  MAX_FLOAT;
        static const float  MIN_FLOAT;
        static const double MAX_DOUBLE;
        static const double MIN_DOUBLE;
        static const char   MAX_CHAR;
        static const char   MIN_CHAR;

        static bool    check_int(const std::string& target);
        static bool    check_float(const std::string& target);

        static t_type  get_type(const std::string& target);
};

typedef enum e_type
{
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
    OTHER
} t_type;

#endif
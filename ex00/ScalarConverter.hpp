
#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <limits>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>

typedef enum e_type
{
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
    OTHER
} t_type;

class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter& other);
        ScalarConverter& operator=(const ScalarConverter& other);
    public:
        ~ScalarConverter();

        static char     char_version;
        static int      int_version;
        static float    float_version;
        static double   double_version;

        static bool char_overflow;
        static bool int_overflow;
        static bool float_overflow;
        static bool double_overflow;
        static bool scientific_notation;

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
        static bool    check_double(const std::string& target);
        static bool    check_char(const std::string& target);

        static void     printer();
        static bool     check_pseudo(const std::string& target);
        static t_type   get_type(const std::string& target);
        static void     convert(const std::string& target);
};

#endif

#include "ScalarConverter.hpp"
#include <cctype>
#include <cstdlib>
#include <limits>

const int ScalarConverter::MAX_INT = std::numeric_limits<int>::max();
const int ScalarConverter::MIN_INT = std::numeric_limits<int>::min();
const float ScalarConverter::MAX_FLOAT = std::numeric_limits<float>::max();
const float ScalarConverter::MIN_FLOAT = std::numeric_limits<float>::min();
const double ScalarConverter::MAX_DOUBLE = std::numeric_limits<double>::max();
const double ScalarConverter::MIN_DOUBLE = std::numeric_limits<double>::min();
const char ScalarConverter::MAX_CHAR = std::numeric_limits<char>::max();    // gives a value of -128
const char ScalarConverter::MIN_CHAR = std::numeric_limits<char>::min();    // gives a value of 127

bool ScalarConverter::char_overflow = false;
bool ScalarConverter::int_overflow = false;
bool ScalarConverter::float_overflow = false;
bool ScalarConverter::double_overflow = false;

bool    ScalarConverter::check_int(const std::string& target)
{
    char    *endptr;
    long    result;

    result = strtol(target.c_str(), &endptr, 10);
    if (*endptr != '\0')
        return (false);
    // if (*target.c_str() == *endptr)
    //     return (false);
    if (result > MAX_INT || result < MIN_INT)
    {
        int_overflow = true;
        return (false);
    }

    int_version = static_cast<int>(result);
    if (int_version > MAX_CHAR || int_version < MIN_CHAR)
        char_overflow = true;
    return (true);
}

/*
    Use strtod and not strtof so we can capture overflow and
    be able to check if the target_string when converted exceeds
    the limits of float or not. Just like how a long number is
    required to check if MAX_INT or MIN_INT are exceeded.
*/
bool ScalarConverter::check_float(const std::string& target)
{
    char    *endptr;
    double  result;

    result = strtod(target.c_str(), &endptr);
    if (!(*endptr == 'f' && (*(endptr + 1) == '\0')))
        return (false);
    if (result > MAX_FLOAT || result < MIN_FLOAT)
        return (float_overflow = 1, false);

    if (result > MAX_INT || result < MIN_INT)
        int_overflow = 1;
    if (result > MAX_CHAR || result < MIN_CHAR)
        char_overflow = 1;

    float_version = static_cast<float>(result);
    int_version = static_cast<int>(result);
    return (true);
}

t_type ScalarConverter::get_type(const std::string& target)
{
    if (check_int(target) == true)
        return (INT);
}

void ScalarConverter::convert(const std::string& target)
{
    t_type type;

    type = get_type(target);
}

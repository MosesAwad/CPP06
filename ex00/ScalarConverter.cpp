
#include "ScalarConverter.hpp"


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

char     ScalarConverter::char_version;
int     ScalarConverter::int_version;
float   ScalarConverter::float_version;
double  ScalarConverter::double_version;

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


    if (int_version > MAX_CHAR || int_version < MIN_CHAR)
        char_overflow = true;
    if (result > CHAR_MAX || result < CHAR_MIN)
        char_overflow = true;

    double_version = static_cast<double>(result);
    float_version = static_cast<float>(result);
    int_version = static_cast<int>(result);

    char_version = static_cast<char>(result);
        
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
        return (float_overflow = true, false);
    if (result > MAX_INT || result < MIN_INT)
        int_overflow = true;
    if (result > MAX_CHAR || result < MIN_CHAR)
        char_overflow = true;

    double_version = static_cast<double>(result);
    float_version = static_cast<float>(result);
    int_version = static_cast<int>(result);

    char_version = static_cast<char>(result);
    return (true);
}

bool ScalarConverter::check_double(const std::string& target)
{
    char    *endptr;
    double  result;

    result = strtod(target.c_str(), &endptr);
    if (*endptr != '\0')
        return (false);
    if (errno == ERANGE)
        return (double_overflow = true, false);
    if (result > MAX_FLOAT || result < MIN_FLOAT)
        float_overflow = true;
    if (result > MAX_INT || result < MIN_INT)
        int_overflow = true;
    if (result > CHAR_MAX || result < CHAR_MIN)
        char_overflow = true;
    
    double_version = static_cast<double>(result);
    float_version = static_cast<float>(result);
    int_version = static_cast<int>(result);

    char_version = static_cast<char>(result);
    return (true);
}

bool ScalarConverter::check_char(const std::string& target)
{
    if (target.size() != 1)
        return (false);

    std::stringstream   sso;
    char                result;
    sso << target;
    sso >> result;

    if (sso.fail())
        return (false);

    /*
        No need to check for the following condition:
            
            if (result > CHAR_MAX || result < CHAR_MIN)
                char_overflow = true;
    
        Because if result is greater than or less than
        CHAR_MAX or CHAR_MIN, the check_int would be the 
        one to catch it anyways.
    */

    double_version = static_cast<double>(result);
    float_version = static_cast<float>(result);
    int_version = static_cast<int>(result);
    char_version = static_cast<char>(result);
    return (true);
}

t_type ScalarConverter::get_type(const std::string& target)
{
    if (check_int(target) == true)
        return (INT);
    if (check_double(target))
        return (DOUBLE);
    if (check_float(target))
        return (FLOAT);
    if (check_char(target))
        return (CHAR);
    return (OTHER);
}

void ScalarConverter::printer()
{
    std::cout << "char: ";
    if (char_overflow)
        std::cout << "impossible" << std::endl;
    else if (std::isprint(char_version) == false)
        std::cout << "not displayable" << std::endl;
    else
        std::cout << char_version << std::endl;

    std::cout << "int: ";
    if (int_overflow)
        std::cout << "impossible" << std::endl;
    else
        std::cout << int_version << std::endl;

    /*
        For floats and doubles, we set the precision to 1 because 
        By default, std::cout does not preserve trailing zeroes 
        in floating-point numbers, so if target is 98.0000 it will 
        print 98 instead of 98.0000; so to fix this issue, we have 
        to set the precision ourselves in order to let std::cout 
        display those trailing zeroes. But, the subject pdf shows 
        only one trailing zero after the decimal, so we deduce that 
        the precision they require of us is just 1.
    */    
    std::cout << "float: ";
    if (float_overflow)
        std::cout << "impossible" << std::endl;
    else
        std::cout << std::fixed << std::setprecision(1) << float_version << std::endl;

    std::cout << "double: "; 
    if (double_overflow)
        std::cout << "impossible" << std::endl;
    else
        std::cout << std::fixed << std::setprecision(1) << double_version << std::endl;
}

void ScalarConverter::convert(const std::string& target)
{
    t_type type;

    type = get_type(target);
    if (type != OTHER)
        printer();
    else
        std::cerr << "Entry does not match any of the following literals:"
            " char, int, float, double" << std::endl;
}

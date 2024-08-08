
#include "ScalarConverter.hpp"

/*
                    --------------------------
            ------ STATIC VARIABLE DECLARATIONS ------
                    --------------------------
*/
const int ScalarConverter::MAX_INT = std::numeric_limits<int>::max();
const int ScalarConverter::MIN_INT = std::numeric_limits<int>::min();
const float ScalarConverter::MAX_FLOAT = std::numeric_limits<float>::max();
const float ScalarConverter::MIN_FLOAT = -1 * std::numeric_limits<float>::max();
const double ScalarConverter::MAX_DOUBLE = std::numeric_limits<double>::max();
const double ScalarConverter::MIN_DOUBLE = -1 * std::numeric_limits<double>::min();
const char ScalarConverter::MAX_CHAR = std::numeric_limits<char>::max();    // gives a value of -128
const char ScalarConverter::MIN_CHAR = std::numeric_limits<char>::min();    // gives a value of 127

bool ScalarConverter::char_overflow = false;
bool ScalarConverter::int_overflow = false;
bool ScalarConverter::float_overflow = false;
bool ScalarConverter::double_overflow = false;
bool ScalarConverter::scientific_notation = false;

char    ScalarConverter::char_version;
int     ScalarConverter::int_version;
float   ScalarConverter::float_version;
double  ScalarConverter::double_version;

/*
                    ---------------
            ------ CHECKER FUNCTIONS ------ 
                    ---------------
*/
bool    ScalarConverter::check_int(const std::string& target)
{
    char    *endptr;
    long    result;

    result = strtol(target.c_str(), &endptr, 10);
    if (*endptr != '\0')
        return (false);
    if (target.size() > 6)
        scientific_notation = true;
    if (result > MAX_INT || result < MIN_INT)
    {
        int_overflow = true;
        return (false);
    }

    if (int_version > MAX_CHAR || int_version < MIN_CHAR)
        char_overflow = true;
    if (result > CHAR_MAX || result < CHAR_MIN)
        char_overflow = true;

    int_version = static_cast<int>(result);
    float_version = static_cast<float>(int_version);
    double_version = static_cast<double>(int_version);
    char_version = static_cast<char>(int_version);

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
    if (check_pseudo(target))
        return (true);
    if (result > MAX_FLOAT || result < MIN_FLOAT)
        return (float_overflow = true, false);
    if (result > MAX_INT || result < MIN_INT)
        int_overflow = true;
    if (result > MAX_CHAR || result < MIN_CHAR)
        char_overflow = true;

    size_t  dec_pos = target.find('.');
    if (dec_pos > 6 || (target.find('e') != std::string::npos))
        scientific_notation = true;

    float_version = static_cast<float>(result);
    double_version = static_cast<double>(result);
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
    if (check_pseudo(target))
        return (true);
    if (result == HUGE_VAL || result == -HUGE_VAL)
        return (double_overflow = true, false);
    if (result > MAX_FLOAT || result < MIN_FLOAT)
        float_overflow = true;
    if (result > MAX_INT || result < MIN_INT)
        int_overflow = true;
    if (result > CHAR_MAX || result < CHAR_MIN)
        char_overflow = true;

    size_t  dec_pos = target.find('.');
    /*
        This if (dec_pos == std::string::npos) statement is what also lets 
        me parse the target string to check whether an "int" that has exceeded 
        MAX_INT or MIN_INT has been inputted.

        That is because technically a double always has to have a decimal 
        in it to distinguish it from an int or a long. Meanwhile a float 
        would only be cast as a float from the target string if an 'f' has 
        been inputted at its end. So,
            21474836478 -> rejected (not an int, float, or a double)
            21474836478f -> accepted (a float)
            21474836478. or 21474836478.0 -> accepted (a double)
    */
    if (dec_pos > 6 || (target.find('e') != std::string::npos))
        scientific_notation = true;
    if (dec_pos == std::string::npos)
        return (false);
    std::cout << "Value -> " << dec_pos << std::endl;
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

    char_version = static_cast<char>(result);
    float_version = static_cast<float>(result);
    double_version = static_cast<double>(result);
    int_version = static_cast<int>(result);
    return (true);
}

bool    ScalarConverter::check_pseudo(const std::string& target)
{
    std::string array[8] = { "inf", "inff", "+inf",  "+inff", 
        "-inf", "-inff", "nan", "nanf"
        };

    size_t i = 0;
    int case_flag = 0;

    while (i < sizeof(array) / sizeof(array[0]))
    {
        if (target == array[i])
            break ;
        i++;
    }

    if (i >= 0 && i < 4)
        case_flag = 0;
    else if (i >= 4 && i < 6)
        case_flag = 1;
    else if (i >= 6 && i < 8)
        case_flag = 2;
    else
        return (false);

    int_overflow = true;
    char_overflow = true;

    float_overflow = false;
    double_overflow = false;
    
    switch (case_flag)
    {
        case 0:
            float_version = std::numeric_limits<float>::infinity();
            double_version = std::numeric_limits<double>::infinity();
            break ;
        case 1:
            float_version = -1 * std::numeric_limits<float>::infinity();
            double_version = -1 * std::numeric_limits<double>::infinity();
            break ;
        case 2:
            float_version = std::numeric_limits<float>::quiet_NaN();
            double_version = std::numeric_limits<double>::quiet_NaN();
            break ;
    }
    return (true);
}

/*
                    ---------------
            ------ PRINTER FUNCTION ------
                    ---------------

    For floats and doubles, we set the precision to 1 because 
    By default, std::cout does not preserve trailing zeroes 
    in floating-point numbers, so if target is 98.0000 it will 
    print 98 instead of 98.0000; so to fix this issue, we have 
    to set the precision ourselves in order to let std::cout 
    display those trailing zeroes. But, the subject pdf shows 
    only one trailing zero after the decimal, so we deduce that 
    the precision they require of us is just 1.

    But I do that in the following condition:
        else if (float_version == static_cast<int>(float_version))
    
    The reason is because if I only had:
        if (double_overflow)
                std::cout << "impossible" << std::endl;
        else
            std::cout << std::fixed << std::setprecision(1) << double_version << std::endl;
    
    Then if I had something like:
        ./convert 184845151555512
    
    Then the output would be:
        char: impossible
        int: impossible
        float: 184845151555512.0
        double: 184845151555512.0
    instead of:
        char: impossible
        int: impossible
        float: 1.84845e+14
        double: 1.84845e+14
    
    So basically, I only want it to set the precision to 1 when I do something
    ./convert 98 or ./convert 98.0000
    and in these scenarios float_version == static_cast<int>(float_version) would 
    be true. 

    But in a case like ./convert 184845151555512, i want the answer in scientific
    notation and 184845151555512 is larger than MAX_INT anyways so the line
    static_cast<int>(float_version)) would default to -2147483648 automatically 
    whenever a we cast from a float value that is larger than int max to the 
    int type. Then since, 184845151555512 != -2147483648, it would automatically 
    give us the desired output which is scientific notation display.
*/
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
 
    std::cout << "float: ";
    if (float_overflow)
        std::cout << "impossible" << std::endl;
    else if (scientific_notation == false)
        std::cout << std::fixed << std::setprecision(1) << float_version << "f" << std::endl;
    else
        std::cout << float_version << "f" << std::endl;

    std::cout << "double: "; 
    if (double_overflow)
        std::cout << "impossible" << std::endl;
    else if (scientific_notation == false)
        std::cout << std::fixed << std::setprecision(1) << double_version << std::endl;
    else
        std::cout << double_version << std::endl;
}

/*
                   ----------
           ------ TYPE GETTER ------
                   ----------
*/
t_type ScalarConverter::get_type(const std::string& target)
{
    if (check_int(target) == true)
        return (INT);
    if (check_float(target))
        return (FLOAT);
    if (check_double(target))
        return (DOUBLE);
    if (check_char(target))
        return (CHAR);
    return (OTHER);
}

/*
                    --------------
            ------ CONVERT FUNCTION ------
                    --------------
*/
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

/*
                    ---------------------
            ------ ORTHODOX CANONICAL FORM ------
                    ---------------------
*/
ScalarConverter::ScalarConverter() {};

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
    *this = other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
    (void) other;
    return (*this);
}

ScalarConverter::~ScalarConverter() {};
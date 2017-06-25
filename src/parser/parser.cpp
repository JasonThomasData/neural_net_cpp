#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "parser.h"

Parser::Parser(){};

int Parser::to_int(std::string to_convert)
{
    try
    {
        int result = stoi(to_convert);
        return result;
    } catch (...)
    {
        std::string error_message = "Your file contains information that is not alpha-numeric. Check to_int + " + to_convert;
        throw std::invalid_argument(error_message);
    }
}
/*These look very similar, as are the functions below. Is there a way to combine them?*/
double Parser::to_double(std::string to_convert)
{
    try
    {
        double result = stod(to_convert);
        return result;
    } catch (...)
    {
        std::string error_message = "Your file contains information that is not alpha-numeric. Check to_double + " + to_convert;
        throw std::invalid_argument(error_message);
    }
}

std::vector<std::string> Parser::string_vector(std::string number_string)
{
    std::istringstream iss(number_string);
    std::string to_add;
    char delimiter = ',';

    std::vector<std::string> string_list;
    while(std::getline(iss, to_add, delimiter))
    {
        string_list.emplace_back(to_add);
    }
    return string_list;
}

std::vector<int> Parser::string_vector_int_vector(std::vector<std::string> string_list)
{
    std::vector<int> int_list;

    for(auto& string: string_list)
    {
        int to_add = to_int(string);
        int_list.emplace_back(to_add);
    }
    return int_list;
}
/*Same as above*/
std::vector<double> Parser::string_vector_double_vector(std::vector<std::string> string_list)
{
    std::vector<double> double_list;

    for(auto& string: string_list)
    {
        double to_add = to_double(string);
        double_list.emplace_back(to_add);
    }
    return double_list;
}

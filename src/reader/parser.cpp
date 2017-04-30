#include <string>
#include <sstream>
#include <vector>
#include "parser.h"

Parser::Parser(){};

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
        int to_add = stoi(string);
        int_list.emplace_back(to_add);
    }
    return int_list;
}

std::vector<double> Parser::string_vector_double_vector(std::vector<std::string> string_list)
{
    std::vector<double> double_list;

    for(auto& string: string_list)
    {
        double to_add = stod(string);
        double_list.emplace_back(to_add);
    }
    return double_list;
}

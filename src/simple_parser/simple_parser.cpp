#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iterator>
#include "simple_parser.h"


int SimpleParser::to_int(std::string to_convert)
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
double SimpleParser::to_double(std::string to_convert)
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

std::vector<std::string> SimpleParser::string_vector(std::string number_string)
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

std::vector<int> SimpleParser::string_vector_int_vector(std::vector<std::string> string_list)
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
std::vector<double> SimpleParser::string_vector_double_vector(std::vector<std::string> string_list)
{
    std::vector<double> double_list;

    for(auto& string: string_list)
    {
        double to_add = to_double(string);
        double_list.emplace_back(to_add);
    }
    return double_list;
}

std::vector<int> SimpleParser::int_to_one_hot_vector_set_size(int int_value, int vector_size)
{
    std::vector<int> int_vector;
    //Start loop at one, because a zero input will be a one_hot vector of zeros
    for(int i = 1; i <= vector_size; i++)
    {
        if (i == int_value)
        {
            int_vector.emplace(int_vector.begin(), 1);
        }
        else
        {
            int_vector.emplace(int_vector.begin(), 0);
        }
    }
    return int_vector;
}

std::vector<int> SimpleParser::int_vector_one_hot_vector_set_size(std::vector<int> int_list, std::vector<int> vector_sizes)
{
    std::vector<int> int_outputs;
    int int_list_size = int_list.size();

    for(int i = 0; i < int_list_size; i++)
    {
        std::vector<int> vector_to_append = SimpleParser::int_to_one_hot_vector_set_size(int_list.at(i), vector_sizes.at(i));
        int_outputs.insert(int_outputs.end(), vector_to_append.begin(), vector_to_append.end());
    }
    return int_outputs;
}

std::string SimpleParser::int_vector_to_string(std::vector<int> vector_of_ints)
{
    std::stringstream ss;
    std::copy(vector_of_ints.begin(), vector_of_ints.end(), std::ostream_iterator<int>(ss, ","));
    std::string string = ss.str();
    std::string string_sans_last_comma = string.substr(0, string.size()-1);
    return string_sans_last_comma;
}

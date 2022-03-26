#include <vector>

namespace SimpleParser
{
    int to_int(std::string to_convert);
    double to_double(std::string to_convert);
    std::vector<std::string> string_vector(std::string number_string);
    std::vector<int> string_vector_int_vector(std::vector<std::string> parse_string_list);
    std::vector<double> string_vector_double_vector(std::vector<std::string> parse_string_list);
    std::vector<int> int_to_one_hot_vector_set_size(int int_value, int vector_size);
    std::vector<int> int_vector_one_hot_vector_set_size(std::vector<int> int_list, std::vector<int> vector_sizes);
    std::string int_vector_to_string(std::vector<int> vector_of_ints);
};

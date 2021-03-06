#include <vector>

namespace SimpleParser
{
    int to_int(std::string to_convert);
    double to_double(std::string to_convert);
    std::vector<std::string> string_vector(std::string number_string);
    std::vector<int> string_vector_int_vector(std::vector<std::string> parse_string_list);
    std::vector<double> string_vector_double_vector(std::vector<std::string> parse_string_list);
};

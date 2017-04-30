#ifndef Parser_h
#define Parser_h

/* Responsible for parsing raw strings from files into more useful formats.
 */

class Parser
{
    public:
        std::vector<std::string> string_vector(std::string number_string);
        std::vector<int> string_vector_int_vector(std::vector<std::string> parse_string_list);
        std::vector<double> string_vector_double_vector(std::vector<std::string> parse_string_list);
        Parser();
};

#endif

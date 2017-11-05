#ifndef SimpleParser_h
#define SimpleParser_h

/* Responsible for parsing raw strings from files into more useful formats.
 */

class SimpleParser
{
    private:
        SimpleParser();
    public:
        static int to_int(std::string to_convert);
        static double to_double(std::string to_convert);
        static std::vector<std::string> string_vector(std::string number_string);
        static std::vector<int> string_vector_int_vector(std::vector<std::string> parse_string_list);
        static std::vector<double> string_vector_double_vector(std::vector<std::string> parse_string_list);
};

#endif

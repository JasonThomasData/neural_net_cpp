#include <vector>
#include <iostream>
#include "../../lib/catch.h"
#include "../../src/simple_parser/simple_parser.h"

TEST_CASE( "SimpleParser - unit test - test a string is parsed to a vector")
{
    std::string str_to_parse = "2,2,1";

    std::vector<std::string> parsed_vector = SimpleParser::string_vector(str_to_parse);

    int expected_result_1 = 3;
    int actual_result_1 = parsed_vector.size();
    REQUIRE(actual_result_1 == expected_result_1);

    std::string expected_result_2 = "2";
    std::string actual_result_2 = parsed_vector.at(1);
    REQUIRE(actual_result_2 == expected_result_2);
}

TEST_CASE( "SimpleParser - unit test - vector of strings is parsed to a vector of ints")
{
    std::vector<std::string> vector_to_parse {"4","10","4"};

    std::vector<int> parsed_vector = SimpleParser::string_vector_int_vector(vector_to_parse);

    int expected_result_1 = 3;
    int actual_result_1 = parsed_vector.size();
    REQUIRE(actual_result_1 == expected_result_1);

    int expected_result_2 = 4;
    int actual_result_2 = parsed_vector.at(2);
    REQUIRE(actual_result_2 == expected_result_2);
}

TEST_CASE( "SimpleParser - unit test - vector of strings is parsed to a vector of doubles")
{
    std::vector<std::string> vector_to_parse {"3","2","2","2"};

    std::vector<double> parsed_vector = SimpleParser::string_vector_double_vector(vector_to_parse);

    int expected_result_1 = 4;
    int actual_result_1 = parsed_vector.size();
    REQUIRE(actual_result_1 == expected_result_1);

    double expected_result_2 = 2.0;
    double actual_result_2 = parsed_vector.at(3);
    REQUIRE(actual_result_2 == expected_result_2);
}

TEST_CASE( "parser - unit test - string to int, double, throws error")
{
    std::string int_string = "A.";
    std::string double_string = "@";

    REQUIRE_THROWS( SimpleParser::to_int(int_string) );
    REQUIRE_THROWS( SimpleParser::to_double(double_string) );
}


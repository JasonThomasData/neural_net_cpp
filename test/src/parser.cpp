#include "../catch.h"
#include "../../src/parser/parser.h"
#include <vector>
#include <iostream>

TEST_CASE( "parser - unit test - test a string is parsed to a vector")
{
    Parser parser;
    std::string str_to_parse = "2,2,1";

    std::vector<std::string> parsed_vector = parser.string_vector(str_to_parse);

    int expected_result_1 = 3;
    int actual_result_1 = parsed_vector.size();
    REQUIRE(actual_result_1 == expected_result_1);

    std::string expected_result_2 = "2";
    std::string actual_result_2 = parsed_vector.at(1);
    REQUIRE(actual_result_2 == expected_result_2);
}

TEST_CASE( "parser - unit test - vector of strings is parsed to a vector of ints")
{
    Parser parser;
    std::vector<std::string> vector_to_parse = {"4","10","4"};

    std::vector<int> parsed_vector = parser.string_vector_int_vector(vector_to_parse);

    int expected_result_1 = 3;
    int actual_result_1 = parsed_vector.size();
    REQUIRE(actual_result_1 == expected_result_1);

    int expected_result_2 = 4;
    int actual_result_2 = parsed_vector.at(2);
    REQUIRE(actual_result_2 == expected_result_2);
}

TEST_CASE( "parser - unit test - vector of strings is parsed to a vector of doubles")
{
    Parser parser;
    std::vector<std::string> vector_to_parse = {"3","2","2","2"};

    std::vector<double> parsed_vector = parser.string_vector_double_vector(vector_to_parse);

    int expected_result_1 = 4;
    int actual_result_1 = parsed_vector.size();
    REQUIRE(actual_result_1 == expected_result_1);

    double expected_result_2 = 2.0;
    double actual_result_2 = parsed_vector.at(3);
    REQUIRE(actual_result_2 == expected_result_2);
}

TEST_CASE( "parser - unit test - string to int, double, throws error")
{
    Parser parser;
    std::string int_string = "A.";
    std::string double_string = "@";

    REQUIRE_THROWS( parser.to_int(int_string) );
    REQUIRE_THROWS( parser.to_double(double_string) );
}


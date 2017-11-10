#include <vector>

#include "../../lib/catch.h"
#include "../../lib/json.hpp"
#include "../../src/json_parser/json_parser.h"
#include "../../src/json_parser/parsed_data.h"

TEST_CASE( "JsonParser - integration test - structure from json")
{

    nlohmann::json json_data;
    json_data["structure"] = {2,3,1};
    json_data["learning_rate"] = 0.2;
    json_data["target_total_error"] = 0.05;
    json_data["training_set"] = {};
    std::vector<int> input_values = {0,0};
    std::vector<int> target_values = {1};
    nlohmann::json training_value_target_pair = nlohmann::json::object({ {"input_values", input_values },
                                                                         {"target_values", target_values } });
    json_data["training_set"].emplace_back(training_value_target_pair);

    TrainingData training_data = JsonParser::parse_training_data_from_json(json_data);

    std::vector<int> actual_structure = training_data.structure;
    std::vector<int> expected_structure = {2,3,1};
    REQUIRE(actual_structure == expected_structure); 

    double actual_learning_rate = training_data.learning_rate;
    double expected_learning_rate = 0.2;
    REQUIRE(actual_learning_rate == expected_learning_rate);

    double actual_target_total_error = training_data.target_total_error;
    double expected_target_total_error = 0.05;
    REQUIRE(actual_target_total_error == expected_target_total_error);

    std::vector<double> actual_data = training_data.training_set.at(0).input_values;
    std::vector<double> expected_data = {0.0, 0.0};
    REQUIRE(actual_data == expected_data);

    std::vector<double> actual_targets = training_data.training_set.at(0).target_values;
    std::vector<double> expected_targets = {1.0};
    REQUIRE(actual_targets == expected_targets);
}

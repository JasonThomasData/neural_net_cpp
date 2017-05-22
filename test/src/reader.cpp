#include "../catch.h"
#include "../../src/reader/reader.h"
#include "../../src/reader/parsed_data.h"

TEST_CASE( "reader - unit test - test there's no file")
{
    Reader reader;

    std::string file_name = "totally not a real file";

    REQUIRE_THROWS( reader.read_training_data(file_name) );
}

/*
 * This test uses test/training_data file, which is a Nand gate
 *
 *   structure 2,3,1
 *   learning_rate 0.15
 *   target_total_error 0.0005
 *   0,0 1
 *   0,1 1
 *   1,0 1
 *   1,1 0
 */
TEST_CASE( "reader - integration test - test the dummy file is loaded")
{
    Reader reader;

    std::string file_name = "test/training_data";

    TrainingData test_training_data = reader.read_training_data(file_name);
    
    std::vector<int> actual_structure = test_training_data.structure;
    std::vector<int> expected_structure = {2,3,1};
    REQUIRE(actual_structure == expected_structure); 

    double actual_learning_rate = test_training_data.learning_rate;
    double expected_learning_rate = 0.15;
    REQUIRE(actual_learning_rate == expected_learning_rate);

    double actual_target_total_error = test_training_data.target_total_error;
    double expected_target_total_error = 0.0005;
    REQUIRE(actual_target_total_error == expected_target_total_error);

    std::vector<double> actual_data = test_training_data.data.at(2);
    std::vector<double> expected_data = {1.0, 0.0};
    REQUIRE(actual_data == expected_data);

    std::vector<double> actual_targets = test_training_data.targets.at(3);
    std::vector<double> expected_targets = {0.0};
    REQUIRE(actual_targets == expected_targets);
}

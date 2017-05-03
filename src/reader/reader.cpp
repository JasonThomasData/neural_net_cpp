#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "parsed_data.h"
#include "reader.h"

Reader::Reader(){}

std::ifstream Reader::read_file(std::string file_name)
{
    std::ifstream file;
    file.open(file_name);

    if (!file)
    {
        throw std::invalid_argument( "Reader could not open a file at given location." );
    }
    return file;
}

TrainingData Reader::read_training_data(std::string file_name)
{
    TrainingData training_data;
    std::ifstream file = read_file(file_name);

    std::string col_1, col_2;
    while (file >>col_1 >>col_2)
    {
        if (col_1 == "structure")
        {
            std::vector<std::string> structure_string_list = parser.string_vector(col_2);
            std::vector<int> parsed_structure = parser.string_vector_int_vector(structure_string_list);
            training_data.structure = parsed_structure;
        } else if (col_1 == "learning_rate")
        {
            training_data.learning_rate = parser.to_double(col_2);
        } else if (col_1 == "target_total_error")
        {
            training_data.target_total_error = parser.to_double(col_2);
        } else
        {
            std::vector<std::string> data_string_list = parser.string_vector(col_1);
            std::vector<double> parsed_data = parser.string_vector_double_vector(data_string_list);
            training_data.data.emplace_back(parsed_data);

            std::vector<std::string> target_string_list = parser.string_vector(col_2);
            std::vector<double> parsed_targets = parser.string_vector_double_vector(target_string_list);
            training_data.targets.emplace_back(parsed_targets);
        }
    }

    return training_data;
}

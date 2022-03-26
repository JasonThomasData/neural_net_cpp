#include <fstream>
#include <iostream>
#include <string>

#include "../../lib/json.hpp" 
#include "../data_converter/data_converter.h" 
#include "../json_io/json_io.h" 

int main(int argc, char** argv)
{
    if(argc != 4 || (std::string(argv[3]) != "training" && std::string(argv[3]) != "new_data"))
    {
        std::cout<< "Parse two file locations to convert and the type of document (training/new_data), like ./convert_data path/to/in path/to/out training"<< std::endl;
        std::exit(1);
    }
    else
    {
        std::string in_path = std::string(argv[1]);
        std::string out_path = std::string(argv[2]);
        std::string document_type = std::string(argv[3]);

        std::ifstream original_data = DataConverter::read_file(in_path);
        nlohmann::json out_data;
        if (document_type == "training")
        {
            out_data = DataConverter::convert_training_data_to_json(original_data);
        }
        else
        {
            out_data = DataConverter::convert_new_data_to_json(original_data);
        }
        JsonIO::save_json_data(out_path, out_data);
        std::cout<< "Data saved at "<< out_path<< std::endl;
    }
}

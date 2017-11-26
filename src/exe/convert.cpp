#include <fstream>
#include <iostream>
#include <string>

#include "../../lib/json.hpp" 
#include "../data_converter/data_converter.h" 
#include "../json_io/json_io.h" 

int main(int argc, char** argv)
{
    if(argc == 3)
    {
        std::string in_path = std::string(argv[1]);
        std::string out_path = std::string(argv[2]);

        std::ifstream original_data = DataConverter::read_file(in_path);
        nlohmann::json out_data = DataConverter::convert_to_json(original_data);
        JsonIO::save_json_data(out_path, out_data);
    }
    else
    {
        std::cout<< "Parse two file locations to convert, like ./convert_data path/to/in path/to/out"<< std::endl;
        std::exit(1);
    }
}

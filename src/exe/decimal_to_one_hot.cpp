#include <fstream>
#include <iostream>
#include <string>

#include "../data_converter/data_converter.h" 

void save_data(std::string out_path, std::stringstream out_data)
{
    std::ofstream filestream;
    filestream.open(out_path);
    filestream << out_data.rdbuf() << std::endl;
    filestream.close();
}

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        std::cout<< "Parse two file locations to convert (first should be decimal values) like ./decimal_to_one_hot path/to/in path/to/out"<< std::endl;
        std::exit(1);
    }
    else
    {
        std::string in_path = std::string(argv[1]);
        std::string out_path = std::string(argv[2]);

        std::ifstream original_data = DataConverter::read_file(in_path);
        std::stringstream out_data = DataConverter::convert_decimal_to_one_hot(original_data);
        //save to a new text file with the same format
        save_data(out_path, std::move(out_data));
        std::cout<< "Data saved at "<< out_path<< std::endl;
    }
}

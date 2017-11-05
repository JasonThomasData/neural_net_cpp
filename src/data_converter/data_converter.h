#ifndef DataConverter_h
#define DataConverter_h

#include <fstream>
#include <vector>
#include "../../lib/json.hpp"

class DataConverter
{
    private:
        DataConverter();
    public:
        static std::ifstream read_file(std::string file_name);
        static nlohmann::json convert_to_json(std::ifstream& original_data);
        static void save_data(std::string out_path, nlohmann::json out_data);
};

#endif

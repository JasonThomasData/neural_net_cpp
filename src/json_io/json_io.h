#ifndef JsonIO_h
#define JsonIO_h

#include "../../lib/json.hpp"

struct TrainingData;
class Network;

class JsonIO
{
    private:
        JsonIO();
        static nlohmann::json read_file(std::string file_name);
    public:
        static TrainingData read_training_data(std::string file_name);
        static void save_network_data(std::string file_name, Network& network);
        static void save_json_data(std::string file_name, nlohmann::json json_data);
};

#endif

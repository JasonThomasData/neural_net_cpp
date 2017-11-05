#ifndef JsonIO_h
#define JsonIO_h

#include <string>

#include "../../lib/json.hpp"

struct TrainingData;
class Network;

class JsonIO
{
    private:
        nlohmann::json read_file(std::string file_name);
        void save_file(std::string file_name, nlohmann::json json_data);
    public:
        JsonIO();
        TrainingData read_training_data(std::string file_name);
        void save_network_data(std::string file_name, Network network);
};

#endif

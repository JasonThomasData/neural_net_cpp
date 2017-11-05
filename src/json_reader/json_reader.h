#ifndef JsonReader_h
#define JsonReader_h

#include "../../lib/json.hpp"

struct TrainingData;

class JsonReader
{
    private:
        nlohmann::json read_file(std::string file_name);
    public:
        JsonReader();
        TrainingData read_training_data(std::string file_name);
};

#endif

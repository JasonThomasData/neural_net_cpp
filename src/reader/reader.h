#ifndef Reader_h
#define Reader_h

#include <fstream>
#include "../parser/parser.h"

struct TrainingData;

/* Responsible for loading and parsing text files. One public member function for each type of file.
 */

class Reader
{
    private:
        Parser parser;
        std::ifstream read_file(std::string file_name);
    public:
        Reader();
        TrainingData read_training_data(std::string file_name);
};

#endif

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "../network/network.h"
#include "../network_builder/network_builder.h"
#include "../neuron/neuron.h"
#include "../classifier/classifier.h"
#include "../trainer/trainer.h"
#include "../json_io/json_io.h"
#include "../json_parser/parsed_data.h"

double get_average_error(std::vector<double> all_total_errors)
{
    double sum = 0.0;
    for(auto& total_error: all_total_errors)
    {
        sum += total_error;
    }
    double average = sum / all_total_errors.size();
    return average;
}

// Rename to something that makes responsibility more obvious... is this really train_ ?
void train_epoch(Network& network, TrainingData& training_data, Classifier& classifier, Trainer& trainer)
{
    std::vector<double> all_total_errors;
    std::vector<TrainingDocument> training_set = training_data.training_set;

    for(TrainingDocument training_document: training_set)
    {
        std::vector<double> new_inputs = training_document.input_values;
        classifier.set_input_values(new_inputs);
        classifier.classify();

        std::vector<double> new_targets = training_document.target_values;
        trainer.set_target_values(new_targets);
        trainer.train();
 
        double total_error = trainer.calculate_total_error(network.output_layer);
        all_total_errors.emplace_back(total_error);
    }

    trainer.epoch += 1;
    network.epoch_average_total_error = get_average_error(all_total_errors);
    if(trainer.epoch % 500 == 0)
    {
        std::cout<< trainer.epoch<<", "<< std::setprecision(15)<< network.epoch_average_total_error<< std::endl;
    }
}

int main(int argc, char** argv)
{
    std::string training_file_path;
    std::string network_save_path;
    if(argc == 3)
    {
        training_file_path = std::string(argv[1]);
        network_save_path = std::string(argv[2]);
    } else
    {
        std::cout<< "You must declare training and network save file paths, like ./bin/train data/training/and_gate.json data/networks/and_gate.json";
    }
    TrainingData training_data = JsonIO::read_training_data(training_file_path);
    Network network = NetworkBuilder::build_network(training_data.structure);
    Classifier classifier(network);
    Trainer trainer(network, training_data.learning_rate);

    std::cout<< "Epoch, epoch_average_total_error"<< std::endl;
    train_epoch(network, training_data, classifier, trainer);

    while(network.epoch_average_total_error > training_data.target_total_error)
    {
        train_epoch(network, training_data, classifier, trainer);
    }

    std::cout<< "Target total error achieved at epoch "<< trainer.epoch<< std::endl;
    std::cout<< "Saving the trained network to "<< network_save_path<< std::endl;
    std::cout<< "Run:"<< std::endl;
    std::cout<< "./bin/classify "<< network_save_path<< " data/new_data/<path>"<< std::endl;
    JsonIO::save_network_data(network_save_path, network);

    return 0;
}

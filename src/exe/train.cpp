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

// Is this really classify_ ? If not then rename it.
void classify_epoch(Network& network, TrainingData& training_data, Classifier& classifier)
{
    std::vector<TrainingDocument> training_set = training_data.training_set;

    for(TrainingDocument training_document: training_set)
    {
        std::vector<double> new_inputs = training_document.input_values;
        classifier.set_input_values(new_inputs);
        classifier.classify();

        int new_inputs_size = new_inputs.size();
        for(int j=0; j<new_inputs_size; j++)
        {
            std::cout<< new_inputs.at(j);
            std::cout<< ",";
        }

        std::cout<< " - ";

        std::vector<Neuron>& updated_outputs = network.output_layer;

        int updated_outputs_size = updated_outputs.size();
        for(int k=0; k<updated_outputs_size; k++)
        {
            std::cout<< round( updated_outputs.at(k).outgoing_value );
            std::cout<< ",";
        }
        std::cout<< std::endl;
    }
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
    std::string file_name;
    if(argc > 0)
    {
        file_name = std::string(argv[1]);
    } else
    {
        std::cout<< "You must declare a file path, like ./bin/train data/training/and_gate.json";
    }
    TrainingData training_data = JsonIO::read_training_data(file_name);
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
    classify_epoch(network, training_data, classifier);

    JsonIO::save_network_data(file_name, network);

    return 0;
}

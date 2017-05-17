#include "../network/network.h"
#include "../classifier/classifier.h"
#include "../trainer/trainer.h"
#include "../reader/reader.h"
#include "../reader/parsed_data.h"
#include <vector>
#include <iostream>
#include <sstream> //For char conversion
#include <string> //For char conversion


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

void classify_epoch(Network& network, TrainingData& training_data, Classifier& classifier)
{
    for(int i=0; i<training_data.data.size(); i++)
    {
        std::vector<double> new_inputs = training_data.data.at(i);
        classifier.set_input_values(new_inputs);
        classifier.classify();

        for(int j=0; j<new_inputs.size(); j++)
        {
            std::cout<< new_inputs.at(j);
            std::cout<< ",";
        }

        std::cout<< " - ";

        for(int k=0; k<network.output_layer.size(); k++)
        {
            std::cout<< network.output_layer.at(k).outgoing_value;
            std::cout<< ",";
        }
        std::cout<< std::endl;
    }
}

void train_epoch(Network& network, TrainingData& training_data, Classifier& classifier, Trainer& trainer)
{
    std::vector<double> all_total_errors;

    for(int i=0; i < training_data.data.size(); i++)
    {
        std::vector<double> new_inputs = training_data.data.at(i);
        classifier.set_input_values(new_inputs);
        classifier.classify();

        std::vector<double> new_targets = training_data.targets.at(i);
        trainer.set_target_values(new_targets);
        trainer.train();
 
        double total_error = trainer.calculate_total_error(network.output_layer);
        all_total_errors.emplace_back(total_error);
    }

    trainer.epoch += 1;
    network.epoch_average_total_error = get_average_error(all_total_errors);
    if(trainer.epoch % 500 == 0)
    {
        std::cout<< trainer.epoch<<", "<< network.epoch_average_total_error<< std::endl;
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
        std::string file_name = "data/training/scatter_plot";
    }
    Reader reader;
    TrainingData training_data = reader.read_training_data(file_name);
    Network network(training_data.structure);
    Classifier classifier(network);
    Trainer trainer(network, training_data.learning_rate);

    std::cout<< "Epoch"<<", "<< "epoch_average_total_error"<< std::endl;
    train_epoch(network, training_data, classifier, trainer);

    while(network.epoch_average_total_error > training_data.target_total_error)
    {
        train_epoch(network, training_data, classifier, trainer);
    }

    classify_epoch(network, training_data, classifier);
    return 0;
}

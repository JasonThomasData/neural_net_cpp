#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "../network/network.h"
#include "../network_builder/network_builder.h"
#include "../neuron/neuron.h"
#include "../classifier/classifier.h"
#include "../json_io/json_io.h"
#include "../json_parser/parsed_data.h"

void show_inputs_for_new_document(std::vector<Neuron>& inputs)
{
    int inputs_size = inputs.size();

    std::cout<< round( inputs.at(0).outgoing_value);
    for(int k=1; k<inputs_size; k++)
    {
        std::cout<< ",";
        std::cout<< round( inputs.at(k).outgoing_value);
    }
}

void show_outputs(std::vector<Neuron>& outputs)
{
    int outputs_size = outputs.size();

    std::cout<< round( outputs.at(0).outgoing_value );
    for(int k=1; k<outputs_size; k++)
    {
        std::cout<< ",";
        std::cout<< round( outputs.at(k).outgoing_value );
    }
}


int main(int argc, char** argv)
{
    std::string network_save_path;
    std::string new_data_path;
    if(argc == 3)
    {
        network_save_path = std::string(argv[1]);
        new_data_path = std::string(argv[2]);
    } else
    {
        std::cout<< "You must declare network and new data file paths, like ./bin/classify data/networks/and_gate.json data/new_data/and_gate.json";
    }

    NetworkData network_data = JsonIO::read_network_data(network_save_path);
    Network network = NetworkBuilder::build_network(network_data.structure, network_data);
    Classifier classifier(network);
    NewData new_data = JsonIO::read_new_data(new_data_path);

    for(NewDocument new_document: new_data.new_documents)
    {
        classifier.set_input_values(new_document.input_values);
        classifier.classify();

        show_inputs_for_new_document(network.input_layer);
        std::cout<< " | ";
        show_outputs(network.output_layer);
        std::cout<< std::endl;
    }

    return 0;
}

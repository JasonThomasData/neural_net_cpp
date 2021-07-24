#include <exception>

#include "../../lib/json.hpp"

#include "parsed_data.h"
#include "from_json.h"

void FromJson::structure(DataCollection& data_collection, nlohmann::json json_data)
{
    try
    {
        for(int neurons_in_layer: json_data["structure"])
        {
            data_collection.structure.emplace_back(neurons_in_layer);
        }
    }
    catch (const std::exception& exception)
    {
        std::cout<< "check structure[int]"<< std::endl;
        std::cout<< exception.what()<< std::endl;
        throw exception;
    }
}

void FromJson::learning_rate(TrainingData& training_data, nlohmann::json json_data)
{
    try
    {
        training_data.learning_rate = json_data["learning_rate"];
    }
    catch (const std::exception& exception)
    {
        std::cout<< "check learning_rate"<< std::endl;
        std::cout<< exception.what()<< std::endl;
        throw exception;
    }
}

void FromJson::target_total_error(TrainingData& training_data, nlohmann::json json_data)
{
    try
    {
        training_data.target_total_error = json_data["target_total_error"];
    }
    catch (const std::exception& exception)
    {
        std::cout<< "check target_total_error"<< std::endl;
        std::cout<< exception.what()<< std::endl;
        exit(1);
    }
}

void FromJson::training_set(TrainingData& training_data, nlohmann::json json_data)
{
    for(auto training_document_json: json_data["training_set"])
    {
        TrainingDocument training_document;

        try
        {
            std::vector<double> parsed_input_values = training_document_json["input_values"];
            training_document.input_values = parsed_input_values; 
        }
        catch (const std::exception& exception)
        {
            std::cout<< "check training_set[n].input_values"<< std::endl;
            std::cout<< exception.what()<< std::endl;
            throw exception;
        }

        try
        {
            std::vector<double> parsed_target_values = training_document_json["target_values"];
            training_document.target_values = parsed_target_values; 
        }
        catch (const std::exception& exception)
        {
            std::cout<< "check training_set[n].output_values"<< std::endl;
            std::cout<< exception.what()<< std::endl;
            throw exception;
        }

        training_data.training_set.emplace_back(training_document);
    }
}

void FromJson::layers(NetworkData& network_data, nlohmann::json json_data)
{
    nlohmann::json hidden_layer_json_data = json_data["hidden_layer"];
    one_layer(network_data.hidden_layer, hidden_layer_json_data);

    nlohmann::json output_layer_json_data = json_data["output_layer"];
    one_layer(network_data.output_layer, output_layer_json_data);
}

void FromJson::one_layer(std::vector<SynapseData>& layer, nlohmann::json layer_json_data)
{
    for(nlohmann::json synapse_json_data: layer_json_data)
    {
        SynapseData synapse_data;
        synapse(synapse_data, synapse_json_data);
        layer.emplace_back(synapse_data);
    }
}

void FromJson::synapse(SynapseData& synapse_data, nlohmann::json synapse_json_data)
{
    neuron_index(synapse_data, synapse_json_data);
    incoming_synapse_index(synapse_data, synapse_json_data);
    incoming_synapse_weight(synapse_data, synapse_json_data);
}

void FromJson::neuron_index(SynapseData& synapse_data, nlohmann::json json_data)
{
    try
    {
        int neuron_index = json_data["neuron_index"];
        synapse_data.neuron_index = neuron_index;
    }
    catch (const std::exception& exception)
    {
        std::cout<< "check synapse data in network data file"<< std::endl;
        std::cout<< exception.what()<< std::endl;
        throw exception;
    }
}

void FromJson::incoming_synapse_index(SynapseData& synapse_data, nlohmann::json json_data)
{
    try
    {
        int incoming_synapse_index = json_data["incoming_synapse_index"];
        synapse_data.incoming_synapse_index = incoming_synapse_index;
    }
    catch (const std::exception& exception)
    {
        std::cout<< "check synapse data in network data file"<< std::endl;
        std::cout<< exception.what()<< std::endl;
        throw exception;
    }
}

void FromJson::incoming_synapse_weight(SynapseData& synapse_data, nlohmann::json json_data)
{
    try
    {
        double incoming_synapse_weight = (double)json_data["incoming_synapse_weight"];
        synapse_data.incoming_synapse_weight = incoming_synapse_weight;
    }
    catch (const std::exception& exception)
    {
        std::cout<< "check synapse data in network data file"<< std::endl;
        std::cout<< exception.what()<< std::endl;
        throw exception;
    }
}

void FromJson::new_data(NewData& new_data, nlohmann::json json_data)
{
    for(auto new_document_json: json_data["new_data"])
    {
        NewDocument new_document;

        try
        {
            std::vector<double> parsed_input_values = new_document_json;
            new_document.input_values = parsed_input_values; 
        }
        catch (const std::exception& exception)
        {
            std::cout<< "check the new data"<< std::endl;
            std::cout<< exception.what()<< std::endl;
            throw exception;
        }

        new_data.new_documents.emplace_back(new_document);
    }
}
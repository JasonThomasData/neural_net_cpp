#include <vector>
#include "../../lib/catch.h"
#include "../../src/writer/writer.h"
#include "../../src/network/network.h"

TEST_CASE( "writer - integration test - get weights between two layers")
{
	int input_layer = 2;
	int hidden_layer = 3;
	int output_layer = 1;
	std::vector<int> layer_counts;
	layer_counts.emplace_back(input_layer);
	layer_counts.emplace_back(hidden_layer);
	layer_counts.emplace_back(output_layer);

	Network network(layer_counts);
    network.hidden_layer.at(0).incoming_synapses.at(0)->set_weight(0.37);
    network.hidden_layer.at(0).incoming_synapses.at(1)->set_weight(0.61);
    network.hidden_layer.at(1).incoming_synapses.at(0)->set_weight(0.23);
    network.hidden_layer.at(1).incoming_synapses.at(1)->set_weight(0.58);

    Writer writer;
    //writer.dump_network_data(network);

    REQUIRE(input_layer == output_layer); 
}


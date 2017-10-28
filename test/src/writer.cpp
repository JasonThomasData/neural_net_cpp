#include <vector>
#include "../../lib/catch.h"
#include "../../src/writer/writer.h"
#include "../../src/network/network.h"
#include "../../src/network_builder/network_builder.h"

TEST_CASE( "writer - integration test - get weights between two layers")
{
	std::vector<int> layer_counts {2, 3, 1};

	Network network = NetworkBuilder.build_network(layer_counts);
    network.hidden_layer.at(0).incoming_synapses.at(0)->set_weight(0.37);
    network.hidden_layer.at(0).incoming_synapses.at(1)->set_weight(0.61);
    network.hidden_layer.at(1).incoming_synapses.at(0)->set_weight(0.23);
    network.hidden_layer.at(1).incoming_synapses.at(1)->set_weight(0.58);

    Writer writer;
    //writer.dump_network_data(network);

    REQUIRE(input_layer == output_layer); 
}


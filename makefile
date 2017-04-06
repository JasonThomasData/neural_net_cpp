all: synapse.o soma.o input.o neuron.o network.o main.o classifier.o main i_t_synapse.o i_t_soma.o i_t_neuron.o i_t_network.o i_t_classifier.o i_t_main.o integration clean
.PHONY: all CXXFLAGS clean
CXXFLAGS = -std=c++14 -Wall

#Network
synapse.o: src/network/synapse/synapse.cpp
	g++ -c $(CXXFLAGS) src/network/synapse/synapse.cpp -o build/synapse.o
soma.o: src/network/soma/soma.cpp
	g++ -c $(CXXFLAGS) src/network/soma/soma.cpp -o build/soma.o
input.o: src/network/neuron/input.cpp
	g++ -c $(CXXFLAGS) src/network/neuron/input.cpp -o build/input.o
neuron.o: src/network/neuron/neuron.cpp
	g++ -c $(CXXFLAGS) src/network/neuron/neuron.cpp -o build/neuron.o
network.o: src/network/network.cpp
	g++ -c $(CXXFLAGS) src/network/network.cpp -o build/network.o

#Agents
classifier.o: src/classifier/classifier.cpp
	g++ -c $(CXXFLAGS) src/classifier/classifier.cpp -o build/classifier.o


main.o: src/exe/main.cpp
	g++ -c $(CXXFLAGS) src/exe/main.cpp -o build/main.o
main:
	g++ $(CXXFLAGS) build/synapse.o build/soma.o build/input.o build/neuron.o build/network.o build/main.o -o bin/main


#Integration tests
i_t_synapse.o: test/integration/synapse.cpp
	g++ -c $(CXXFLAGS) test/integration/synapse.cpp -o build/i_t_synapse.o
i_t_soma.o: test/integration/soma.cpp
	g++ -c $(CXXFLAGS) test/integration/soma.cpp -o build/i_t_soma.o
i_t_neuron.o: test/integration/neuron.cpp
	g++ -c $(CXXFLAGS) test/integration/neuron.cpp -o build/i_t_neuron.o
i_t_network.o: test/integration/network.cpp
	g++ -c $(CXXFLAGS) test/integration/network.cpp -o build/i_t_network.o
i_t_classifier.o: test/integration/classifier.cpp
	g++ -c $(CXXFLAGS) test/integration/classifier.cpp -o build/i_t_classifier.o
i_t_main.o: test/integration/main.cpp
	g++ -c $(CXXFLAGS) test/integration/main.cpp -o build/i_t_main.o
integration:
	g++ $(CXXFLAGS) build/i_t_synapse.o build/i_t_soma.o build/i_t_neuron.o build/i_t_network.o build/i_t_classifier.o build/i_t_main.o build/soma.o build/synapse.o build/input.o build/neuron.o build/network.o build/classifier.o -o bin/tests/integration



clean:
	\rm build/*

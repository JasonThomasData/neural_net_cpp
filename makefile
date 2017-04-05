all: synapse.o soma.o input_neuron.o neuron.o neural_net.o neural_net integration.o tests clean
.PHONY: all CXXFLAGS clean
CXXFLAGS = -std=c++14 -Wall


synapse.o: src/network/synapse/synapse.cpp
	g++ -c $(CXXFLAGS) src/network/synapse/synapse.cpp -o build/synapse.o
soma.o: src/network/soma/soma.cpp
	g++ -c $(CXXFLAGS) src/network/soma/soma.cpp -o build/soma.o
input_neuron.o: src/network/input_neuron/input_neuron.cpp
	g++ -c $(CXXFLAGS) src/network/input_neuron/input_neuron.cpp -o build/input_neuron.o
neuron.o: src/network/neuron/neuron.cpp
	g++ -c $(CXXFLAGS) src/network/neuron/neuron.cpp -o build/neuron.o
neural_net.o: src/exe/neural_net.cpp
	g++ -c $(CXXFLAGS) src/exe/neural_net.cpp -o build/neural_net.o
neural_net:
	g++ $(CXXFLAGS) build/synapse.o build/soma.o build/input_neuron.o build/neuron.o build/neural_net.o -o bin/neural_net


integration.o:
	g++ -c $(CXXFLAGS) test/integration.cpp -o build/integration.o
tests:
	g++ $(CXXFLAGS) build/integration.o build/soma.o build/synapse.o build/input_neuron.o build/neuron.o -o bin/tests/integration


clean:
	\rm build/*

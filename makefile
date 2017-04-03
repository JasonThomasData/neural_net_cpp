all: synapse.o soma.o input_neuron.o neuron.o neural_net.o neural_net integration.o tests clean
.PHONY: all CXXFLAGS clean
CXXFLAGS = -std=c++14 -Wall


synapse.o: src/assets/synapse.cpp
	g++ -c $(CXXFLAGS) src/assets/synapse.cpp -o build/synapse.o
soma.o: src/assets/soma.cpp
	g++ -c $(CXXFLAGS) src/assets/soma.cpp -o build/soma.o
input_neuron.o: src/assets/input_neuron.cpp
	g++ -c $(CXXFLAGS) src/assets/input_neuron.cpp -o build/input_neuron.o
neuron.o: src/assets/neuron.cpp
	g++ -c $(CXXFLAGS) src/assets/neuron.cpp -o build/neuron.o
neural_net.o: src/neural_net.cpp
	g++ -c $(CXXFLAGS) src/neural_net.cpp -o build/neural_net.o
neural_net:
	g++ $(CXXFLAGS) build/synapse.o build/soma.o build/input_neuron.o build/neuron.o build/neural_net.o -o bin/neural_net


integration.o:
	g++ -c $(CXXFLAGS) test/integration.cpp -o build/integration.o
tests:
	g++ $(CXXFLAGS) build/integration.o build/soma.o build/synapse.o build/input_neuron.o build/neuron.o -o bin/tests/integration


clean:
	\rm build/*

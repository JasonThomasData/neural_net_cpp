all: synapse.o soma.o input_neuron.o neuron.o network.o main.o classifier.o main int_tests_synapse.o int_tests_soma.o int_tests_neuron.o int_tests_main.o integration clean
.PHONY: all CXXFLAGS clean
CXXFLAGS = -std=c++14 -Wall

#Network stuff
synapse.o: src/network/synapse/synapse.cpp
	g++ -c $(CXXFLAGS) src/network/synapse/synapse.cpp -o build/synapse.o
soma.o: src/network/soma/soma.cpp
	g++ -c $(CXXFLAGS) src/network/soma/soma.cpp -o build/soma.o
input_neuron.o: src/network/input_neuron/input_neuron.cpp
	g++ -c $(CXXFLAGS) src/network/input_neuron/input_neuron.cpp -o build/input_neuron.o
neuron.o: src/network/neuron/neuron.cpp
	g++ -c $(CXXFLAGS) src/network/neuron/neuron.cpp -o build/neuron.o
network.o: src/network/network.cpp
	g++ -c $(CXXFLAGS) src/network/network.cpp -o build/network.o


classifier.o: src/classifier/classifier.cpp
	g++ -c $(CXXFLAGS) src/classifier/classifier.cpp -o build/classifier.o


main.o: src/exe/main.cpp
	g++ -c $(CXXFLAGS) src/exe/main.cpp -o build/main.o
main:
	g++ $(CXXFLAGS) build/synapse.o build/soma.o build/input_neuron.o build/neuron.o build/network.o build/main.o -o bin/main

#Integration tests
int_tests_synapse.o: test/integration/synapse.cpp
	g++ -c $(CXXFLAGS) test/integration/synapse.cpp -o build/int_tests_synapse.o
int_tests_soma.o: test/integration/soma.cpp
	g++ -c $(CXXFLAGS) test/integration/soma.cpp -o build/int_tests_soma.o
int_tests_neuron.o: test/integration/neuron.cpp
	g++ -c $(CXXFLAGS) test/integration/neuron.cpp -o build/int_tests_neuron.o
int_tests_main.o: test/integration/main.cpp
	g++ -c $(CXXFLAGS) test/integration/main.cpp -o build/int_tests_main.o
integration:
	g++ $(CXXFLAGS) build/int_tests_synapse.o build/int_tests_soma.o build/int_tests_neuron.o build/int_tests_main.o build/soma.o build/synapse.o build/input_neuron.o build/neuron.o build/network.o build/classifier.o -o bin/tests/integration


clean:
	\rm build/*

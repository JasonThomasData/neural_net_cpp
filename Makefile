all: $(objects) classify integration clean
.PHONY: all CXXFLAGS objects clean
CXXFLAGS = -std=c++14 -Wall

objects = $(obj_network) $(obj_trainer) $(obj_classifier) $(obj_integration_tests) $(obj_main_files)

obj_network = build/synapse.o build/soma.o build/input.o build/neuron.o build/network.o
obj_trainer = build/backpropagation.o
#trainer = build/trainer.o build/backpropagation.o
obj_classifier = build/classifier.o
obj_integration_tests = build/i_t_synapse.o build/i_t_soma.o build/i_t_neuron.o build/i_t_network.o \
    build/i_t_classifier.o build/i_t_backpropagation.o
obj_main_files = build/train_main.o build/classify_main.o build/i_t_main.o

#Network objects
build/synapse.o: src/network/synapse/synapse.cpp
	g++ -c $(CXXFLAGS) src/network/synapse/synapse.cpp -o build/synapse.o
build/soma.o: src/network/soma/soma.cpp
	g++ -c $(CXXFLAGS) src/network/soma/soma.cpp -o build/soma.o
build/input.o: src/network/neuron/input.cpp
	g++ -c $(CXXFLAGS) src/network/neuron/input.cpp -o build/input.o
build/neuron.o: src/network/neuron/neuron.cpp
	g++ -c $(CXXFLAGS) src/network/neuron/neuron.cpp -o build/neuron.o
build/network.o: src/network/network.cpp
	g++ -c $(CXXFLAGS) src/network/network.cpp -o build/network.o

#Trainer objects
#trainer.o: src/trainer/trainer.cpp
#	g++ -c $(CXXFLAGS) src/trainer/trainer.cpp -o build/classifier.o
build/backpropagation.o: src/trainer/backpropagation.cpp
	g++ -c $(CXXFLAGS) src/trainer/backpropagation.cpp -o build/backpropagation.o

#Classifier objects
build/classifier.o: src/classifier/classifier.cpp
	g++ -c $(CXXFLAGS) src/classifier/classifier.cpp -o build/classifier.o

#Integration test objects
build/i_t_synapse.o: test/integration/synapse.cpp
	g++ -c $(CXXFLAGS) test/integration/synapse.cpp -o build/i_t_synapse.o
build/i_t_soma.o: test/integration/soma.cpp
	g++ -c $(CXXFLAGS) test/integration/soma.cpp -o build/i_t_soma.o
build/i_t_neuron.o: test/integration/neuron.cpp
	g++ -c $(CXXFLAGS) test/integration/neuron.cpp -o build/i_t_neuron.o
build/i_t_network.o: test/integration/network.cpp
	g++ -c $(CXXFLAGS) test/integration/network.cpp -o build/i_t_network.o
build/i_t_classifier.o: test/integration/classifier.cpp
	g++ -c $(CXXFLAGS) test/integration/classifier.cpp -o build/i_t_classifier.o
build/i_t_backpropagation.o: test/integration/backpropagation.cpp
	g++ -c $(CXXFLAGS) test/integration/backpropagation.cpp -o build/i_t_backpropagation.o

#Main file objects. Each has a main function
build/train_main.o: src/exe/main.cpp
	g++ -c $(CXXFLAGS) src/exe/main.cpp -o build/train_main.o
build/classify_main.o: src/exe/main.cpp
	g++ -c $(CXXFLAGS) src/exe/main.cpp -o build/classify_main.o
build/i_t_main.o: test/main.cpp
	g++ -c $(CXXFLAGS) test/main.cpp -o build/i_t_main.o

# The actual executables
train: $(obj_network) $(obj_classifier) $(obj_trainer) build/train_main.o
	g++ $(CXXFLAGS) $(obj_network) $(obj_classifier) $(obj_trainer) build/train_main.o -o bin/train
classify: $(obj_network) $(obj_classifier) build/classify_main.o
	g++ $(CXXFLAGS) $(obj_network) $(obj_classifier) build/classify_main.o -o bin/classify
integration: $(obj_network) $(obj_classifier) $(obj_trainer) $(obj_integration_tests) build/i_t_main.o
	g++ $(CXXFLAGS) $(obj_network) $(obj_classifier) $(obj_trainer) $(obj_integration_tests) build/i_t_main.o -o bin/tests/integration

clean:
	\rm build/*
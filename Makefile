all: $(objects) train convert test
.PHONY: all CXXFLAGS objects clean
CXXFLAGS = -std=c++14 -Wall

objects = $(obj_network) $(obj_trainer) $(obj_classifier) $(obj_read_write) $(obj_main_files) $(obj_tests)

obj_network = build/synapse.o build/neuron.o build/network.o build/network_builder.o
obj_trainer = build/trainer.o build/backpropagation.o
obj_classifier = build/feed_forward.o build/classifier.o
obj_read_write = build/json_reader.o build/json_parser.o build/simple_parser.o build/data_converter.o
obj_tests = build/test_synapse.o build/test_network.o build/test_classifier.o \
	build/test_feed_forward.o build/test_trainer.o build/test_backpropagation.o \
	build/test_simple_parser.o build/test_json_reader.o build/test_json_parser.o
obj_main_files = build/train_main.o build/classify_main.o build/test_main.o build/convert_main.o

#Network objects
build/synapse.o: src/synapse/synapse.cpp
	g++ -c $(CXXFLAGS) src/synapse/synapse.cpp -o build/synapse.o
build/neuron.o: src/neuron/neuron.cpp
	g++ -c $(CXXFLAGS) src/neuron/neuron.cpp -o build/neuron.o
build/network.o: src/network/network.cpp
	g++ -c $(CXXFLAGS) src/network/network.cpp -o build/network.o
build/network_builder.o: src/network_builder/network_builder.cpp
	g++ -c $(CXXFLAGS) src/network_builder/network_builder.cpp -o build/network_builder.o

#Trainer objects
build/backpropagation.o: src/trainer/backpropagation.cpp
	g++ -c $(CXXFLAGS) src/trainer/backpropagation.cpp -o build/backpropagation.o
build/trainer.o: src/trainer/trainer.cpp
	g++ -c $(CXXFLAGS) src/trainer/trainer.cpp -o build/trainer.o

#Classifier objects
build/feed_forward.o: src/classifier/feed_forward.cpp
	g++ -c $(CXXFLAGS) src/classifier/feed_forward.cpp -o build/feed_forward.o
build/classifier.o: src/classifier/classifier.cpp
	g++ -c $(CXXFLAGS) src/classifier/classifier.cpp -o build/classifier.o

#Reader and writer objects
build/json_reader.o: src/json_reader/json_reader.cpp
	g++ -c $(CXXFLAGS) src/json_reader/json_reader.cpp -o build/json_reader.o
build/json_parser.o: src/json_parser/json_parser.cpp
	g++ -c $(CXXFLAGS) src/json_parser/json_parser.cpp -o build/json_parser.o
build/simple_parser.o: src/simple_parser/simple_parser.cpp
	g++ -c $(CXXFLAGS) src/simple_parser/simple_parser.cpp -o build/simple_parser.o
build/data_converter.o: src/data_converter/data_converter.cpp
	g++ -c $(CXXFLAGS) src/data_converter/data_converter.cpp -o build/data_converter.o

#Test objects
build/test_synapse.o: test/src/synapse.cpp
	g++ -c $(CXXFLAGS) test/src/synapse.cpp -o build/test_synapse.o
build/test_network.o: test/src/network.cpp
	g++ -c $(CXXFLAGS) test/src/network.cpp -o build/test_network.o
build/test_feed_forward.o: test/src/feed_forward.cpp
	g++ -c $(CXXFLAGS) test/src/feed_forward.cpp -o build/test_feed_forward.o
build/test_classifier.o: test/src/classifier.cpp
	g++ -c $(CXXFLAGS) test/src/classifier.cpp -o build/test_classifier.o
build/test_trainer.o: test/src/trainer.cpp
	g++ -c $(CXXFLAGS) test/src/trainer.cpp -o build/test_trainer.o
build/test_backpropagation.o: test/src/backpropagation.cpp
	g++ -c $(CXXFLAGS) test/src/backpropagation.cpp -o build/test_backpropagation.o
build/test_simple_parser.o: test/src/simple_parser.cpp
	g++ -c $(CXXFLAGS) test/src/simple_parser.cpp -o build/test_simple_parser.o
build/test_json_reader.o: test/src/json_reader.cpp
	g++ -c $(CXXFLAGS) test/src/json_reader.cpp -o build/test_json_reader.o
build/test_json_parser.o: test/src/json_parser.cpp
	g++ -c $(CXXFLAGS) test/src/json_parser.cpp -o build/test_json_parser.o

#Main file objects. Each has a main function
build/train_main.o: src/exe/train.cpp
	g++ -c $(CXXFLAGS) src/exe/train.cpp -o build/train_main.o
build/classify_main.o: src/exe/classify.cpp
	g++ -c $(CXXFLAGS) src/exe/classify.cpp -o build/classify_main.o
build/test_main.o: test/main.cpp
	g++ -c $(CXXFLAGS) test/main.cpp -o build/test_main.o
build/convert_main.o: src/exe/convert.cpp
	g++ -c $(CXXFLAGS) src/exe/convert.cpp -o build/convert_main.o

# The actual executables
train: $(obj_network) $(obj_classifier) $(obj_trainer) $(obj_read_write) build/train_main.o
	g++ $(CXXFLAGS) $(obj_network) $(obj_classifier) $(obj_trainer) $(obj_read_write) build/train_main.o -o bin/train
classify: $(obj_network) $(obj_classifier) build/classify_main.o
	g++ $(CXXFLAGS) $(obj_network) $(obj_classifier) build/classify_main.o -o bin/classify
test: $(obj_network) $(obj_classifier) $(obj_trainer) $(obj_read_write) $(obj_tests) build/test_main.o
	g++ $(CXXFLAGS) $(obj_network) $(obj_classifier) $(obj_trainer) $(obj_read_write) $(obj_tests) build/test_main.o -o bin/test
convert: $(obj_read_write) build/convert_main.o
	g++ $(CXXFLAGS) $(obj_read_write) build/convert_main.o -o bin/convert

clean:
	\rm build/*

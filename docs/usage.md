### Using the program

If you're missing permissions, do: `chmod +x bin/*`

When this project is finished, it will have two programs: `train` and `classify`. This is a WIP.

The `train` will allow you to train a neural network, and then dump all weights of all Synapses that
connect Neurons into a file.

You might use it like this:

    ./bin/train --structure (2,30,1) --train data/training/XnorGate --dump data/networks/231_XnorGate

The --options mean:

- structure - creates a network of 3 layers with 2 input, 30 hidden, 1 output Neurons
- training - the data to train the network. Should be documents and the labels, or categories, they
  map to
- dump - the save location for the finished state of the network

Next, the classify program:

    ./bin/classify --load data/networks/231_XnorGate --classify data/test/XnorGate --dump data/results/231_XnorGate

Similarly, these --options mean

- load - the network state that was saved, we can use to recreate a network
- classify - the data to test the network, to make sure it can classify (preferably unseen) documents
- dump - the location to save statistics about the training, so we can see if it was a success, or
  not

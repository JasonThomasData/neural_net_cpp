### Using the program

If you're missing permissions, do: `chmod +x bin/*`

When this project is finished, it will have two programs: `train` and `classify`. This is a WIP.

The `train` will allow you to train a neural network, and then dump all weights of all Synapses that
connect Neurons into a file.

You might use it like this:

    ./bin/train --train data/training/XnorGate --dump data/networks/231_XnorGate

The --options mean:

- training - the data to train the network. Should be documents and the labels, or categories, they
  map to. This file should include details about the network's structure, learn_rate and
  target_total_error.
- dump - the save location for the finished state of the network. To be loaded later

Next, the classify program:

    ./bin/classify --load data/networks/231_XnorGate --classify data/test/XnorGate

Similarly, these --options mean

- load - the network state that was saved, we can use to recreate a network. Should include the
  network structure.
- classify - the data to test the network, to make sure it can classify (preferably unseen) documents.

This last program will just print to the terminal, for now.

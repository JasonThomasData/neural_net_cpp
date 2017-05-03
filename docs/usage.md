### Using the program

If you're missing permissions, do: `chmod +x bin/*`

When this project is finished, it will have two programs: `train` and `classify`. This is a WIP.

The `train` will allow you to train a neural network, and then dump all weights of all Synapses that
connect Neurons into a file.

You might use it like this:

    ./bin/train --train data/training/XnorGate --dump data/networks/231_XnorGate

The --options mean:

- training - the data to train the network. Should be documents and the labels, or categories, they
  map to. This file should include details about the network's `structure`, `learning_rate` and
  `target_total_error`. See docs for [training data](docs/data_files.md) for more.
- dump - the save location for the finished state of the network. To be loaded later.

When you run the program, the network will have a `total_error`, although the value printed will be
the average for the entire epoch (all training documents). That average should approach zero until
it reaches the `total_target_error` specified in the training file. If it doesn't approach zero, try
amending the settings at the top of the training data file.

Next, the classify program:

    ./bin/classify --load data/networks/231_XnorGate --classify data/test/XnorGate

Similarly, these --options mean

- load - the network state that was saved, we can use to recreate a network. Should include the
  network `structure`. See docs for [persistent network structure](docs/data_files.md) for more.
- classify - the data to test the network, to make sure it can classify (preferably unseen) documents.

You should aim to test the network with documents that are unseen (not used for training) to test
the network for how well it responds to real world applications.

This last program will just print to the terminal, for now.

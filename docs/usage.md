### Using the program

If you're missing permissions, do: `chmod +x bin/*`

When this project is finished, it will have two programs: `train` and `classify`. This is a WIP.

The `train` will allow you to train a neural network, and then dump all weights of all Synapses that
connect Neurons into a file.

You might use it like this:

    ./bin/train data/training/and_gate.json data/networks/and_gate.json
  
The first arg is where to load the labeled training data. The second is where the resulting network will be saved.

When you run the program, the network will have a `total_error`, although the value printed will be
the average for the entire epoch (all training documents). That average should approach zero until
it reaches the `total_target_error` specified in the training file. If it doesn't approach zero, try
amending the settings at the top of the training data file.

Next, the classify program:

    ./bin/classify data/networks/and_gate.json data/new_data/and_gate.json

The first arg is the network that was saved during training. The second is the data that is used with
a trained classifier. This might be test data or unseen data.

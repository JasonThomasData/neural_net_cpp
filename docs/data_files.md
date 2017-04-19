Several types of data are stored here. Spaces should be used as delimiters for all files.

It is easier to split lines by space first in C++, and then with a delimiter. All data files should
have two columns separated by one space, and a further delimiter if it's needed.

---

`data/training/` - for training a neural network

The training data will be separated from the target lables/categories via a space

Eg - an Xor gate, with 2 input and 1 output:

    structure 2,10,1
    learn_rate 0.3
    target_total_error 0.0005
    0,0 0
    0,1 1
    1,0 1
    1,1 0

Eg - binary converter, with one input and 4 outputs:

    structure 1,15,4
    learn_rate 0.3
    target_total_error 0.0005
    0 0,0,0,0
    1 0,0,0,1
    2 0,0,1,0
    3 0,0,1,1
    4 0,1,0,0
    5 0,1,0,1
    6 0,1,1,0
    7 0,1,1,1
    8 1,0,0,0
    9 1,0,0,1

---

`data/network/` - for recreating a network after it was trained.

The structure will be a text file separated with spaces. 

The top row is the structure of the network to initialise in Neurons - input, hidden, output
Every row underneath describes the weight of a Synapse - layer, neuron, incoming_synapse, weight

Eg:

    structure 2,3,1
    1,0,0 0.56431
    1,0,1 0.71223
    1,1,0 0.83745
    1,1,1 0.45213
    1,2,0 0.35661
    1,2,1 0.66131
    2,0,0 0.34091
    2,0,1 0.14120
    2,0,2 0.94911

Therefore, the first line says it should be a neural net of 2 inputs, 3 hidden and 1 output Neurons,
and the second line refers to the first incoming Synapse to the first Neuron in the hidden layer.

---

`data/classify/` - for classifying data with a trained network

You can recycle the training data, or drop the ,

Eg:

    0,0
    0,1
    1,0
    1,1


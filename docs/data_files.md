Several types of data are stored here. Spaces should be used as delimiters for all files.

---

`data/training/` - for training a neural network

The training data will be separated from the target lables/categories via a |

Eg - an Xor gate, with 2 input and 1 output:

    0 0 | 0
    0 1 | 1
    1 0 | 1
    1 1 | 0

Eg - binary converter, with one input and 4 outputs:

    0 | 0 0 0 0
    1 | 0 0 0 1
    2 | 0 0 1 0
    3 | 0 0 1 1
    4 | 0 1 0 0
    5 | 0 1 0 1
    6 | 0 1 1 0
    7 | 0 1 1 1
    8 | 1 0 0 0
    9 | 1 0 0 1

---

`data/network/` - for recreating a network after it was trained.

The structure will be a text file separated with spaces. 

The top row is the structure of the network to initialise in Neurons - input, hidden, output
Every row underneath describes the weight of a Synapse - layer, neuron, incoming_synapse, weight

Eg:

    2 3 1
    hidden 0 0 0.56431
    hidden 0 1 0.71223
    hidden 1 0 0.83745
    hidden 1 1 0.45213
    hidden 2 0 0.35661
    hidden 2 1 0.66131
    output 0 0 0.34091
    output 0 1 0.14120
    output 0 2 0.94911

Therefore, the first line says it should be a neural net of 2 inputs, 3 hidden and 1 output Neurons,
and the second line refers to the first incoming Synapse to the first Neuron in the hidden layer.

---

`data/classify/` - for classifying data with a trained network

You can recycle the training data, or drop the |

Eg:

    0 0
    0 1
    1 0
    1 1


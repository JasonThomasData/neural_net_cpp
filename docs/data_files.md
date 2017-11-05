Several types of data are stored here. 

Simple text files are used as an easier way to compile the data.

Eg:

    structure 2,20,1
    learning_rate 0.30
    target_total_error 0.0005
    0,0 1
    0,1 1
    1,0 1
    1,1 0

Use `./bin/convert` to convert the above to json. json files are used to store training data.

Eg:
    
    {
        "learning_rate":0.3,
        "structure":[2,20,1],
        "target_total_error":0.0005,
        "training_set":[
            {
                "input_values":[0.0,0.0],
                "target_values":[1.0]
            },
            {
                "input_values":[0.0,1.0],
                "target_values":[1.0]
            },
            {
                "input_values":[1.0,0.0],
                "target_values":[1.0]
            },
            {
                "input_values":[1.0,1.0],
                "target_values":[0.0]
            }
        ]
    }

Normally the JSON files are minfified when saved.

---

Some terms need explaining:

- structure: in Neurons, the first, hidden and output layers. The first and output layers should
  have as many Neurons as the training set has training documents, and training labels (each in
  columns, separated by commas).
- learning_rate: during backpropagation, the weight of a Synapse, or connection between Neurons, is
  modified by this variable. Useful for making sure those weights don't change too quickly, and this
  has good results with some networks.
- target_total_error: when training an entire epoch (all documents and labels) produces an average
  total_error for the epoch, and that average error is lower than this, training stops.

---

`data/training/` - for training a neural network

It seems that the network generally performs better when the input and target values are binary
numbers.

---

`data/network/` - for recreating a network after it was trained.

The program creates these files for you.

---

`data/classify/` - for classifying data with a trained network

You can recycle the training data, and the training-specific data will be dropped.

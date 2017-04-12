### Things to add

- Bias - a constant rate across a network, or layer, that can assist in training.
- Deep nets - this project implements a vanilla neural network of three layers, but it would be cool
to have more than one hidden layer. This is to investigate, might be unrealistic.
- Dataviz plugin - could potentially dump the output of each synapse at each epoch and then make a
dataviz. Pretty colours, straight lines, etc. Could even just make some videos for fun.
- Some analysis on how quickly different networks (size, shape, activation functions) can achieve an
acceptable total error rate, counting by epoch.
- Figure out how to mock objects so I can write actual unit tests.

Regarding the point about making the network a deep network: the data members in the Network class
for input_layer and output_layer can remain, but those will be to a layer class that's added with
composition. The layer class will have references to former and next layers, allowing for as
many hidden layers as the user wants.

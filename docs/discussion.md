### Discussion

This project has two classes that important for doing stuff - `Classifier` and `Trainer`. Both accept a
reference to the `Network`.

The `Network` is a container for the data model. It has internal objects like `Neurons` and `Synapses`
that do their own logic internally. The network creates layers of these smaller objects when it is
initialised.

The `Classifier` and `Trainer` classes manipulate the `Network`.

The `./bin/train` program will use the `Classifier` and `Trainer` classes, while `./bin/classify` will only
initialise and use the `Classifier` object.

I found the biological model of a neural network to be useful to some extent when doing this
project. Here are the original pics I made to help me think about it:

![neuron](neuron.png)
![soma](soma.png)
![neural_net](neural_net.png)

The `Soma` concept above I got from studying biological networks, but these functions are not internal
to `Neurons` and the `Classifier` handles everything to do with forward feed.

The concept of backpropagation deserves an explanation in itself. I've found Matt Mazur's
[explainer](https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/)
to be great, if you're prepared to step through the example step by step. Videos also helped my
understanding of it.

I've chosen to use a logistic function for activating the neurons. See the Classifier functions for
details on that. Two other functions look useful. However, it's not clear if backpropagation will
need to change if the logistic function is not used because the articles I used as references to
make the backpropagation use the logistic activation function; the learning rule uses the partial
derivative of the logistic function.

![functions](activation_functions.png)

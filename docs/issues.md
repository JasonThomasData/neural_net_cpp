### Issues

Occasionally, a neural network's total error will grow instead of approaching zero. That is an issue
with exploding gradients, and I have no plans to fix that. If the total error during training grows
then it's best to turn it off and start again, because the ones I've let run overnight never
approach zero.

![target total error grows](issue_target_total_error.png)

This happens roughly 10-20% of all training cases. I've found that setting a higher `target_total_error`
for the network will mean the network is trained before this anomaly happens.

An issue I've seen is that the network will take a very long time to train if the input values are
larger than one. Increasing the number of neurons in the middle layer does seem to help. Solutions 
to this are:

- Divide your inputs by a common denominator first eg: `98` and `23` become `98/100 = 0.98` and `23/100 =
  0.23`
- Convert your numbers to binary and have more input neurons, eg: `5` becomes `1 0 1`

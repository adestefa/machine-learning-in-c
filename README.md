
# Machine Learning in C

Let's skip all the high level data science and see if we can use some simple C to train a model using simple maths.

![Image](imgs/artifical_neuron.png)

Our first job is to start by building a single artifical neuron with a single input and weight.

![Image](imgs/single_input.png)

At its most basic level we have a single input 'x', a weight 'w' that is summed and provides and output 'y'. Using this neuron we can feed it an input and using the weight value drive an output in y. Using repetition over and over again we can try different values in weight to get closer to the desired outcome.


In order to 'learn' we must show the neuron patterns in values we can iterate over and over until we 'train' the neuron to give us the ouput that matches the desired outcome of the model. In this case some simple data doubles the input:

<img src="imgs/double.png" alt="training data" style="width:300px;">

Now we ahve the data, we build a a simple cost function to calculate how far we are from the target, the closer the cost gets to zero, the closer we are to the target outcome. We do the heavy lifting of finding the distance using an average square, and include a bias to drive the model toward accuracy

<img src="imgs/cost_function.png" alt="Cost function" style="width:500px;">


Using this approch we can begin iterating over the cost fuction for some basic training:

<img src="imgs/double_outcome.png" alt="training output" style="width:340px;">


But a single input can only do so much work, let's add another input and increase our power

<img src="imgs/two_inputs.png" alt="Nueron with two inputs" style="width:400px;">

First we update our training method to add the second weight and bind the output range using sigmoid

<img src="imgs/two_input_logic.png" alt="two input logic" style="width:400px;">




It is important to note how critical the added bias parameter is here for accuracy, as without it we can only drive the output based on the input parameters alone. But with a bias, the model can take the entire state of the output and shift it around left or right regardless of the inputs. 


We then construct our training method that iterates over the cost and drives it down using epsilon and a set rate as dial knobs to experiement changing for finer control of the outcome

<img src="imgs/training_cycles.png" alt="Training cycles" style="width:500px;">




Now we have a single artificial neuron with two inputs which uses signmoid as an activity function to limit unbound values, and uses a bias to shift the outcome. We can now begin training on new data to model logic gates. This gives us AND, OR and NAND gate models that function well. 

<img src="imgs/gate_training_data.png" alt="Gate Training Data" style="width:200px;">



This yeilds good results with one million training cycles:

![Image](imgs/img.png)


One challenge is an XOR gate which can not be modeled with a single neuron. We must look to create copies of this neuron into a network to increase the processing power. Using these non-XOR gates, we can compose them into a small neural network to approximate an XOR gates function.


![Image](imgs/neural_net.png)











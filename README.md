
# Machine Learning in C

Let's skip all the high level data science and see if we can use some basic C to train a model using some less complex maths.

![Image](imgs/artifical_neuron.png)

Our first job is to start by building a single artificial neuron with a single input 'x' and weight 'w', that when summed will yield a desired outcome in 'y'.

![Image](imgs/single_input.png)


In order to 'learn' we must give the neuron input patterns in values we can iterate over until we 'train' the neuron to give us the expected 'y' output value that matches the desired outcome. In this example we do this with simple training data that doubles the input. With enough training, the model weights should be able to predict the correct answer, which is the the double of any input value without knowing the math directly. 

<img src="imgs/double.png" alt="training data" style="width:300px;">

Now we have the data, we build a a simple cost function to calculate how far the guess is from the target 'y' value. The closer the cost gets to zero, the closer we are to the target outcome value. We do the heavy lifting of finding the distance using an average square function, and include a bias to drive the model toward accuracy independent of input values.

<img src="imgs/cost_function.png" alt="Cost function" style="width:500px;">


Using this approach, and with random inputs values, we can begin iterating over the cost function and use the training data as our target answers. This works well enough, as the cost gets close to zero with little training.

<img src="imgs/double_outcome.png" alt="training output" style="width:340px;">

But a single input can only do so much work, let's add another input and increase our power!

<img src="imgs/two_inputs.png" alt="Nueron with two inputs" style="width:400px;">

First we update our cost function to add the second input and calculate the weights correctly, then bind the output range using the sigmoid function.

<img src="imgs/two_input_logic.png" alt="two input logic" style="width:400px;">




It is important to note how critical the added bias parameter is here for accuracy, as without it we can only drive the output based on the input parameters alone. But with a bias, the model can take the entire state of the output and shift it around left or right regardless of the inputs. 


We then construct our training method that iterates over the cost and drives it down toward our target value using the help of epsilon and a set rate as dial knobs we can alter for better results.

<img src="imgs/training_cycles.png" alt="Training cycles" style="width:500px;">




Now we have a single artificial neuron with two inputs which uses sigmoid as an activity function to limit unbound values, and a bias to shift the outcome as needed. We can now begin training on new data, in this case truth tables to model logic gates. This data allows us to train AND, OR and NAND gate models. 

<img src="imgs/gate_training_data.png" alt="Gate Training Data" style="width:200px;">



This yields good results with one million training cycles:

![Image](imgs/img.png)


One challenge is an XOR gate which can not be modeled with a single neuron alone. We need to design an architecture to reuse our neuron and build a small neural network to increase the processing power and compose our gates to do work together.

Using our trained non-XOR gate models, we can compose them into a small neural network to approximate an XOR gate.


![Image](imgs/neural_net.png)

We are not sure at this point if this is the correct pattern yet, but we can allocate enough neurons for a small network that can  begin to find the solution with.  Each gate will have two weights and a bias which increases the total number of our parameters from two to nine.














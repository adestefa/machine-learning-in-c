
# Machine Learning in C

Let's skip all the high data science, matrices and derivatives and see if we can use simple C to train a model using basic methods...

![Image](imgs/artifical_neuron.png)

We start by building a single artifical neuron with a single input and weight.

![Image](imgs/single_input.png)

Then we train this on some simple training data that doubles the input:

<img src="imgs/double.png" alt="Image Description" style="width:300px;">

A simple cost function that includes an average square and bias 

<img src="imgs/cost_function.png" alt="Image Description" style="width:500px;">

Using this approch we can begin training the model:

<img src="imgs/double_outcome.png" alt="Image Description" style="width:340px;">

But a single input can only do so much work, let's add another input and increase our power

<img src="imgs/two_inputs.png" alt="Image Description" style="width:400px;">

Now we have a single artificial neuron with  two inputs that uses signmoid as an activity function to limit unbound values, and uses a bias to shift the outcome. 

We can then begin training on new data to model logic gates. This gives us AND, OR and NAND models that function well. 

<img src="imgs/gate_training_data.png" alt="Image Description" style="width:300px;">



This yeilds good results with one million training cycles:

![Image](imgs/img.png)

One challenge is an XOR gate which can not be modeled with a single neuron. We must look to create copies of this neuron into a network to increase the processing power.

Using these non-XOR gates, we can compose them into a small neural network to approximate an XOR gates function.


![Image](imgs/neural_net.png)











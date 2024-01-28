#import <stdio.h>
#import <stdlib.h>
#import <time.h>


/*

   Machine Learning in C with Tsoding! 1/24/2024 11:24PM
   trying to predict some number based on input number
   https://www.youtube.com/watch?v=PGSba51aRYU&t=4797s

   >Create a single neuron with two input signals
   >Use sigmoid as our action function to constrain unbound values
   >Model a simple OR Gate

    Artificial Neuron
   [x2] -w1- | LF | AF | 
                        ---- y
   [x2] -w2- | LF | AF | 
  
  inputs are connected to weights and neuron sums them up by multiplying by the weights
  y = ((x1*w1) + (x2*w2) + (x3*w3) + b)... 
  Then we add the bias after weights are calculated
  Our model is a single artificial neuron with a two input connections

  1.  Inputs:              Several input x's            x1,x2
  2.  Bias:                shifts the value L|R         b
  3.  Weights:             how strong is this conn      w1,w2
  3.  Linear Function:     sum the inputs with weights  x1*w1 + x2*w2...
  4.  Activation Function: constrain unbound values     sigmoid function maps -infinity / +infinity to 0/1
  5.  Output:                                           y      


  */


/*
 Define Xor as 9 parameters
    Weight parameters per gate:
      OR   : w1,w2,b
      NAND : w1,w2,b
      AND  : w1,w2,b
*/
typedef struct {
    // Layer 1
    float or_w1;
    float or_w2;
    float or_b;

    float nand_w1;
    float nand_w2;
    float nand_b;
    
    // Layer 2s
    float and_w1;
    float and_w2;
    float and_b;
    
} Xor;



// constrain unbound values between 0 and 1
float sigmoidf(float x)
{
    return 1.f / (1.f + expf(-x));
}

/*

    Now we have a functioning model of gates using a single artificial neuron
    How can we use them to build an architecture for a small neural network?

    Input    Layer1    Layer2    Output
    ------------------------------------
    x1 -->  [OR]   -->  |
        |              [AND] --> y
    x2 -->  [NAND] -->  |
    -----------------------------------

    compose neurons into a network of gate layers
    without matrices, doing it as manually as possible
    explicit mapping between the architecture
    and actual code we have here
*/
float forward(Xor m, float x, float y)
{
   
   // layer 1
   float a =  sigmoidf(m.or_w1*x + m.or_w2*y + m.or_b);
   float b =  sigmoidf(m.nand_w1*x + m.nand_y + m.nand_b);
   
   // layer 2
   return sigmoidf(a*m.and_w1 + b*m.and_w2 + m.and_b);

}

// Define our training data
 float trainXOR[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0},
 }; 


// cost function does not know about 
// the neural node architecture, and 
// it doesn't know the concept of neuron
// instead you just feed it two inputs
float cost(Xor m, float x1, float x2) 
{
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i) {
        
        // train using two inputs
        float x1 = train[i][0];
        float x2 = train[i][1];
        
        // feed data into the model
        float y = forward(m, x1, x2) 
        
        // find the distance between input and outcome
        float d = y - train[i][2];

        // amplify small errors
        result += d*d;
        
        // if the value is big it is very bad
        // if it is zero it fits the data perfectly
        result /= train_count;

        // is y equal to what we expect?  (print the training goal data)
        //printf("actual: %f, expected: %f, AvgSq: %f\n", y, train[i][1], result);

    }
    return result;
}

// Xor can be calculated with (x|y) & -(x&y)
int main(void) 
{
    printf("XOR");
    return 0;
}
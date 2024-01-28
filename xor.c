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


int main(void) 
{
    printf("XOR");
    return 0;
}
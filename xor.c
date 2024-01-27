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

    Artifical Neuron
   [x2] -w1- | LF | AF | 
                        ---- y
   [x2] -w2- | LF | AF | 
  
  inputs are connected to weights and neuron sums them up by multiplying by the weights
  y = ((x1*w1) + (x2*w2) + (x3*w3) + b)... 
  Then we add the bias after weights are calcualted
  Our model is a single artificial neuron with a two input connections

  1.  Inputs:              Several input x's            x1,x2
  2.  Bias:                shifts the value L|R         b
  3.  Weights:             how strong is this conn      w1,w2
  3.  Linear Function:     sum the inputs with weights  x1*w1 + x2*w2...
  4.  Activation Function: constrain unbound values     sigmoid function maps -infinity / +infinty to 0/1
  5.  Output:                                           y      


    Now we have a functioning model of gates using a single artificial neuron
    How can we use them to biuld an architecture for a small neural network?

    Input    Layer1    Layer2    Result
    ------------------------------------
    x -->  [OR]   -->  |
        |              [AND] --> y
    y -->  [NAND] -->  |
    -----------------------------------
    Weight parameters per gate:
      OR   : w1,w2,b
      NAND : w1,w2,b
      AND  : w1,w2,b



  */





int main(void) 
{
    printf("XOR");
    return 0;
}
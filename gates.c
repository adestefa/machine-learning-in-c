#import <stdio.h>
#import <stdlib.h>
#import <time.h>
#import <math.h>

/*

   Machine Learning in C with Tsoding! 1/24/2024 11:24PM
   trying to predict some number based on input number
   https://youtu.be/PGSba51aRYU?si=AoukTdQHbrXzhnFW&t=2458

   >Model a single neuron with a two input signals
  
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
  5.  Output:              

  */





float sigmoidf(float x)
{
    return 1.f / (1.f + expf(-x));
}


 float train[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1},
 };
#define train_count (sizeof(train)/sizeof(train[0]))


// returns 0 to RAND_MAX
float rand_float(void)
{
   int r = rand();
   //printf("\n--------------------\nR:%d \n", r);
   return (float) r/ (float) RAND_MAX;
}


float cost(float w1, float w2) 
{
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i) {
        
        // train using two inputs
        float x1 = train[i][0];
        float x2 = train[i][1];
        
        // feed data into the model
        // sigmoid constrains unbounded values to 0 and 1
        float y = sigmoidf(x1*w1 + x2*w2); 

        // how bad is it? let's use the Average Square 
        // find the distance between actual and expected
        // subtract the actual
        // find the distance between input and outcome
        float d = y - train[i][2];

        // first any negatives by negative will be positive
        // will amplfy small errors, something off will be
        // instantly visible 
        // note: a cube here will be non-zero, square is steeper curve
        result += d*d;
        
        // if the value is big it is very bad
        // if it is zero it fits the data perfectly
        // Note: look out for "over-fitting", works but fails to predict new data
        // only predicts training data and nothing new. 
        result /= train_count;

        // is y equal to what we expect?  (print the training goal data)
        //printf("actual: %f, expected: %f, AvgSq: %f\n", y, train[i][1], result);

    }
    return result;
}


int main(void)
{
    
    // we are not starting from a good initial state
    // what if we just do this thing randomly every time
    //srand(69);    // fixed
    srand(time(0)); // randomly

    // we can modify the one parameter we have 
    float eps = 1e-1;
    float rate = 1e-1;
 
    float w1 = rand_float();
    float w2 = rand_float();

    size_t cycles = 1000*1000;

    for (size_t i = 0; i < cycles; ++i) {
        // calculate the cost
        float c = cost(w1, w2);
        // can we drive the cost down?
        float dw1 = (cost(w1 + eps, w2) - c)/eps;
        float dw2 = (cost(w1, w2 + eps) - c)/eps;
        w1 -= rate*dw1;
        w2 -= rate*dw2;
        printf("w1 = %f,  w2 = %f, c = %f\n", w1, w2, cost(w1, w2));
        
    }
        printf("----------[ Training Cycles: %zu ]-----------\n", cycles);
        printf("> w1 = %f,  w2 = %f, c = %f\n", w1, w2, cost(w1, w2));
        printf("-------------------------------------------------\n");

    return 0;
}
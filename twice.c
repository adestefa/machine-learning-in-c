#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 /*

   Machine Learning in C with Tsoding! 1/24/2024 11:24PM
   trying to predict some number based on input number
   https://youtu.be/PGSba51aRYU?si=AoukTdQHbrXzhnFW&t=2458

   >Model a single neuron with a two input signals
  
     Artificial Neuron
   [x2] -w1- | LF | AF | 
                        ---- y
   [x2] -w2- | LF | AF | 
  
  inputs are connected to weights and neuron sums them up by multiplying by the weights
  y = ((x1*w1) + (x2*w2) + (x3*w3) + b)... 
  Then we add the bias after weights are calculated
  Our model is a single artificial neuron with a two input connections

  1.  Inputs:              Several input x's            x1,x2,x3,x4
  2.  Bias:                shifts the value L|R         b
  3.  Weights:             how strong is this conn      w1,w2,w3,w4
  3.  Linear Function:     
  4.  Activation Function: 
  5.  Output:              

  */




// training set (one number in, one number out)
// array of pair of numbers
//  first: input 
// second: what we expect
float train[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
};

// gives us the amount of elements dynamically
#define train_count (sizeof(train)/sizeof(train[0]))


// 1 000 000 000 000 => GPT-4
// 1 => us


// returns 0 to RAND_MAX
float rand_float(void)
{
   int r = rand();
   //printf("\n--------------------\nR:%d \n", r);
   return (float) r/ (float) RAND_MAX;
}

// input is the whole model
// we need to find if w finds the answer
// how do we know it found it in the data?
// we can iterate over the training data and see if it fits our data
// does it return the same or not.. we know nothing about the data or model
// just see how well it performs 
float cost(float w, float b) 
{
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i) {
        
        // training input data
        float x = train[i][0];
        
        // feed into the model
        float y = x*w + b; // include bias

        // how bad is it? let's use the Average Square 
        // find the distance between actual and expected
        // subtract the actual
        // find the distance between input and outcome
        float d = y - train[i][1];

        // first any negatives by negative will be positive
        // will amplify small errors, something off will be instantly visible 
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

int main()
{
    // formula: y = x*w
    // srand(time(0));    
    srand(69);

    // weight
    float w = rand_float()*10.0f;

    // bias
    float b = rand_float()*5.0f;

    // our job is to drive the cost function to zero!
    // the closer to zero the better the model behaves on that training data
    //printf("B:%f\n", cost(w));
    
    // we can modify the one parameter we have 
    float eps = 1e-3;
    float rate = 1e-3;
    // let's gently shift and see how it impacts the performance of the model
    // printf("%f\n", cost(w - eps*2));

    // since this works, we can automate the process!
    // we are someplace on the slope of the cost function
    // if we take the derivative, it will tell us which direction the function grows
    // if you go in the opposite direction it grows, you will go to the minimum and get stuck there (drain)
    // approximate a derivative
    for ( size_t i = 0; i<800; ++i) {
        float c = cost(w, b);

        // model now takes two parameters
        float dw = (cost(w + eps, b) - c)/eps;
        float db = (cost(w, b + eps) - c)/eps;
        
        // single artificial neuron (perceptron)
        w -= rate*dw;
        b -= rate*db;

        printf("cost = %f, w = %f, b = %f\n", cost(w, b), w, b); 
    }
    printf("-----------------------\n");
    printf("w = %f, b = %f\n", w, b);


    // sometimes where you start is important
    // this is why it is randomized so if it doesn't happen one time you can try again
    // re run from a different place.. stir the pile of linear algebra and try again


    return 0;
}
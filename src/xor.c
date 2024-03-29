#import <stdio.h>
#import <stdlib.h>
#import <time.h>
#import <math.h>

/*
   Inspired by:
   Machine Learning in C with Tsoding!
   Trying to approximate an XOR gate using a small neural network.
   https://www.youtube.com/watch?v=PGSba51aRYU&t=7989s

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

    Now let's design an architecture to combine neurons into a small neural network. 

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


// returns 0 to RAND_MAX
float rand_float(void)
{
   int r = rand();
   //printf("\n--------------------\nR:%d \n", r);
   return (float) r/ (float) RAND_MAX;
}

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
   float b =  sigmoidf(m.nand_w1*x + m.nand_w2*y + m.nand_b);
   
   // layer 2
   return sigmoidf(a*m.and_w1 + b*m.and_w2 + m.and_b);

}

// Define our training data
 float train[][4] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0},
 }; 
#define model_name "AND-Gate"
#define train_count (sizeof(train)/sizeof(train[0]))

// cost function does not know about 
// the neural node architecture, and 
// it doesn't know the concept of neuron
// instead you just feed it two inputs
float cost(Xor m) 
{
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i) {
        
        // train using two inputs
        float x1 = train[i][0];
        float x2 = train[i][1];
        
        // feed data into the model
        float y = forward(m, x1, x2);
        
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

// Randomize Xor
Xor rand_xor(void)
{

    Xor m;
    m.or_w1 = rand_float();
    m.or_w2 = rand_float();
    m.or_b = rand_float();

    m.and_w1 = rand_float();
    m.and_w2 = rand_float();
    m.and_b = rand_float();

    m.nand_w1 = rand_float();
    m.nand_w2 = rand_float();
    m.nand_b = rand_float();

    return m;
}

// report values
void print_xor(Xor m)
{
    printf("XOR Random Values:\n");
  
    printf("or_w1 = %f\n", m.or_w1);
    printf("or_w1 = %f\n", m.or_w2); 
    printf("or_b = %f\n", m.or_b); 

    printf("and_w1 = %f\n", m.and_w1);
    printf("and_w1 = %f\n", m.and_w2);
    printf("and_b = %f\n", m.and_b);

    printf("nand_w1 = %f\n", m.nand_w1);
    printf("nand_w1 = %f\n", m.nand_w2);
    printf("nand_b = %f\n", m.nand_b);
   
 
}

/*
    Compute original cost,
    Then "wiggle" the values
*/
Xor finite_diff(Xor m, float eps)
{
    // store our calculations
    Xor g; 

    // running operations on floats incurs errors
    // let's restore our bit values after our calculations
    float saved; 

    // calculate original cost
    float c = cost(m);
   
    // OR weight 1
    saved = m.or_w1;                // save the original
    m.or_w1 += eps;                 // wiggle it by epsilon
    g.or_w1 = (cost(m) - c) / eps;  // compute the new cost, find the diff
    m.or_w1 = saved;                // restore original bits
    
    // OR weight 2
    saved = m.or_w2;
    m.or_w2 += eps;
    g.or_w2 = (cost(m) -c) / eps;
    m.or_w2 = saved;

     // OR bias
    saved = m.or_b;
    m.or_b += eps;
    g.or_b = (cost(m) -c) / eps;
    m.or_b = saved;

    // .. repeat for other six params...
      
    // NAND weight 1
    saved = m.nand_w1;                // save the original
    m.nand_w1 += eps;                 // wiggle it by epsilon
    g.nand_w1 = (cost(m) - c) / eps;  // compute the new cost, find the diff
    m.nand_w1 = saved;                // restore original bits
    
    // NAND weight 2
    saved = m.nand_w2;
    m.nand_w2 += eps;
    g.nand_w2 = (cost(m) -c) / eps;
    m.nand_w2 = saved;

     // NAND bias
    saved = m.nand_b;
    m.nand_b += eps;
    g.nand_b = (cost(m) -c) / eps;
    m.nand_b = saved;


     
    // AND weight 1
    saved = m.and_w1;                // save the original
    m.and_w1 += eps;                 // wiggle it by epsilon
    g.and_w1 = (cost(m) - c) / eps;  // compute the new cost, find the diff
    m.and_w1 = saved;                // restore original bits
    
    // AND weight 2
    saved = m.and_w2;
    m.and_w2 += eps;
    g.and_w2 = (cost(m) -c) / eps;
    m.and_w2 = saved;

     // AND bias
    saved = m.and_b;
    m.and_b += eps;
    g.and_b = (cost(m) -c) / eps;
    m.and_b = saved;

    return g;

}

// Subtract G from M to give us the distance
Xor learn(Xor m, Xor g, float learning_rate)
{
    m.or_w1 -= learning_rate*g.or_w1;
    m.or_w2 -= learning_rate*g.or_w2;
    m.or_b  -= learning_rate*g.or_b;

    m.and_w1 -= learning_rate*g.and_w1;
    m.and_w2 -= learning_rate*g.and_w2;
    m.and_b -= learning_rate*g.and_b;

    m.nand_w1 -= learning_rate*g.nand_w1;
    m.nand_w2 -= learning_rate*g.nand_w2;
    m.nand_b -= learning_rate*g.nand_b;

    return m;
} 




int main(void) 
{
    float eps = 1e-1;
    float rate = 1e-1;

    // Initialize and randomize an Xor data structure
    Xor m = rand_xor();
    
     // drive down the cost over cycles of learning
    for (size_t i=0; i<100*1000; ++i) {
        
        // Calculate cost and wiggle weights/bias
        Xor g = finite_diff(m, eps);
        
        // subtract the diff from the original
        m = learn(m, g, rate);

        // calculate new cost
        printf("%f\n", cost(m));
    }

    printf("--------------------------\n");
    for (size_t i=0; i<2; ++i) {
        for (size_t j=0; j<2; ++j) {
            printf("%zu ^ %zu = %f\n", i, j, forward(m, i, j));  
        }
    }


    return 0;
}
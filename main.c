#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define MAX_INPUT 1000
#define MAX_ITERATIONS 900000
#define LEARNING_RATE .2


int main()
{
      int i,j,k=0;
      int input_record_count=0;
      int error=0;
      double summation = 0;
      int iteration_count = 0;
      double height[MAX_INPUT]= {0};
      double BMI[MAX_INPUT]= {0};
      char output[MAX_INPUT];
      int normalized_output[MAX_INPUT];
      int prediction = 0;
      bool weights_updated = true;
            
            
    printf("Perceptron - Machine Learning - Linear Regression Algorithym\n\n");

    // Read in the initial dataset into an array.
    FILE *pFile;
    //pFile = fopen ("input2.txt", "r");
    pFile = fopen ("kaggle_plus479x.txt", "r");
    //pFile = fopen ("kaggle_master.txt", "r");
    if (pFile == NULL)
    {
      printf ("error opening file");
      return 0;
    }

    while (fscanf(pFile,"%lf,%lf,%c", &height[input_record_count], &BMI[input_record_count], &output[input_record_count]) != EOF)
    {
        if (output[input_record_count] == '1') {
          normalized_output[input_record_count] = 1; // Positive output
        } else {
          normalized_output[input_record_count] = 0; // Negative output
        }
        printf ("Height = %-15.13lf  BMI = %-15.13lf Output = %c \toutput = %d\n",height[input_record_count], BMI[input_record_count], output[input_record_count], normalized_output[input_record_count]);
        input_record_count++;
    }
    printf ("Total input records: %d\n\n", input_record_count);

    
    // Train the algorythm.
    // Initialize the weight vector to zero.
    double weights[3] = {0}; // Three features: bias, height, and BMI

    //Keep looping until the weight is no loner updated.
    while ( (weights_updated == true) && (iteration_count < MAX_ITERATIONS) ) {
      iteration_count++;
      //printf ("Iteration %d\t\t\ty = (%.13lf)x + %.13lf\n", iteration_count, weights[1]/fabsf(weights[2]), weights[0]);
      weights_updated = false; // Reset the flag for this iteration
        
      
      //Loop through each data point and update the weights if needed.
        for(i=0; i<input_record_count; i++) {
          //printf("\tData Point %d\n: ", i+1);
          //printf("\t\tWeight Vector   = %-15.13lf %-15.13lf %-15.13lf\n", weights[0], weights[1], weights[2]);
          //printf("\t\tData_Vector     = %-15.13lf %-15.13lf %-15.13lf\n", 1.00, height[i], BMI[i]);
          
          //summation = normalized_output[i] * ((weights[0] * 1) + (weights[1] * height[i]) + (weights[2] * BMI[i]));
          summation = (weights[0] * 1) + (weights[1] * height[i]) + (weights[2] * BMI[i]);
          if (summation >= 0) {
            prediction = 1; // Positive output
          } else {
            prediction = 0; // Negative output
          }

          error = normalized_output[i] - prediction;
          
          if (error != 0) {
//          if (summation <= 0) {
            weights[0] = (weights[0] + (LEARNING_RATE * error * 1)); // Update weight for bias
            weights[1] = (weights[1] + (LEARNING_RATE * error * height[i])); // Update weight for height
            weights[2] = (weights[2] + (LEARNING_RATE * error * BMI[i]));    // Update weight for BMI
//            weights[0] = (weights[0] + (LEARNING_RATE * normalized_output[i] * 1)); // Update weight for bias
//            weights[1] = (weights[1] + (LEARNING_RATE * normalized_output[i] * height[i])); // Update weight for height
//            weights[2] = (weights[2] + (LEARNING_RATE * normalized_output[i] * BMI[i]));    // Update weight for BMI
            weights_updated = true; 
            //printf("\t\t\t\t\t--> Updated weight Vector= [%.13lf, %.13lf, %.13lf]\n", weights[0], weights[1], weights[2]);
          } else {          
            //printf("\t\tNo update needed for weight Vector\n");
          }
        }

        

      }


    // ========================================================
    // FINAL Results
    // ========================================================
    printf("\n\n========================================================\n");
    printf("===================    FINAL RESULTS    ==================\n");
    printf("========================================================\n");
    printf("\nFinal weight Vector after %d iterations: [%.2f, %.2f, %.2f]\n", iteration_count, weights[0], weights[1], weights[2]);
    printf("Formula of the hyperplane: y = (%.6f)x + %.4f\n", weights[1]/fabsf(weights[2]), weights[0]);
    
    
    return 0;
}




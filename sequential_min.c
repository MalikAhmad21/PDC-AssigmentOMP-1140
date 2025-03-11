#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define N 1000000 // Size of an array

// Function to generate random numbers with a shifting range
void generate_array(int arr[], int size)
{
   int min_range = rand() % 1000 + 1; // Ensures a changing minimum start from 1 to 1000
   int max_range = min_range + 1000;  // Keeps range dynamic

   for (int i = 0; i < size; i++)
   {
      arr[i] = rand() % (max_range - min_range) + min_range; // Random numbers in a shifting range
   }
}

int find_min_sequential(int arr[], int size)
{
   int min_val = INT_MAX;
   for (int i = 0; i < size; i++)
   {
      if (arr[i] < min_val)
      {
         min_val = arr[i];
      }
   }
   return min_val;
}

int main()
{
   int arr[N];
   srand(time(0) + rand()); // For More Randomness

   generate_array(arr, N);

   // Sequential Execution
   clock_t start_time = clock();
   int min_seq = find_min_sequential(arr, N);
   clock_t end_time = clock();

   double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
   printf("Sequential Min: %d \nTime: %f seconds\n", min_seq, time_taken);

   return 0;
}

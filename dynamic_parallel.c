#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <omp.h>

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

// Parallel function to find the minimum using OpenMP with dynamic scheduling
int find_min_parallel_dynamic(int arr[], int size, int num_threads)
{
   int min_val = INT_MAX;

#pragma omp parallel for num_threads(num_threads) schedule(dynamic) reduction(min : min_val)
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
   srand(time(0) + rand()); // For more randomness

   generate_array(arr, N);

   // // Parallel execution with 2 threads for Dynamic Scheduling
   // double start_time = omp_get_wtime();
   // int min_par_2 = find_min_parallel_dynamic(arr, N, 2);
   // double end_time = omp_get_wtime();
   // printf("Parallel Min for 2 threads, dynamic: %d \nTime: %f seconds\n", min_par_2, end_time - start_time);

   // Parallel execution with 4 threads for Dynamic Scheduling
   double start_time = omp_get_wtime();
   int min_par_4 = find_min_parallel_dynamic(arr, N, 4);
   double end_time = omp_get_wtime();
   printf("Parallel Min for 4 threads, dynamic: %d \nTime: %f seconds\n", min_par_4, end_time - start_time);

   return 0;
}

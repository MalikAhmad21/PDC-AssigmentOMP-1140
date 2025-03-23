#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <omp.h>

#define N 1000000       // Size of an array
#define CHUNK_SIZE 1000 // Chunk size for static scheduling

// Function to generate random numbers
void generate_array(int arr[], int size)
{
   int min_range = rand() % 1000 + 1;
   int max_range = min_range + 1000;

   for (int i = 0; i < size; i++)
   {
      arr[i] = rand() % (max_range - min_range) + min_range;
   }
}

// Parallel function using Static Scheduling (Chunk Size = 1000)
int find_min_parallel_static(int arr[], int size, int num_threads)
{
   int min_val = INT_MAX;

#pragma omp parallel for num_threads(num_threads) schedule(static, CHUNK_SIZE) reduction(min : min_val)
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
   srand(time(0) + rand());

   generate_array(arr, N);

   // // Parallel execution with 2 threads Static Scheduling, Chunk Size 1000
   // double start_time = omp_get_wtime();
   // int min_par_static_2 = find_min_parallel_static(arr, N, 2);
   // double end_time = omp_get_wtime();
   // printf("Parallel Min for 2 threads with Static Chunk 1000: %d \nTime: %f seconds\n", min_par_static_2, end_time - start_time);

   // // Parallel execution with 4 threads Static Scheduling, Chunk Size 1000
   double start_time = omp_get_wtime();
   int min_par_static_4 = find_min_parallel_static(arr, N, 4);
   double end_time = omp_get_wtime();
   printf("Parallel Min for 4 threads with Static Chunk 1000: %d \nTime: %f seconds\n", min_par_static_4, end_time - start_time);

   return 0;
}

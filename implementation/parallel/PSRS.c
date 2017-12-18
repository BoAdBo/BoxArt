#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mpi.h"

#define MAX_ARRAY_SIZE (int)1e8

int array[MAX_ARRAY_SIZE];
int buffer[MAX_ARRAY_SIZE];

// since c doesn't support reference, implement a simple swap function
void swap(int * a, int * b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

/*
  Suppose the pivot's index is n
  Put the elements smaller than pivot before index n, and the elements larger than pivot after index n
  return n
 */
int parition(int* array, int pivot_pos, int low, int high) {
  // isolate the low(i.e the first position), which puts the pivot here
  int pivot = array[pivot_pos];
  swap(array + low, array + pivot_pos);// passing pointers here
  int less = low; // points to the last index of the smaller elements

  // starts to iterate and updates the less pointer when a smaller elements are found and swap
  for(int iter = low + 1; iter <= high; ++ iter) {
    if(array[iter] < pivot) {
      less++;
      swap(array + iter, array + less);
    }
  }

  // swap the pivot into the right position
  swap(array + low, array + less);
  return less;
}

void quicksort_rec(int * array, int low, int high) {
  if(low < high) {
    int pivot_pos = (low + high) / 2;

    pivot_pos = parition(array, pivot_pos, low, high);

    quicksort_rec(array, low, pivot_pos-1);
    quicksort_rec(array, pivot_pos+1, high);
  }
}

void quicksort(int * array, int length) {
  quicksort_rec(array, 0, length - 1);
}

/*
  After calling, the merged list will be in the buffer space, index starts from 0, and have enough space to hold the new array
  with length of (high2 + high1 - (low1 + low2) + 2)
 */
void merge(int * first, int * second, int * buffer, int low1, int high1, int low2, int high2) {
  //int p1(low1), p2(low2), buff_p(0); this is the c plus plus way of initilization

  int p1 = low1, p2 = low2, buff_p = 0;
  // picks out the smaller of the two array, until one of the array is exhausted
  while(p1 <= high1 && p2 <= high2) {
    if(first[p1] < second[p2]) {
      buffer[buff_p] = first[p1];
      p1++;
    }
    else {
      buffer[buff_p] = second[p2];
      p2++;
    }
    buff_p++;
  }

  // although don't know which array is exhausted, but the one of the pointer would indicate that, pick out the rest of the array
  while(p1 <= high1) {
    buffer[buff_p] = first[p1];
    p1++;
    buff_p++;
  }

  while(p2 <= high2) {
    buffer[buff_p] = second[p2];
    p2++;
    buff_p++;
  }
}

void test() {
  // MPI_Init(argc, argv);
  // int rank, size;

  // MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // MPI_Comm_size(MPI_COMM_WORLD, &size);

  // MPI_Finalize();
  srand(time(0));
  int size = 1e8;
  for(int i = 0; i < size; ++ i) {
    //array[i] = size-i;
    array[i] = rand() % 100000;
  }

  quicksort_rec(array, 0, size/2);
  quicksort_rec(array, size/2+1, size-1);
  merge(array, array,buffer,  0, size/2, size/2+1, size-1);

  for(int i = 0; i < size-1; ++ i) {
    /* if(array[i] > array[i + 1]) { */
    /*   printf("Wrong!\n"); */
    /* } */
    if(buffer[i] > buffer[i + 1]) {
      printf("Wrong!\n");
    }
  }

  /* for(int i = 0; i < size; ++ i) { */
  /*   //printf("%d, ", array[i]); */
  /*   printf("%d, ", buffer[i]); */
  /* } */
}

void divide_quicksort(int * array, int rank, int size, int n) {
  // Send messages
  if(rank == 0) {
    
  }
  else {
    
  }
}



int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);
  int array_length = 10;
  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if(rank == 0) {
    srand(time(0));
    int size = array_length;
    for(int i = 0; i < size; ++ i) {
      //array[i] = size-i;
      array[i] = rand() % 100000;
    }
  }

  divide_quicksort(array, rank, size, array_length);

  MPI_Finalize();
  /* if(rank == 0) { */
  /*   for(int i = 0; i < array_length; ++ i) { */
  /*     printf("%d ", array[i]); */
  /*   } */
  /* } */
}

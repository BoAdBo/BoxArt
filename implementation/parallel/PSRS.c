#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mpi.h"
#include <stdbool.h>

#define comm MPI_COMM_WORLD

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

/* Try an easy implementation first*/
void k_way_merge(int ** arrays, int * merged, int * epos, int k) {
  // find mean
  int * ps = (int*)malloc(sizeof(int)*k);
  bool * ended_array = (bool *)malloc(sizeof(bool)*k);
  int p_merged = 0;
  for(int i = 0; i < k; ++ i) {
    ps[i] = 0;// stores the pointer to current number
  }

  int min = arrays[0][0];
  int min_index = 0;
  //printf("In k way merge\n");
  for(int i = 0; i < k; ++ i) {
    ended_array[i] = false;
  }

  while(true) {
    for(int i = 0; i < k; ++ i) {
      if(ps[i] < epos[i]) {
        if(min > arrays[i][ps[i]]) {
          min = arrays[i][ps[i]];
          min_index = i;
        }
      }
      else {
        ended_array[i] = true;
      }
    }

    merged[p_merged] = min;
    p_merged++;
    ps[min_index]++;

    bool out = true;
    for(int i = 0; i < k; ++ i) {
      out = out && ended_array[i];
    }
    if(out) {
      break;
    }
  }

  for(int i = 0; i < k*epos[0]; ++ i) {
    printf("%d ", merged[i]);
  }
  printf("\n");

  free(ps);
  free(ended_array);
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

/*
  pass in the divided array for quick sort
 */
void divide_quicksort(int * array, int start, int end) {
  // Send messages
  /* if(rank == 0) { */
  /*   printf */
  /* } */
  /* else { */
  /* } */
  //printf("rank %d: ", rank);
  printf("start: %d, end: %d\n", start, end);
  quicksort_rec(array, start, end-1);
  for(int i = start; i < end; ++ i) {
    printf("%d ", array[i]);
  }
  printf("\n");
}


int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  /*
    In preparation for dividing jobs and initialization
   */
  int array_length = 20;
  int rank, size;
  int local_length;
  int start, end;
  // end points to null, which is i + 1, where i is the last index
  int *array; // to reduce ram consumption, allocate only in process 0
  int *buffer;
  int *local_array;
  int *pivot_buffer, *cbuffer, *temp_buffer;

  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);

  local_length = (array_length + size - 1) / size; // compute celling, to cooperate with passing same amount chunks of data
  //printf("%d %d\n", rank, local_length);
  // each process computes their range
  if(rank == size - 1) {
    start = 0;
    end = ((array_length) % local_length);
    if(end == 0) {
      end = local_length;
    }
  }
  else {
    start = 0;
    end = local_length;
  }

  // Input of data, using rand
  if(rank == 0) {
    // make the array a little bigger, to avoid out of bound index
    array = (int*)malloc(sizeof(int)*(local_length * size));
    srand(time(0));
    for(int i = 0; i < array_length; ++ i) {
      //array[i] = array_length - i;
      array[i] = rand() % 100000;
    }
    //MPI_Send(array, array_length, MPI_INT, )
  }
  local_array = (int*)malloc(sizeof(int)*local_length);
  MPI_Scatter(array, local_length, MPI_INT,
              local_array, local_length, MPI_INT,
              0, comm);
  //MPI_Bcast(array, array_length, MPI_INT, 0, comm);

  divide_quicksort(local_array, start, end);

  int cbuf_size = (size-1);
  cbuffer = (int*)malloc(sizeof(int) * cbuf_size);
  int w = array_length / (size * size);
  // assume big enough array, no exception handling
  for(int i = 1; i <= size-1; ++ i) {
    cbuffer[i-1] = local_array[w * i];
  }

  if(rank == 0) {
    pivot_buffer = (int*)malloc(sizeof(int) * cbuf_size * size);
  }


  MPI_Gather(cbuffer, cbuf_size, MPI_INT,
             pivot_buffer, cbuf_size, MPI_INT,
             0, comm);
  // in this case the cbuffers are in the smae size

  // next, in order to pass in size number of array for k way merge, make a pointer array
  {
    if(rank == 0) {
      int** pivot_spos = (int **)malloc(sizeof(int*)*size); // pointing to the corresponding start
      int* pivot_epos = (int *)malloc(sizeof(int)*size);    // the corresponding end index
      temp_buffer = (int *)malloc(sizeof(int)*size*cbuf_size);

      for(int i = 0; i < size; ++ i) {
        pivot_spos[i] = pivot_buffer + i * (cbuf_size);
        pivot_epos[i] = (i+1) * cbuf_size;
      }

      k_way_merge(pivot_spos, temp_buffer, pivot_epos, size);

      free(pivot_spos);
      free(pivot_epos);
    }
  }

  //MPI_Barrier(comm);


  if(rank == 0) {
    printf("pivot list: ");
    for(int i = 0; i < cbuf_size * size; ++ i) {
      printf("%d ", pivot_buffer[i]);
    }
    printf("\n");
  }

  MPI_Finalize();
  /* if(rank == 0) { */
  /*   for(int i = 0; i < array_length; ++ i) { */
  /*     printf("%d ", array[i]); */
  /*   } */
  /* } */
}

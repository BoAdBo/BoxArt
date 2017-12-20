#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mpi.h"
#include <stdbool.h>

#define comm MPI_COMM_WORLD

void print_delimiter(const char * message) {
  printf("================================================================================\n");
  printf("%s", message);
}

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
int partition(int* array, int pivot_pos, int low, int high) {
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

    pivot_pos = partition(array, pivot_pos, low, high);

    quicksort_rec(array, low, pivot_pos-1);
    quicksort_rec(array, pivot_pos+1, high);
  }
}

void quicksort(int * array, int length) {
  quicksort_rec(array, 0, length - 1);
}

void k_way_merge(int ** arrays, int * merged, int * epos, int k) {
  // find mean
  int * ps = (int*)malloc(sizeof(int)*k);
  bool * ended_array = (bool *)malloc(sizeof(bool)*k);
  int p_merged = 0;
  int min_index;
  int min;
  for(int i = 0; i < k; ++ i) {
    ps[i] = 0;// stores the pointer to current number
  }

  //printf("In k way merge\n");
  for(int i = 0; i < k; ++ i) {
    ended_array[i] = false;
  }

  // test print
  /* for(int i = 0; i < k; ++ i) { */
  /*   printf("This is size %d array[%d]: ", epos[i], i); */
  /*   for(int j = 0; j < epos[i]; ++ j) { */
  /*     printf("%d, ", arrays[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  while(true) {
    // pick the first index to start the iteration
    // rule out the ended array here
    bool out = true;
    for(int i = 0; i < k; ++ i) {
      // have to pick the array that has not ended
      if(ps[i] < epos[i]) {
        min_index = i;
        min = arrays[min_index][ps[min_index]];
        out = false; // signal turned off
        break;
      }
      else {
        //        printf("array[%d] is ended\n", i);
        ended_array[i] = true;
      }
    }

    // exit if all array has ended
    if(out) {
      break;
    }

    for(int i = 0; i < k; ++ i) {
      if(!ended_array[i] && ps[i] < epos[i]) {
        if(min > arrays[i][ps[i]]) {
          min = arrays[i][ps[i]];
          min_index = i;
        }
      }
    }

    //printf("pick (index) %d from array %d to merge\n", ps[min_index], min_index);
    merged[p_merged] = min;
    p_merged++;
    ps[min_index]++;
  }

  print_delimiter("In k way merge\n");
  printf("The merge pointers: ");
  for(int i = 0; i < k; ++ i) {
    printf("%d ", ps[i]);
  }
  printf("\n");


  // In this case, because the arrays passed in have the same size
  for(int i = 0; i < k*epos[0]; ++ i) {
    //printf("%d ", merged[i]);
  }
  //printf("\n");

  free(ps);
  free(ended_array);
}

/*
  p_size is the (last index of pivots + 1) == (size of pivots)
  array to be divided into n parts, where n == p_size + 1
  partition_head[i] points to the start of partition array of index i, partition_size is the (last index of partition + 1)
 */
void mul_partition(int * array, int * pivots, int array_size, int p_size, int** partition_head, int * partition_size) {
  int j = 0;
  int i = 0;
  int head_index = -1;

  for(i = 0; i < p_size; ++ i) {
    // before iteration, note down the head
    head_index = j;
    partition_head[i] = array + j;

    // since array is sorted
    // iterate through array until elements are greater than pivots
    while(array[j] < pivots[i]) {
      j++;
    }
    // now array[j] is the first one to be larger than pivots[i], update the partition
    partition_size[i] = j - head_index;

    // next iteration
  }

  // leaving last one partition, i should be equal to p_size
  partition_head[i] = array + j;
  partition_size[i] = array_size - j;

  // partition done
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

  print_delimiter("in divide_quicksort\n");
  //printf("rank %d: ", rank);
  printf("start: %d, end: %d\n", start, end);
  quicksort_rec(array, start, end-1);
  for(int i = start; i < end; ++ i) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

/* In this program, I have not considered the case for n > p^2, which can cause out of bound for some operation
   where n is the size of array and p as the number of threading*/
int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  /*
    In preparation for dividing jobs and initialization
   */
  int array_length = 200;
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
  for(int i = 1; i <= cbuf_size; ++ i) {
    cbuffer[i-1] = local_array[w * i];
  }

  if(rank == 0) {
    pivot_buffer = (int*)malloc(sizeof(int) * cbuf_size * size);
  }

  MPI_Gather(cbuffer, cbuf_size, MPI_INT,
             pivot_buffer, cbuf_size, MPI_INT,
             0, comm);

  // in this case the cbuffers are in the same size
  // next, in order to pass in size number of array for k way merge, make a pointer array
  {
    if(rank == 0) {
      int** pivot_spos = (int **)malloc(sizeof(int*)*size); // pointing to the corresponding start
      int* pivot_epos = (int *)malloc(sizeof(int)*size);    // the corresponding end index
      temp_buffer = (int *)malloc(sizeof(int)*size*cbuf_size);

      for(int i = 0; i < size; ++ i) {
        pivot_spos[i] = pivot_buffer + i * (cbuf_size);
        pivot_epos[i] = cbuf_size;
      }

      k_way_merge(pivot_spos, temp_buffer, pivot_epos, size);

      free(pivot_spos);
      free(pivot_epos);
    }
  }

  if(rank == 0) {
    // now have the pivots, sample the pivots
      for(int i = 0; i < cbuf_size; ++ i) {
        cbuffer[i] = temp_buffer[cbuf_size*(i + 1)];
      }
  }

  // broadcast the pivots to other nodes
  MPI_Bcast(cbuffer, cbuf_size, MPI_INT, 0, comm);

  if(rank == 0) {
    printf("pivot list: ");
    for(int i = 0; i < cbuf_size * size; ++ i) {
      printf("%d ", temp_buffer[i]);
    }
    printf("\n");
  }

  print_delimiter("sample pivots test print\n");
  printf("rank %d gets sampled pivots: ", rank);
  for(int i = 0; i < cbuf_size; ++ i) {
    printf("%d ", cbuffer[i]);
  }
  printf("\n");

  // well done!
  // partition and sent the partition to the itch node
  int** partition_head = (int**)malloc(sizeof(int*) * (size));
  int* partition_size = (int*)malloc(sizeof(int) * size);

  mul_partition(local_array, cbuffer, end, cbuf_size, partition_head, partition_size);

  // testing partition
  print_delimiter("");
  for(int i = 0; i < size; ++ i) {
    printf("[%d] partition of rank[%d]: ", i, rank);
    for(int j = 0; j < partition_size[i]; ++ j) {
      printf("%d ", partition_head[i][j]);
    }
    printf("\n");
  }

  //MPI_Barrier(comm);
  // after partition, gather from other nodes
  int* recv_partition_size = (int*)malloc(sizeof(int)*size);
  int** recv_partition_head = (int**)malloc(sizeof(int)*size);

  // first receive the size from each node, and reserve space for them

  // ??? what seems like a good approach
  for(int i = 0; i < size; ++ i) {
    MPI_Gather(partition_size + i, 1, MPI_INT,
               recv_partition_size, 1, MPI_INT,
               i, comm);
  }
  // remember to not add an displacement for recv_parition_size, and this method is shorter than below

  /* for(int i = 0; i < size; ++ i) { */
  /*   MPI_Send(partition_size+i, 1, MPI_INT, */
  /*            i, 0, comm); */
  /* } */

  /* for(int i = 0; i < size; ++ i) { */
  /*   MPI_Recv(recv_partition_size+i, 1, MPI_INT, i, 0, comm, MPI_STATUS_IGNORE); */
  /* } */

  // testing sending
  /* for (int i = 0; i < size; ++ i) { */
  /*   printf("rank [%d]: %d ", rank, recv_partition_size[i]); */
  /* }   printf("\n"); */

  // moving onto send receives partitions, first declare length for each
  for(int i = 0; i < size; ++ i) {
    // may receive bad size and cause crashes
    recv_partition_head[i] = (int*)malloc(sizeof(int)*recv_partition_size[i]);
  }

  for(int i = 0; i < size; ++ i) {
    MPI_Send(partition_head[i], partition_size[i], MPI_INT,
             i, 0, comm);
  }

  for(int i = 0; i < size; ++ i) {
    MPI_Recv(recv_partition_head[i], recv_partition_size[i], MPI_INT,
             i, 0, comm, MPI_STATUS_IGNORE);
  }

  print_delimiter("In testing receiving final pivot partition array\n");
  for(int i = 0; i < size; ++ i) {
    printf("[%d] receive partition of rank[%d]: ", i, rank);
    for(int j = 0; j < recv_partition_size[i]; ++ j) {
      printf("%d ", recv_partition_head[i][j]);
    }
    printf("\n");
  }

  int partition_length = 0;
  for(int i = 0; i < size; ++ i) {
    partition_length += recv_partition_size[i];
  }

  int* local_merge = (int*)malloc(sizeof(int)* partition_length);
  // after performing a k_way_merge, the partition will be sorted
  k_way_merge(recv_partition_head, local_merge, recv_partition_size, size);

  print_delimiter("After final merging, showing the local_merge array\n");
  printf("rank[%d]: ", rank);
  for(int i = 0; i < partition_length; ++ i) {
    printf("%d ", local_merge[i]);
  }
  printf("\n");

  // send local_merge to root node, and concatenate the arrays for a sorted array
  int* recv_merge_size = (int*)malloc(sizeof(int) * size);
  MPI_Gather(&partition_length, 1, MPI_INT,
             recv_merge_size, 1, MPI_INT,
             0, comm);

  int* disp = (int*)malloc(sizeof(int) * size);
  disp[0] = 0;
  for(int i = 1; i < size; ++ i) {
    disp[i] = recv_merge_size[i-1] + disp[i - 1];
  }

  int* sorted_array = (int*)malloc(sizeof(int)*array_length);
  MPI_Gatherv(local_merge, partition_length, MPI_INT,
              sorted_array, recv_merge_size, disp, MPI_INT, 0, comm);

  if(rank == 0) {
    printf("The sorted array: ");
    for(int i = 0; i < array_length; ++ i) {
      printf("%d ", sorted_array[i]);
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

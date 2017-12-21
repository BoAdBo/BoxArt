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

void myfree(void * pointer) {
  if(!pointer) {free(pointer);}
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

  /* print_delimiter("In k way merge\n"); */
  /* printf("The merge pointers: "); */
  /* for(int i = 0; i < k; ++ i) { */
  /*   printf("%d ", ps[i]); */
  /* } */
  /* printf("\n"); */

  myfree(ps);
  myfree(ended_array);
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

  //print_delimiter("in divide_quicksort\n");
  //printf("rank %d: ", rank);
  //printf("start: %d, end: %d\n", start, end);
  quicksort_rec(array, start, end-1);
  /* for(int i = start; i < end; ++ i) { */
  /*   printf("%d ", array[i]); */
  /* } */
  /* printf("\n"); */
}

/*
  allocate space for array, and return the size of array
  Note that would need the size of nodes in order to allocate reasonable space
 */
void input(int** array, int* length, int size) {
  int array_length;
  scanf("%d", &array_length);
  // get size of the array, make changes to pointer
  *length = array_length;
  int local_length = (array_length + size - 1) / size;

  // Input of data, using rand
  // make the array a little bigger, to avoid out of bound index, notice the extra 1 at local_length
  *array = (int*)malloc(sizeof(int)*(local_length * size));
  srand(time(0));
  for(int i = 0; i < array_length; ++ i) {
    (*array)[i] = rand() % 100000;
  }
}

void get_range(int * low, int * high, int rank, int size, int array_length, int local_fixed_length) {
  int start, end;

  if(rank == size - 1) {
    start = 0;
    end = ((array_length) % local_fixed_length);
    if(end == 0) {
      end = local_fixed_length;
    }
    //printf("local_fixed_length %d\n", local_fixed_length);
  }
  else {
    start = 0;
    end = local_fixed_length;
  }

  *low = start;
  *high = end;
}

/*
  Return the sampled pivots
 */
int * sample(int * array, int interval, int sample_size) {
  int* sample_array = (int*)malloc(sizeof(int)*sample_size);
  for(int i = 0; i < sample_size; ++ i) {
    // assume big enough array, no exception handling
    sample_array[i] = array[interval * (i + 1)];
  }
  return sample_array;
}

/* In this program, I have not considered the case for n > p^2, which can cause out of bound for some operation
   where n is the size of array and p as the number of threading*/
int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  /*
    In preparation for dividing jobs and initialization
    Phase one: Initialization
    Start up p processors, let the root processor, 0, get data and the size
   */
  int rank, size;

  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);

  int local_fixed_length;
  int array_length;
  int *array;

  if(rank == 0) {
    input(&array, &array_length, size);
  }
  // broadcast array_length for nodes to compute local_fixed_length
  MPI_Bcast(&array_length, 1, MPI_INT, 0, comm);

  // starting time counting here
  double time_start, time_end;

  time_start = MPI_Wtime();

  /*
    Phase two: Scatter data, local sort and regular samples collected
    Scatter the data values to the p processors. Each processor sorts its local data, here the local size is the ceiling of (n/p), using quicksort.
    Each processor chooses (p - 1) sample points, in a very regular manner, from its locally sorted data
   */

  // compute celling, to cooperate with passing same amount chunks of data
  // each process computes their range
  // the actual range of local array

  local_fixed_length = (array_length + size - 1) / size;
  int start, end;
  get_range(&start, &end, rank, size, array_length, local_fixed_length);


  // after input and divide length, scatter arrays
  int *local_array;
  local_array = (int*)malloc(sizeof(int)*local_fixed_length);
  MPI_Scatter(array, local_fixed_length, MPI_INT,
              local_array, local_fixed_length, MPI_INT,
              0, comm);

  myfree(array);

  // every node sort their own unsorted array
  divide_quicksort(local_array, start, end);

  // regular sample the sorted local array of each node
  // end points to null, which is i + 1, where i is the last index
  int *cbuffer;        // local sampled potential pivots

  int sample_size = (size-1);
  int w = array_length / (size * size);
  cbuffer = sample(local_array, w, sample_size);

  /*
    Phase three: Gather and merge samples, choose and broadcast (p-1) pivots
    The root processor, 0, gathers the p sets of (p-1) sample points. It is important to realize that each set of these p points is sorted.
    These p sets are sorted using multimerge, from these p(p-1) sorted points, (p-1) pivot values are regularly chosen and are broadcast to the other (p-1) processors

   */
  int *pivot_buffer; // for root node to gather sampled potential pivots
  if(rank == 0) {
    pivot_buffer = (int*)malloc(sizeof(int) * sample_size * size);
  }

  // Gathers the p sets of p sample points
  MPI_Gather(cbuffer, sample_size, MPI_INT,
             pivot_buffer, sample_size, MPI_INT,
             0, comm);

  myfree(cbuffer);

  // Multimerge the p sets of (p-1) sample points
  int* temp_buffer;
  // next, in order to pass in size number of array for k way merge, make a pointer array
  if(rank == 0) {
    int** pivot_spos;
    int* pivot_epos;
    pivot_spos = (int **)malloc(sizeof(int*)*size);  // pointing to the corresponding start
    pivot_epos = (int *)malloc(sizeof(int)*size);    // the corresponding end index
    temp_buffer = (int *)malloc(sizeof(int)*size*sample_size);

    for(int i = 0; i < size; ++ i) {
      pivot_spos[i] = pivot_buffer + i * (sample_size);
      pivot_epos[i] = sample_size;
    }

    k_way_merge(pivot_spos, temp_buffer, pivot_epos, size);

    myfree(pivot_spos);
    myfree(pivot_epos);
  }

  myfree(pivot_buffer);

  int* sampled_pivot;
  if(rank == 0) {
    // now have the potential pivots, sample the pivots
      sampled_pivot = sample(temp_buffer, sample_size, sample_size);
  }
  else {
    sampled_pivot = (int*)malloc(sizeof(int)*sample_size);
  }

  /* if(rank == 0) { */
  /*   printf("sorted sample points:\n"); */
  /*   for(int i = 0; i < sample_size * size; ++ i) { */
  /*     printf("%d ", temp_buffer[i]); */
  /*   } */
  /*   printf("\n"); */
  /*   myfree(temp_buffer); */
  /* } */

  // broadcast the pivots to other nodes
  MPI_Bcast(sampled_pivot, sample_size, MPI_INT, 0, comm);

  /* print_delimiter("sample pivots test print\n"); */
  /* printf("rank %d gets sampled pivots: ", rank); */
  /* for(int i = 0; i < sample_size; ++ i) { */
  /*   printf("%d ", sampled_pivot[i]); */
  /* } */
  /* printf("\n"); */

  /*
    Phase four: Local data is partitioned
    Each of the p processors partitions its local sorted data, roughly of size (n/p), which is a well-conditioned situation,
    into p classes using the (p-1) pivot values
   */

  // partition and send the partition to the each node
  int** partition_head = (int**)malloc(sizeof(int*) * (size));
  int* partition_size = (int*)malloc(sizeof(int) * size);

  // end is the actual size of local_array
  mul_partition(local_array, sampled_pivot, end, sample_size, partition_head, partition_size);

  // testing partition
  /* print_delimiter(""); */
  /* for(int i = 0; i < size; ++ i) { */
  /*   printf("[%d] partition of rank[%d]: ", i, rank); */
  /*   for(int j = 0; j < partition_size[i]; ++ j) { */
  /*     printf("%d ", partition_head[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  /*
    Phase five: All *ith* classes are gathered and merged
    Processor i gathers the ith class of data from every other processor. Each of these classes is sorted using multimerge.
    To be frank, this is some of the challenging part

    To do this, every processor must know its array size received from ith processor, then it can receive their own array.
    Naturally, it goes into two parts. First, each processor gathers the size of i partition from ith processor.
    Second, each processor sends the partition buffer, then receive their own partition buffer after knowing the sizes
   */

  // after partition, gather from other nodes
  int* recv_partition_size = (int*)malloc(sizeof(int)*size);
  int** recv_partition_head = (int**)malloc(sizeof(int*)*size);

  // first receive the size from each node, and reserve space for them

  // ??? what seems like a good approach
  // this doesn't work, because it gathers partition_size from ith processor to i position
  // where we actually want (partition_size + i) to i position from each processor
  /* MPI_Allgather(partition_size, 1, MPI_INT, */
  /*               recv_partition_size, 1, MPI_INT, comm); */
  for(int i = 0; i < size; ++ i) {
    MPI_Gather(partition_size + i, 1, MPI_INT,
               recv_partition_size, 1, MPI_INT,
               i, comm);
  }

  // remember to not add an displacement for recv_parition_size, and this method is shorter than below
  /* print_delimiter("Receive size:\n"); */
  /* for(int i = 0; i < size; ++ i) { */
  /*   printf("%d ", recv_partition_size[i]); */
  /* } */
  /* printf("\n"); */

  // moving onto send receives partitions, first declare length for each, after knowing the size
  for(int i = 0; i < size; ++ i) {
    // may receive bad size and cause crashes
    recv_partition_head[i] = (int*)malloc(sizeof(int)*recv_partition_size[i]);
  }

  /*
    Notice that for large messages, the below methods will be blocked due to the semantic of send,
    it blocks itself when messages are large.
    Waiting for the receive.
    So a solution is to use MPI_Sendrecv to concurrent run send and receive
    It blocks until all processes finishes their send as well as receive.

    However in this situation it won't work due to different data size of processes
   */

  // each processor send their ith partition to ith processor, and receive ith partition from ith processor
  // after this, local_array can be freed
  MPI_Request mpi_send;

  for(int i = 0; i < size; ++ i) {
    MPI_Isend(partition_head[i], partition_size[i], MPI_INT,
              i, 0, comm, &mpi_send);
  }
  // mind that use Immediate send here to avoid deadlock

  for(int i = 0; i < size; ++ i) {
    MPI_Recv(recv_partition_head[i], recv_partition_size[i], MPI_INT,
             i, 0, comm, MPI_STATUS_IGNORE);
  }

  myfree(local_array);
  // cannot pass pointer... since processes don't share memory :(

  /* print_delimiter("In testing receiving final pivot partition array\n"); */
  /* for(int i = 0; i < size; ++ i) { */
  /*   printf("[%d] receive partition of rank[%d]: ", i, rank); */
  /*   for(int j = 0; j < recv_partition_size[i]; ++ j) { */
  /*     printf("%d ", recv_partition_head[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  // multimerging the receive partition
  int partition_length = 0;
  for(int i = 0; i < size; ++ i) {
    partition_length += recv_partition_size[i];
  }

  int* local_merge = (int*)malloc(sizeof(int)* partition_length);
  // after performing a k_way_merge, the partition will be sorted
  k_way_merge(recv_partition_head, local_merge, recv_partition_size, size);
  myfree(recv_partition_head);
  myfree(recv_partition_size);

  /* print_delimiter("After final merging, showing the local_merge array\n"); */
  /* printf("rank[%d]: ", rank); */
  /* for(int i = 0; i < partition_length; ++ i) { */
  /*   printf("%d ", local_merge[i]); */
  /* } */
  /* printf("\n"); */

  /*
    Phase Six: Root processor collects all the data
    The root processor gathers all the data and assembles the sorted list of n values.

    Like phase five, first need to know the size of each partition from each processor
    then pass in the partition
   */
  // send local_merge to root node, and concatenate the arrays for a sorted array
  int* recv_merge_size;
  int* disp;
  if(rank == 0) {
    recv_merge_size = (int*)malloc(sizeof(int) * size);
  }

  // gather size
  MPI_Gather(&partition_length, 1, MPI_INT,
             recv_merge_size, 1, MPI_INT,
             0, comm);

  // using gatherv to gather the array for root processor
  if(rank == 0) {
    disp = (int*)malloc(sizeof(int) * size);
    disp[0] = 0;
    for(int i = 1; i < size; ++ i) {
      disp[i] = recv_merge_size[i-1] + disp[i - 1];
    }
  }

  int* sorted_array;
  if(rank == 0) {
    sorted_array= (int*)malloc(sizeof(int)*array_length);
  }

  MPI_Gatherv(local_merge, partition_length, MPI_INT,
              sorted_array, recv_merge_size, disp, MPI_INT, 0, comm);

  time_end = MPI_Wtime();
  if(rank == 0) {
    printf("Elapsed time is %f\n", time_end - time_start);
  }
  // the job is done, sorted array in sorted_array

  /* if(rank == 0) { */
  /*   printf("The sorted array: "); */
  /*   for(int i = 0; i < array_length; ++ i) { */
  /*     printf("%d ", sorted_array[i]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  //printf("rank[%d] exits!\n", rank);

  myfree(disp);
  myfree(recv_merge_size);
  myfree(sorted_array);
  myfree(partition_head);
  myfree(partition_size);

  MPI_Finalize();

}

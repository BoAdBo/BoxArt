#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mpi.h"

#define MAX_PARTICLES 100
#define DIM 2
#define X 0
#define Y 1
#define G 6.67e-3
typedef double vect_t[DIM];

double masses[MAX_PARTICLES];
vect_t pos[MAX_PARTICLES];
vect_t vel[MAX_PARTICLES];
vect_t forces[MAX_PARTICLES];

int n;
double delta_t, T;

void get_input() {
  double mass, s_x, s_y, v_x, v_y;

  scanf("%d\n", &n);
  scanf("%lf %lf", &delta_t, &T);

  for(int i = 0; i < n; ++ i) {
    scanf("%lf %lf %lf %lf %lf\n", &mass, &s_x, &s_y, &v_x, &v_y);
    masses[i] = mass;
    pos[i][X] = s_x;
    pos[i][Y] = s_y;
    vel[i][X] = v_x;
    vel[i][Y] = v_y;
  }
}

int main(int argc, char * argv[]) {

  MPI_Init(&argc, &argv);

  int rank, size;
  int temp;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  //printf("%d\n", rank);
  if(rank == 0) {
    get_input();
    int dest = 1;
    while(dest < size) {
      MPI_Send(&temp, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
      dest++;
    }
  }
  else {
    // just for sync waiting for the input
    MPI_Recv(&temp, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  //printf("hello?\n");
  printf("%d\n", n/size);
  int local_n = n / size * rank;
  int local_end;

  if(rank == size - 1) {
    local_end = n;
  }
  else {
    local_end = n / size * (rank+1);
  }

  printf("rank: %d, %d - %d\n", rank, local_n, local_end);

  int total_timestep = T / delta_t + 1;
  double x_diff, y_diff;
  double dist, dist_cubed;
  for(int timestep = 0; timestep < total_timestep; ++ timestep) {
    // clean forces
    if(rank == 0) {
      // print current position and velocity
      for(int i = 0; i < n; ++ i) {
        printf("particle[%d]: v (%lf, %lf), position (%lf, %lf) at time %lf%s\n",
               i,
               vel[i][X], vel[i][Y],
               pos[i][X], pos[i][Y],
               delta_t * timestep, "s");
      }
      for(int i = 0; i < n; ++ i) {
        forces[i][X] = 0;
        forces[i][Y] = 0;
      }

      /* int dest = 1; */
      /* while(dest < size) { */
      /*   MPI_Send(&temp, 1, MPI_INT, dest, 0, MPI_COMM_WORLD); */
      /*   dest++; */
      /* } */
    }
    else {// sync
      //MPI_Recv(&temp, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    }
    //MPI_Scatter(&temp, 1, MPI_INT, &temp, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // compute forces

    for(int i = local_n; i < local_end; ++ i) {
      for(int j = 0; j < n; ++ j) {
        if(i != j) {
          x_diff = pos[i][X] - pos[j][X];
          y_diff = pos[i][Y] - pos[j][Y];
          dist = sqrt(x_diff * x_diff + y_diff * y_diff);
          dist_cubed = dist*dist*dist;
          forces[i][X] -= G * masses[i] * masses[j] / dist_cubed * x_diff;
          forces[i][Y] -= G * masses[i] * masses[j] / dist_cubed * y_diff;
        }
      }
    }

    //vect_t* loc_pos = (vect_t*)malloc((local_end - local_n) * sizeof(vect_t));
    //vect_t* loc_vel = (vect_t*)malloc((local_end - local_n) * sizeof(vect_t));

    for(int i = local_n; i < local_end; ++ i) {
      double temp_X = forces[i][X] / masses[i];
      double temp_Y = forces[i][Y] / masses[i];
      //printf("%lf %lf\n", forces[i][X], forces[i][Y]);
      pos[i][X] += (vel[i][X] + temp_X * delta_t / 2) * delta_t;
      pos[i][Y] += (vel[i][Y] + temp_Y * delta_t / 2) * delta_t;
      vel[i][X] += temp_X * delta_t;
      vel[i][Y] += temp_Y * delta_t;
    }

    int * temp_recv = NULL;
    if(rank == 0) {
      temp_recv = (int*)malloc(sizeof(int)*size);
    }
    // sync
    //printf("hello?\n");
    //int temp1 = 1;
    //MPI_Gather(&temp, 1, MPI_INT, temp_recv, 1, MPI_INT, 0, MPI_COMM_WORLD);

  }
  MPI_Finalize();
}


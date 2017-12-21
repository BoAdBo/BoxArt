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


void get_input(int n,
               double* pos_x, double* pos_y,
               double* vel_x, double* vel_y,
               double * masses) {
  double mass, s_x, s_y, v_x, v_y;

  for(int i = 0; i < n; ++ i) {
    scanf("%lf %lf %lf %lf %lf\n", &mass, &s_x, &s_y, &v_x, &v_y);
    masses[i] = mass;
    pos_x[i] = s_x;
    pos_y[i] = s_y;
    vel_x[i] = v_x;
    vel_y[i] = v_y;
  }
}

int main(int argc, char * argv[]) {
  double * masses;
  double * pos_x;
  double * pos_y;
  double * vel_x;
  double * vel_y;
  int n;
  double delta_t, T;

  // local vel, local pos
  double * loc_vel_x;
  double * loc_vel_y;
  double * loc_pos_x;
  double * loc_pos_y;

  int rank, size;
  int loc_n;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // initialization, allocating space
  if(rank == 0) {
    scanf("%d\n", &n);
    scanf("%lf %lf", &delta_t, &T);
  }

  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&delta_t, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&T, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  masses = (double * )malloc(sizeof(double) * n);
  pos_x = (double *)malloc(sizeof(double) * n);
  pos_y = (double *)malloc(sizeof(double) * n);
  vel_x = (double *)malloc(sizeof(double) * n);
  vel_y = (double *)malloc(sizeof(double) * n);

  // serial input
  if(rank == 0) {
    get_input(n, pos_x, pos_y, vel_x, vel_y, masses);// info in process 0, broadcast
  }

  // broadcast
  /* MPI_Bcast(masses, n, MPI_DOUBLE, 0, MPI_COMM_WORLD); */
  /* MPI_Bcast(pos_x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD); */
  /* MPI_Bcast(pos_y, n, MPI_DOUBLE, 0, MPI_COMM_WORLD); */
  /* MPI_Bcast(vel_x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD); */
  /* MPI_Bcast(vel_y, n, MPI_DOUBLE, 0, MPI_COMM_WORLD); */

  /* MPI_Barrier(MPI_COMM_WORLD); */
  //printf("hello?\n");
  printf("%d %d \n", n, size);
  int local_start = n / size * rank;
  int local_end;

  if(rank == size - 1) {
    local_end = n;
  }
  else {
    local_end = n / size * (rank+1);
  }

  printf("rank: %d, %d - %d\n", rank, local_start, local_end);

  MPI_Bcast(masses, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(pos_x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(pos_y, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(vel_x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(vel_y, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  int total_timestep = T / delta_t + 1;
  double x_diff, y_diff;
  double dist, dist_cubed;
  loc_n = local_end - local_start;
  double *forces_x = (double *)malloc(sizeof(double)*loc_n);
  double *forces_y = (double *)malloc(sizeof(double)*loc_n);

  for(int timestep = 0; timestep < total_timestep; ++ timestep) {
    // clean forces
    MPI_Bcast(pos_x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(pos_y, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(vel_x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(vel_y, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if(rank == 0) {
      // print current position and velocity
      for(int i = 0; i < n; ++ i) {
        printf("particle[%d]: v (%lf, %lf), position (%lf, %lf) at time %lf%s\n",
               i,
               vel_x[i], vel_y[i],
               pos_x[i], pos_y[i],
               delta_t * timestep, "s");
      }
      for(int i = 0; i < loc_n; ++ i) {
        forces_x[i] = 0;
        forces_y[i] = 0;
      }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // compute forces

    for(int i = local_start; i < local_end; ++ i) {
      for(int j = 0; j < n; ++ j) {
        if(i != j) {
          x_diff = pos_x[i] - pos_x[j];
          y_diff = pos_y[i] - pos_y[j];
          dist = sqrt(x_diff * x_diff + y_diff * y_diff);
          dist_cubed = dist*dist*dist;
          forces_x[i] -= G * masses[i] * masses[j] / dist_cubed * x_diff;
          forces_y[i] -= G * masses[i] * masses[j] / dist_cubed * y_diff;
        }
      }
    }

    //vect_t* loc_pos = (vect_t*)malloc((local_end - local_start) * sizeof(vect_t));
    //vect_t* loc_vel = (vect_t*)malloc((local_end - local_start) * sizeof(vect_t));

    for(int i = local_start; i < local_end; ++ i) {
      double temp_x = forces_x[i] / masses[i];
      double temp_y = forces_y[i] / masses[i];
      //printf("%lf %lf\n", forces[i][x], forces[i][y]);
      pos_x[i] += (vel_x[i] + temp_x * delta_t / 2) * delta_t;
      pos_y[i] += (vel_y[i] + temp_y * delta_t / 2) * delta_t;
      vel_x[i] += temp_x * delta_t;
      vel_y[i] += temp_y * delta_t;
    }

    MPI_Allgather(pos_x+local_start, loc_n, MPI_DOUBLE, pos_x, loc_n, MPI_DOUBLE, MPI_COMM_WORLD);
    MPI_Allgather(pos_y+local_start, loc_n, MPI_DOUBLE, pos_y, loc_n, MPI_DOUBLE, MPI_COMM_WORLD);
    MPI_Allgather(vel_x+local_start, loc_n, MPI_DOUBLE, vel_x, loc_n, MPI_DOUBLE, MPI_COMM_WORLD);
    MPI_Allgather(vel_y+local_start, loc_n, MPI_DOUBLE, vel_y, loc_n, MPI_DOUBLE, MPI_COMM_WORLD);
    //printf("rank:%d from %d to %d\n", rank, local_start, local_end);

  }

  free(masses);
  free(pos_x);
  free(pos_y);
  free(vel_x);
  free(vel_y);
  free(forces_y);
  free(forces_y);
  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Finalize();
}


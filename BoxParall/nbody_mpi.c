/*
 * Compile:  mpicc -g -Wall -o nbody_mpi nbody_mpi.c -lm
 *
 * Run:      mpiexec -n <number of processes> ./nbody_mpi testdata
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <mpi.h>

#define DIM 2
#define X 0
#define Y 1
#define G 6.673e-11
#define delta_t 0.1

typedef double vect_t[DIM];

double* masses;
vect_t *pos, *vel, *forces;

int n, T; /* n for the number of the particles, T for timesteps */
int my_rank, comm_sz;
int loc_n;  /* The number of local particles */
MPI_Comm comm;
MPI_Datatype vect_mpi_t;  /* Derive data type */

void initiateSystem(char* fileName) {
	int i;
	FILE* fp = fopen(fileName, "r");

	fscanf(fp,"%d%d", &n, &T);

  masses = (double*)malloc(n * sizeof(double));
  pos = (vect_t*)malloc(n * sizeof(vect_t));
  vel = (vect_t*)malloc(n * sizeof(vect_t));
  forces = (vect_t*)malloc(n * sizeof(vect_t));

  if (my_rank == 0) {
    for (i = 0; i < n; i++) {
      fscanf(fp, "%lf", &masses[i]);
      fscanf(fp, "%lf%lf", &pos[i][X], &pos[i][Y]);
      fscanf(fp, "%lf%lf", &vel[i][X], &vel[i][Y]);
    }
  }

  loc_n = n / comm_sz;

	fclose(fp);
}

void Computing(int rank, int loca_n, vect_t * loca_pos, vect_t* loc_vel) {

  for (int q = 0; q < n; q++) {
    /* Assign 0 to each element of the forces array */
    memset(forces, 0, n*sizeof(vect_t));
  }

  for (int q = loca_n * rank; q < loca_n*(rank+1); q++) {
    for (int k = 0; k < n; k++) {
      if (k != q) {
        double x_diff, y_diff, dist, dist_cubed;
        x_diff = pos[k][X] - pos[k][X];
        y_diff = pos[k][Y] - pos[k][Y];
        dist = sqrt(x_diff * x_diff + y_diff * y_diff);
        dist_cubed = dist * dist * dist;
        forces[q][X] -= G * masses[q] * masses[k] / dist_cubed * x_diff;
        forces[q][Y] -= G * masses[q] * masses[k] / dist_cubed * y_diff;
      }
    }
  }

  for (int q = loca_n * rank; q < loca_n*(rank+1); q++) {
    loca_pos[q][X] += delta_t * vel[q][X];
    loca_pos[q][Y] += delta_t * vel[q][Y];
    loc_vel[q][X] += delta_t / masses[q] * forces[q][X];
    loc_vel[q][Y] += delta_t / masses[q] * forces[q][Y];
  }

  /* Gather to all*/
  MPI_Allgather(loca_pos, loca_n, vect_mpi_t, pos, loca_n, vect_mpi_t, comm);
}

int main(int argc, char* argv[]) {
  vect_t* loc_vel;
  vect_t* loc_pos;
  MPI_Init(&argc, &argv);

  comm = MPI_COMM_WORLD;
  MPI_Comm_size(comm, &comm_sz);
  MPI_Comm_rank(comm, &my_rank);

  double start, finish;  /* Time record */
  if (argc == 2) {
    MPI_Type_contiguous(2, MPI_DOUBLE, &vect_mpi_t);
    MPI_Type_commit(&vect_mpi_t);


    if (my_rank == 0) {
      initiateSystem(argv[1]);  /* Process 0 read the data */
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, comm);
    MPI_Bcast(&loc_n, 1, MPI_INT, 0, comm);
    MPI_Bcast(&T, 1, MPI_INT, 0, comm);

    loc_pos = (vect_t *)malloc(loc_n * sizeof(vect_t));  /* Position of local particles */
    loc_vel = (vect_t*)malloc(loc_n * sizeof(vect_t));

    if (my_rank != 0) {
      masses = (double*)malloc(n * sizeof(double));
      pos = (vect_t*)malloc(n * sizeof(vect_t));
      vel = (vect_t*)malloc(n * sizeof(vect_t));
      forces = (vect_t*)malloc(n * sizeof(vect_t));
    }

    start = MPI_Wtime();
    MPI_Bcast(masses, n, MPI_DOUBLE, 0, comm);  /* Broatcast the masses[] to all processes */
    MPI_Bcast(pos, n, vect_mpi_t, 0, comm);  /* Broatcast the pos[] to all processes, as every process needs the pos to calculate forces */
    MPI_Scatter(vel, loc_n, vect_mpi_t, loc_vel, loc_n, vect_mpi_t, 0, comm);  /* Scatter the vel to all processes*/
    MPI_Scatter(pos, loc_n, vect_mpi_t, loc_pos, loc_n, vect_mpi_t, 0, comm);

    for (int i = 0; i < T; i++) {
      Computing(my_rank, loc_n, loc_pos, loc_vel);

      //      printf("Hello! %d \n", my_rank);

      if (my_rank == 0) {
        printf("\nStep %d\n", i + 1);
        printf("Body :   pos_x     pos_y  |  vel_x    vel_y");
        for (int q = 0; q < n; q++) {
          printf("Body %d: %lf %lf %lf %lf\n", q + 1, pos[q][X], pos[q][Y], vel[q][X], vel[q][Y]);
        }
      }
    }
    MPI_Barrier(comm);  /* block all the processes until comm has reached */
    finish = MPI_Wtime();
  }


  if (my_rank == 0)
    printf("Running time = %e seconds\n", finish-start);
  //  MPI_Type_free(&vect_mpi_t);

  if(argc == 2) {

    free(masses);
    free(pos);
    free(vel);
    free(forces);
    free(loc_vel);
    free(loc_pos);
  }

  MPI_Finalize();
  return 0;
}

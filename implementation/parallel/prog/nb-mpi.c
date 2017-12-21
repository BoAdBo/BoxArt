#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_PARTICLES 100
#define DIM 2
#define X 0
#define Y 1
#define G 6.67e-3
typedef double vect_t[DIM];

struct particle {
  double masses;
  vect_t pos;
  vect_t vel;
};

struct particle particles[MAX_PARTICLES];

int n;
double delta_t, T;

void get_input() {
  double mass, s_x, s_y, v_x, v_y;

  scanf("%d\n", &n);
  scanf("%lf %lf", &delta_t, &T);

  for(int i = 0; i < n; ++ i) {
    scanf("%lf %lf %lf %lf %lf\n", &mass, &s_x, &s_y, &v_x, &v_y);
    particles[i].masses = mass;
    particles[i].pos[X] = s_x;
    particles[i].pos[Y] = s_y;
    particles[i].vel[X] = v_x;
    particles[i].vel[Y] = v_y;
  }
}




int main(int argc, char * argv[]) {
  get_input();
  vect_t* forces = (vect_t *)malloc(n*sizeof(vect_t));
  int total_timestep = T / delta_t + 1;
  double x_diff, y_diff;
  double dist, dist_cubed;
  for(int timestep = 0; timestep < total_timestep; ++ timestep) {
    // print current position and velocity
    for(int i = 0; i < n; ++ i) {
      printf("particle[%d]: v (%lf, %lf), position (%lf, %lf) at time %lf%s\n",
             i,
             particles[i].vel[X], particles[i].vel[Y],
             particles[i].pos[X], particles[i].pos[Y],
             delta_t * timestep, "s");
    }

    // clean forces
    forces = memset(forces, 0, n*sizeof(vect_t));
    // compute forces
    for(int i = 0; i < n; ++ i) {
      for(int j = 0; j < n; ++ j) {
        if(i != j) {
          x_diff = particles[i].pos[X] - particles[j].pos[X];
          y_diff = particles[i].pos[Y] - particles[j].pos[Y];
          dist = sqrt(x_diff * x_diff + y_diff * y_diff);
          dist_cubed = dist*dist*dist;
          forces[i][X] -= G * particles[i].masses * particles[j].masses / dist_cubed * x_diff;
          forces[i][Y] -= G * particles[i].masses * particles[j].masses / dist_cubed * y_diff;
        }
      }
    }

    for(int i = 0; i < n; ++ i) {
      double temp_X = forces[i][X] / particles[i].masses;
      double temp_Y = forces[i][Y] / particles[i].masses;
      //printf("%lf %lf\n", forces[i][X], forces[i][Y]);
      particles[i].pos[X] += (particles[i].vel[X] + temp_X * delta_t / 2) * delta_t;
      particles[i].pos[Y] += (particles[i].vel[Y] + temp_Y * delta_t / 2) * delta_t;
      particles[i].vel[X] += temp_X * delta_t;
      particles[i].vel[Y] += temp_Y * delta_t;
    }
  }
}


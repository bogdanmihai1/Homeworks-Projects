#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <pthread.h>

typedef double complex cplx;

int n;
int numThreads;
int* thread_id;
pthread_t* tid;
pthread_barrier_t *barrier;
pthread_barrier_t barrier2;
double complex *data;
double complex *result;
int* unityStep;
double* theta;
cplx* unityRoot;
cplx** omega;

// calculeaza a cata putere a lui 2 e i
int lg(int i) {
  int count = -1;
  while (i) {
    i >>= 1;
    count++;
  }
  return count;
}

// inverseaza ultimii log2(n) biti ai unui numar
int reverseBits(int num) {
  int res = 0;
  for (int i = 0; i < lg(n); i++) {
    if (num % 2) {
      res ++;
    }
    num >>= 1;
    res <<= 1;
  }
  res >>= 1;
  return res;
}

// 2 la puterea i
int pow2(int i) {
  int res = 1;
  for (int j = 1; j <= i; j++)
  {
    res <<= 1;
  }
  return res;
}

// FFT iterativ
void* iterativeFFT(void* arg) {

  int start, end;
  int start_n, end_n;
  int id = *(int*)arg;

  // imparte sarcinile in mod egal
  start = id * ceil((double)lg(n) / numThreads) + 1;
  end = fmin(lg(n), (id + 1) * ceil((double)lg(n) / numThreads)) + 1;

  start_n = id * ceil((double) n / numThreads);
  end_n = fmin(n, (id + 1) * ceil((double) n / numThreads));

  // calculele ce se fac in paralel
  // theta si unityRoot depind doar de p
  // omega depinde de p si k
  for (int p = start; p < end; p++) {
    unityStep[p] = pow2(p);
    theta[p] = 2 * M_PI / unityStep[p];
    unityRoot[p] = cos(theta[p]) - sin(theta[p])*I;

    omega[p - 1] = (double complex *) malloc(sizeof(double complex) * (unityStep[p] / 2));
    omega[p - 1][0] = 1;
    for (int k = 1; k < unityStep[p]/2; k++) {
      omega[p - 1][k] = omega[p - 1][k - 1] * unityRoot[p];
    }
  }

  for (int i = start_n; i < end_n; i++) {
    result[i] = data[reverseBits(i)];
  }

  // sau puteam sa continui codul asta in main
  // ca sa nu mai folosesc bariere

  pthread_barrier_wait(&barrier2);
  pthread_barrier_wait(&barrier[id]);
  for (int p = start; p < end; p++) {
    for (int offset = 0; offset < n; offset += unityStep[p]) {
      for (int k = 0; k < unityStep[p]/2; k++) { 
        cplx t = omega[p - 1][k] * result[offset + k + unityStep[p]/2];
        cplx u = result[offset + k];
        result[offset + k] = u + t;
        result[offset + k + unityStep[p]/2] = u - t;
      }
    }
  }
  if (id + 1 < numThreads) {
    pthread_barrier_wait(&barrier[id + 1]);
  }

  return NULL;
}

// citire din fisier + alocare memorie
void init(char* file_in) {

  FILE *fin;
  double aux;

  fin = fopen(file_in,"r");

  if(fin == NULL) {
      printf("Error!");
      exit(1);  
    }

  if (!fscanf(fin, "%d", &n)) {
    printf("Error!");
    exit(1);
  }

  int steps = lg(n);
  data = (double complex *) malloc (sizeof(double complex) * n);
  result = (double complex *) malloc (sizeof(double complex) * n);
  unityStep = malloc(sizeof(int) * (steps + 1));
  unityRoot = (double complex *) malloc(sizeof(double complex) * (steps + 1));
  theta = malloc(sizeof(double) * (steps + 1));
  tid = malloc(sizeof(pthread_t) * numThreads);
  thread_id = malloc(sizeof(int) * numThreads);
  barrier = malloc(sizeof(pthread_barrier_t) * numThreads);
  omega = (double complex **) malloc(sizeof(double complex *) * steps);

  pthread_barrier_init(&barrier[0], NULL, 1);
  for (int i = 1; i < numThreads; i++) {
    pthread_barrier_init(&barrier[i], NULL, 2);
  }

  pthread_barrier_init(&barrier2, NULL, numThreads);

  for(int i = 0; i < n; i++) {
    if (!fscanf(fin, "%lf", &aux)) {
      printf("Error!");
      exit(1);
    }
    data[i] = aux;
  }

  fclose(fin);
}

// afisare in fisier
void disp(char* file_out) {

  FILE *fout;

  fout = fopen(file_out, "w");
  fprintf(fout, "%d\n", n);

  for (int i = 0; i < n; i++) {
    fprintf(fout, "%lf %lf\n", creal(result[i]), cimag(result[i]));
  }

  fclose(fout);
}

// functie ce se ocupa de threaduri
void create_threads() {

  for (int i = 0; i < numThreads; i++) {
    thread_id[i] = i;
    pthread_create(&tid[i], NULL, iterativeFFT, &thread_id[i]);
  }

  for (int i = 0; i < numThreads; i++) {
    pthread_join(tid[i], NULL);
  }

  for (int i = 0; i < numThreads; i++) {
    pthread_barrier_destroy(&barrier[i]);
  }
}

int main(int argc, char *argv[]) {

  numThreads = atoi(argv[3]);

  init(argv[1]);
  create_threads();
  disp(argv[2]);

  return 0;
}
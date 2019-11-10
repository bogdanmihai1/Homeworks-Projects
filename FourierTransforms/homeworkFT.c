#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <pthread.h>

int n;
int numThreads;
int* thread_id;
pthread_t* tid;
double complex *data;    // datele de intrare
double complex *result;  // rezultatul dupa aplicarea transf fourier

// functie ce calculeaza transformata fourier
void* ftransform(void* arg) {

	int start, end;
    int id = *(int*)arg;
    complex double sum;
    double angle;

    // vectorul de intrare se imparte in mod egal pe threaduri
    // nu apar conflicte r-w sau w-r
	start = id * ceil((double)n / numThreads);
	end = fmin(n, (id + 1) * ceil((double)n / numThreads));

	for (int k = start; k < end; k++) {
		sum = 0.0f;
		for (int t = 0; t < n; t++) {
			angle = 2 * M_PI * t * k / n;
			sum += data[t] * cexp(-angle * I);
		}
		result[k] = sum;
	}
	return NULL;
}

// functie de initializare(citire din fisier + alocare de memorie)
void init(char* file_in) {

	FILE *fin;
	int i;
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

	data = (double complex *) malloc (sizeof(double complex) * n);
	result = (double complex *) malloc (sizeof(double complex) * n);
	tid = malloc(sizeof(pthread_t) * numThreads);
	thread_id = malloc(sizeof(int) * numThreads);

	for(i = 0; i < n; i++) {
		if (!fscanf(fin, "%lf", &aux)) {
			printf("Error!");
			exit(1);
		}
		data[i] = aux;
	}

	fclose(fin);
}

// functie ce afiseaza raspunsul in fisierul de iesire
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
		pthread_create(&tid[i], NULL, ftransform, &thread_id[i]);
	}
	for (int i = 0; i < numThreads; i++) {
		pthread_join(tid[i], NULL);
	}
}

int main(int argc, char* argv[]) {

	numThreads = atoi(argv[3]);

	init(argv[1]);
	create_threads();
	disp(argv[2]);
	
	return 0;
}
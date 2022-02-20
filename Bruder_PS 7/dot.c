#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* This structure stores all of the
 * variables that are shared between
 * the two threads. Handle with care. */
typedef struct {
	int       idx;  /* index of this thread */
	double *a, *b;  /* vectors to dot product */
	int       dim;  /* dimensionality of vectors */
	double   psum;  /* partial dot product */
} thread_data;

/* This is the function each thread will call
 * to do the work of computing the partial dot
 * product. */
void* worker(void* arg) {
	thread_data* dat;
	int     idx, dim;
	double    *a, *b;
	
	/* Get thread arguments */
	dat = (thread_data*) arg;
	idx = dat->idx;
	a = dat->a;
	b = dat->b;
	dim = dat->dim;
	
	/* TODO compute partial dot product 
	 * and safely exit the thread... */
}

int main(int argc, char* argv[]) {
	
	int dim;
	
	/* Parse program arguments */
	if(argc != 2) {
		printf("usage: ./dot <dimensionality>\n");
		exit(2);
	}
	dim = atoi(argv[1]);
	
	/* TODO initialize thread data structure,
	 * create threads, wait for them to terminate,
	 * add the partial sums together, then print! */
	
	/* Be sure not to have any memory errors/leaks!! */
	
	/* Done! */
	return 0;
}

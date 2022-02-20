#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>

int computeInCircle(int m, unsigned short index);

int main(int argc,char* argv[])
{
  int numDarts = atoi(argv[1]);
  int numWorkers = atoi(argv[2]);
  printf("Each of %d workers is running %d points, for a total of %d points\n", numWorkers, numDarts, numDarts*numWorkers);
  fflush(stdout);
  /*
    TODO: Create the shared memory object, which will be used to store the total number of darts that fall in the circle.

    Also create the semaphore to synchronize the manipulation of this shared memory. 
   */
  for(int i = 0; i < numWorkers; i++) {
    pid_t child = fork();
    if (child == 0) {
      int nbInCircle = computeInCircle(numDarts, (unsigned short)i);
      /*
	TODO: Add nbInCircle to the shared memory object. 
       */
      return 0;
    } 
  }
  /*
    TODO: Wait for all of the workers to finish.
   */
  int dartsInCircle = *nbIn;
  int totalDarts = numDarts*numWorkers;
  double pi = ((double)dartsInCircle)/totalDarts*4.0;
  /*
    TODO: Cleanup here. 
   */
  printf("Computation completed: %d - %d : PI = %lf\n",dartsInCircle,totalDarts,pi);
  return 0;
}

int computeInCircle(int m, unsigned short index)
{
  unsigned short seed[3] = {index, index, index};
  seed48(seed);
  int in = 0;
  for(int i=0; i< m;i++) {
    float x = erand48(seed);
    float y = erand48(seed);
    int  inCircle = (x*x+y*y) < 1.0;
    in += inCircle;
  }
  return in;
}


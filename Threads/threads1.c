//author: Coimer
//Corono Times:) 05.05.2020 ANKARA UNIVERSITY OS HOMEWORK

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct _thread_data_t {
  int tid; //thread id
  int offset; //how many line it will read
  int start; //start line of thread section
  FILE *fp; //which file it will read
  int sntncNum; //how many sentences are in this section

} thread_data_t;
 
//FUNCTION OF THREAD
void *thr_func(void *arg) {

	int *iptr=(int *) malloc(sizeof(int)); //*

	thread_data_t *data = (thread_data_t *)arg;
	char array[1000];
	char ch;
	int count=0;
	int sen=0;
	int i=0;
	while(i< ( data->offset) ){
		
		fgets(array,999,data->fp);
		if(feof(data->fp)) break;

		for(count = 0; array[count] != '\n'; count++){
			
			if(array[count]=='.')
			sen++;
			
		}
	i++;
	}

	*iptr=sen; //*

	data->sntncNum=sen;
	return iptr; //*
//printf("Number of scanned lines: %d Number of sentences: %d\n",data->offset, data->sntncNum);

//pthread_exit(NULL);

}

//MAIN FUNC
int main(int argc, char **argv) {
FILE *fp;
int nthreads;
thread_data_t depo;
char karakter;
pthread_t tid;

//FILE READING
/*
 * It will open and read input.txt file
 * You should create exact name of txt file.
 * Or you can simply change the name of file in here
 */
fp = fopen("input.txt", "r"); 
  if (fp==NULL) 
  {   //opening problems shown here
      perror("Cannot open input file for reading.");
      exit(1);
  }

//FIND LINE NUMBER
/*
 * How many line in input file
 */
int lineNumber=0;  
for (char c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // Increment count if this character is newline 
            lineNumber = lineNumber + 1; 

printf("The file input.txt has %d lines\n", lineNumber);

fseek(fp,0,SEEK_SET);//


//Number of Thread taken from user
  printf("Enter the number of threads: ");
  scanf("%d",&nthreads);
//Make a thread_data_t argument array
  pthread_t thr[nthreads];

  int i, rc;

thread_data_t thr_data[nthreads];
int chunk_size;

/*//ANOTHER WAY ABOUT NUMBER OF LINES FOR EACH THREAD
	
	if(lineNumber % nthreads !=0){
		chunk_size=(float)lineNumber/nthreads;
		chunk_size++;
	}
*/ 

/*
 * Calculate the number of lines of the file and
 * decide how many lines each thread should read. 
 * The value should be rounded up when this value is not an integer
 *
 */
  if(lineNumber%nthreads!=0){  chunk_size=(lineNumber/nthreads)+1;  }
  else {  chunk_size=lineNumber/nthreads;  }

//CREATE THREADS**
int toplamaLine=0;
int sayi=0;
int flag=0;
  for (i = 0; i < nthreads-1; i++) {

  thr_data[i].start=sayi;
  thr_data[i].fp=fp;
  if(toplamaLine+chunk_size > lineNumber )
  {   
	if(lineNumber-toplamaLine>=0)
	{thr_data[i].offset=lineNumber-toplamaLine;  toplamaLine+=chunk_size; flag+=1;}
	else{thr_data[i].offset=0;toplamaLine+=chunk_size;}

  }
  else{
	
	thr_data[i].offset=chunk_size;  toplamaLine+=chunk_size; 
  }
  
  sayi+=chunk_size;

  thr_data[i].tid = i;

      if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
          fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
          return EXIT_FAILURE;
     }
  }


/*last thread process:: lineNumber- (ntherad-1)*chunk_size */
thr_data[nthreads-1].fp=fp;
thr_data[nthreads-1].start=sayi;
if(flag==0){
	if(lineNumber - (nthreads-1)*chunk_size > 0)
	{thr_data[nthreads-1].offset= lineNumber- (nthreads-1)*chunk_size; }
	else{
		thr_data[nthreads-1].offset=0;
	}
}
else{
	thr_data[nthreads-1].offset=0;
	
}
//thr_data[nthreads-1].offset= lineNumber- (nthreads-1)*chunk_size;
 

if ((rc = pthread_create(&thr[nthreads-1], NULL, thr_func, &thr_data[nthreads-1]))) {
        fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
        return EXIT_FAILURE;
}

int  *result;
for (i = 0; i < nthreads; ++i) {
    pthread_join(thr[i], (void*)&result);
    printf("Number of scanned lines: %d Number of sentences: %d\n",thr_data[i].offset,*result);
//"Number of scanned lines: %d Number of sentences: %d\n",data->offset, data->sntncNum
  }
 
  //return EXIT_SUCCESS;
}


/*********************************************************************************************

BONUS SECTION: How to return a value from pthread threads in C? 


#include <pthread.h>
#include <stdio.h>

int something_worked(void) {
    // thread operation might fail, so here's a silly example 
    void *p = malloc(10);
    free(p);
    return p ? 1 : 0;
}

void *myThread(void *result)
{
   if (something_worked()) {
       *((int*)result) = 42;
       pthread_exit(result);
   } else {
       pthread_exit(0);
   }
}

int main()
{
   pthread_t tid;
   void *status = 0;
   int result;

   pthread_create(&tid, NULL, myThread, &result); //&thr_data[i]
   pthread_join(tid, &status);

   if (status != 0) {
       printf("dondur: %d\n",result);
   } else {
       printf("thread failed\n");
   }

   return 0;
}



*********************************************************************************************/


/*
 *
 *
 * HELPFUL RESOURCES **
 *
 * https://www.youtube.com/playlist?list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM  MOST USEFUL VIDEO SERIES:)
 *
 * http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
 *
 * https://randu.org/tutorials/threads/
 *
 * https://courses.engr.illinois.edu/cs241/fa2010/ppt/10-pthread-examples.pdf
 *
 * https://www.ibm.com/support/knowledgecenter/SSLTBW_2.4.0/com.ibm.zos.v2r4.bpxbd00/ptjoin.htm
 *
 *
 *
 */

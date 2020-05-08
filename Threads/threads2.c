#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct _thread_data_t {
  int tid;
  int offset; //kac satır
  int start;
  FILE *fp;
  int sntncNum;

} thread_data_t;
 
//FUNCTION OF THREAD
void *thr_func(void *arg) {

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
	data->sntncNum=sen;

printf("Number of scanned lines: %d Number of sentences: %d\n",data->offset, data->sntncNum);

pthread_exit(NULL);

}

//MAIN FUNC
int main(int argc, char **argv) {
FILE *fp;
int nthreads;
thread_data_t depo;
char karakter;
pthread_t tid;

//FILE READING
fp = fopen("input.txt", "r"); 
  if (fp==NULL) 
  {
      perror("Cannot open input file for reading.");
      exit(1);
  }

//FIND LINE NUMBER
int lineNumber=0;  
for (char c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // Increment count if this character is newline 
            lineNumber = lineNumber + 1; 

printf("The file input.txt has %d lines\n", lineNumber);

fseek(fp,0,SEEK_SET);



  printf("Enter the number of threads: ");
  scanf("%d",&nthreads);
  pthread_t thr[nthreads];

  int i, rc;

thread_data_t thr_data[nthreads];
int chunk_size;
/*
if(lineNumber % nthreads !=0){
chunk_size=(float)lineNumber/nthreads;
chunk_size++;
}*/ 


  if(lineNumber%nthreads!=0){  chunk_size=(lineNumber/nthreads)+1;  }
  else {  chunk_size=lineNumber/nthreads;  }


int sayi=0;
  for (i = 0; i < nthreads-1; i++) {

  thr_data[i].fp=fp;
  thr_data[i].offset=chunk_size;
  thr_data[i].start=sayi;
  sayi+=chunk_size;

      thr_data[i].tid = i;

      if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
          fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
          return EXIT_FAILURE;
     }
  }


thr_data[nthreads-1].fp=fp;
thr_data[nthreads-1].offset= lineNumber- (nthreads-1)*chunk_size;
thr_data[nthreads-1].start=sayi;

if ((rc = pthread_create(&thr[nthreads-1], NULL, thr_func, &thr_data[nthreads-1]))) {
        fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
        return EXIT_FAILURE;
}

  for (i = 0; i < nthreads; ++i) {
    pthread_join(thr[i], NULL);
  }
 
  return EXIT_SUCCESS;
}

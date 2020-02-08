#include <fcntl.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/mman.h> 
#include <sys/shm.h>
#include <sys/time.h> 
#include <sys/wait.h> 
#include <sys/stat.h>


int main()
{
   
        pid_t pid;
        pid = fork();
	if( pid <0  )
	{
           fprintf( stderr, "Fork Failed" );
	   return 1;
	}
	
	
	typedef struct timeval timeval_t;
	
	const int SIZE = 4096;
	
	const char *name = "OS";


        int shm_fd;
       
		shm_fd =  shm_open(name,O_CREAT|O_RDWR,0666 );
		
		
		ftruncate( shm_fd ,SIZE );
		
		
		timeval_t *sharedMemory= mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shm_fd ,0);
		
	
	if( pid == 0 ) 
	{
	
		gettimeofday( sharedMemory, 0 );
		
		
	        execlp("/bin/ls","ls",NULL);
	}
	
	
	else 
	{
	
		wait( NULL);
		
		
		timeval_t bitis_zaman;
		gettimeofday( &bitis_zaman, 0 );
		
		
		timeval_t baslangicZaman;
		baslangicZaman = *sharedMemory; 
		
		
		
		timeval_t gecen_sure;
		timersub( &bitis_zaman, &baslangicZaman, &gecen_sure );
		
		
		
	        printf( "\nGecen sure: %d.%06d seconds\n", gecen_sure.tv_sec, gecen_sure.tv_usec );
		
	}
	
       return 0;
}

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main( void )
{
    int pid = fork();
	printf("%d\n", pid);
    if ( pid == 0 )
    {

        execlp( "sudo", "sudo", "bash", NULL );
    }

    int status;


    wait( &status );

    return 0;
}

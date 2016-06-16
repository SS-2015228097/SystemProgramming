#include	<stdio.h>
#include	<signal.h>

main()
{
	void	f(int);			// declare handler
	int	i;

	signal( SIGINT, f );		// installing the handler
	for(i=0; i<5; i++ ){		
		printf("hello\n");
		sleep(1);
	}
}

void f(int signum)			// function signum called
{
	char	ans[BUFSIZ];

	printf("   Interrupted!  OK to quit (y/n)? ");
	if ( fgets(ans, BUFSIZ, stdin) != NULL && (ans[0]=='y'||ans[0]=='Y') ) // fget(char *str,int size, FILE *stream) and ans[0] exit
		exit(0);
}


#include	<stdio.h>
#include	<signal.h>

#define	MAXARGS		20				/* cmdline args	*/
#define	ARGLEN		100				/* token length	*/

main()
{
	char	*arglist[MAXARGS+1];	// Array
	int	numargs;					// index into array	
	char	argbuf[ARGLEN];			// reading
	char	*makestring();			// malloc etc	

	numargs = 0;
	while ( numargs < MAXARGS )
	{					
		printf("Arg[%d]? ", numargs);
		if ( fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n' )
			arglist[numargs++] = makestring(argbuf);
		else
		{
			if ( numargs > 0 ){		// args
				arglist[numargs]=NULL;	// closing list
				execute( arglist );	// execute
				numargs = 0;		// reset
			}
		}
	}
	return 0;
}

execute( char *arglist[] )
/*
 *	use fork and execvp and wait to do it
 */
{
	int	pid,exitstatus;				// of child

	pid = fork();					// new process
	switch( pid ){
		case -1:	
			perror("fork failed");
			exit(1);
		case 0:
			execvp(arglist[0], arglist);		//execute
			perror("execvp failed");
			exit(1);
		default:
			while( wait(&exitstatus) != pid )
				;
			printf("child exited with status %d,%d\n",
					exitstatus>>8, exitstatus&0377);
	}
}

char *makestring( char *buf )
/*
 * trim off newline and create storage for the string
 */
{
	char	*cp, *malloc();

	buf[strlen(buf)-1] = '\0';		// trimming newline	
	cp = malloc( strlen(buf)+1 );		// getting memory
	if ( cp == NULL ){			// if not die 
		fprintf(stderr,"no memory\n");
		exit(1);
	}
	strcpy(cp, buf);		// copy chars
	return cp;			// return ptr	
}


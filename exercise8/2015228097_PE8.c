#include        <stdio.h>
#include        <signal.h>

#define READ    0
#define WRITE   1

main()
{
        FILE    *fp;
        FILE    *popen2(const char *command, const char *mode);
        int i;

        char    buf[BUFSIZ];
        char    buf_2[5]="cadbe";


        fp = popen("ls","r");
        while( fgets(buf, BUFSIZ,fp) != NULL)
                fputs(buf, stdout);

         fputs("\n\n\n",stdout);


        fp=popen2("sort","w");
        for(i=0;i<5;i++)
         {
                 fputc(buf_2[i],fp);
                 fputc('\n',fp);
         }

}


FILE *popen2(const char *command, const char *mode)
{
        int     pip[2], pid;
        FILE    *fdopen(), *fp;
        int     close_parent,close_child;

        if ( *mode == 'r' )
       {
                close_parent = READ;
                close_child = WRITE ;
        }
        else if ( *mode == 'w' )
        {
                close_parent = WRITE;
               close_child = READ ;
        }
        else
           return NULL ;

        if ( pipe(pip) == -1 )
                return NULL;
        if ( (pid = fork()) == -1 )
        {
                return NULL;
        }



        if ( pid == 0 )
        {
                if (close( pip[close_child] ) == -1 )
                        return NULL;
                return fdopen( pip[close_parent] , mode);
        }



        if ( close(pip[close_parent]) == -1 )
                exit(1);

        if ( dup2(pip[close_child], close_child) == -1 )
                exit(1);

        if ( close(pip[close_child]) == -1 )
                exit(1);

        execl( "/bin/sh", "sh", "-c", command, NULL );
        exit(1);
}


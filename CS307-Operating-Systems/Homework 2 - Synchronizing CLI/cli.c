#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define TOTAL_THREADS 50

// You can declare your shared variables here.
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int fds[TOTAL_THREADS][2]; // pipes array

// You should fill this function.
void *display(void* args)
{
	pthread_mutex_lock(&lock);

 	int fdno = (int) args;
	int len = 1000;
	char buf[len];
	read(fds[fdno][0], buf, len);

	printf("---- %ld\n", pthread_self());

	printf("%s", buf);

	printf("---- %ld\n", pthread_self());

	fflush(stdout);

	pthread_mutex_unlock(&lock);

	return NULL;
}

// You can modify the main except for the parser.
int main(int argc, char *argv[])
{
    FILE *fptr;

    // You can use these variables for creating and manipulating shell threads.
    pthread_t threads[TOTAL_THREADS];
	int threadStatus[TOTAL_THREADS]; // 0 not created, 1 active, -1 created and joined
    int thrCount = 0;

    fptr = fopen("./commands.txt", "r");

    if (fptr == NULL)
    {
        exit(1);
    }

    char line[256];

	int no = 0; // to keep line number to use for piping

    while (fgets(line, sizeof(line), fptr))
    {

	char redirection = '-';
	char background = 'n';

	for(int i = 0; i < strlen(line); i++)
        {
	    if( line[i] == '<' )
            {
		redirection = '<';
	    }
	    else if( line[i] == '>' )
	    {
		redirection = '>';
	    }
	    if (line[i] == '&')
	    {
		background = 'y';
	    }
        }

	// PARSER STARTS
	// DO NOT MODIFY THE PARSER!
	char *myargs[10];

	int fileFlag = 0;

	int argNumber = 0;

	char *redirFile;

	int onWord = 0;
	char wordLength = 0;

	int redirFilelen = 0;

	for(int i = 0; i < strlen(line) && line[i] != '&' && line[i] != '\n'; i++)
	{
	    if (line[i] != ' ' && line[i] != '<' && line[i] != '>')
	    {
		onWord = 1;
		wordLength++;

		if ( (i + 1 < strlen(line) && line[i + 1] == '\n') || i + 1 == strlen(line) )
		{
		    char *word = (char*)malloc(sizeof(char)*(wordLength + 1));
		    memcpy(word, line + i + 1 - wordLength, wordLength);
		    myargs[argNumber] = strdup(word);
		    argNumber++;
		    break;
		}
	    }

	    else if (onWord == 1 && line[i] == ' ')
	    {
		onWord = 0;
		char *word = (char*)malloc(sizeof(char) * (wordLength + 1));
		memcpy(word, line + i - wordLength, wordLength);
		myargs[argNumber] = strdup(word);
		argNumber++;
		wordLength = 0;
	    }

	    else if (line[i] == '<' || line[i] == '>')
	    {
		int k;
		for(k = i + 1; k < strlen(line) && line[k] != '\n'; k++)
		{
		    if (line[k] != ' ')
		    {
			fileFlag = 1;
		        redirFilelen++;
			if (k + 1 == strlen(line))
			{
			    break;
			}
		    }
		    else if (fileFlag == 1 && line[k] == ' ')
		    {
			break;
		    }
		}
		redirFile = (char*)malloc(sizeof(char) * (redirFilelen + 1));
		memcpy(redirFile, line + k - redirFilelen, redirFilelen);
		break;
	    }
	}
	// PARSER ENDS
    // All the modifications for MAIN comes after this point.

	myargs[argNumber] = NULL;

	pipe(fds[no]); // piping

    // You should fill this 'if' block for handling wait commands.
	if (myargs[0][0] == 'w' && myargs[0][1] == 'a')
	{
		while(wait(NULL) != -1); // wait for all children to terminate

		for (int i = 0; i < TOTAL_THREADS; i++) // iterate all threads
		{
			if (threadStatus[i] == 1) { // if current thread is running...
				pthread_join(threads[i], NULL); // ...wait for it
				threadStatus[i] = -1; // set thread's status to joined
			}
		}
	}

	else {
		int rc = fork();
		if (rc < 0)
		{
			exit(1);
		}
		else if (rc == 0)
		{
			if (redirection == '-')
			{
				dup2(fds[no][1], STDOUT_FILENO); // referance STDOUT to PIPE WRITE
			}
			else if (redirection == '<')
			{
				close(STDIN_FILENO);
				int fileNo = open(redirFile, O_RDONLY);

				dup2(fds[no][1], STDOUT_FILENO); // referance STDOUT to PIPE WRITE
			}
			else
			{
				close(STDOUT_FILENO);
				open(redirFile, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
			}

			execvp(myargs[0], myargs);
		}
		else
		{
			if (redirection != '>') {
				pthread_create(&threads[thrCount], NULL, display, (void*) no); // create thread
				threadStatus[thrCount] = 1; // set thread's status to active
			}

			if (background == 'n')
			{
				waitpid(rc, NULL, 0);

				if (redirection != '>') {
					pthread_join(threads[thrCount], NULL); // wait for the thread to terminate (no ampersand)
					threadStatus[thrCount] = -1; // set thread's status to joined
				}
			}

			thrCount++;
		}
	}

	no++;

    }

	while(wait(NULL) != -1); // wait all active processes to terminate

	for (int i = 0; i < TOTAL_THREADS; i++) // wait all active threads to terminate and join
	{
		if (threadStatus[i] == 1) {
			pthread_join(threads[i], NULL);
			threadStatus[i] = -1;
		}
	}

    return 0;
}

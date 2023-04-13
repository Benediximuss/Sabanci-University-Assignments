#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t globalMutex = PTHREAD_MUTEX_INITIALIZER ;

struct threadArgs // a struct to pass arguements to the function executed by threads
{
    sem_t* semsArray;
    int* fansArray;
    int team; // 0 is for team A, 1 is for team B
};

void* findRide(void* arg)
{
	
    struct threadArgs* args = (struct threadArgs*) arg; // casting argument passed to the function

    int currenTeam = args->team;
    int otherTeam = 1 - currenTeam; // if current team is 0 (A) then other is 1 (B), and vice-versa.

	int isFull = 0; // to decide the captain thread

    pthread_mutex_lock(&globalMutex);
    
    printf("Thread ID: %ld, Team: %c, I am looking for a car\n", pthread_self(), (char) (currenTeam+65)); // char 65 is 'A', 66 is 'B'

    args->fansArray[currenTeam]++; // incrementing current team's fan count that looking for a ride by 1


    if (args->fansArray[currenTeam] > 1 && args->fansArray[otherTeam] == 2) { // if there are at least 2 'currenTeam' fans and exact 2 'otherTeam' fans in queue
        sem_post(&args->semsArray[currenTeam]); // one from current team (since this thread is from current team also, in total 2 from current team)
        for (int i = 0; i < 2; i++) sem_post(&args->semsArray[otherTeam]); // two from other team

        args->fansArray[0] -= 2; // decrementing both teams fans waiting queue by 2 for each, since this is 2 vs 2 car in this case  
        args->fansArray[1] -= 2;
        isFull = 1; // car is full
        
        pthread_mutex_lock(&globalMutex);         
    } 
    else if (args->fansArray[currenTeam] == 4) { // if there are exact 4 'currentTeam' fans in queue
        for (int i = 0; i < 3; i++) sem_post(&args->semsArray[currenTeam]); // three from current team (also +1 since this thread is from current team, in total 4 from current team)
        
        args->fansArray[currenTeam] -= 4; // decrementing current team's fans waiting queue by 4, since this car is for 4 fan from a team
        isFull = 1; // car is full

        pthread_mutex_lock(&globalMutex);   
    }
    else {	
        pthread_mutex_unlock(&globalMutex);
        sem_wait(&args->semsArray[currenTeam]); // waiting to be woken up when a proper car is found
    }   

    printf( "Thread ID: %ld, Team: %c, I have found a spot in a car \n" , pthread_self(), (char) (currenTeam+65));
    
    if (isFull == 1 ) { // car is full 
        pthread_mutex_unlock(&globalMutex);
        printf( "Thread ID: %ld, Team: %c, I am the captain and driving the car \n" , pthread_self(), (char) (currenTeam+65));
        pthread_mutex_unlock(&globalMutex);
    }
    
    pthread_mutex_unlock(&globalMutex);
}

int main(int argc, char* argv[]) {

    int counts[2] = { atoi(argv[1]), atoi(argv[2]) };

    if ((counts[0]+counts[1]) % 4 != 0 || (counts[0] % 2 != 0) || (counts[1]%2 != 0)) { // check validity..
        printf("The main terminates\n");
    }
    else {
        sem_t sems[2]; // creating semaphores and initializing them afterwards.. ([0] = A, [1] = B)
        for (int i = 0; i < 2; i++) sem_init(&sems[i], 0, 0); // initializinging both semaphores
        
        int totalCount = counts[0] + counts[1];
        pthread_t threads[totalCount]; // creating threads

        int fans[2] = { 0, 0 }; // creating fans array which shows how many fans are waiting for a ride currently ([0] = A, [1] = B)

        struct threadArgs threadArgs_A = { &sems, &fans, 0 };
        struct threadArgs threadArgs_B = { &sems, &fans, 1 };

        int k = 0;
        while (k != totalCount) { // initializing threads..
            if (k < counts[0]) { // thread is for team A fan
                pthread_create(&threads[k], NULL, findRide, &threadArgs_A);
            } else { // thread is for team B fan
                pthread_create(&threads[k], NULL, findRide, &threadArgs_B);
            }
            k++;
        }
        
        k = 0;
        while(k != totalCount) { // waiting for all threads to join..
            pthread_join(threads[k], NULL);
            k++;
        }

        printf("The main terminates\n");

        for (int i = 0; i < 2; i++) sem_destroy(&sems[i]); // destroying both semaphores
    }

}
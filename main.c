#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int arrNums[16];
int arrPID[16];
int numChildren = 0;

void sig_handler_parent(int signum)
{
  printf("\nParent: Inside handler function\n");
}

void sig_handler_child(int signum)
{
    //printf("\nChild:Inside handler function\n");
    sleep(1);
    if(numChildren == 2)
    {
        printf("\nPID: %d - ", arrPID[0]);
        for(int i = 0; i<5; i++)
        {
            printf("%d ", arrNums[i]);
        }
        printf("\nPID: %d - ", arrPID[1]);
        for(int i = 5; i<10; i++)
        {
            printf("%d ", arrNums[i]);
        }
    }
    else if(numChildren == 4)
    {
        printf("\nPID: %d - ", arrPID[2]);
        for(int i = 0; i<3; i++)
        {
            printf("%d ", arrNums[i]);
        }
        printf("\nPID: %d - ", arrPID[3]);
        for(int i = 3; i<5; i++)
        {
            printf("%d ", arrNums[i]);
        }
    }
    else if(numChildren == 6)
    {
        printf("\nPID: %d - ", arrPID[4]);
        for(int i = 5; i<8; i++)
        {
            printf("%d ", arrNums[i]);
        }
        printf("\nPID: %d - ", arrPID[5]);
        for(int i = 8; i<10; i++)
        {
            printf("%d ", arrNums[i]);
        }
    }
    else if(numChildren == 8)
    {
        printf("\nPID: %d - ", arrPID[6]);
        for(int i = 0; i<1; i++)
        {
            printf("%d ", arrNums[i]);
        }
        printf("\nPID: %d - ", arrPID[7]);
        for(int i = 1; i<2; i++)
        {
            printf("%d ", arrNums[i]);
        }
    }
    else if(numChildren == 10)
    {
        printf("\nPID: %d - ", arrPID[8]);
        for(int i = 5; i<6; i++)
        {
            printf("%d ", arrNums[i]);
        }
        printf("\nPID: %d - ", arrPID[9]);
        for(int i = 6; i<7; i++)
        {
            printf("%d ", arrNums[i]);
        }
    }
    else if(numChildren == 12)
    {
        printf("\nPID: %d - ", arrPID[10]);
        for(int i = 3; i<4; i++)
        {
            printf("%d ", arrNums[i]);
        }
        printf("\nPID: %d - ", arrPID[11]);
        for(int i = 4; i<5; i++)
        {
            printf("%d ", arrNums[i]);
        }
    }
    else if(numChildren == 14)
    {
        printf("\nPID: %d - ", arrPID[12]);
        for(int i = 8; i<9; i++)
        {
            printf("%d ", arrNums[i]);
        }
        printf("\nPID: %d - ", arrPID[13]);
        for(int i = 9; i<10; i++)
        {
            printf("%d ", arrNums[i]);
        }
    }
    else if(numChildren == 16)
    {
        printf("\nPID: %d - ", arrPID[14]);
        for(int i = 2; i<3; i++)
        {
            printf("%d ", arrNums[i]);
        }
        printf("\nPID: %d - ", arrPID[15]);
        for(int i = 7; i<8; i++)
        {
            printf("%d ", arrNums[i]);
        }
    }
}
void kidKiller(int kidToKill)
{
  sleep(1);
  printf("\nenter KILL MODE\n");
  //added this 3 due to a weird race condition
  sleep(3);
  printf("Killed PID: %d\n", kidToKill);
  kill(getpid(), SIGKILL);

}

void sigIntHandler(int signum)
{
  sleep(1);
  printf("\nInterupted\n");
  int varToPass = getpid();
  kidKiller(varToPass);
  sleep(1);
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));
    //printf("Starting Array: ");
    for (int a = 0; a < 10; a++)
    {
        arrNums[a] = rand() % 300;
        //printf("%d ", arrNums[a]);
    }




    for(int i = 0; i<6; i++)
    {
        sleep(1);
        int pid = fork();
        if (pid == 0)
        {
            //child
            for(int a = 0; a < 16; a++)
            {
                if(arrPID[a]== 0)
                {
                    //printf("%d ", getpid());
                    arrPID[a] = getpid();
                    numChildren = numChildren + 1;
                    break;
                }
            }
            sleep(.5);
            signal(SIGUSR1, sig_handler_child);
            raise(SIGUSR1);
        }
        else
        {
            //parent
            for(int a = 0; a < 16; a++)
            {
                if(arrPID[a]== 0)
                {
                    
                    arrPID[a] = getpid();
                    numChildren = numChildren + 1;
                    sleep(.5);
                    break;
                }
            }


        }

    }
}
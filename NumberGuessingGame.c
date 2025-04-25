#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int random,guess;
    int count = 0;
    srand(time(NULL));

    printf("....Welcome to the world of Guessing Numbers!!!....\n");
    random= rand()%100+1;// Generating between 0 to 100

    do{
        printf("\nPlease Enter Your Guess between (1 to 100):");
        scanf("%d",&guess);
        count ++;

        if (guess<random){
            printf("Guess a large Number.\n");
        }
        else if(guess>random){
            printf("Guess a smaller Number.\n");
        }
        else{
        printf("\nCongratulations !!! \nYou have Successfully Guessed the Number in %d attempts.\n",count);
        }

    }

    while(guess != random);

    printf("\nBye Bye, Thanks For Playing !");
    printf("\nDeveloped By LakiyaDEV\n\n");

    return 0;
}

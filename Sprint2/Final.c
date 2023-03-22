/*
 ============================================================================
 Name        : Final(War the Card Game).c
 Author      : Brodie Busby
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


int cards[52] = {1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13};

int player1[52];
int player2[52];
int pile[52];

//Shuffles deck, Got code from stack overflow
void shuffle(int *array, size_t n){
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}
void display_deck(int *arr){
    int i = 0;
    for(i = 0; i < 52 -1; i++){
    	printf("%d,",arr[i]);
    }

}
//Shifts the entire array over eliminating the first item
void delete(int *arr){
    int i;
    for(i = 0; i < 52 - 1; i++) arr[i] = arr[i + 1];


}
//Clear the pile so repeats don't show
void clear_pile(){
    int i;
    for(i = 0; i < 52 -1; i++){
    	if(pile[i] != 0)
    	{
    		pile[i] = 0;
    	}
    }

}
// Add to the end of the deck
void append(int *arr, int number){
	int i = 0;
	for(i = 0;i<52 -1;i++)
	{
		if(arr[i] == 0)
		{
			arr[i] = number;

			return;
		}
	}
}

int main(void) {
		int i=0;
		shuffle(cards,52);

//Player1's deck
		for(i=0;i<26;i++){
	        	player1[i] = cards[i];
	        }
//Player2's deck
		for(i=0;i<26;i++){
	        	player2[i] = cards[i+26];
	        }
		int done = 0;
		int k = 0;

		int *ptr1 = NULL;
		int *ptr2 = NULL;

		printf("Welcome to War the Card game(Two Ai's)\n");
		printf("-------------------------------------");
		while(!done){

			printf("\n");
				if(player1[0] == 0){
					printf("Player 2 wins the game\n");
		        	  ptr1 = &done;
					  *ptr1 = 1;
							}
				if(player2[0] == 0){
		               printf("Player 1 wins the game\n");
			        	  ptr1 = &done;
						  *ptr1 = 1;

                    	}
		        if(player1[0+k]<player2[0+k]&& player1[0] != 0 && player2[0] != 0){
		               append(player2, player1[0]);
		               append(player2, player2[0]);
 		               delete(player1);
		               delete(player2);

		               if(pile[0] != 0){
				       printf("Cards in pile:");
				       }
		               for(i =0 ; pile[i]!=0; i++){
				       append(player1, pile[i]);
				       printf( "%d," ,pile[i]);
				       }
				       printf("\n");
				       clear_pile();
				       printf("\n");

				       ptr2 = &k;
					   *ptr2 = 0;
		               printf("Player 1 had a %d and Player 2 had a %d\n",player1[0+k],player2[0+k]);
		                                         }

		        if(player2[0+k]<player1[0+k]&& player1[0] != 0 && player2[0] != 0){
		        	 append(player1, player1[0]);
			         append(player1, player2[0]);

			         delete(player1);
			         delete(player2);

			         if(pile[0] != 0){
			         printf("Cards in pile:");
			         }
			         for(i =0 ; pile[i]!=0; i++){
			         append(player1, pile[i]);
			         printf( "%d," ,pile[i]);
			         }
			         printf("\n");
			         clear_pile();
				     printf("\n");

		        	  ptr2 = &k;
					  *ptr2 = 0;

			          printf("Player 1 had a %d and Player 2 had a %d\n",player1[0+k],player2[0+k]);

		                     }
		        // If there is a tie add to the pile
		        if(player1[0+k]==player2[0+k] && player1[0] != 0 && player2[0] != 0){

				         append(pile, player1[0]);
				         append(pile, player2[0]);

				         delete(player1);
				         delete(player2);

			        	  ptr2 = &k;
						  *ptr2 += 1;
						  if(player1[0] !=0 || player2[0] !=0){
						  printf("Player 1 had a %d and Player 2 had a %d\n",player1[0+k],player2[0+k]);
						  }
						  }

		}

	return EXIT_SUCCESS;
}


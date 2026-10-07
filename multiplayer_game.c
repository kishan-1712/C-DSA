#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    int n_players, turns;
    int scores[50] ={0};
    int max_score = 0;

    srand(time(NULL));
    printf("enter number of players:");
    scanf("%d",&n_players);
    printf("enter number of turns:");
    scanf("%d",&turns);
    for(int i=0;i<turns; i++){
        for(int i=0;i<n_players;i++){
            int roll=(rand()%6)+1;
            scores[i]+=roll;
        }
    }
    printf("\n---Final Scores---\n");
    for(int i=0;i<n_players;i++){
        printf("Player %d: %d\n", i+1, scores[i]);
        if(scores[i]>max_score){
            max_score=scores[i];
        }
    }
    printf("\nwinner(s) with %d points:\n", max_score);
    for(int i=0; i<n_players;i++){
        if(scores[i]==max_score){
            printf("Player %d\n",i+1);
        }
    }
    return 0;
}
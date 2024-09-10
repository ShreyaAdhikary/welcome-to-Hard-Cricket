#include <stdio.h>
#include<string.h>

#include <stdlib.h>
#include <time.h>

int GetPlayerToss(char player1[], char player2[], int overToplay);
int batting(char battingplayer[], char bowlingplayer[], int overToplay);

int main() {
    int i, overs, noovers, player1Toss, player2Toss;
    char player1[50], player2[50];
    
    srand(time(NULL));
    
    printf("WELCOME TO HARD CRICKET TEAM\n");
    printf("Enter Player 1 Name: ");
    fgets(player1, sizeof(player1), stdin);
    player1[strcspn(player1, "\n")] = '\0'; // Remove newline character

    printf("Enter Player 2 Name: ");
    fgets(player2, sizeof(player2), stdin);
    player2[strcspn(player2, "\n")] = '\0'; // Remove newline character
    
    printf("Enter\n1 - Fixed over\n2 - Play Until Out\n3 - How to play?\n4 - Exit: ");
    scanf("%d", &noovers);
    
    while (noovers >= 1 && noovers <= 4) {
        if (noovers == 1) {
            printf("Enter the number of overs: ");
            scanf("%d", &overs);
            player1Toss = GetPlayerToss(player1, player2, overs);
        } else if (noovers == 2) {
            player1Toss = GetPlayerToss(player1, player2, 0);
        } else if (noovers == 3) {
            printf("How to play?\n");
            printf("Until a player wins the toss, follow the output and provide the requested inputs.\n");
            printf("The player who wins the toss chooses either to Bat or to Bowl.\n");
            printf("The player who chooses batting and bowling has to proceed by pressing the Enter key one by one.\n");
            printf("The system will generate a random number of runs for both players. Player 1's runs keep adding until their runs equal Player 2's runs.\n");
            printf("Finally, when Player 1 is out, their runs are their final score. The same process will be conducted for Player 2.\n");
            printf("Finally, whoever has the highest score is the winner.\n\n");
        } else {
            printf("Invalid choice\n");
        }
        
        printf("Enter 1 - Fixed Overs\n2 - Play Until Out\n3 - How to play?\n4 - Exit: ");
        scanf("%d", &noovers);
    }
    
    return 0;
}

int GetPlayerToss(char player1[], char player2[], int overToplay) {
    int player1choice, player2choice, toss, player1Toss, batorbowlchoice;
    int player1score = 0, player2score = 0;
    char c;
    
    printf("%s, choose your choice: 1 for head or 2 for tail: ", player1);
    scanf("%d", &player1choice);
    
    player2choice = (player1choice == 1) ? 2 : 1;
    printf("%s's choice is %s\n", player2, (player2choice == 1) ? "head" : "tail");
    
    toss = rand() % 2 + 1;
    printf("Toss is %s\n", (toss == 1) ? "head" : "tail");
    
    if (toss == player1choice) {
        player1Toss = 1;
        printf("Player 1 %s won the toss\n", player1);
        printf("Choose\n1 - Batting\n2 - Bowling: ");
        scanf("%d", &batorbowlchoice);
        
        if (batorbowlchoice == 1) {
            printf("%s is going to bat now\n", player1);
            player2score = batting(player2, player1, overToplay);
            printf("%s is going to bat now\n", player2);
            player1score = batting(player1, player2, overToplay);
        } else {
            printf("%s is going to bat now\n", player2);
            player2score = batting(player2, player1, overToplay);
            printf("%s is going to bat now\n", player1);
            player1score = batting(player1, player2, overToplay);
        }
    } else {
        player1Toss = 2;
        printf("Player 2 %s won the toss\n", player2);
        printf("Choose\n1 - Batting\n2 - Bowling: ");
        scanf("%d", &batorbowlchoice);
        
        if (batorbowlchoice == 1) {
            printf("%s is going to bat now\n", player2);
            player2score = batting(player2, player1, overToplay);
            printf("%s is going to bat now\n", player1);
            player1score = batting(player1, player2, overToplay);
        } else {
            printf("%s is going to bat now\n", player1);
            player1score = batting(player1, player2, overToplay);
            printf("%s is going to bat now\n", player2);
            player2score = batting(player2, player1, overToplay);
        }
    }
    
    if (player1score == player2score) {
        printf("Draw match\nThanks for playing the game\n");
    } else if (player1score > player2score) {
        printf("%s won the match\nThanks for playing the game\n", player1);
    } else {
        printf("%s won the match\nThanks for playing the game\n", player2);
    }
    
    return player1Toss;
}

int batting(char battingplayer[], char bowlingplayer[], int overToplay) {
    int i, j, battingscore, sum = 0, bowlerscore;
    char c;
    
    for (i = 1; i <= 6; i++) {
        for (j = 1; j <= 6; j++) {
            printf("%d.%d ball\n", i, j);
            printf("Please press Enter to bowl: ");
            while (getchar() != '\n'); // Wait for Enter key
            bowlerscore = rand() % 7; // Generate from 0-6 where 0 means no ball
            
            printf("%s press Enter to bat: ", battingplayer);
            while (getchar() != '\n'); // Wait for Enter key
            battingscore = rand() % 7; // Generate 0-6 run
            
            if (battingscore == bowlerscore) {
                printf("%s is out\n", battingplayer);
                printf("Total score = %d\n", sum);
                if (sum == 0) {
                    printf("Duck out\n");
                }
                return sum;
            } else {
                printf("Got %d runs\n", battingscore);
                if (battingscore == 6) {
                    printf("Six! Keep it up\n");
                } else if (battingscore == 4) {
                    printf("It's a four! Great shot\n");
                }
                sum += battingscore;
                printf("%s score = %d\n", battingplayer, sum);
            }
        }
    }
    
    return sum;
}
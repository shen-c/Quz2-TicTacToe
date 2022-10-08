#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[10];//the board used for the game
int winCondition();//check if a win condition is met
void displayBoard();//print board to console
int boardTracker[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};//tracks unused positions, used for computer player

//display the board
void displayBoard(){
    printf("\n     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[1], board[2], board[3]);
    printf("_ _ _|_ _ _|_ _ _\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[4], board[5], board[6]);
    printf("_ _ _|_ _ _|_ _ _\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[7], board[8], board[9]);

    printf("     |     |     \n\n");
}

//reset the board
void resetBoard(){
    //reset the board to this
    char baseBoard[10] = {'-', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    for(int i = 0; i < 10; i++){
        board[i] = baseBoard[i];
        boardTracker[i] = i;
    }
}

//check win conditions
int winCondition(){

    if (board[1] == board[2] && board[2] == board[3] ||//across
        board[4] == board[5] && board[5] == board[6] ||
        board[7] == board[8] && board[8] == board[9] ||
        board[1] == board[4] && board[4] == board[7] ||//down
        board[2] == board[5] && board[5] == board[8] ||
        board[3] == board[6] && board[6] == board[9] ||
        board[1] == board[5] && board[5] == board[9] ||//diag
        board[3] == board[5] && board[5] == board[7]
        )
        return 1;
    else
        return  0;
}

//play game
void playGame(int computer){

    srand(time(NULL));//for random seed
    
    char piece;//the piece to be placed in char board[10]
    int player = 1;//tracks player's turn
    int turnCounter = 1;//tracks how many turns have elapsed
    int winStatus = 0;//tracks win conditions
    int selection;//user selection
    int random;//used to generate random move by computer
    int emptySpace = 0;//used to help track valid moves
    

    do{
        displayBoard();
        player = (player % 2) ? 1 : 2;

        if(player == 2 && computer == 1){//check computer boolean
            do{//generate random, valid move
                random = rand()%10;
                if(boardTracker[random] != 0){
                    selection = boardTracker[random];
                    printf("Player 2 (COMPUTER) places a piece in position: %d", selection);
                    emptySpace++;
                }
            }while (emptySpace == 0);

            emptySpace = 0;
            
        }else{//get move selection from user
            printf("Enter a number on the board, player %d: ", player);
            scanf("%d", &selection);
        }

        piece = (player == 1) ? 'X' : 'O';//set piece according to user

        if(boardTracker[selection] == 0){//validates move
            printf("That spot is taken, please try again: ");
            player--;
            getchar();
        }else{
            board[selection] = piece;
            boardTracker[selection] = 0;
            turnCounter++;
        }


        player++;
        winStatus = winCondition();
    }while(winStatus == 0 && turnCounter < 10);

    displayBoard();

    if(winStatus == 1){//checks win conditions
        printf("GAME OVER: Player %d wins!", --player);
    }else{
        printf("GAME OVER: DRAW!");
    }

}

//main execution
int main(){

    int choice;

    printf("\n\n=========================== ");
    printf("\n\nWELCOME TO TIC TAC TOE!\n");

    do{
        resetBoard();//reset the board each play
        printf("\nPlay with a computer?");
        printf("\n(1 - yes, 2 - no): ");
        scanf("%d", &choice);
        //start the game
        printf("\nStarting game......\n");
        playGame(choice);
        //restart the game
        printf("\nPlay again?");
        printf("\n(1 - yes, 0 - no): ");
        scanf("%d", &choice);
    }while(choice != 0);

    printf("\nTHANKS FOR PLAYING! \n\n");
    printf("===========================\n");

    return 0;
}
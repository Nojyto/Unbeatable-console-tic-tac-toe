#include <iostream>
#include <time.h>
#include <random>
#include <algorithm>

#define Player 'O'
#define Ai 'X'

char grid[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

void printGrid()
{
    system("cls");
    printf("   ----Tic Tac Toe----\n  Player (O)  -  Ai (X)\n\n");
    printf("        |     |     \n");
    printf("     %c  |  %c  |  %c\n", grid[0], grid[1], grid[2]);
    printf("   _____|_____|_____\n");
    printf("        |     |     \n");
    printf("     %c  |  %c  |  %c\n", grid[3], grid[4], grid[5]);
    printf("   _____|_____|_____\n");
    printf("        |     |     \n");
    printf("     %c  |  %c  |  %c\n", grid[6], grid[7], grid[8]);
    printf("        |     |     \n\n");
}

void getUserMove()
{
    int gridNumber;

    printGrid();
    printf("Player enter a number: ");
    scanf("%i", &gridNumber);

    if(isdigit(gridNumber) || gridNumber > 9 || grid[gridNumber - 1] == Player || grid[gridNumber - 1] == Ai)
        getUserMove();
    else
        grid[gridNumber - 1] = Player;
}

int isWin(char who)
{
    if (grid[0] == grid[1] && grid[1] == grid[2]) return who == grid[0] ? 1 : -1;
    if (grid[3] == grid[4] && grid[4] == grid[5]) return who == grid[3] ? 1 : -1;
    if (grid[6] == grid[7] && grid[7] == grid[8]) return who == grid[6] ? 1 : -1;
    if (grid[0] == grid[3] && grid[3] == grid[6]) return who == grid[0] ? 1 : -1;
    if (grid[1] == grid[4] && grid[4] == grid[7]) return who == grid[1] ? 1 : -1;
    if (grid[2] == grid[5] && grid[5] == grid[8]) return who == grid[2] ? 1 : -1;
    if (grid[0] == grid[4] && grid[4] == grid[8]) return who == grid[0] ? 1 : -1;
    if (grid[2] == grid[4] && grid[4] == grid[6]) return who == grid[2] ? 1 : -1;
    if (grid[0] != '1' && grid[1] != '2' && grid[2] != '3' && grid[3] != '4' && grid[4] != '5' && grid[5] != '6' && grid[6] != '7' && grid[7] != '8' && grid[8] != '9') return 0;
    return 2;
}

int minimax(char *tmpgrid, bool isMax)
{
    if(isWin(Ai) != 2)
        return isWin(Ai);

    if(isMax){
        int bestScore = INT_MIN;
        for(int i = 0; i < 9; i++){
            if(isdigit(tmpgrid[i])){
                tmpgrid[i] = Ai;
                int score = minimax(tmpgrid, false);
                tmpgrid[i] = i + 49;
                bestScore = std::max(bestScore, score);
            }
        }
        return bestScore;
    }else{
        int bestScore = INT_MAX;
        for(int i = 0; i < 9; i++){
            if(isdigit(tmpgrid[i])){
                tmpgrid[i] = Player;
                int score = minimax(tmpgrid, true);
                tmpgrid[i] = i + 49;
                bestScore = std::min(bestScore, score);
            }
        }
        return bestScore;
    }
}

void getAiMove()
{
    int bestScore = INT_MIN, bestMove;

    for(int i = 0; i < 9; i++){
        if(isdigit(grid[i])){
            grid[i] = Ai;
            int score = minimax(grid, false);
            grid[i] = i + 49;
            if(bestScore < score){
                bestScore = score;
                bestMove = i;
            }
        }
    }

    grid[bestMove] = Ai;
}

void getFirstMove()
{
    srand(time(NULL));
    int corners[4] = {0, 2, 6, 8};
    if(rand() % 2)
        grid[corners[rand() % 4]] = Ai;
}

bool isGameOver()
{
    switch (isWin(Player)){
        case 2:
            break;
        case 1:
            printGrid();
            printf("You win!");
            return true;
        case 0:
            printGrid();
            printf("It's a tie.");
            return true;
        case -1:
            printGrid();
            printf("You lose.");
            return true;
    }

    return false;
}

int main()
{
    getFirstMove();

    while(true){
        getUserMove();
        if(isGameOver())
            break;

        getAiMove();
        if(isGameOver())
            break;
    }

    std::cin.ignore();
    std::cin.get();
}

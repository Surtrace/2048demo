#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define SIZE 4

int board[SIZE][SIZE];
int score = 0;

// Functions
void initBoard();
void addRandomTile();
void printBoard();
int isGameOver();
int isWin();
void moveLeft();
void moveRight();
void moveUp();
void moveDown();

// Gameboard initialization
void initBoard() {
    int i, j;
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
    score = 0;
    
    // 2 random tiles on the gameboard
    addRandomTile();
    addRandomTile();
}

// Randomly add 2 or 4 on the gameboard
void addRandomTile() {
    int emptyCells[SIZE * SIZE][2];
    int count = 0;
    int i, j;
    
    // Find all the empty cells
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            if(board[i][j] == 0) {
                emptyCells[count][0] = i;
                emptyCells[count][1] = j;
                count++;
            }
        }
    }
    
    if(count > 0) {
        // Randomly choose an empty cell
        int index = rand() % count;
        int x = emptyCells[index][0];
        int y = emptyCells[index][1];
        
        // With a 90% possibility to summon 2, and 10% possibility to summon 4
        board[x][y] = (rand() % 10 == 0) ? 4 : 2;
    }
}

// Print the gameboard
void printBoard() {
    system("cls"); // Clear
    printf("2048 - Score: %d\n\n", score);
    
    int i, j;
    for(i = 0; i < SIZE; i++) {
        printf("+------+------+------+------+\n");
        printf("|");
        for(j = 0; j < SIZE; j++) {
            if(board[i][j] == 0) {
                printf("      |");
            } else {
                printf("%5d |", board[i][j]);
            }
        }
        printf("\n");
    }
    printf("+------+------+------+------+\n");
    printf("\nUse WASD or arrow keys to move the tiles, Q to exit\n");
}

// To check if the game is over
int isGameOver() {
    int i, j;
    
    // To check if there's empty cell
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            if(board[i][j] == 0) {
                return 0;
            }
        }
    }
    
    // To check if there's a pair of adjacent cells that can be merged
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            if((j < SIZE - 1 && board[i][j] == board[i][j + 1]) ||
               (i < SIZE - 1 && board[i][j] == board[i + 1][j])) {
                return 0;
            }
        }
    }
    
    return 1;
}

// Winning
int isWin() {
    int i, j;
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            if(board[i][j] == 2048) {
                return 1;
            }
        }
    }
    return 0;
}

// Left
void moveLeft() {
    int i, j, k;
    int moved = 0;
    
    for(i = 0; i < SIZE; i++) {
        // Remove space
        for(j = 0, k = 0; j < SIZE; j++) {
            if(board[i][j] != 0) {
                board[i][k] = board[i][j];
                if(k != j) {
                    board[i][j] = 0;
                    moved = 1;
                }
                k++;
            }
        }
        
        // Merge similar cells
        for(j = 0; j < SIZE - 1; j++) {
            if(board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                board[i][j] *= 2;
                score += board[i][j];
                board[i][j + 1] = 0;
                moved = 1;
                
                // Move other cells
                for(k = j + 1; k < SIZE - 1; k++) {
                    board[i][k] = board[i][k + 1];
                }
                board[i][SIZE - 1] = 0;
            }
        }
    }
    
    if(moved) {
        addRandomTile();
    }
}

// Right
void moveRight() {
    int i, j, k;
    int moved = 0;
    
    for(i = 0; i < SIZE; i++) {
        // Remove space
        for(j = SIZE - 1, k = SIZE - 1; j >= 0; j--) {
            if(board[i][j] != 0) {
                board[i][k] = board[i][j];
                if(k != j) {
                    board[i][j] = 0;
                    moved = 1;
                }
                k--;
            }
        }
        
        // Merge similar cells
        for(j = SIZE - 1; j > 0; j--) {
            if(board[i][j] != 0 && board[i][j] == board[i][j - 1]) {
                board[i][j] *= 2;
                score += board[i][j];
                board[i][j - 1] = 0;
                moved = 1;
                
                // Move other cells
                for(k = j - 1; k > 0; k--) {
                    board[i][k] = board[i][k - 1];
                }
                board[i][0] = 0;
            }
        }
    }
    
    if(moved) {
        addRandomTile();
    }
}

// Up
void moveUp() {
    int i, j, k;
    int moved = 0;
    
    for(j = 0; j < SIZE; j++) {
        // Remove space
        for(i = 0, k = 0; i < SIZE; i++) {
            if(board[i][j] != 0) {
                board[k][j] = board[i][j];
                if(k != i) {
                    board[i][j] = 0;
                    moved = 1;
                }
                k++;
            }
        }
        
        // Merge similar cells
        for(i = 0; i < SIZE - 1; i++) {
            if(board[i][j] != 0 && board[i][j] == board[i + 1][j]) {
                board[i][j] *= 2;
                score += board[i][j];
                board[i + 1][j] = 0;
                moved = 1;
                
                // Move other cells
                for(k = i + 1; k < SIZE - 1; k++) {
                    board[k][j] = board[k + 1][j];
                }
                board[SIZE - 1][j] = 0;
            }
        }
    }
    
    if(moved) {
        addRandomTile();
    }
}

// Down
void moveDown() {
    int i, j, k;
    int moved = 0;
    
    for(j = 0; j < SIZE; j++) {
        // Remove space
        for(i = SIZE - 1, k = SIZE - 1; i >= 0; i--) {
            if(board[i][j] != 0) {
                board[k][j] = board[i][j];
                if(k != i) {
                    board[i][j] = 0;
                    moved = 1;
                }
                k--;
            }
        }
        
        // Merge similar cells
        for(i = SIZE - 1; i > 0; i--) {
            if(board[i][j] != 0 && board[i][j] == board[i - 1][j]) {
                board[i][j] *= 2;
                score += board[i][j];
                board[i - 1][j] = 0;
                moved = 1;
                
                // Move other cells
                for(k = i - 1; k > 0; k--) {
                    board[k][j] = board[k - 1][j];
                }
                board[0][j] = 0;
            }
        }
    }
    
    if(moved) {
        addRandomTile();
    }
}

int main() {
    srand(time(NULL)); // Random seed
    
    initBoard();
    printBoard();
    
    char input;
    while(1) {
        input = getch();
        
        switch(input) {
            case 'w':
            case 'W':
            case 72: // Up
                moveUp();
                break;
            case 's':
            case 'S':
            case 80: // Down
                moveDown();
                break;
            case 'a':
            case 'A':
            case 75: // Left
                moveLeft();
                break;
            case 'd':
            case 'D':
            case 77: // Right
                moveRight();
                break;
            case 'q':
            case 'Q':
                printf("Game over! Score: %d\n", score);
                return 0;
            default:
                continue;
        }
        
        printBoard();
        
        if(isWin()) {
            printf("Congratulations! You win! Score: %d\n", score);
            break;
        }
        
        if(isGameOver()) {
            printf("Game over! Score: %d\n", score);
            break;
        }
    }
    
    return 0;
}
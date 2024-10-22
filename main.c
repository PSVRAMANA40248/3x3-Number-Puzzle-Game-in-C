//3x3 Number Puzzle Game in C



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

// Function declarations
void initializeGrid(int grid[SIZE][SIZE]);
void shuffleGrid(int grid[SIZE][SIZE]);
void displayGrid(int grid[SIZE][SIZE]);
int isSolved(int grid[SIZE][SIZE]);
void moveTile(int grid[SIZE][SIZE], char move, int *moves);
void findEmptyTile(int grid[SIZE][SIZE], int *emptyRow, int *emptyCol);

int main() {
    int grid[SIZE][SIZE];
    int moves = 0;
    char move;
    
    // Initialize and shuffle the grid
    initializeGrid(grid);
    shuffleGrid(grid);
    
    while (1) {
        // Display the current state of the grid
        displayGrid(grid);
        
        // Check if the puzzle is solved
        if (isSolved(grid)) {
            printf("Congratulations! You solved the puzzle in %d moves!\n", moves);
            break;
        }
        
        // Get the user's move
        printf("Enter move (w=up, s=down, a=left, d=right): ");
        scanf(" %c", &move);
        
        // Process the move
        moveTile(grid, move, &moves);
    }

    return 0;
}

// Initialize the grid with numbers 1 to 8 and an empty tile (0)
void initializeGrid(int grid[SIZE][SIZE]) {
    int num = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == SIZE - 1 && j == SIZE - 1)
                grid[i][j] = 0; // empty tile
            else
                grid[i][j] = num++;
        }
    }
}

// Shuffle the grid randomly
void shuffleGrid(int grid[SIZE][SIZE]) {
    srand(time(0));
    for (int i = 0; i < SIZE * SIZE * 10; i++) {
        int emptyRow, emptyCol;
        findEmptyTile(grid, &emptyRow, &emptyCol);

        int direction = rand() % 4;
        char move;
        switch (direction) {
            case 0: move = 'w'; break; // Up
            case 1: move = 's'; break; // Down
            case 2: move = 'a'; break; // Left
            case 3: move = 'd'; break; // Right
        }
        moveTile(grid, move, NULL);
    }
}

// Display the grid to the user
void displayGrid(int grid[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0)
                printf("   ");
            else
                printf("%2d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Check if the puzzle is solved
int isSolved(int grid[SIZE][SIZE]) {
    int num = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == SIZE - 1 && j == SIZE - 1 && grid[i][j] == 0) {
                return 1; // Puzzle solved
            } else if (grid[i][j] != 0 && grid[i][j] != num++) {
                return 0; // Not solved
            }
        }
    }
    return 0;
}

// Move the tile based on user input (w, s, a, d)
void moveTile(int grid[SIZE][SIZE], char move, int *moves) {
    int emptyRow, emptyCol;
    findEmptyTile(grid, &emptyRow, &emptyCol);
    
    int newRow = emptyRow, newCol = emptyCol;
    
    switch (move) {
        case 'w': newRow = emptyRow + 1; break; // Up
        case 's': newRow = emptyRow - 1; break; // Down
        case 'a': newCol = emptyCol + 1; break; // Left
        case 'd': newCol = emptyCol - 1; break; // Right
        default: printf("Invalid move! Use w, s, a, or d.\n"); return;
    }
    
    if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE) {
        grid[emptyRow][emptyCol] = grid[newRow][newCol];
        grid[newRow][newCol] = 0;
        if (moves != NULL) {
            (*moves)++;
        }
    } else {
        printf("Move not allowed!\n");
    }
}

// Find the position of the empty tile (0)
void findEmptyTile(int grid[SIZE][SIZE], int *emptyRow, int *emptyCol) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) {
                *emptyRow = i;
                *emptyCol = j;
                return;
            }
        }
    }
}

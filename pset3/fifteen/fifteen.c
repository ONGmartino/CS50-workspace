/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(50);
        }

        // sleep thread for animation's sake
        usleep(50);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(20);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // init the maximum value
	int tab = (d*d)-1;
	
	// for every row, for every column, place a decrescent value
	for(int row = 0; row < d; row++)
		for(int col = 0; col < d; col++, tab--)
			board[row][col] = tab;
	
    // if even dimension, switch the last 2 values to ensure possible solution
	if (d%2 == 0){
		board[d-1][d-3] = 1;
		board[d-1][d-2] = 2;
	}
}

/**
 * Prints the board in its current state.
 */
void draw(void){
    
    // separate the board from the left and type the upper edge
	printf("\n\n\n");
	for (int i = 0; i < d; i++)
		printf("-----");
	printf("-\n");
	
	// per line, type each line ensuring readability 
	for(int row = 0; row < d; row++){
		printf("|");
		
		for(int col = 0; col < d; col++){
		    
			if (board[row][col] == 0)
				printf("    |");
				
			else if (board[row][col]<10)
				printf("  %i |", board[row][col]);
			
			else
				printf(" %i |", board[row][col]);
			
		}
		
	    //end the line and type a separator
	    
		printf("\n");
		for (int i = 0; i < d; i++)
			printf("-----");
		printf("-\n");
	}
	printf("\n\n\n\n");
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile){
    
    // I tried, but this is the best stylistic form I came up with that <i>works</i>
    
    // Iterate through the board, when you find the item suggested:
    // look at every side permitted (not over the edge) and swap the element with the zero
    
	for (int row = 0; row < d; row++ ){
		for (int col = 0; col < d; col++){
		    if (board[row][col] == tile){
			
				if (board[row][col+1] == 0 && (col+1) < d){
					board[row][col] = 0;
					board[row][col+1] = tile;
					return true;
				}
				if (board[row][col-1] == 0 && col > 0){
					board[row][col] = 0;
					board[row][col-1] = tile;
					return true;
				}
				if (board[row+1][col] == 0 && (row+1) < d){
					board[row][col] = 0;
					board[row+1][col] = tile;
					return true;
				}
				if (board[row-1][col] == 0 && row > 0){
					board[row][col] = 0;
					board[row-1][col] = tile;
					return true;
				}
			}
		}
	}
	
	// if there is no zero neighbours, move not permitted
	return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
	int check = 1;

    // iterate through the board, for each position, compare with an increasing int (check)
    // the first value that doesn't match, return false (aka TRY AGAIN)
	
	for(int row = 0; row < d; row++){
		for(int col = 0; col < d; col++, check++)
		{
            if(board[row][col] == 0 && check == (d*d))
                return true;
            
            if(board[row][col] != 0 && board[row][col] != check)
                return false;
		}
	}
	
	// logically, the next line is not required. However, Clang told me that
	// "control may reach end of non-void function". 
	return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}








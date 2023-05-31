/*
    Juego del Gato y el ratón con IA
    Trabajo hecho para la materia de Inteligencia Artificial I.
    Por Elizabeth Loaeza Morales
*/

#include<stdio.h>
#include<stdbool.h>

#define IA 1
#define HUMAN 2

#define SIDE 3

#define IAMOVE 'O'
#define HUMANMOVE 'X'

void printBoard(char board[][SIDE])
{
	printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
	printf("\t\t\t-----------\n");
	printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
	printf("\t\t\t-----------\n");
	printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

void moves()
{
	printf("\t\nElija el numero de casilla que quiera usar\n\n");

	printf("\t\t\t 1 | 2 | 3 \n");
	printf("\t\t\t-----------\n");
	printf("\t\t\t 4 | 5 | 6 \n");
	printf("\t\t\t-----------\n");
	printf("\t\t\t 7 | 8 | 9 \n\n");
}

void start(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
			board[i][j] = ' ';
	}
}

void winner(int playerTurn)
{
	if (playerTurn == IA)
		printf("\t\tHa ganado la IA\n");
	else
		printf("\t\tGanaste!\n");
}

bool rowWin(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[i][0] == board[i][1] &&
			board[i][1] == board[i][2] &&
			board[i][0] != ' ')
			return (true);
	}
	return(false);
}

bool columnWin(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[0][i] == board[1][i] &&
			board[1][i] == board[2][i] &&
			board[0][i] != ' ')
			return (true);
	}
	return(false);
}

bool diagonalWin(char board[][SIDE])
{
	if (board[0][0] == board[1][1] &&
		board[1][1] == board[2][2] &&
		board[0][0] != ' ')
		return(true);

	if (board[0][2] == board[1][1] &&
		board[1][1] == board[2][0] &&
		board[0][2] != ' ')
		return(true);

	return(false);
}

bool gameOver(char board[][SIDE])
{
	return(rowWin(board) || columnWin(board) || diagonalWin(board) );
}

int alphabeta(char board[][SIDE], int depth, int alpha, int beta, bool isAI)
{
    int score;
    if(gameOver(board) == true)
    {
        if(isAI)
            return -1;
        else
            return 1;
    }

    if(depth == 9)
        return 0;

    if(isAI)
    {
        for(int i=0; i<SIDE; i++)
        {
            for(int j=0; j<SIDE; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = IAMOVE;
                    score = alphabeta(board, depth + 1, alpha, beta, false);
                    board[i][j] = ' ';
                    if(score > alpha)
                    {
                        alpha = score;
                    }
                    if(beta <= alpha)
                    {
                        return alpha;
                    }
                }
            }
        }
        return alpha;
    }
    else
    {
        for(int i=0; i<SIDE; i++)
        {
            for(int j=0; j<SIDE; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = HUMANMOVE;
                    score = alphabeta(board, depth + 1, alpha, beta, true);
                    board[i][j] = ' ';
                    if(score < beta)
                    {
                        beta = score;
                    }
                    if(beta <= alpha)
                    {
                        return beta;
                    }
                }
            }
        }
        return beta;
    }
}

int bestMove(char board[][SIDE], int moveList)
{
    int x = -1, y = -1;
    int score, bestScore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = IAMOVE;
                score = alphabeta(board, moveList+1, -1000, 1000, false);
                board[i][j] = ' ';
                if(score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x*3+y;
}

void startGame(int playerTurn)
{
	char board[SIDE][SIDE];
	int moveIndex = 0, x = 0, y = 0;

	start(board);

	while (gameOver(board) == false && moveIndex != SIDE*SIDE)
	{
		int n;
		if (playerTurn == IA)
		{
			n = bestMove(board, moveIndex);
			x = n / SIDE;
			y = n % SIDE;
			board[x][y] = IAMOVE;
			printBoard(board);
			moveIndex ++;
			playerTurn = HUMAN;
		}

		else if (playerTurn == HUMAN)
		{
			printf("\t\n\nSu casilla = ");
			scanf("%d",&n);
			n--;
			x = n / SIDE;
			y = n % SIDE;
			if(board[x][y] == ' ' && n<9 && n>=0)
			{
				board[x][y] = HUMANMOVE;
				printBoard(board);
				moveIndex ++;
				playerTurn = IA;
			}
            			else if(board[x][y] != ' ' && n<9 && n>=0)
			{
				printf("\t\nCasilla ocupada");
			}
			else if(n<0 || n>8)
			{
				printf("\tPosicion no valida\n");
			}
		}
	}

	if (gameOver(board) == false && moveIndex == SIDE * SIDE)
		printf("Haz empatado\n");
	else
	{
		if (playerTurn == IA)
			playerTurn = HUMAN;
		else if (playerTurn == HUMAN)
			playerTurn = IA;

		winner(playerTurn);
	}
}

int main()
{
    char cont='y';
    do {
        char choice;
        printf("Desea empezar primero? (y/n): ");
        scanf(" %c", &choice);
        if(choice=='n') {
            moves();
            startGame(IA);
        }
        else if(choice=='y') {
            moves();
            startGame(HUMAN);
        }
        else {
            printf("\nNo sabe leer? escoja y para si y n para no\n");
            continue; // Continúa con la siguiente iteración del bucle do-while
        }

        printf("\t\nRevancha? (y/n): ");
        scanf(" %c", &cont);
    } while(cont=='y');
    return (0);
}

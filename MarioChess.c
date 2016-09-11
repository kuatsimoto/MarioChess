#include "stdio.h"
#include "defs.h"

#define FEN1 "3k1b2/pp6/3Q4/8/3R4/8/5PP1/4K3 b - - 0 1 "
#define FEN2 "rnqbkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b KQkq e3 0 1  "
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
#define FEN4 "r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1B3/PP3PPP/RN1QKB1R w - - 0 1 "
#define KNIGHTSKINGS "5k2/1n6/4n3/6N1/8/3N4/8/5K2 b - - 0 1 "
#define ROOKS "6k1/8/5r2/8/1nR5/5N2/8/6K1 w - - 0 1 "
#define BISHOPS "6k1/1b6/5n2/8/1n4B1/1B3N2/1N6/2b3K1 w - - 0 1 "
#define QUEENS "6k1/8/4nq2/8/1nQ5/5N2/1N6/6K1 b - - 0 1 "
#define CASTLE1 "r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1  "
#define CASTLE2 "3rk2r/8/8/8/8/8/6p1/R3K2R b KQkq - 0 1  "



int main() {
	
	AllInit();
	
	S_BOARD board[1];
	InitPvTable(board->PvTable);
	S_MOVELIST list[1];
	S_SEARCHINFO info[1];
	int i;
	
	Parse_FEN(START_FEN,board);
	
	
	unsigned int Move = NOMOVE;
	char input[6] = "a2a3";
	int temp;
	int PvNum = 0;
	int Max = 0;
	
	
	//PrintBoard(board);
	//Move = ParseMove(input, board);
	//printf("\nEPFLAG = %X\n",MFLAGEP);
	//printf("move parsed\n");
	
	//MakeMove(board,Move);
	//PrintBoard(board);
	//printf("move made");
	
	
	while(TRUE) {
		PrintBoard(board);
		printf("Please enter a move > ");
		fgets(input , 6 , stdin);
		
		if(input[0]=='q') {
			break;
		} else if(input[0]=='t') {
			TakeMove(board);
		} else if(input[0] == 's') {
			info->depth = 6;
			SearchPosition(board, info);
			MakeMove(board,board->PvArray[0]);
		
		} else {
			Move = ParseMove(input, board);
			printf("Move = %X\n",Move);
			if(Move != NOMOVE) {
				//StorePvMove(board,Move);
				MakeMove(board,Move);
				printf("Move Made:%X",Move);
			} else { 
				printf("Move Not Found\n");
			}
			
		
		}
		
		
		fflush(stdin);
		
		//Parse_FEN(START_FEN,board);
	}
	
	free(board->PvTable->pTable);
	
	
	return 0;
}

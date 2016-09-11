#ifndef DEFS_H
#define DEFS_H

#include "stdio.h"
#include "stdlib.h"

//#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n); \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif


typedef unsigned long long U64; // unsigned 64bit number used for declarations

#define NAME "MarioChess 1.0"
#define BRD_SQ_NUM 120 //number of squares on the board

#define MAXGAMEMOVES 2048
#define MAXPOSITIONMOVES 256
#define MAXDEPTH 64

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK}; // defines the different pieces
enum {F_A, F_B, F_C, F_D, F_E, F_F, F_G, F_H, F_NONE}; //defines the files
enum {R_1, R_2, R_3, R_4, R_5, R_6, R_7, R_8, R_NONE}; //defines the ranks

enum {WHITE, BLACK, BOTH}; //defines colors of pieces

enum {
	A1 = 21, B1, C1, D1, E1, F1, G1, H1,
	A2 = 31, B2, C2, D2, E2, F2, G2, H2,
	A3 = 41, B3, C3, D3, E3, F3, G3, H3,
	A4 = 51, B4, C4, D4, E4, F4, G4, H4,
	A5 = 61, B5, C5, D5, E5, F5, G5, H5,
	A6 = 71, B6, C6, D6, E6, F6, G6, H6,
	A7 = 81, B7, C7, D7, E7, F7, G7, H7,
	A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
}; // defines each square on the board (taking into account O.B. squares)

enum { FALSE, TRUE };

enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8};

typedef struct {
	int move;
	int score;
} S_MOVE;

typedef struct {
	S_MOVE moves[MAXPOSITIONMOVES];
	int count;
}S_MOVELIST;

//Struct that will allow us to keep a history of each move and undo a move if nessesary
typedef struct {
	
	int move;
	int castlePerm;
	int enPas;
	int fiftyMove;
	U64 posKey;
	
} S_UNDO;

typedef struct {
	
	U64 posKey;
	int move;
	
}S_PVENTRY;

typedef struct {
	
	S_PVENTRY *pTable;
	int numEntries;
	
}S_PVTABLE;

//Struct that defines the board
typedef struct {
	
	int pieces[BRD_SQ_NUM];
	U64 pawns[3]; 
	
	int KingSq[2];
	
	int side;
	int enPas;
	int fiftyMove;
	
	int ply;
	int hisPly;
	
	int castlePerm;
	
	U64 posKey;
	
	int pceNum[13];
	int bigPce[2];
	int majPce[2];
	int minPce[2];
	int material[2];
	
	S_UNDO history[MAXGAMEMOVES];
	
	//piece list. Using this list we can add pieces to the board. e.g. to add a white knight to E1 pList[wN][0] = E1;
	int pList[13][10];
	
	S_PVTABLE PvTable[1];
	int PvArray[MAXDEPTH];
	
	int searchHistory[13][BRD_SQ_NUM];
	int searchKillers[2][MAXDEPTH];
	
	
} S_BOARD;

typedef struct {
	
	int starttime;
	int stoptime;
	int depth;
	int depthset;
	int timeset;
	int movestogo;
	int infinite;
	
	long nodes;
	
	int quit;
	int stopped;
	
	float fh;
	float fhf;
	
}S_SEARCHINFO;

/* GAME MOVES */

/*
move integer =

0000 0000 0000 0000 0000 0111 1111 -> From 0x7F
0000 0000 0000 0011 1111 1000 0000 -> To >> 7 = 0x7F
0000 0000 0011 1100 0000 0000 0000 -> Capture >> 14 = 0xF
0000 0000 0100 0000 0000 0000 0000 -> enPas 0x40000
0000 0000 1000 0000 0000 0000 0000 -> Pawn Start 0x80000
0000 1111 0000 0000 0000 0000 0000 -> Promoted Piece >> 20 = 0xF
0001 0000 0000 0000 0000 0000 0000 -> Castle move 0x1000000

*/

#define FROMSQ(m) ((m) & 0x7F)
#define TOSQ(m) (((m)>>7) & 0x7F)
#define CAPTURED(m) (((m)>>14) & 0xF)
#define PROMOTED(m) (((m)>>20) & 0XF)

#define MFLAGEP 0X40000
#define MFLAGPS 0X80000
#define MFLAGCA 0X1000000

#define MFLAGCAP 0x007C000
#define MFLAGPROM 0x0F00000

#define NOMOVE 0



/* MACROS */

//Macro that outputs the index on a 120 square board with the inputs of file and rank of a 64 square board.
#define FR2SQ(f,r) ( (21+(f) ) + ( (r) * 10 ) )
#define SQ64(sq120) (Sq120ToSq64[(sq120)])
#define SQ120(sq64) (Sq64ToSq120[(sq64)])
#define POP(b) PopBit(b)
#define CNT(b) CountBits(b)
#define CLRBIT(bb,sq) ((bb) &= ClearMask[(sq)])
#define SETBIT(bb,sq) ((bb)|= SetMask[(sq)])

#define IsBQ(p) (PieceBishopQueen[(p)])
#define IsRQ(p) (PieceRookQueen[(p)])
#define IsKn(p) (PieceKnight[(p)])
#define IsKi(p) (PieceKing[(p)])

/* GLOBALS */

//arrays to convert from 120 square board to 64 square board and vice versa
extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];

extern U64 SetMask[64];
extern U64 ClearMask[64];

extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];

extern char PceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];

extern int PieceBig[13];
extern int PieceMaj[13];
extern int PieceMin[13];
extern int PieceVal[13];
extern int PieceCol[13];
extern int PiecePawn[13];

extern int FilesBrd[BRD_SQ_NUM];
extern int RanksBrd[BRD_SQ_NUM];

extern int PieceKnight[13];
extern int PieceKing[13];
extern int PieceRookQueen[13];
extern int PieceBishopQueen[13];
extern int PieceSliding[13];

/* FUNCTIONS */

//init.c
extern void AllInit();

//bitboards.c
extern void PrintBitBoard(U64 bb);
extern int PopBit(U64 *bb);
extern int CountBits(U64 b);

//hashkeys.c
extern U64 GeneratePosKey(const S_BOARD *pos);

//board.c
extern void ResetBoard(S_BOARD *pos);
extern void PrintBoard(const S_BOARD *pos);
extern int Parse_FEN(char *fen, S_BOARD *pos) ;
extern void UpdateListsMaterial(S_BOARD *pos);
extern int CheckBoard(const S_BOARD *pos);

//attack.c
extern int SqAttacked(const int sq, const int side, const S_BOARD *pos);

//io.c
extern char *PrMove(const int move);
extern char *PrSq(const int sq);
extern void PrintMoveList(const S_MOVELIST *list);
extern unsigned int ParseMove(char *ptrChar, S_BOARD *pos); 

//validate.c
extern int PieceValid(const int pce);
extern int PieceValidEmpty(const int pce);
extern int FileRankValid(const int fr);
extern int SideValid(const int side);
extern int SqOnBoard(const int sq);

//movegen.c
extern void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *list);
extern void GenerateAllCaps(const S_BOARD *pos, S_MOVELIST *list);
extern int MoveExists(S_BOARD *pos, const int move);
extern int InitMvvLva();

//makemove.c
extern void TakeMove(S_BOARD *pos);
extern int MakeMove(S_BOARD *pos, unsigned int move);

//perft.c
extern void PerftTest(int depth, S_BOARD *pos);

//search.c
extern int SearchPosition(S_BOARD *pos, S_SEARCHINFO *info);

//misc.c
extern int GetTimeMs();

//pvtable.c
extern void InitPvTable(S_PVTABLE *table);
extern void  StorePvMove(const S_BOARD *pos, const int move);
extern int ProbePvTable(const S_BOARD *pos);
extern int GetPvLine(const int depth, S_BOARD *pos);
extern void ClearPvTable(S_PVTABLE *table);

//evaluate.c
extern int EvalPosition(const S_BOARD *pos);

#endif
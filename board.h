//
//  board.h
//  FloppyFour
//
//  Created by Martin Schijf on 10/02/2022.
//

#ifndef board_h
#define board_h

extern int board[7][6];
extern int top[7];
extern int clr;

extern int *field2tuple[7][6][14];
extern int tuple[69];

extern void initBoard(void);
    
#endif /* board_h */

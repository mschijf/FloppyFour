//
//  search.c
//  FloppyFour
//
//  Created by Martin Schijf on 10/02/2022.
//

#include "search.h"
#include "board.h"
#include "move.h"
#include "eval.h"

long nodeCount;

int isThread(int **tuple, int clr) {
    int threadOpponent = 0;
    int threadTupleColor;
    int threadTupleOpponent;
    if (clr < 0) {
        threadTupleColor = 3;
        threadTupleOpponent = 24;
    } else {
        threadTupleColor = 24;
        threadTupleOpponent = 3;
    }
    while (*tuple) {
        if (**tuple == threadTupleColor)
            return 1;
        if (**tuple == threadTupleOpponent)
            threadOpponent = -1;
        tuple++;
    }
    return threadTupleOpponent;
}

int generateMoves(int *moveBuffer) {
    int moveCount = 0;
    int onlyLosingMoves = -1;
    int preventLosingMove = -1;
    for (int col=0; col<7; ++col){
        if (top[col] < 6) {
            int thread = isThread(field2tuple[col][top[col]], clr);
            if (thread == 1) {
                moveBuffer[0] = col;
                return 1;
            } else if (thread == -1) {
                preventLosingMove = col;
            } else if (top[col] < 5 && isThread(field2tuple[col][top[col]+1], clr) == -1) {
                onlyLosingMoves = col;
            } else {
                moveBuffer[moveCount++] = col;
            }
        }
    }
    if (preventLosingMove >= 0) {
        moveBuffer[0] = preventLosingMove;
        return 1;
    } else if (moveCount == 0 && onlyLosingMoves > 0) {
        moveBuffer[0] = onlyLosingMoves;
        return 1;
    }
    return moveCount;
}

int alfabeta(int depth) {
    nodeCount++;
    if (eval > 5000 || eval < -5000) {
        return clr * 5000;
    }
    if (depth <= 0) {
        return clr * eval;
    }

    int moves[7];
    int moveCount = generateMoves(moves);
    int best = -10000000;
    for (int i=0; i<moveCount; ++i) {
        doMove(moves[i]);
        int v = -alfabeta(depth-1);
        if (v > best)
            best = v;
        undoMove(moves[i]);
    }
    return best;
}

//
//  eval.c
//  FloppyFour
//
//  Created by Martin Schijf on 10/02/2022.
//

#include "eval.h"
#include "board.h"

const int tupleValue[64] = {
          0, -1, -3, -7, -9999,  0,  0,  0,
          1,  0,  0,  0,     0,  0,  0,  0,
          3,  0,  0,  0,     0,  0,  0,  0,
          7,  0,  0,  0,     0,  0,  0,  0,
       9999,  0,  0,  0,     0,  0,  0,  0,
          0,  0,  0,  0,     0,  0,  0,  0,
          0,  0,  0,  0,     0,  0,  0,  0,
          0,  0,  0,  0,     0,  0,  0,  0
};

int eval;

void evaluateBoard(void) {
    eval=0;
    for (int t=0; t<69; ++t)
        eval += tupleValue[tuple[t]];
}

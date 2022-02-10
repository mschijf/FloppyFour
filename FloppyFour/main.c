//
//  main.c
//  FloppyFour
//
//  Created by Martin Schijf on 07/02/2022.
//

#include <stdio.h>
#include <stdlib.h>

#include "general.h"
#include "board.h"
#include "eval.h"
#include "search.h"



int  main(void) {
    char str[16];

    initBoard();
    evaluateBoard();

    int depth = 10;
    nodeCount = 0;
    timer_t *timer = startTimer();
    printf ("eval before: %d, ", eval);
    int v = alfabeta(depth);
    printf ("-> %d (after), \n", eval);

    long uSec = stopTimer(timer);
    printf ("value = %d, depth = %d\n", v, depth);
    printf("%ld nodes visited in: %.6lf seconds, ", nodeCount, uSec/1000000.0);
    printf("average of %s moves per second\n", sprintInt(str, nodeCount*1.0/(uSec/1000000.0), '.'));
    
    return 0;
}

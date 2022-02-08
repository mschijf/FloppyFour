/*
 * general.h
 *
 *  Created on: 23 jan. 2016
 *      Author: martin
 */

#ifndef GENERAL_H_
#define GENERAL_H_

#define abs(a) ((a) < 0 ? -(a) : (a))

#undef NULL
#define NULL ( (void *) 0)

typedef unsigned char bool_t;
#define TRUE	1
#define FALSE	0

extern void initGeneral(void);

char *sprintInt(char *str, int number, char seperator);
int word2num(char *s);

typedef struct timeval timer_t;
timer_t *startTimer(void);
long stopTimer(timer_t *timer);

extern long getRandom(int max);


#define _LOGFILE "/Users/martin/Documents/Dropbox/Martin/Programmeren/Eclipse/WorkspaceCPP/FloppyChess/logfiles/log.txt"
#define log(msg, args...) {\
	FILE* _fp = fopen(_LOGFILE, "a"); \
	if (_fp != NULL) {\
		fprintf(_fp, msg, ##args);\
		fclose(_fp);\
	}\
}

#define logPrint(msg, args...) {\
	printf(msg, ##args);\
	log(msg, ##args);\
}


#endif /* GENERAL_H_ */

/*
 * general.c
 *
 *  Created on: 22 aug. 2015
 *      Author: martin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/time.h>

#include "general.h"

void initGeneral() {
	srand(time(NULL));
}
char *sprintInt(char *str, int number, char seperator) {
	char *pbuf = str;

	if (number >= 1000000000){
		sprintf(pbuf, "%d%c", number / 1000000000, seperator);
		pbuf = pbuf + strlen(pbuf);
	}

	if (number >= 1000000) {
		if (number >= 1000000000)
			sprintf(pbuf, "%03d%c", (number % 1000000000) / 1000000, seperator);
		else
			sprintf(pbuf, "%d%c", (number % 1000000000) / 1000000, seperator);
		pbuf = pbuf + strlen(pbuf);
	}
	if (number >= 1000) {
		if (number >= 1000000)
			sprintf(pbuf, "%03d%c", (number % 1000000) / 1000, seperator);
		else
			sprintf(pbuf, "%d%c", (number % 1000000) / 1000, seperator);
		pbuf = pbuf + strlen(pbuf);
		sprintf(pbuf, "%03d", (number % 1000));
	} else {
		sprintf(pbuf, "%d", number);
	}
	return str;
}


int word2num(char *s) {
	char *err;
	int num = strtol(s, &err, 10);
	if (errno == EINVAL)
		return -1;
	return num;
}


timer_t *startTimer() {
	timer_t *timer = (timer_t *) malloc(sizeof(timer_t));
	gettimeofday(timer, NULL);
	return timer;
}


long stopTimer(timer_t *timer) {
	struct timeval stop;
	gettimeofday(&stop, NULL);
	long uSec = (stop.tv_sec-timer->tv_sec)*1000000 + (stop.tv_usec-timer->tv_usec);
	free(timer);
	return uSec;
}

long getRandom(int max) {

	return rand() % max;
}

#ifndef __RUNFIFO_H__
#define __RUNFIFO_H__

#define SIZE_RUNFIFO 1000

typedef struct squarefile {
	Square *data[SIZE_RUNFIFO];
	int head;
	int queue;
} RunFIFO;

int RunFIFO_empty(RunFIFO *f);
int RunFIFO_full(RunFIFO *f);

int RunFIFO_push(Square *s, RunFIFO *f);
Square *RunFIFO_pop(RunFIFO *f);

int RunFIFO_next(int i);

RunFIFO *RunFIFO_create();
RunFIFO *RunFIFO_alloc();
void RunFIFO_free(RunFIFO *f);

void RunFIFO_printf(RunFIFO *f);

#endif

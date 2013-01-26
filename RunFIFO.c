#include "main.h"
#include "RunFIFO.h"

int RunFIFO_empty(RunFIFO *f) {
	
	if (f->queue == -1) {
		
		return 1;
	}
	
	return 0;
}

int RunFIFO_full(RunFIFO *f) {

	if (RunFIFO_next(f->queue) == f->head) {
		return 1;
	}
	
	return 0;
}

int RunFIFO_push(Square *s, RunFIFO *f) {
		
	if (f != NULL && !RunFIFO_full(f)) {
		
		if (!RunFIFO_empty(f)) {
				
			f->queue = RunFIFO_next(f->queue);
			f->data[f->queue] = s;
		} else {
		
			f->head = 0;
			f->queue = 0;
			
			f->data[0] = s;
		}
		
		return 1;
	}

	return 0;
}

Square *RunFIFO_pop(RunFIFO *f) {
	
	Square *s = NULL;
	
	if (f != NULL && !RunFIFO_empty(f)) {
			
		s = f->data[f->head];
		
		//Si le pop vide la file : remise à zero
		if(f->head == f->queue){
			
			f->head = -1;
			f->queue = -1;
		} else {
		
			f->head = RunFIFO_next(f->head);
		}
	}
	
	return s;
}

int RunFIFO_next(int i) {

	return (i + 1) % SIZE_RUNFIFO;
}

RunFIFO *RunFIFO_create() {
	
	RunFIFO *f = RunFIFO_alloc();
	
	if (f != NULL) {
		
		f->queue = -1;
		f->head = -1;
	}
	
	return f;
}

RunFIFO *RunFIFO_alloc() {
	
	RunFIFO *f = (RunFIFO*) malloc(sizeof(RunFIFO));
	
	return f;
}

void RunFIFO_free(RunFIFO *f) {
	
	free(f);
}

void RunFIFO_printf(RunFIFO *f) {
	
	int i;
	
	printf("FIFO at %p : \n", f);
	printf("\t head : %d\n", f->head);
	printf("\tqueue : %d\n", f->queue);

	printf("\n");
	printf("--DATA\n");
	
	if (!RunFIFO_empty(f)) {
		if (f->head <= f->queue) {
			for (i = f->head; i <= f->queue; i++) {
				Square_printf(f->data[i]);
			}
		} else {
			for (i = f->head; i < SIZE_RUNFIFO; i++) {
				Square_printf(f->data[i]);
			}
			for (i = 0; i <= f->queue; i++) {
				Square_printf(f->data[i]);
			}
		}
	} else {
		printf("no data\n");
	}
	printf("------------------------------------------\n\n");
}
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "circbuf.h"

CB_e cb_IsFull (CircBuf_t * cb){
	return (cb->length == cb->size ? FULL : NORMAL);
}

CB_e cb_IsEmpty (CircBuf_t * cb){
	return (cb->length == 0 ? EMPTY : NORMAL);
}

uint8_t * cb_NextPosition (CircBuf_t * cb, uint8_t * p){
	return (cb->buffer+cb->length == p ? cb->buffer : p++);
}

CB_e cb_Enqueue(CircBuf_t * cb, uint8_t data){
	if (FULL==cb_IsFull(cb))
		return OVERFILL;
	cb->tail = cb_NextPosition(cb, cb->tail);
	*(cb->tail) = data;
	cb->length++;
	return NORMAL;
}

CB_e cb_Dequeue(CircBuf_t * cb, uint8_t *output){
	if (cb_IsEmpty(cb) == EMPTY)
		return UNDERDEQUEUE;
	* output = * (cb->head);
	cb->head = cb_NextPosition(cb, cb->head);
	cb->length--;
	return NORMAL;
}

CB_e cb_Init(CircBuf_t * cb, size_t num_items){
	//cb = (CircBuf_t *)malloc(sizeof(CircBuf_t));
	//if(!cb)
	//	return MALLOC_ERROR;
	cb->buffer = (uint8_t *)malloc(sizeof(uint8_t)*num_items);
	cb->size = num_items;
	if(!cb->buffer)
		return MALLOC_ERROR;
	cb->head = cb->buffer;
	cb->tail = cb->buffer;
	cb->length = 0;
	return INIT_SUCCESS;
}

CB_e cb_Destroy(CircBuf_t * cb){
	if(!cb)
		return FREE_ERROR;
	free(cb->buffer);
	cb->buffer = NULL;
	free(cb);
	cb = NULL;
	return FREE_SUCCESS;
}




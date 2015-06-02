#include "hw.h"
#include "fifo.h"

void fifo_init (fifo_t *self, void* bufPtr, size_t bufSize, size_t recSize)
{
	self->bufPtr = bufPtr;
	self->bufSize = bufSize;
	self->recSize = recSize;
}

void fifo_push (fifo_t *self, void* data)
{
}

void* fifo_pop (fifo_t *self)
{
}

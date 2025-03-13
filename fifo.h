#pragma once

extern void fifo_init (fifo_t *self, void* bufPtr, size_t bufSize, size_t recSize);
extern void fifo_push (fifo_t *self, void* data);
extern void* fifo_pop (fifo_t *self);

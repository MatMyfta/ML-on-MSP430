#ifndef MAIN_H
#define MAIN_H

#define CONF

#define AUTO_DT

//#define DEBUG

#ifdef DEBUG
#define PRINT
#endif

#include "dataset.h"
#include "fixed.h"
#include "pipeline.h"

void quicksort_idx(uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t indices[MEMORY_SIZE + UPDATE_THR], uint16_t first, uint16_t last);
uint16_t update_mem(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], uint16_t indices[MEMORY_SIZE+UPDATE_THR], uint16_t n_samples);

#endif // !MAIN_H

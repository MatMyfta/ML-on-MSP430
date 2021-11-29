#ifndef MAIN_H
#define MAIN_H

#define AUTO_DT
//#define PRINT

#ifdef PRINT
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#endif

#include "kmeans.h"
#include "dataset.h"
#include "fixed.h"
#include "pipeline.h"
#include "dt_training.h"
#include "dt_classification.h"
#include "knn_classification.h"
#include "test.h"
#include "pf_sim.h"

void quicksort_idx(uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t indices[MEMORY_SIZE + UPDATE_THR], uint16_t first, uint16_t last);
uint16_t update_mem(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], uint16_t indices[MEMORY_SIZE+UPDATE_THR], uint16_t n_samples);

#endif // !MAIN_H

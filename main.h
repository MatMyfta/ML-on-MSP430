#ifndef MAIN_H
#define MAIN_H

#define AUTO_KNN
#define PRINT

#include "kmeans.h"
#include "dataset.h"
#include "fixed.h"
#include "pipeline.h"
#include "dt_training.h"
#include "dt_classification.h"
#include "knn_classification.h"
#include "test.h"
#include "pf_sim.h"

extern fixed _X_train[N_TRAIN][N_FEATURE];

void quicksort_idx(uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t indices[MEMORY_SIZE + UPDATE_THR], uint16_t first, uint16_t last);
uint16_t update_mem(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], uint16_t indices[MEMORY_SIZE+UPDATE_THR], uint16_t n_samples);

#endif // !MAIN_H

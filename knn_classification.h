#ifndef KNN_CLASSIFICATION_H

#define KNN_CLASSIFICATION_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "main.h"
#include "dataset.h"
#include "kmeans.h"
#include "pipeline.h"

#define K_NEIGHBOR 5

struct neighbour
{
  uint16_t id;
  fixed score;
};

uint16_t knn_classification(fixed X[], fixed training_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t n_samples);
int struct_cmp_by_score_dec(const void *, const void *);

#endif

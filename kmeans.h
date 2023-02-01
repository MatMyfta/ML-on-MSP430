#ifndef KMEANS_H
#define KMEANS_H

#define K 2
#define ITERATION
#define CONFIDENCE
#define CONFIDENCE_THR F_LIT(0.8)

#include <stdint.h>
#include "fixed.h"
#include "dataset.h"
#include "pipeline.h"


uint16_t kmeans(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], fixed centroids[K][N_FEATURE], fixed weights[MEMORY_SIZE][K], uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t n_samples);
void initial_centroids(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], fixed centroids[K][N_FEATURE], uint16_t n_samples);
uint16_t kmeanspp(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], fixed centroids[K][N_FEATURE], uint16_t n_samples, uint16_t next_centroid);
uint16_t clustering(fixed X[], fixed centroids[K][N_FEATURE], fixed weights[MEMORY_SIZE][K], uint16_t samples_per_cluster[], uint16_t index);
void update_cluster_assignment(fixed max_samples[MEMORY_SIZE+UPDATE_THR], uint16_t index);
void update_centroids(fixed centroids[K][N_FEATURE], uint16_t samples_per_cluster[]);

#endif

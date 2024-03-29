#ifndef PIPELINE_H
#define PIPELINE_H

#define INITIAL_THR 50
#define UPDATE_THR 100
#define MEMORY_SIZE 200

struct Node;

#include <stdio.h>
#include <stdint.h>
#include "kmeans.h"
#include "dataset.h"
#include "test.h"
#include "fixed.h"
#include "dt_training.h"
#include "dt_classification.h"
#include "knn_classification.h"
#include "perceptron.h"
#include "main.h"

uint16_t pipeline(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], struct Node* root, uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t n_samples, uint16_t counter);

#endif

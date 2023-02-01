#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <stdint.h>
#include "fixed.h"
#include "dataset.h"
#include "pipeline.h"

#define EPOCHS 20
#define LEARNING_RATE F_LIT(0.2)

void perceptron_training(fixed X_train[MEMORY_SIZE+UPDATE_THR][N_FEATURE], uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t n);
uint16_t perceptron_classification(fixed X[N_FEATURE]);

#endif // !PERCEPTRON_H

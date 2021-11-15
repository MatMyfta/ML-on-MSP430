#ifndef DATASET_H
#define DATASET_H

#define N_TRAIN 614             // number of training data

#define N_FEATURE 4             // number of features

#define N_CLASSES 2             // number of classes

#include <stdint.h>
#include "fixed.h"

extern uint8_t classes[N_CLASSES];
extern float X_train[N_TRAIN][N_FEATURE];
extern uint8_t labels[N_TRAIN];

#endif

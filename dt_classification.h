#ifndef DECISION_TREE_CLASSIFIER_H

#define DECISION_TREE_CLASSIFIER_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include "main.h"
#include "test.h"
#include "dt_training.h"

uint16_t decision_tree_classifier(struct Node* root, fixed X[]);

#endif

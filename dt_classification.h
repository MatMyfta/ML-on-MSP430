#ifndef DECISION_TREE_CLASSIFIER_H

#define DECISION_TREE_CLASSIFIER_H

#include <stdint.h>
#include "dt_training.h"

uint16_t decision_tree_classifier(struct Node* root, fixed X[]);

#endif

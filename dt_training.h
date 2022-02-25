#ifndef DT_TRAINING
#define DT_TRAINING

<<<<<<< HEAD
#define MAX_DEPTH 3
#define DT_DIM 15		// SUM(i=[0...MAX_DEPTH], 2^i)
=======
#define MAX_DEPTH 7
>>>>>>> changed dataset
#define MIN_SIZE 10

#include <stdint.h>
#include "fixed.h"
#include "dataset.h"
#include "pipeline.h"

struct Node {
	fixed threshold;
    uint16_t feature;
	uint16_t Left_group[MEMORY_SIZE];
	uint16_t Right_group[MEMORY_SIZE];
	uint16_t left_counter;
	uint16_t right_counter;
	uint16_t left_class;
	uint16_t right_class;
	struct Node* left;
	struct Node* right;
};

extern struct Node dt[DT_DIM];

struct Node* decision_tree_training(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], struct Node* root, uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t size);
struct Node* get_split(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], struct Node* root, uint16_t* group, uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t size);
struct Node* split_samples(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], struct Node* root, uint16_t* group, uint16_t feature, fixed threshold, uint16_t size);
fixed gini_index(struct Node* root, uint16_t y_train[MEMORY_SIZE+UPDATE_THR]);
struct Node* split(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], struct Node* node, uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t max_depth, uint16_t min_size, uint16_t depth);
struct Node* GetNewNode();
uint16_t to_terminal(uint16_t *group, uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t size);

#endif

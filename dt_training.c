#include <stdlib.h>
#include <string.h>
#include "dt_training.h"

uint16_t counter = 1;
uint16_t n = 0;

#pragma PERSISTENT(newNode)
struct Node* newNode = NULL;

struct Node* decision_tree_training(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], struct Node* root, uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t size)
{
	get_split(max_samples, root, NULL, y_train, size);
	return root;
}

struct Node* split_samples(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], struct Node* root, uint16_t* group, uint16_t feature, fixed threshold, uint16_t size)
{
    uint16_t left_counter = 0;
    uint16_t right_counter = 0;
    uint16_t sample_index;
    uint16_t j;

	for(j = 0; j < size; j++) {
		/* first split of the samples */
		if(group == NULL)
			sample_index = j;
		/* instead of saving the whole samples (features of a child), we saved the samples indexes and use them */
		else
			sample_index = group[j];
		
		if (max_samples[sample_index][feature] < threshold) {
			root->Left_group[left_counter] = sample_index;
			left_counter++;
		}
		else {
			root->Right_group[right_counter] = sample_index;
			right_counter++;
		}
	}
    root->left_counter = left_counter;
    root->right_counter = right_counter;
	
	if(group != NULL)
		return root;
	return NULL;
}

fixed gini_index(struct Node* root, uint16_t y_train[MEMORY_SIZE+UPDATE_THR])
{
	fixed first_class_counter = 0;
	fixed second_class_counter = 0;
	fixed score, score2;
	fixed gini = 0;
	uint16_t r_lc = root->left_counter;
	uint16_t r_rc = root->right_counter;
	uint16_t sample_index;
	uint16_t j;

	if (r_lc != 0) {
		for (j = 0; j < r_lc; j++) {
			sample_index = root->Left_group[j];
			if (y_train[sample_index] == classes[0])
				first_class_counter+=F_LIT(1);
			else
				second_class_counter+=F_LIT(1);
		}
		//score =  (first_class_counter/r_lc)*(first_class_counter/r_lc) + (second_class_counter/r_lc)*(second_class_counter/r_lc);
		fixed fcc = F_DIV(first_class_counter, F_LIT(r_lc));
		fixed scc = F_DIV(second_class_counter, F_LIT(r_lc));
		score = F_MUL(fcc,fcc) + F_MUL(scc,scc);
		//gini = (1.0 - score) * (r_lc / (r_lc + r_rc));
		gini = F_MUL(F_LIT(1)-score, F_DIV(F_LIT(r_lc), F_LIT(r_lc)+F_LIT(r_rc)));
		first_class_counter = 0;
		second_class_counter = 0;
	}
	if (r_rc != 0) {
		for (j = 0; j < r_rc; j++) {
			sample_index = root->Right_group[j];
			if (y_train[sample_index] == classes[0])
				first_class_counter+=F_LIT(1);
			else
				second_class_counter+=F_LIT(1);
		}
		//score2 =  (first_class_counter / r_rc)*(first_class_counter / r_rc) + (second_class_counter / r_rc)*(second_class_counter / r_rc);
		fixed fcc = F_DIV(first_class_counter, F_LIT(r_rc));
		fixed scc = F_DIV(second_class_counter, F_LIT(r_rc));
		score2 = F_MUL(fcc,fcc) + F_MUL(scc,scc);
		//gini += (1.0 - score2) * (r_rc/(r_lc + r_rc));
		gini += F_MUL(F_LIT(1)-score2, F_DIV(F_LIT(r_rc), F_LIT(r_lc)+F_LIT(r_rc)));
	}
	return gini;
}

struct Node* get_split(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], struct Node* root, uint16_t* group, uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t size)
{
	fixed b_score = F_LIT(999);
	fixed gini, threshold;
	uint16_t left_ctr=0, right_ctr=0;
	uint16_t left_grp[MEMORY_SIZE];
	uint16_t right_grp[MEMORY_SIZE];
	uint16_t sample_index;
	uint16_t i,j;

	for(i = 0; i < N_FEATURE; i++) {
		for(j = 0; j < size; j++) {
			if(group == NULL)
				threshold = max_samples[j][i];
			else {
				sample_index = group[j];
				threshold = max_samples[sample_index][i];
			}
			split_samples(max_samples, root, group, i, threshold, size);
			gini = gini_index(root, y_train);
			if (gini < b_score) {
				root->threshold = threshold;
				root->feature = i;
				left_ctr = root->left_counter;
				right_ctr = root->right_counter;
				memcpy(left_grp, root->Left_group, sizeof(uint16_t)*size);
				memcpy(right_grp, root->Right_group, sizeof(uint16_t)*size);
				b_score = gini;
			}
		}
	}
	root->left_counter = left_ctr;
	root->right_counter = right_ctr;
	memcpy(root->Left_group, left_grp, sizeof(uint16_t)*size);
	memcpy(root->Right_group, right_grp, sizeof(uint16_t)*size);
	if(group == NULL)
		split(max_samples, root, y_train, MAX_DEPTH, MIN_SIZE, 0);
	return root;
}

struct Node* GetNewNode()
{
	newNode = (struct Node*)malloc(sizeof(struct Node*));
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

struct Node* split(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], struct Node* node, uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t max_depth, uint16_t min_size, uint16_t depth)
{	
	uint16_t out;
	if (node->left_counter == 0 || node->right_counter == 0 || depth >= max_depth) {
		out = to_terminal(node->Left_group, y_train, node->left_counter);
		node->left_class = out;
		out = to_terminal(node->Right_group, y_train, node->right_counter);
		node->right_class = out;
		return node;
	}
	if(node->left_counter + node->right_counter <= min_size) {
		out = to_terminal(node->Left_group, y_train, node->left_counter);
		node->right_class = out;
	}
	else {
		node->left = GetNewNode();
		get_split(max_samples, node->left, node->Left_group, y_train, node->left_counter);
		split(max_samples, node->left, y_train, max_depth, min_size, depth+1);
	}
	if(node->right_counter + node->left_counter <= min_size) {
		out = to_terminal(node->Right_group, y_train, node->right_counter);
		node->right_class = out;
	}
	else {
		node->right = GetNewNode();
		get_split(max_samples, node->right, node->Right_group, y_train, node->right_counter);
		split(max_samples, node->right, y_train, max_depth, min_size, depth+1);
	}
	return node;
}

uint16_t to_terminal(uint16_t *group, uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t size)
{
	uint16_t first_class = 0;
	uint16_t second_class = 0;
	uint16_t sample_index, out;
    uint16_t i;

	for (i = 0; i < size; i++)
	{
		sample_index = group[i];
		if (y_train[sample_index] == classes[0])
			first_class++;
		else
			second_class++;
	}
	if(first_class > second_class)
		out = classes[0];
	else
		out = classes[1];
	return out;
}


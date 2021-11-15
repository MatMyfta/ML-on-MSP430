#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "main.h"
#include "dataset.h"
#include "dt_training.h"

uint16_t decision_tree_classifier(struct Node* root, fixed X[])
{
    if(X[root->feature] < root->threshold) {
		if(root->left != NULL) {
			decision_tree_classifier(root->left, X);
		}
		else {
			return root->left_class;
		}
	}
	if(root->right != NULL) {
		decision_tree_classifier(root->right, X);
	}
	return root->right_class;
}

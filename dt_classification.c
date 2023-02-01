#include "dt_classification.h"

uint16_t decision_tree_classifier(struct Node* root, fixed X[])
{
    if(X[root->feature] < root->threshold) {
		if(root->left != NULL) {
			return decision_tree_classifier(root->left, X);
		}
		else {
			return root->left_class;
		}
	}
    else {
		if(root->right != NULL) {
			return decision_tree_classifier(root->right, X);
		}
		else {
			return root->right_class;
		}
	}
    // no return statement, because it can cause a logical error in the algorithm
}

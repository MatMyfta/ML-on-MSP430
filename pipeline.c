#include "pipeline.h"

uint16_t pred_class;

uint16_t pipeline(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], struct Node* root, uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t n_samples, uint16_t counter)
{
    uint16_t i,j;

    for(i = 0; i < UPDATE_THR; i++) {
        #ifdef AUTO_DT
        pred_class = decision_tree_classifier(root, X_train[i + counter - UPDATE_THR]);
        #endif

        #ifdef AUTO_KNN
        pred_class = knn_classification(X_train[i + counter - UPDATE_THR], max_samples, y_train, n_samples);
        #endif
    }

    for(i = 0; i < UPDATE_THR; i++) {
        for(j = 0; j < N_FEATURE; j++)
            max_samples[n_samples + i][j] = X_train[i + counter - UPDATE_THR][j];
    }
    n_samples += UPDATE_THR;
    return n_samples;
}

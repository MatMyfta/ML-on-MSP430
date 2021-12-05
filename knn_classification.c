#include <stdio.h>
#include <stdlib.h>			//qsort()
#include <string.h>         //memset()
#include <math.h>           //sqrt()
#include "KNN_classification.h"
#include "kmeans.h"

uint16_t knn_classification(fixed X[], fixed training_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t n_samples)
{
    struct neighbour neighbours[MEMORY_SIZE];

    uint16_t j;
    for(j = 0; j < n_samples; j++) {
        neighbours[j].id = j;
        float acc=0;
        uint16_t skip=0;
        uint16_t k;

        for(k=0; k < N_FEATURE; k++) {
            acc += (X[k]-training_samples[j][k]) * (X[k]-training_samples[j][k]);
            if (acc > 10000000) {
                neighbours[j].score = 0;
                skip=1;
                break;
            }
        }
        if (skip == 0) {
            acc = sqrt(acc);
            if (acc < 0.0000001)
                neighbours[j].score = 10000000;
            else {
                neighbours[j].score = 1/acc;
            }
        }
    }

    qsort(neighbours, n_samples, sizeof(struct neighbour), struct_cmp_by_score_dec);

    uint16_t n;
    float scores[K];
    memset(scores, 0, K*sizeof(float));

    for(n = 0; n < K_NEIGHBOR; n++)
        scores[y_train[neighbours[n].id]] += neighbours[n].score;

    float bestScore = F_LIT(0);
    uint16_t bestClass;

    for(n = 0; n < K; n++) {
        if (scores[n] > bestScore) {
            bestScore = scores[n];
            bestClass = n;
        }
    }

    return bestClass;
}

int struct_cmp_by_score_dec(const void *a, const void *b)
{
    struct neighbour *ia = (struct neighbour *)a;
    struct neighbour *ib = (struct neighbour *)b;
    return -(int)(100000.f*ia->score - 100000.f*ib->score);
}

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
        fixed acc=0;
        uint16_t skip=0;
        uint16_t k;

        for(k=0; k < N_FEATURE; k++) {
        	fixed tmp = (X[k]-training_samples[j][k]);
            acc += (tmp < 0 ? -tmp : tmp);
            if (acc > F_LIT(1000)) {
                neighbours[j].score = 0;
                skip=1;
                break;
            }
        }
        if (skip == 0) {
        	fixed temp = F_LIT(0.001);
            if (acc < temp) {
                neighbours[j].score = F_LIT(1000);
            }
            else {
            	temp = F_DIV(F_LIT(1.0), acc);
                neighbours[j].score = temp;
            }
        }
    }

    qsort(neighbours, n_samples, sizeof(struct neighbour), struct_cmp_by_score_dec);

    {
        uint16_t n;
        fixed scores[K];
        memset(scores, 0, K*sizeof(fixed));

        for(n = 0; n < K_NEIGHBOR; n++)
            scores[y_train[neighbours[n].id]] += neighbours[n].score;

        fixed bestScore = F_LIT(0);
        uint16_t bestClass;

        for(n = 0; n < K; n++) {
            if (scores[n] > bestScore) {
                bestScore = scores[n];
                bestClass = n;
            }
        }

        return bestClass;
    }
}

int struct_cmp_by_score_dec(const void *a, const void *b)
{
    struct neighbour *ia = (struct neighbour *)a;
    struct neighbour *ib = (struct neighbour *)b;
    return -(ia->score - ib->score);
}

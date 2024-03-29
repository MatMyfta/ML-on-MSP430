#include <stdio.h>              // printf
#include <string.h>             // memcmp, memset
#include <math.h>
#include "kmeans.h"
#include "main.h"

#ifndef DEBUG
#include "pf_sim.h"
#else
#include <time.h>               // time
#include <stdlib.h>             // srand, rand
#endif


// Cannot be in fixed type because it causes an overflow in update_cluster_assignment().
// So I prefer to use the float type.
float cluster_assignment[K][N_FEATURE];
fixed prev_centroids[K][N_FEATURE];

uint16_t kmeans(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], fixed centroids[K][N_FEATURE], fixed weights[MEMORY_SIZE][K],  uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t n_samples)
{
    uint16_t cluster;
    uint16_t iteration = 0;
    uint16_t stop = 0;
    uint16_t counter = 0;

    uint16_t i, j, k;


	#ifdef PRINT
	printf("\n> kmeans:\n");
	#endif

    initial_centroids(max_samples, centroids, n_samples);

    // run until no further change in the results
    while (iteration < 50 && stop < 2) {
        uint16_t samples_per_cluster[K] = {0,0};

        // clustering
        for (j = 0; j < n_samples; j++) {
            cluster = clustering(max_samples[j], centroids, weights, samples_per_cluster, j);
            y_train[j] = cluster;
            update_cluster_assignment(max_samples[j], cluster);
        }

        // save centroids to prev_centroids
        for (i = 0; i < K; i++) {
            for (k = 0; k < N_FEATURE; k++) {
                prev_centroids[i][k] = centroids[i][k];
            }
        }
        update_centroids(centroids, samples_per_cluster);

        // stop the algorithm when centroids stop changing
        uint16_t is_equal = memcmp(centroids, prev_centroids, sizeof(prev_centroids));
        if (is_equal == 0) {
            stop++;
        } 
        iteration++;

        // reset cluster assignment
        memset(cluster_assignment, 0, sizeof(cluster_assignment));
    }

	#ifdef PRINT
    printf("\t- Final centroids:\n");
	printf("\t+------------+------------+------------+------------+\n");
    for(i = 0; i < K; i++) {
        printf("\t|");
        for (j = 0; j < N_FEATURE; j++) {
            printf("%12.2f|", F_TO_FLOAT(centroids[i][j]));
        }
        printf("\n");
    }
	printf("\t+------------+------------+------------+------------+\n");
	#endif


    #ifdef CONFIDENCE
	float weight = 0;
	double tmp;
    /* weight calculation */
    for(i = 0; i < n_samples; i++) {
        weight = 0;
        for(j = 0; j < K; j++) {
			// weight = (1 / weights[1][j])^2
            tmp = (double) F_TO_FLOAT(weights[i][j]);
            tmp *= tmp;
            weight += (float) (1.0/(tmp));
        }
        uint16_t k;
        for(k = 0; k < K; k++) {
            // weights[i][k] = 1 / (weight * weights[i][k]^2)
			tmp = (double) F_TO_FLOAT(weights[i][k]);
			tmp = (double) (1.0 / (weight * tmp * tmp));
            weights[i][k] = F_LIT((float) tmp);
		}
    }
    uint16_t n, l;
    for(n = 0; n < n_samples; n++) {
        if(weights[n][y_train[n]] > CONFIDENCE_THR) {
            for(l = 0; l < N_FEATURE; l++)
                max_samples[n-counter][l] = max_samples[n][l];
            y_train[n-counter] = y_train[n];
        }
		else
			counter++;
    }
    #endif

    n_samples = n_samples - counter;
	#ifdef PRINT
    printf("\t- Removed %d samples, total: %d\n\n", counter, n_samples);
	#endif

    return n_samples;
}

// choose the first centroid
void initial_centroids(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], fixed centroids[K][N_FEATURE], uint16_t n_samples)
{
    uint16_t random;

    #ifdef DEBUG
    time_t t;
    srand((unsigned) time(&t));
    random = rand() % n_samples;
    #else
	random = random_number() % n_samples;
    #endif

    uint16_t i,j;
    for (i = 0; i < K; i++) {
        for (j = 0; j < N_FEATURE; j++) {
            centroids[i][j] = max_samples[random][j];
        }
        // use kmeans++ to choose the other centroids
        if (i+1 != K) {
            random = kmeanspp(max_samples, centroids, n_samples,i+1);
        }
    }
}

uint16_t kmeanspp(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], fixed centroids[K][N_FEATURE], uint16_t n_samples, uint16_t next_centroid)
{
    float max = -1000;
    uint16_t random, dist;
    uint16_t i,k,j;
    for (i = 0; i < n_samples; i++) {
        for (k = 0; k < next_centroid; k++) {
            for (j = 0; j < N_FEATURE; j++) {
                fixed tmp = max_samples[i][j]-centroids[k][j];
                dist += F_TO_FLOAT(tmp) * F_TO_FLOAT(tmp);
            }
            if (dist > max) {
                max = dist;
                random = i;
            }
            dist = 0;
        }
    }
    return random;
}

uint16_t clustering(fixed X[], fixed centroids[K][N_FEATURE], fixed weights[MEMORY_SIZE][K], uint16_t samples_per_cluster[], uint16_t index)
{
    float y = 0, min_distance = 1000000;
    uint16_t cluster = 0;

    uint16_t k,j;
    for (k = 0; k < K; k++) {
        for (j = 0; j < N_FEATURE; j++) {
            float tmp = F_TO_FLOAT(X[j]-centroids[k][j]);
            y += tmp*tmp;
        }

        y = (y == 0 ? 0 : sqrt(y));
        weights[index][k] = F_LIT(y);				// weight is the distance between index and centroid

        if (y < min_distance) {
            min_distance = y;
            cluster = k;
        }
        y = 0;
    }
    samples_per_cluster[cluster] += 1;
    return cluster;
}

void update_cluster_assignment(fixed max_samples[MEMORY_SIZE+UPDATE_THR], uint16_t index)
{
    uint16_t i;
    for (i = 0; i < N_FEATURE; i++) {
        cluster_assignment[index][i] += F_TO_FLOAT(max_samples[i]);
    }
}

void update_centroids(fixed centroids[K][N_FEATURE], uint16_t samples_per_cluster[])
{
    uint16_t j;
    for (j = 0; j < N_FEATURE; j++) {
        if (samples_per_cluster[0] != 0) {
            centroids[0][j] = F_LIT(cluster_assignment[0][j] / samples_per_cluster[0] );
        }
        if (samples_per_cluster[1] != 0) {
            centroids[1][j] = F_LIT( cluster_assignment[1][j] / samples_per_cluster[1] );
        }
    }
}

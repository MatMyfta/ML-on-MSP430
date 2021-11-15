#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"

fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE];
uint16_t y_train[MEMORY_SIZE+UPDATE_THR];
fixed centroids[K][N_FEATURE];
fixed weights[MEMORY_SIZE+UPDATE_THR][K];

/**
 * main.c
 */
int main(void)
{


	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;


    #ifdef PRINT
    fprintf(stdout, "AEP initialization\n\n"); fflush(stdout);
    #endif

	uint16_t n_samples;
    uint16_t pred_class, pred_class_perm;
    float acc = 0;
    float acc_perm = 0;
	uint16_t counter = 0;
	uint16_t increment = 0;
	uint16_t i, j;

	n_samples = INITIAL_THR; 		// MAX MEMORY ALLOCATION

	// READ INITIAL DATA
	for (i = 0; i < n_samples; i++) {
		for (j = 0; j < N_FEATURE; j++) {
			max_samples[i][j] = F_LIT(X_train[i][j]);
		}
	}

    // Read test data
    fixed _X_test[N_TEST][N_FEATURE];
    for (i = 0; i < N_TEST; i++) {
        for (j = 0; j < N_FEATURE; j++) {
            _X_test[i][j] = F_LIT(X_test[i][j]);
        }
    }

    #ifdef PRINT
    #ifdef AUTO_DT
    printf(ANSI_COLOR_GREEN"* Decision Tree classifier: \n\n");
    printf("\t- Max Depth: %d\n", MAX_DEPTH);
    printf("\t- Min Size: %d\n\n" ANSI_COLOR_RESET, MIN_SIZE);
    #endif

    #ifdef AUTO_KNN
    printf(ANSI_COLOR_GREEN "* KNN classifier:\n\n");
    printf("\t- Number of neighbors: %d\n\n" ANSI_COLOR_RESET, K_NEIGHBOR);
    #endif
    #endif

	counter = n_samples;

	while (1) {

		n_samples = kmeans(max_samples, centroids, weights, y_train, n_samples);

		if (n_samples > MEMORY_SIZE) {

            uint16_t indices[MEMORY_SIZE + UPDATE_THR];

            for(i=0; i<n_samples; i++)
                indices[i]=i;

            quicksort_idx(y_train, indices, 0, n_samples-1);
            n_samples = update_mem(max_samples, indices, n_samples);

			// FIFO
			for(i = 0; i < MEMORY_SIZE; i++) {
				for(j = 0; j < N_FEATURE; j++)
					max_samples[i][j] = max_samples[i+(n_samples - MEMORY_SIZE)][j];
				y_train[i] = y_train[i+(n_samples - MEMORY_SIZE)];
			}
			n_samples = MEMORY_SIZE;
		}

		struct Node* root = (struct Node*)realloc(NULL, sizeof(struct Node));
        #ifdef AUTO_DT
		root = decision_tree_training(max_samples, root, y_train, n_samples);
        #endif


        // Compute classification
		for (j = 0; j < N_TEST; j++) {

            #ifdef AUTO_DT
			pred_class = decision_tree_classifier(root, _X_test[j]);
            #endif

            #ifdef AUTO_KNN
            pred_class = knn_classification(_X_test[j], max_samples, y_train, n_samples);
            #endif

			pred_class_perm = 1 - pred_class;

			if(pred_class == y_test[j])
				acc++;
			else if(pred_class_perm == y_test[j])
				acc_perm++;
		}

		if (acc_perm > acc)
			acc = acc_perm;

        #ifdef PRINT
        #ifdef AUTO_DT
        printf ("^ Decision Tree:\n\n");
        printf (ANSI_COLOR_GREEN"\t- Number of samples correctly classified using the Decision Tree: %0.0f\n"ANSI_COLOR_RESET, acc);
        #endif

        #ifdef AUTO_KNN
        printf("^ KNN: \n\n");
        printf (ANSI_COLOR_GREEN"\t- Number of samples correctly classified using the KNN classifier: %0.0f\n"ANSI_COLOR_RESET, acc);
        #endif
        #endif

		acc = (acc / N_TEST) * 100.0;
        #ifdef PRINT
        printf(ANSI_COLOR_YELLOW"\t- Accuracy: %0.2f%s\n\n" ANSI_COLOR_RESET, acc, "%");
        #endif

        counter += UPDATE_THR;
		acc = 0;
		acc_perm = 0;

		if(counter > N_TRAIN)
			break;
		else
			n_samples = pipeline(max_samples, root, y_train, n_samples, counter);

		if(counter - INITIAL_THR == MEMORY_SIZE)
			increment = INITIAL_THR;
		else if(counter > MEMORY_SIZE)
			increment += UPDATE_THR;

	}

	return 0;
}

void quicksort_idx(uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t indices[MEMORY_SIZE + UPDATE_THR], uint16_t first, uint16_t last){
   uint16_t i, j, pivot, temp;

   if(first>=MEMORY_SIZE){
       return;
   }// Avoid useless computation, as the other samples will be cut

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(weights[indices[i]][y_train[indices[i]]]>=weights[indices[pivot]][y_train[indices[pivot]]]&&i<last)
            i++;
         while(weights[indices[j]][y_train[indices[j]]]<weights[indices[pivot]][y_train[indices[pivot]]])
            j--;
         if(i<j){
            temp=indices[i];
            indices[i]=indices[j];
            indices[j]=temp;
         }
      }

        temp=indices[pivot];
        indices[pivot]=indices[j];
        indices[j]=temp;

      quicksort_idx(y_train, indices,first,j-1);
      quicksort_idx(y_train, indices,j+1,last);

   }
}

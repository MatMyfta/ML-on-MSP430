#ifndef DEBUG
#include "pf_sim.h"
#include <msp430.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "main.h"
#include "kmeans.h"
#include "knn_classification.h"
#include "perceptron.h"
#include "test.h"
#include "inferenceset.h"

#define ACCURACIES 40

fixed centroids[K][N_FEATURE];
#ifndef DEBUG
#pragma PERSISTENT(weights)
#pragma PERSISTENT(y_train)
#pragma PERSISTENT(max_samples)
#ifdef AUTO_DT
#pragma PERSISTENT(tree_node)
#endif
#endif
fixed weights[MEMORY_SIZE+UPDATE_THR][K] = {{0}};
uint16_t y_train[MEMORY_SIZE+UPDATE_THR] = {{0}};
fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE] = {{0}};
#ifdef AUTO_DT
struct Node tree_node[MAX_NODES] = {0};
#endif

void set_freq(int f){
    CSCTL0_H = CSKEY_H; //Unlock clock configuration register
    //1 MHz by default
    if (f == 4) {
        CSCTL1 = DCOFSEL_3; //Clock frequency is set to 4 MHz (DCOFWEL = 3h, (R/W) = If DCORSEL = 0: 4 MHz; If DCORSEL = 1: 8 MHz)
        CSCTL3 = DIVM_0 | DIVS_0 | DIVA_0; //Clock prescaler is set to /1
    } else if (f == 8) {
        CSCTL1 = DCORSEL | DCOFSEL_3; //Clock frequency is set to 8 MHz (DCOFWEL = 3h, (R/W) = If DCORSEL = 0: 4 MHz; If DCORSEL = 1: 8 MHz)
        CSCTL3 = DIVM_0 | DIVS_0 | DIVA_0; //Clock prescaler is set to /1
    } else if (f == 16) {
        FRCTL0 = 0xA500 | ((1) << 4); // FRCTLPW | NWAITS_1;    // Disable FRAM wait cycles to allow clock operation over 8MHz
        __delay_cycles(3);
        FRCTL0_H |= (FWPW) >> 8; // init FRAM
        __delay_cycles(3);
        CSCTL1 = DCORSEL | DCOFSEL_4; //Clock frequency is set to 16 MHz (DCOFWEL = 4h, (R/W) = If DCORSEL = 0: 5.33 MHz; If DCORSEL = 1: 16 MHz)
        CSCTL3 = DIVM_0 | DIVS_0 | DIVA_0; //Clock prescaler is set to /1
    }
    CSCTL0_H = 0; //Lock clock configuration register
}

/**
 * main.c
 */
int main(void)
{

	#ifndef DEBUG
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

	// Change frequency
	// Default frequency is 1MHz
//    set_freq(4);             // 4MHz
    set_freq(8);             // 8MHz
//    set_freq(16);            // 16MHz

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // RTC
    RTC_start();
	#endif // !DEBUG


    #ifdef PRINT
    printf("AEP initialization\n\n");
    #endif // PRINT

	uint16_t n_samples;
    uint16_t pred_class, pred_class_perm;
    fixed acc = F_LIT(0);
    fixed acc_perm = F_LIT(0);
	uint16_t counter = 0;
	uint16_t increment = 0;
	uint16_t i, j;
    struct Node *root;

    uint16_t index = 0;
    fixed accs[ACCURACIES] = {0};

	n_samples = INITIAL_THR; 		// MAX MEMORY ALLOCATION

	// READ INITIAL DATA
	for (i = 0; i < n_samples; i++) {
		for (j = 0; j < N_FEATURE; j++) {
			max_samples[i][j] = X_train[i][j];
		}
	}

    #ifdef PRINT
    #ifdef AUTO_DT
    printf("* Decision Tree classifier: \n\n");
    printf("\t- Max Depth: %d\n", MAX_DEPTH);
    printf("\t- Min Size: %d\n\n", MIN_SIZE);
    #endif // AUTO_DT

    #ifdef AUTO_KNN
    printf("* KNN classifier:\n\n");
    printf("\t- Number of neighbors: %d\n\n", K_NEIGHBOR);
    #endif // AUTO_KNN
    #endif // PRINT

	counter = n_samples;

	while (1) {

		n_samples = kmeans(max_samples, centroids, weights, y_train, n_samples);

		if (n_samples > MEMORY_SIZE) {
			#ifdef CONF
            uint16_t indices[MEMORY_SIZE + UPDATE_THR];

            for(i=0; i<n_samples; i++)
                indices[i]=i;

            quicksort_idx(y_train, indices, 0, n_samples-1);
            n_samples = update_mem(max_samples, indices, n_samples);
            #endif // CONF

			#ifdef FIFO
			for(i = 0; i < MEMORY_SIZE; i++) {
				for(j = 0; j < N_FEATURE; j++)
					max_samples[i][j] = max_samples[i+(n_samples - MEMORY_SIZE)][j];
				y_train[i] = y_train[i+(n_samples - MEMORY_SIZE)];
			}
			n_samples = MEMORY_SIZE;
			#endif // FIFO
		}

        #ifdef AUTO_DT
        for (i=0; i<MAX_NODES; i++) {
            tree_node[i].threshold = 0;
            tree_node[i].feature = 0;
            tree_node[i].left_counter = 0;
            tree_node[i].right_counter = 0;
            tree_node[i].left_class = 0;
            tree_node[i].right_class = 0;
            tree_node[i].left = NULL;
            tree_node[i].right = NULL;
            tree_node[i].taken = 0;
        }

		root = &tree_node[0];
        root->taken = 1;
		root = decision_tree_training(max_samples, root, y_train, n_samples);
        #endif // AUTO_DT

        #ifdef AUTO_PRC
        perceptron_training(max_samples, y_train, n_samples);
        #endif  

        if (false) break;

        // Compute classification
		for (j = 0; j < N_TEST; j++) {

            #ifdef AUTO_DT
			pred_class = decision_tree_classifier(root, X_test[j]);
            #endif // AUTO_DT

            #ifdef AUTO_KNN
            pred_class = knn_classification(X_test[j], max_samples, y_train, n_samples);
            #endif // AUTO_KNN
            
            #ifdef AUTO_PRC
            pred_class = perceptron_classification(X_test[j]);
            #endif // AUTO_PRC

			pred_class_perm = 1 - pred_class;

			if(pred_class == y_test[j])
				acc += F_LIT(1);
			else if(pred_class_perm == y_test[j])
				acc_perm += F_LIT(1);
		}

		if (acc_perm > acc)
			acc = acc_perm;

        #ifdef PRINT
        #ifdef AUTO_DT
        printf ("^ Decision Tree:\n\n");
        printf ("\t- Number of samples correctly classified using the Decision Tree: %0.0f\n", acc);
        #endif //AUTO_DT

        #ifdef AUTO_KNN
        printf("^ KNN: \n\n");
        printf ("\t- Number of samples correctly classified using the KNN classifier: %0.0f\n", acc);
        #endif //AUTO_KNN
        #endif //PRINT

        // acc = acc / 4928 * 100
		// acc = F_LIT((float) (F_TO_FLOAT(acc)/N_TEST * 100.0));

        #ifdef PRINT
        printf("\t- Accuracy: %0.2f%s\n\n", F_TO_FLOAT(acc)/N_TEST * 100.0, "%");
        #endif


        // printf("acc : %d\n", acc);

        accs[index] = acc;
        index++;

        counter += UPDATE_THR;
		acc = F_LIT(0);
		acc_perm = F_LIT(0);

		if(counter > N_TRAIN)
			break;

 		n_samples = pipeline(max_samples, root, y_train, n_samples, counter);

		if(counter - INITIAL_THR == MEMORY_SIZE)
			increment = INITIAL_THR;
		else if(counter > MEMORY_SIZE)
			increment += UPDATE_THR;

	}

	if (0 == 0) index = ACCURACIES;

//	for (i = 0; i < ACCURACIES; i++) {
//        printf("%d;\n", accs[i]);
//	}

	uint8_t inference[N_TEST];

	for(i = 0; i < N_TEST; i++) {

        #ifdef AUTO_DT
        inference[i] = decision_tree_classifier(root, X_test[i]);
        #endif // AUTO_DT

        #ifdef AUTO_KNN
        inference[i] = knn_classification(X_test[i], max_samples, y_train, n_samples);
        #endif // AUTO_KNN

        #ifdef AUTO_PRC
        inference[i] = perceptron_classification(X_test[i]);
        #endif // AUTO_PRC
	}

	for (i = 0; i < N_TEST; i++) {
        printf("%d\n", inference[i]);
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

uint16_t update_mem(fixed max_samples[MEMORY_SIZE+UPDATE_THR][N_FEATURE], uint16_t indices[MEMORY_SIZE+UPDATE_THR], uint16_t n_samples){
    uint16_t n_samples_updated = n_samples;
	uint16_t i,j,k;
    if (n_samples > MEMORY_SIZE)
        n_samples_updated = MEMORY_SIZE;
    uint16_t n_rows_erased=0;
    uint16_t n_indices_found=0;

	for(i=0; i<n_samples; i++){
        uint16_t row_to_keep = 0;
        for(j=0; j<n_samples_updated-n_indices_found; j++){
            if (i==indices[j]){
                row_to_keep=1;
                for(k=j; k<n_samples_updated-n_indices_found-1; k++){
                    indices[k]=indices[k+1];
                }
                n_indices_found++;
                break;
            }
        }
        if (!row_to_keep){
            for(j=i-n_rows_erased; j<n_samples-1-n_rows_erased; j++){
                for(k=0; k<N_FEATURE; k++){
                    max_samples[j][k]=max_samples[j+1][k];
                    y_train[j] = y_train[j+1];
                }
            }
            n_rows_erased++;
        }
    }
    n_samples = n_samples_updated;
    return n_samples;
}

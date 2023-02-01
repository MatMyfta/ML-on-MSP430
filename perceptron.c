#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "perceptron.h"

fixed weight[N_FEATURE];
fixed bias = F_LIT(-1);

fixed weight_generator() {
    return F_SIN(rand() % 32 + 1);
}

uint16_t activation(fixed result) {
    return (result <= 0 ? 0 : F_LIT(1));
}

fixed right_propagation(fixed X[N_FEATURE], fixed weight[N_FEATURE]) {
    fixed result = 0;
    uint16_t i;

    // result = w[0]*x[0] + w[1]*x[1] + ... + w[n]*x[n] + bias
    for (i=0; i<N_FEATURE; i++) {
        result += F_MUL(weight[i], X[i]);
    }
    //result += bias;

    return activation(result);
}

void perceptron_training(fixed X_train[MEMORY_SIZE+UPDATE_THR][N_FEATURE], uint16_t y_train[MEMORY_SIZE+UPDATE_THR], uint16_t n) {
    fixed output;
    uint16_t epoch,i,j;
    
    // initialize the weights
    for (i=0; i<N_FEATURE; i++) {
        weight[i] = weight_generator();
    }

    #if defined(DEBUG) && defined(PRINT_WEIGHTS)
    printf("\t> Perceptron weights:\n\t+-----------+----------+----------+----------+----------+\n");
    #endif // DEBUG

    for (epoch=0; epoch<EPOCHS; epoch++) {
        for (i=0; i<n; i++) {

            output = right_propagation(X_train[i],weight);
            fixed error = F_LIT(y_train[i]) - output;

            if (output != F_LIT(y_train[i])) {
                for (j=0; j<N_FEATURE; j++) {
                    weight[j] += F_MUL(LEARNING_RATE, F_MUL(error, X_train[i][j]));
                }
                bias += F_MUL(LEARNING_RATE, error);
            }
        }

        #if defined(DEBUG) && defined(PRINT_WEIGHTS)
        printf("\t| epoch %3d ", epoch);
        for (i=0; i<N_FEATURE; i++) {
            printf("| %8.2f ", F_TO_FLOAT(weight[i]));
        }
        printf("|\n");
        #endif // DEBUG
    }
    #if defined(DEBUG) && defined(PRINT_WEIGHTS)
    printf("\t+-----------+----------+----------+----------+----------+\n");
    #endif // DEBUG
}

uint16_t perceptron_classification(fixed X[N_FEATURE]) {
    uint16_t res = (uint16_t) F_TO_FLOAT(right_propagation(X,weight));
    return res;
}

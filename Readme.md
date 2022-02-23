# Machine Learning on MSP430

Sample project of a Machine Learning algorithm running on MSP430FR5994 launchpad.

## Algorithm

The algorithm is an adaptation of the AEP algorithm for the MSP430 FR5994 controller, in particular the changes involve the memory usage of the algorithm. For instance, the `int` type is changed with the `uint16_t` type implemented in the `stdint.h` library; another important type modification is the float, that is the main memory harvesting type because of the implementation of the dataset, and it is changed with the `fixed` type implemented in the `fixed.h` library (from libfixed).

Other changes come with the algorithm implementation, because of the bit dimension of the new types, it is possible (and it is very frequent) the overflow of a value. For example, in the `knn_classification.c` inference algorithm, given the centroid $c$ with features $c_i$, and the example $e$ with features $e_i$, the euclidean distance between the points is calculated with the formula:
$$
d(c,e) =\sum_{i=1}^n |c_i-e_i|
$$
In this way it is no more used the square of the difference, and the values that are distant from the centroids do not overflow.

### Dataset

The dataset is the original dataset presented in the AEP algorithm.

## Usage

The main usage difference against the original AEP algorithm is the possibility of using the `DEBUG` label in order to print some information in the console, in this way it is possible to debug the code during the execution.

## References

- [AEP](https://github.com/Edge-Learning-Machine/AEP) - The original AEP algorithm.
- [libfixed](https://github.com/CMUAbstract/libfixed/tree/b6a5caf12468fd4d573f17f1984706e1b9f5bcc0) - The libfixed library.

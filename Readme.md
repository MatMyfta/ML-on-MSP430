# Machine Learning on MSP430

Sample project of a Machine Learning algorithm running on MSP430FR5994 launchpad.

## Dataset

The dataset is composed of:

| Class | number of Training Set samples | number of Test Set samples |
|-------|----------------------|------------------|
| sit5 | 777 | 197 |
| wlk7 | 197 | 110 |

## Results

The following results are 

| Iteration number | kNN Accuracy % |
|------------------|------------|
| 1 | 83.12% |
| 2 | 86.06% |
| 3 | 87.66% |
| 4 | 86.36% |
| 5 | 83.12% |
| 6 | 80.52% |
| 7 | 81.17% |
| 8 | 76.95% |
| 9 | 76.95% |
| 10 | 74.68% |
| 11 | 61.69% |


## References

- [AEP](https://github.com/Edge-Learning-Machine/AEP) - The original AEP algorithm.
- [libfixed](https://github.com/CMUAbstract/libfixed/tree/b6a5caf12468fd4d573f17f1984706e1b9f5bcc0) - The libfixed library.

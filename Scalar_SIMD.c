//Muhammad Hasnain Akhtar CS-6A 22i-1241
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h> // AVX intrinsics (x86)

#define N 512  // Large matrix

void scalar_2Dimplementation(float *A, float *B, float *C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i * N + j] = A[j * N + i] * B[i * N + j];
        }
    }
}

void scalar_1Dimplementation(float *A, float *B, float *C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i * N + j] = A[j * N + i] * B[i * N + j];
        }
    }
}

void simd_implementation(float *A, float *B, float *C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j += 8) { // Process 8 elements at a time
            __m256 a_vec = _mm256_loadu_ps(&A[j * N + i]); // Load 8 floats
            __m256 b_vec = _mm256_loadu_ps(&B[i * N + j]); // Load 8 floats
            __m256 c_vec = _mm256_mul_ps(a_vec, b_vec); // Multiply
            _mm256_storeu_ps(&C[i * N + j], c_vec); // Store result
        }
    }
}

int main() {
    // Allocate memory dynamically
    float *A = (float *)malloc(N * N * sizeof(float));
    float *B = (float *)malloc(N * N * sizeof(float));
    float *C = (float *)malloc(N * N * sizeof(float));

    if (!A || !B || !C) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < N * N; i++) {
        A[i] = (float)rand() / RAND_MAX;
        B[i] = (float)rand() / RAND_MAX;
    }

    clock_t start, end;
    start = clock();
    scalar_2Dimplementation(A, B, C);
    end = clock();
    printf("Scalar 2D time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    scalar_1Dimplementation(A, B, C);
    end = clock();
    printf("Scalar 1D time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    simd_implementation(A, B, C);
    end = clock();
    printf("SIMD time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(A);
    free(B);
    free(C);

    return 0;
}


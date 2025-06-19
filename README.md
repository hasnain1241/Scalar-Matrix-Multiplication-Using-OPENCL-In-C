
# Scalar vs SIMD Matrix Multiplication



This C program compares the performance of **scalar** and **SIMD** (Single Instruction, Multiple Data) implementations of a matrix computation. It performs element-wise operations on two large `512x512` matrices and records the time taken by each approach:

* Scalar 2D loop implementation
* Scalar 1D loop implementation (same logic, different access pattern)
* SIMD implementation using AVX intrinsics

## ⚙️ Implementation Details

### Matrix Operation:

For each element `(i, j)` in result matrix `C`, the computation performed is:

```
C[i][j] = A[j][i] * B[i][j]
```

This computation is done in three different ways to analyze performance differences due to memory access patterns and vectorization.

### SIMD:

Utilizes AVX intrinsics:

* `_mm256_loadu_ps()` — loads 8 `float`s into a 256-bit vector.
* `_mm256_mul_ps()` — performs element-wise multiplication.
* `_mm256_storeu_ps()` — stores result back into memory.

##  Benchmarking

The execution time for each method is measured using `clock()` from `<time.h>`, and results are printed in seconds.

Example output:

```
Scalar 2D time: 0.503000 seconds
Scalar 1D time: 0.502000 seconds
SIMD time: 0.097000 seconds
```

##  Learnings

* **Scalar vs SIMD**: SIMD significantly reduces execution time due to parallel processing.
* **Memory Access Patterns**: The scalar 1D and 2D implementations are logically the same, but careful indexing can impact cache performance.

##  How to Compile

Ensure you are using a compiler that supports AVX intrinsics (e.g., GCC on x86\_64 architecture).

```bash
gcc -O2 -mavx -o simd_test i221241_Q1_Scalar_SIMD.c
```

## ▶ How to Run

```bash
./simd_test
```

##  Memory Management

All matrices are dynamically allocated and freed at the end of execution to prevent memory leaks.

##  Dependencies

* Standard C libraries: `stdio.h`, `stdlib.h`, `time.h`
* AVX intrinsics: `immintrin.h`

---


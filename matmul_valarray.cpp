#include <valarray>
#include <iostream>
#include <omp.h>
#include <chrono>
#include <algorithm>

constexpr int BLOCK_SIZE = 32;

void matmul(const std::valarray<double>& A, const std::valarray<double>& B, std::valarray<double>& C, int M, int K, int N) {
    // Peeling over the rows and columns at the edges
    #pragma omp parallel for
    for (int i = 0; i < std::min(BLOCK_SIZE, M); ++i) {
        for (int j = 0; j < std::min(BLOCK_SIZE, N); ++j) {
            for (int k = 0; k < K; ++k) {
                C[i * N + j] += A[i * K + k] * B[k * N + j];
            }
        }
    }

    // Process the main matrix in blocks of size BLOCK_SIZE x BLOCK_SIZE
    #pragma omp parallel for collapse(2) schedule(static)
    for (int i = BLOCK_SIZE; i < M; i += BLOCK_SIZE) {
        for (int j = BLOCK_SIZE; j < N; j += BLOCK_SIZE) {
            for (int k = BLOCK_SIZE; k < K; k += BLOCK_SIZE) {
                for (int ii = i; ii < std::min(i + BLOCK_SIZE, M); ++ii) {
                    for (int jj = j; jj < std::min(j + BLOCK_SIZE, N); ++jj) {
                        for (int kk = k; kk < std::min(k + BLOCK_SIZE, K); ++kk) {
                            C[ii * N + jj] += A[ii * K + kk] * B[kk * N + jj];
                        }
                    }
                }
            }
        }
    }

    // Now handle the peeled sections of the remaining rows or columns at the edges
    if (M % BLOCK_SIZE != 0 || K % BLOCK_SIZE != 0 || N % BLOCK_SIZE != 0) {
        int last_block_start_M = (M / BLOCK_SIZE) * BLOCK_SIZE;
        int last_block_start_K = (K / BLOCK_SIZE) * BLOCK_SIZE;
        int last_block_start_N = (N / BLOCK_SIZE) * BLOCK_SIZE;

        // Handle remaining rows (peel the last row block)
        #pragma omp parallel for
        for (int i = last_block_start_M; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < K; ++k) {
                    C[i * N + j] += A[i * K + k] * B[k * N + j];
                }
            }
        }

        // Handle remaining columns (peel the last column block)
        #pragma omp parallel for
        for (int j = last_block_start_N; j < N; ++j) {
            for (int i = 0; i < M; ++i) {
                for (int k = 0; k < K; ++k) {
                    C[i * N + j] += A[i * K + k] * B[k * N + j];
                }
            }
        }

        // Handle remaining inner blocks (peel the last column of the inner product)
        #pragma omp parallel for
        for (int k = last_block_start_K; k < K; ++k) {
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < N; ++j) {
                    C[i * N + j] += A[i * K + k] * B[k * N + j];
                }
            }
        }
    }
}

int main() {
    int M = 1024;  // Number of rows of A and C
    int K = 512;   // Number of columns of A and rows of B
    int N = 1024;  // Number of columns of B and C
    
    std::valarray<double> A(M * K), B(K * N), C(M * N);

    // Initialize A, B, and C (e.g., with random values)
    for (int i = 0; i < M * K; ++i) A[i] = rand() % 10 + 1;
    for (int i = 0; i < K * N; ++i) B[i] = rand() % 10 + 1;
    C = 0;  // Initialize result matrix to zero

    auto start = std::chrono::high_resolution_clock::now();
    matmul(A, B, C, M, K, N);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Time: " << duration.count() << " seconds\n";
    
    return 0;
}
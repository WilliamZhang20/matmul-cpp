#include <immintrin.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

constexpr int TILE = 64;
constexpr int SIMD_WIDTH = 8;
constexpr int NUM_THREADS = 12;
constexpr int ALIGNMENT = 32; // Bytes for AVX2 (__m256)

// Matrix multiplication with AVX2, loop peeling, OpenMP, and cache blocking
void matmul_avx(const float* A, const float* B, float* C, int M, int K, int N) {
    #pragma omp parallel for collapse(2) num_threads(NUM_THREADS)
    for (int ii = 0; ii < M; ii += TILE) {
        for (int jj = 0; jj < N; jj += TILE) {
            for (int kk = 0; kk < K; kk += TILE) {
                for (int i = ii; i < std::min(ii + TILE, M); ++i) {
                    for (int j = jj; j < std::min(jj + TILE, N); ++j) {
                        __m256 sum_vec = _mm256_setzero_ps();
                        int k = kk;

                        for (; k <= std::min(kk + TILE, K) - SIMD_WIDTH; k += SIMD_WIDTH) {
                            __m256 a_vec = _mm256_loadu_ps(&A[i * K + k]);
                            __m256 b_vec = _mm256_loadu_ps(&B[k * N + j]); // gather emulated
                            alignas(32) float b_tmp[SIMD_WIDTH];
                            for (int t = 0; t < SIMD_WIDTH; ++t)
                                b_tmp[t] = B[(k + t) * N + j];
                            b_vec = _mm256_load_ps(b_tmp);
                            sum_vec = _mm256_fmadd_ps(a_vec, b_vec, sum_vec);
                        }

                        float sum = 0.0f;
                        alignas(32) float tmp[SIMD_WIDTH];
                        _mm256_store_ps(tmp, sum_vec);
                        for (int t = 0; t < SIMD_WIDTH; ++t)
                            sum += tmp[t];

                        for (; k < std::min(kk + TILE, K); ++k)
                            sum += A[i * K + k] * B[k * N + j];

                        C[i * N + j] += sum;
                    }
                }
            }
        }
    }
}

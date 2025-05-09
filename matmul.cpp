#include "matmul_avx.h"
#include <vector>
#include <random>
#include <chrono>
#include <iostream>

void benchmark(int M, int K, int N) {
    // Allocate aligned memory
    float* A = static_cast<float*>(std::aligned_alloc(ALIGNMENT, M * K * sizeof(float)));
    float* B = static_cast<float*>(std::aligned_alloc(ALIGNMENT, K * N * sizeof(float)));
    float* C = static_cast<float*>(std::aligned_alloc(ALIGNMENT, M * N * sizeof(float)));

    if (!A || !B || !C) {
        std::cerr << "Failed to allocate aligned memory!" << std::endl;
        std::free(A);
        std::free(B);
        std::free(C);
        return;
    }

    std::mt19937 rng(42);
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    for (int i = 0; i < M * K; ++i) A[i] = dist(rng);
    for (int i = 0; i < K * N; ++i) B[i] = dist(rng);
    for (int i = 0; i < M * N; ++i) C[i] = 0.0f;

    auto start = std::chrono::high_resolution_clock::now();
    matmul_avx(A, B, C, M, K, N);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "M=" << M << ", K=" << K << ", N=" << N
              << " → Time: " << elapsed.count() << " sec" << std::endl;

    // Free aligned memory
    std::free(A);
    std::free(B);
    std::free(C);
}

int main() {
    const int start = 1024;
    const int end = 4096;
    const int step = 128;

    for (int dim = start; dim <= end; dim += step) {
        int M = dim;
        int K = dim / 2;
        int N = dim * 3 / 4;
        benchmark(M, K, N);
    }

    return 0;
}
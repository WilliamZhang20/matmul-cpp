#include "matmul_avx.h"
#include <vector>
#include <random>
#include <chrono>
#include <iostream>

void benchmark(int M, int K, int N) {
    std::vector<float> A(M * K), B(K * N), C(M * N, 0.0f);
    std::mt19937 rng(42);
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    for (auto& val : A) val = dist(rng);
    for (auto& val : B) val = dist(rng);

    auto start = std::chrono::high_resolution_clock::now();
    matmul_avx(A.data(), B.data(), C.data(), M, K, N);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "M=" << M << ", K=" << K << ", N=" << N
              << " → Time: " << elapsed.count() << " sec" << std::endl;
}

int main() {
    const int start = 128;
    const int end = 1024;
    const int step = 128;

    for (int dim = start; dim <= end; dim += step) {
        int M = dim;
        int K = dim / 2;
        int N = dim * 3 / 4;
        benchmark(M, K, N);
    }

    return 0;
}
# C++ Matrix Multiplication

An extension of [this](https://github.com/WilliamZhang20/matmul) repository.

But using C++, which has enabled a dramatic shortening of the code.

Additionally, C++26 will soon allow for the `<simd>` header, but for now, we will just use the rather old `<valarray>` header.

To vectorize operations on it, we will add compiler optimizations `-O3 -march=native`. 

This repository's code was built with [Bazel](https://bazel.build/install/ubuntu).

To run it in Bazel, I use:

```bash
bazel build //:matrix_mul
./bazel-bin/matrix_mul
```
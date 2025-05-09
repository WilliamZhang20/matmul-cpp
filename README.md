# C++ Matrix Multiplication

An extension of [this](https://github.com/WilliamZhang20/matmul) repository.

But using C++, which has enabled a dramatic shortening of the code.

While C++26 will soon allow for the `<simd>` header, we will just use for now the rather old `<valarray>` header.

For vectorizing operations over `std::valarray`, we will add compiler optimizations `-O3 -march=native`. 

You can see the effect of vectorization in the file `valarray.s` with the loading of values into YMM registers.

To make compilation and running quick, this repository's code was built with [Bazel](https://bazel.build/install/ubuntu).

To run it in Bazel, I use:

```bash
bazel build //:matrix_mul
./bazel-bin/matrix_mul
```
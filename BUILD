cc_binary(
    name = "matrix_mul",
    srcs = ["matmul_valarray.cpp"],
    copts = ["-O3", "-march=native", "-fopenmp"],
    linkopts = ["-fopenmp", "-lgomp"],
)
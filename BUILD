cc_library(
    name = "matmul",
    srcs = ["matmul.cpp"],
    hdrs = ["matmul_avx.h"],
    copts = ["-O3", "-march=native", "-fopenmp"],
    linkopts = ["-fopenmp", "-lgomp", "-std=c++17"],
)

cc_binary(
    name = "matrix_multiplier",
    srcs = ["matmul.cpp"],
    deps = [":matmul"],
    copts = ["-O3", "-march=native", "-fopenmp", "-std=c++17"],
    linkopts = ["-fopenmp", "-lgomp"],
)
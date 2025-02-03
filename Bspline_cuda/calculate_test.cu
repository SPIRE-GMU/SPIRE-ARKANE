#include <stdio.h>
#include <stdlib.h>
#include <chrono>  // 高精度计时

#define N 2000
#define GRID_SIZE 11  // grid 数组的大小

// 设备函数：计算 B 样条基函数
__device__ double calculate_bspline(double *grid, double x) {
    double N0[4] = {0};
    double N1[3] = {0};
    double N2[2] = {0};
    double N3[1] = {0};

    // 计算0阶B样条系数
    for (int i = 0; i <= 3; i++) {
        N0[i] = (grid[i] <= x && x < grid[i + 1]) ? 1.0 : 0.0;
    }

    // 计算1阶B样条系数
    for (int i = 0; i < 3; i++) {
        double alpha_denominator = grid[i + 1] - grid[i];
        double beta_denominator = grid[i + 2] - grid[i + 1];
        double alpha = (alpha_denominator == 0) ? 0 : (x - grid[i]) / alpha_denominator * N0[i];
        double beta = (beta_denominator == 0) ? 0 : (grid[i + 2] - x) / beta_denominator * N0[i + 1];
        N1[i] = alpha + beta;
    }

    // 计算2阶B样条系数
    for (int i = 0; i < 2; i++) {
        double alpha_denominator = grid[i + 2] - grid[i];
        double beta_denominator = grid[i + 3] - grid[i + 1];
        double alpha = (alpha_denominator == 0) ? 0 : (x - grid[i]) / alpha_denominator * N1[i];
        double beta = (beta_denominator == 0) ? 0 : (grid[i + 3] - x) / beta_denominator * N1[i + 1];
        N2[i] = alpha + beta;
    }

    // 计算3阶B样条系数
    for (int i = 0; i < 1; i++) {
        double alpha_denominator = grid[i + 3] - grid[i];
        double beta_denominator = grid[i + 4] - grid[i + 1];
        double alpha = (alpha_denominator == 0) ? 0 : (x - grid[i]) / alpha_denominator * N2[i];
        double beta = (beta_denominator == 0) ? 0 : (grid[i + 4] - x) / beta_denominator * N2[i + 1];
        N3[i] = alpha + beta;
    }

    return N3[0];
}

// 测试内核：调用 calculate_bspline 并将结果存储到全局内存
__global__ void test_kernel(double *grid, double *x, double *result) {
    // 定义共享内存
    __shared__ double s_grid[GRID_SIZE];

    // 线程索引
    int xid = blockIdx.x * blockDim.x + threadIdx.x;
    int tid = threadIdx.x;

    // 将 grid 数据加载到共享内存
    if (tid < GRID_SIZE) {
        s_grid[tid] = grid[tid];
    }
    __syncthreads();  // 确保所有线程都完成了共享内存的加载

    if (xid < N) {
        double x_val = x[xid];
        for (int i = 0; i < 7; i++) {
            result[xid * 7 + i] = calculate_bspline(s_grid + i, x_val);
        }
    }
}

int main() {
    int threads_per_block = 256;
    int number_of_blocks = (N + threads_per_block - 1) / threads_per_block;

    // 定义 grid 数组和 x 值
    double h_grid[GRID_SIZE] = {0};  // grid 数组
    for (int i = 0; i < GRID_SIZE; i++) {
        h_grid[i] = -1.0 + i * (2.0 / (GRID_SIZE - 1));
    }

    double h_x[N] = {0};  // 要计算 B 样条基函数的点
    for (int i = 0; i < N; ++i) {
        h_x[i] = (float)rand() / RAND_MAX * 2.0f - 1.0f;
    }

    double h_result[N * 7] = {0.0};  // 存储结果的变量

    // 分配设备内存
    double *d_grid, *d_result, *d_x;
    cudaMalloc((void**)&d_grid, sizeof(h_grid));
    cudaMalloc((void**)&d_result, sizeof(h_result));
    cudaMalloc((void**)&d_x, sizeof(h_x));

    // 将数据复制到设备
    cudaMemcpy(d_x, h_x, sizeof(h_x), cudaMemcpyHostToDevice);
    cudaMemcpy(d_grid, h_grid, sizeof(h_grid), cudaMemcpyHostToDevice);

    // 计时开始
    auto start_time = std::chrono::high_resolution_clock::now();

    // 运行测试内核 1000 次
    for (int j = 0; j < 1000; j++) {
        test_kernel<<<number_of_blocks, threads_per_block>>>(d_grid, d_x, d_result);
        cudaDeviceSynchronize();
    }

    // 计时结束
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_spent = end_time - start_time;
    printf("Execution time: %.6f seconds\n", time_spent.count());

    // 将结果复制回主机
    cudaMemcpy(h_result, d_result, sizeof(double) * N * 7, cudaMemcpyDeviceToHost);

    // 打印部分结果
    // for (int i = 0; i < 10; ++i) {
    //     printf("B-spline values for x = %.2f:\n", h_x[i]);
    //     for (int j = 0; j < 7; ++j) {
    //         printf("  B[%d] = %f\n", j, h_result[i * 7 + j]);
    //     }
    // }

    // 释放设备内存
    cudaFree(d_grid);
    cudaFree(d_x);
    cudaFree(d_result);

    return 0;
}
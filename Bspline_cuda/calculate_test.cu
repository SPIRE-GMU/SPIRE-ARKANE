#include <stdio.h>
#include <stdlib.h>
#include <chrono>  // time

#define N 2000
#define GRID_SIZE 11  // grid 

// compute 3-order B spline
__device__ double calculate_bspline(double *grid, double x) {
    double N0[4] = {0};
    double N1[3] = {0};
    double N2[2] = {0};
    double N3[1] = {0};

    // compute 0-order B-spline coefficients
    for (int i = 0; i <= 3; i++) {
        N0[i] = (grid[i] <= x && x < grid[i + 1]) ? 1.0 : 0.0;
    }

    // compute 1-order B-spline coefficients
    for (int i = 0; i < 3; i++) {
        double alpha_denominator = grid[i + 1] - grid[i];
        double beta_denominator = grid[i + 2] - grid[i + 1];
        double alpha = (alpha_denominator == 0) ? 0 : (x - grid[i]) / alpha_denominator * N0[i];
        double beta = (beta_denominator == 0) ? 0 : (grid[i + 2] - x) / beta_denominator * N0[i + 1];
        N1[i] = alpha + beta;
    }

    // compute 2-order B-spline coefficients
    for (int i = 0; i < 2; i++) {
        double alpha_denominator = grid[i + 2] - grid[i];
        double beta_denominator = grid[i + 3] - grid[i + 1];
        double alpha = (alpha_denominator == 0) ? 0 : (x - grid[i]) / alpha_denominator * N1[i];
        double beta = (beta_denominator == 0) ? 0 : (grid[i + 3] - x) / beta_denominator * N1[i + 1];
        N2[i] = alpha + beta;
    }

    // compute 3-order B-spline coefficients
    for (int i = 0; i < 1; i++) {
        double alpha_denominator = grid[i + 3] - grid[i];
        double beta_denominator = grid[i + 4] - grid[i + 1];
        double alpha = (alpha_denominator == 0) ? 0 : (x - grid[i]) / alpha_denominator * N2[i];
        double beta = (beta_denominator == 0) ? 0 : (grid[i + 4] - x) / beta_denominator * N2[i + 1];
        N3[i] = alpha + beta;
    }

    return N3[0];
}

// CUDA kernel
__global__ void test_kernel(double *grid, double *x, double *result) {
    // shared memory
    __shared__ double s_grid[GRID_SIZE];

    // index
    int xid = blockIdx.x * blockDim.x + threadIdx.x;
    int tid = threadIdx.x;

    // load grid into shared memory
    if (tid < GRID_SIZE) {
        s_grid[tid] = grid[tid];
    }
    __syncthreads();  // wait for all threads to load grid

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

    // define grid
    double h_grid[GRID_SIZE] = {0};  // grid 
    for (int i = 0; i < GRID_SIZE; i++) {
        h_grid[i] = -1.0 + i * (2.0 / (GRID_SIZE - 1));
    }

    double h_x[N] = {0};  // x values
    for (int i = 0; i < N; ++i) {
        h_x[i] = (float)rand() / RAND_MAX * 2.0f - 1.0f;
    }

    double h_result[N * 7] = {0.0};  // result

    // shared memory
    double *d_grid, *d_result, *d_x;
    cudaMalloc((void**)&d_grid, sizeof(h_grid));
    cudaMalloc((void**)&d_result, sizeof(h_result));
    cudaMalloc((void**)&d_x, sizeof(h_x));

    // copy data to device
    cudaMemcpy(d_x, h_x, sizeof(h_x), cudaMemcpyHostToDevice);
    cudaMemcpy(d_grid, h_grid, sizeof(h_grid), cudaMemcpyHostToDevice);

    // start_time
    auto start_time = std::chrono::high_resolution_clock::now();

    // run kernel
    for (int j = 0; j < 1000; j++) {
        test_kernel<<<number_of_blocks, threads_per_block>>>(d_grid, d_x, d_result);
        cudaDeviceSynchronize();
    }

    // end_time
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_spent = end_time - start_time;
    printf("Execution time: %.6f seconds\n", time_spent.count());

    // copy result back to host
    cudaMemcpy(h_result, d_result, sizeof(double) * N * 7, cudaMemcpyDeviceToHost);

    // 打印部分结果
    // for (int i = 0; i < 1000; ++i) {
    //     printf("B-spline values for x = %.2f:\n", h_x[i]);
    //     for (int j = 0; j < 7; ++j) {
    //         printf("  B[%d] = %f\n", j, h_result[i * 7 + j]);
    //     }
    // }

    // release device memory
    cudaFree(d_grid);
    cudaFree(d_x);
    cudaFree(d_result);

    return 0;
}

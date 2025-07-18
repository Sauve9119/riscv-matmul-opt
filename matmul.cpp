#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cstdlib>
#include <cstring>

using namespace std;
using namespace std::chrono;

const int DEFAULT_SIZE = 512;
const int TILE_SIZE = 32; // Adjust based on L1/L2 cache for better performance

void fill_matrix(vector<vector<float>>& mat) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0f, 1.0f);
    int N = mat.size();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            mat[i][j] = dis(gen);
}

// Naive matrix multiplication
void matmul_naive(const vector<vector<float>>& A, const vector<vector<float>>& B, vector<vector<float>>& C) {
    int N = A.size();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];
}

// Cache-aware blocked matrix multiplication
void matmul_tiled(const vector<vector<float>>& A, const vector<vector<float>>& B, vector<vector<float>>& C) {
    int N = A.size();
    for (int ii = 0; ii < N; ii += TILE_SIZE)
        for (int jj = 0; jj < N; jj += TILE_SIZE)
            for (int kk = 0; kk < N; kk += TILE_SIZE)
                for (int i = ii; i < min(ii + TILE_SIZE, N); ++i)
                    for (int j = jj; j < min(jj + TILE_SIZE, N); ++j)
                        for (int k = kk; k < min(kk + TILE_SIZE, N); ++k)
                            C[i][j] += A[i][k] * B[k][j];
}

// Benchmarking utility
void benchmark(const string& label,
               void (*func)(const vector<vector<float>>&, const vector<vector<float>>&, vector<vector<float>>&),
               const vector<vector<float>>& A,
               const vector<vector<float>>& B,
               vector<vector<float>>& C) {
    auto start = high_resolution_clock::now();
    func(A, B, C);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << label << " Execution Time: " << duration.count() << " ms\n";
}

int main(int argc, char* argv[]) {
    int N = DEFAULT_SIZE;
    if (argc >= 2) N = atoi(argv[1]);

    cout << "Matrix size: " << N << " x " << N << endl;

    vector<vector<float>> A(N, vector<float>(N));
    vector<vector<float>> B(N, vector<float>(N));
    vector<vector<float>> C_naive(N, vector<float>(N, 0.0f));
    vector<vector<float>> C_tiled(N, vector<float>(N, 0.0f));

    fill_matrix(A);
    fill_matrix(B);

    benchmark("Naive", matmul_naive, A, B, C_naive);
    benchmark("Tiled", matmul_tiled, A, B, C_tiled);

    return 0;
}

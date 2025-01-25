#include <iostream>
#include <iomanip>
#include <cmath>
#include <armpl.h>
#include <mpi.h> 
#include <vector>
#include <random>

#define ui64 u_int64_t

double exp_optimized(double x) {
    double result = 1.0;
    
    result = 1 + (x / 4.0) * result;
    result = 1 + (x / 3.0) * result;
    result = 1 + (x / 2.0) * result;
    result = 1 + (x / 1.0) * result;

    return result;
}

// Parallel Gaussian random number generation
void generate_gaussian_vector(float* Z, ui64 num_simulations, unsigned long long seed) {
    VSLStreamStatePtr stream;
    vslNewStream(&stream, VSL_BRNG_PHILOX4X32X10, seed);
    vsRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER2, stream, num_simulations, Z, 0.0f, 1.0f);
    vslDeleteStream(&stream);
}


// Black-Scholes Monte Carlo with per-process simulation
float black_scholes_monte_carlo(
    ui64 S0, ui64 K, float T, float r, float sigma, float q, 
    ui64 num_simulations, unsigned long long seed
) {
    std::vector<float> Z(num_simulations);
    generate_gaussian_vector(Z.data(), num_simulations, seed);
    
    float A = (r - q - 0.5f * sigma * sigma) * T;
    float B = sigma * std::sqrt(T);
    float sum_payoffs = 0.0f;

    #pragma omp parallel for reduction(+:sum_payoffs)
    for (ui64 i = 0; i < num_simulations; ++i) {
        float ST = S0 * exp_optimized(A + B * Z[i]);
        sum_payoffs += std::max(ST - K, 0.0f);
    }

    return exp_optimized(-r * T) * (sum_payoffs / num_simulations);
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 3) {
        if (rank == 0) {
            std::cerr << "Usage: " << argv[0] << " <num_simulations> <num_runs>" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    ui64 num_simulations = std::stoull(argv[1]);
    ui64 num_runs = std::stoull(argv[2]);

    // Black-Scholes parameters
    ui64 S0 = 100;
    ui64 K = 110;
    float T = 1.0f;
    float r = 0.06f;
    float sigma = 0.2f;
    float q = 0.03f;

    // Seed generation
    std::random_device rd;
    unsigned long long global_seed = rd();

    if(rank == 0)
        std::cout << "Global initial seed: " << global_seed << "      argv[1]= " << argv[1] << "     argv[2]= " << argv[2] <<  std::endl;
    // Distribute runs and simulations across processes
    ui64 runs_per_proc = num_runs / size;
    ui64 sims_per_proc = num_simulations / size;

    float local_sum = 0.0f;
    float global_sum = 0.0f;

    double t1 = MPI_Wtime();

    // Parallelize both runs and simulations
    for (ui64 run = rank; run < num_runs; run += size) {
        local_sum += black_scholes_monte_carlo(
            S0, K, T, r, sigma, q, 
            sims_per_proc, global_seed + run
        );
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, 
               MPI_SUM, 0, MPI_COMM_WORLD);

    double t2 = MPI_Wtime();

    if(rank == 0)
        std::cout << std::fixed << std::setprecision(6) << " value= " << global_sum/num_runs << " in " << (t2-t1) << " seconds" << std::endl;

    MPI_Finalize();
    return 0;
}
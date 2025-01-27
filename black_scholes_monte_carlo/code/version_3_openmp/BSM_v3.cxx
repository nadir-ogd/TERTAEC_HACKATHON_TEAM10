#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <limits>
#include <algorithm>
#include <iomanip>     // For setting precision
#include <cblas.h>     // For exp_optimized_cblas()
#include <cmath>       // For std::erf et std::sqrt

#define ui64 u_int64_t

double exp_optimized(double x) {
    double result = 1.0;
    
    result = 1 + (x / 4.0) * result;
    result = 1 + (x / 3.0) * result;
    result = 1 + (x / 2.0) * result;
    result = 1 + (x / 1.0) * result;

    return result;
}

// Function to generate Gaussian noise using Box-Muller transform
double gaussian_box_muller() {
    static std::mt19937 generator(std::random_device{}());
    static std::normal_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

// Function to calculate the Black-Scholes call option price using Monte Carlo method
double black_scholes_monte_carlo(ui64 S0, ui64 K, double T, double r, double sigma, double q, ui64 num_simulations) {
    double sum_payoffs = 0.0;

    double A = (r - q - 0.5 * sigma * sigma) * T;
    double expA = S0*exp_optimized(A);
    double B = sigma * sqrt(T);

    #pragma omp parallel for schedule(dynamic, 100) reduction(+:sum_payoffs)
    for (ui64 i = 0; i < num_simulations; ++i) {
        double Z = gaussian_box_muller();
        double ST = expA * exp_optimized(B * Z);
        sum_payoffs += (ST - K) * (ST > K);
    }

    return exp_optimized(-r * T) * (sum_payoffs / num_simulations);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <num_simulations> <num_runs>" << std::endl;
        return 1;
    }

    ui64 num_simulations = std::stoull(argv[1]);
    ui64 num_runs        = std::stoull(argv[2]);

    // Input parameters
    ui64 S0      = 100;                   // Initial stock price
    ui64 K       = 110;                   // Strike price
    double T     = 1.0;                   // Time to maturity (1 year)
    double r     = 0.06;                  // Risk-free interest rate
    double sigma = 0.2;                   // Volatility
    double q     = 0.03;                  // Dividend yield

    // Generate a random seed at the start of the program using random_device
    std::random_device rd;
    unsigned long long global_seed = rd();  // This will be the global seed

    std::cout << "Global initial seed: " << global_seed << "      argv[1]= " << argv[1] << "     argv[2]= " << argv[2] <<  std::endl;

    // Get the number of threads from the environment variable OMP_NUM_THREADS
    
    // const char* omp_threads_env = getenv("OMP_NUM_THREADS");
    // int num_threads = omp_threads_env ? std::stoi(omp_threads_env) : omp_get_max_threads();
    // omp_set_num_threads(num_threads);
    
    int num_threads = 16;
    omp_set_num_threads(num_threads);

    double sum=0.0;
    double t1 = omp_get_wtime();

    #pragma omp parallel for schedule(static, 100) reduction(+:sum)
    for (ui64 run = 0; run < num_runs; ++run) {
        sum+= black_scholes_monte_carlo(S0, K, T, r, sigma, q, num_simulations);
    }
    
    double t2 = omp_get_wtime();
    std::cout << std::fixed << std::setprecision(6) << " value= " << sum/num_runs << " in " << (t2-t1) << " seconds" << std::endl;

    return 0;
}
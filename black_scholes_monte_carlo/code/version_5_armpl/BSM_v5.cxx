#include <iostream>
#include <iomanip>
#include <cmath>
#include <armpl.h>    // OpenRNG is included in ArmPL
#include <cstdlib>
#include <cstring>
#include <random>     // For random_device
#include <sys/time.h> // For dml_micros

#define ui64 u_int64_t

double dml_micros()
{
    static struct timezone tz;
    static struct timeval  tv;
    gettimeofday(&tv,&tz);
    return((tv.tv_sec*1000000.0)+tv.tv_usec);
}

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

// Generate Gaussian random numbers using OpenRNG (float precision for performance)
void generate_gaussian_vector(float* Z, ui64 num_simulations, unsigned long long seed) {
    VSLStreamStatePtr stream;
    int errcode = vslNewStream(&stream, VSL_BRNG_PHILOX4X32X10, seed);
    if (errcode != VSL_STATUS_OK) {
        std::cerr << "Failed to create RNG stream!" << std::endl;
        exit(1);
    }

    errcode = vsRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER2, stream, num_simulations, Z, 0.0f, 1.0f);
    if (errcode != VSL_STATUS_OK) {
        std::cerr << "Failed to generate random numbers!" << std::endl;
        vslDeleteStream(&stream);
        exit(1);
    }

    vslDeleteStream(&stream);
}

// Black-Scholes Monte Carlo implementation using OpenRNG
float black_scholes_monte_carlo(ui64 S0, ui64 K, float T, float r, float sigma, float q, ui64 num_simulations, unsigned long long seed) {
    float* Z = (float*)malloc(num_simulations * sizeof(float));
    float* payoffs = (float*)malloc(num_simulations * sizeof(float));

    if (!Z || !payoffs) {
        std::cerr << "Memory allocation failed!" << std::endl;
        exit(1);
    }

    // Generate Gaussian random numbers
    generate_gaussian_vector(Z, num_simulations, seed);

    float A = (r - q - 0.5f * sigma * sigma) * T;
    float B = sigma * sqrt(T);
    float sum_payoffs = 0.0f;

    // Calculate payoffs in parallel
    for (ui64 i = 0; i < num_simulations; ++i) {
        float ST = S0 * exp_optimized(A + B * Z[i]);
        payoffs[i] = (ST - K) * (ST > K);
    }

    // Sum up payoffs
    sum_payoffs = cblas_sasum(num_simulations, payoffs, 1);

    free(Z);
    free(payoffs);

    return exp_optimized(-r * T) * (sum_payoffs / num_simulations);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <num_simulations> <num_runs>" << std::endl;
        return 1;
    }

    ui64 num_simulations = std::stoull(argv[1]);
    ui64 num_runs = std::stoull(argv[2]);
    ui64 S0 = 100;
    ui64 K = 110;
    float T = 1.0f;
    float r = 0.06f;
    float sigma = 0.2f;
    float q = 0.03f;

    // Generate a random seed
    std::random_device rd;
    unsigned long long global_seed = rd();
    
    std::cout << "Global initial seed: " << global_seed << "      argv[1]= " << argv[1] << "     argv[2]= " << argv[2] <<  std::endl;

    double t1 = dml_micros();
    float sum = 0.0f;

    for (ui64 run = 0; run < num_runs; ++run) {
        sum += black_scholes_monte_carlo(S0, K, T, r, sigma, q, num_simulations, global_seed + run);
    }

    double t2 = dml_micros();
    std::cout << std::fixed << std::setprecision(6) << " value= " << sum/num_runs << " in " << (t2-t1)/1000000.0 << " seconds" << std::endl;

    return 0;
}
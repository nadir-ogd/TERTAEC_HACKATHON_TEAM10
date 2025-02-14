#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <limits>
#include <algorithm>
#include <iomanip>     // For setting precision
#include <cblas.h>     // For exp_optimized_cblas()
#include <cmath>       // For std::erf et std::sqrt
#include <sys/time.h>  // For dml_micros()

#define ui64 u_int64_t

double dml_micros()
{
        static struct timezone tz;
        static struct timeval  tv;
        gettimeofday(&tv,&tz);
        return((tv.tv_sec*1000000.0)+tv.tv_usec);
}

// Function to generate Gaussian noise using Box-Muller transform
double gaussian_box_muller() {
    static std::mt19937 generator(std::random_device{}());
    static std::normal_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

// Good time wise but we lose a lot in precision
// double exp_optimized_cblas(double x) {
//     double result = 1.0;  

//     double factors[] = {1.0, 2.0, 3.0, 4.0};
    
//     for (int i = 3; i >= 0; i--) {
//         cblas_daxpy(1, x / factors[i], &result, 1, &result, 1);
//     }

//     return result;
// }

// with this, we don't lose in precision 
double exp_optimized(double x) {
    double result = 1.0;
    
    result = 1 + (x / 4.0) * result;
    result = 1 + (x / 3.0) * result;
    result = 1 + (x / 2.0) * result;
    result = 1 + (x / 1.0) * result;

    return result;
}

// Function to calculate the Black-Scholes call option price using Monte Carlo method
double black_scholes_monte_carlo(ui64 S0, ui64 K, double T, double r, double sigma, double q, ui64 num_simulations) {
    double sum_payoffs = 0.0;

    double A = (r - q - 0.5 * sigma * sigma) * T;
    double expA = S0*exp_optimized(A);
    double B = sigma * sqrt(T);

    for (ui64 i = 0; i < num_simulations; ++i) {
        double Z = gaussian_box_muller();
        double ST = expA * exp_optimized(B * Z);

        // Remplacement de std::max par une pproche conditionnelle
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

    double sum=0.0;
    double t1=dml_micros();
    for (ui64 run = 0; run < num_runs; ++run) {
        sum+= black_scholes_monte_carlo(S0, K, T, r, sigma, q, num_simulations);
    }
    
    double t2=dml_micros();
    std::cout << std::fixed << std::setprecision(6) << " value= " << sum/num_runs << " in " << (t2-t1)/1000000.0 << " seconds" << std::endl;

    return 0;
}

#include <fgt.hpp>
#include <iostream>
#include <string>
#include <Eigen/Dense>
#include <random>
#include <chrono>

const double DEFAULT_EPSILON = 1e-4;

int main(int argc, char** argv) {
    double eps = DEFAULT_EPSILON;
    std::string mode = argv[1];
    size_t num_points = std::stoi(argv[2]);
    double bandwidth = std::stod(argv[3]);

    // Define the number of data points
    const int dims = 1;

    // Initialize random number generators
    std::mt19937 rng(12345); // Seed for reproducibility
    std::normal_distribution<> dist1(-2, 1);
    std::normal_distribution<> dist2(2, 1);

    // Create x and y matrices with random values
    Eigen::MatrixXd x(num_points, dims);

        for (int i = 0; i < num_points/2; i++) {
            x(i,0) = dist1(rng);
        }
        
        for (int i = num_points/2; i < num_points; i++) {
            x(i,0) = dist2(rng);
        }


    // Timing
    std::vector<double> result;
    auto tic = std::chrono::high_resolution_clock::now();
    if (mode == "direct") {
        fgt::direct(x, x, bandwidth);
    } else if (mode == "direct_tree") {
        fgt::direct_tree(x, x, bandwidth, eps);
    } else if (mode == "ifgt") {
        fgt::ifgt(x, x, bandwidth, eps);
    } else {
        std::cout << "Invalid mode: " << mode << "\n";
        return 1;
    }

    auto toc = std::chrono::high_resolution_clock::now();

    auto runtime = toc - tic;
    std::cout << double(std::chrono::duration_cast<std::chrono::microseconds>(
                            runtime)
                            .count()) *
                     1e-6f
              << "\n";
    return 0;
}

#include <fgt.hpp>
#include <iostream>
#include <string>
#include <Eigen/Dense>
#include <random>

const double DEFAULT_EPSILON = 1e-4;

int main() {
    double eps = DEFAULT_EPSILON;

    // Define the number of data points
    const int num_points = 1000;
    const int dimensions = 4;

    // Initialize random number generator
    std::mt19937 rng(12345); // Seed for reproducibility
    std::uniform_real_distribution<> dist(-1, 1);

    // Create x and y matrices with random values
    Eigen::MatrixXd x(num_points, dimensions);
    Eigen::MatrixXd y(num_points, dimensions);

    for (int i = 0; i < num_points; ++i) {
        for (int j = 0; j < dimensions; ++j) {
            x(i, j) = dist(rng);
            y(i, j) = dist(rng);
        }
    }

    // Define a reasonable bandwidth
    double bandwidth = 0.2;

    // Apply the Fast Gauss Transform methods
    Eigen::VectorXd res_direct = fgt::direct(x, y, bandwidth);
    Eigen::VectorXd res_dir_tree = fgt::direct_tree(x, y, bandwidth, eps);
    Eigen::VectorXd res_ifgt = fgt::ifgt(x, y, bandwidth, eps);

    // Print results
    std::cout << "Direct result:\n" << res_direct.transpose() << std::endl;
    std::cout << "Direct tree result:\n" << res_dir_tree.transpose() << std::endl;
    std::cout << "IFGT result:\n" << res_ifgt.transpose() << std::endl;

    return 0;
}
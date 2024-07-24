#include <boost/algorithm/string.hpp>
#include <Eigen/Dense>
#include <fgt.hpp>
#include <iostream>
#include <string>

int main() {
    // Test Eigen
    Eigen::MatrixXd x(2, 2);
    x(0, 0) = 3;
    x(1, 0) = 2.5;
    x(0, 1) = -1;
    x(1, 1) = x(1, 0) + x(0, 1);
    std::cout << "Eigen Matrix:\n" << x << std::endl;

    // Test Boost
    std::string s = "Boost and Eigen";
    boost::to_upper(s);
    std::cout << "Boost String: " << s << std::endl;

    // Test fgt
    Eigen::MatrixXd y(2, 2);
    y(0, 0) = 1;
    y(1, 0) = 0.5;
    y(0, 1) = -0.5;
    y(1, 1) = y(1, 0) + y(0, 1);

    double bandwidth = 0.3;
    Eigen::VectorXd result = fgt::direct(x, y, bandwidth);
    std::cout << "FGT Result:\n" << result << std::endl;g

    return 0;
}

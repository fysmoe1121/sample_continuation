#include <Eigen/Dense>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>

int main() {
    // Test Eigen
    Eigen::MatrixXd m(2, 2);
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    m(1, 1) = m(1, 0) + m(0, 1);
    std::cout << "Eigen Matrix:\n" << m << std::endl;

    // Test Boost
    std::string s = "Boost and Eigen";
    boost::to_upper(s);
    std::cout << "Boost String: " << s << std::endl;

    return 0;
}

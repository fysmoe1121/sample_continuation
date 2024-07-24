#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <fgt.hpp>
#include <iostream>
#include <string>
#include <Eigen/Dense>
#include <random>
#include <chrono>
#include <fstream>
#include <cmath>

namespace py = pybind11;

const int niter = 3;

fgt::Matrix load_ascii_test_matrix(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::stringstream msg;
        msg << "Unable to open test data file: " << filename;
        throw std::runtime_error(msg.str());
    }
    std::vector<double> data;
    size_t rows = 0;
    size_t cols = 0;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        double value = 0.0;
        size_t nvalues = 0;
        while (ss >> value) {
            data.push_back(value);
            ++nvalues;
        }
        if (cols == 0) {
            cols = nvalues;
        } else if (cols != nvalues) {
            std::stringstream msg;
            msg << "Dimension mismatch (" << cols << ", " << nvalues << ")";
            throw std::runtime_error(msg.str());
        }
        ++rows;
    }
    fgt::Matrix matrix(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix(i, j) = data[i * cols + j];
        }
    }
    return matrix;
}

double timer(const std::string& mode, double bandwidth, double epsilon, const fgt::Matrix &points) {

    // Timing
    auto tic = std::chrono::high_resolution_clock::now();
    if (mode == "direct") {
        fgt::direct(points, points, bandwidth);
    } else if (mode == "direct_tree") {
        fgt::direct_tree(points, points, bandwidth, epsilon);
    } else if (mode == "ifgt") {
        fgt::ifgt(points, points, bandwidth, epsilon);
    } else {
        throw std::invalid_argument("Invalid mode: " + mode);
    }
    auto toc = std::chrono::high_resolution_clock::now();

    auto runtime = toc - tic;
    double res = double(std::chrono::duration_cast<std::chrono::microseconds>(
                            runtime)
                            .count()) * 1e-6f;
    return res;
}

double accuracy(const std::string& mode, double bandwidth, double epsilon, const fgt::Matrix &points) {
    auto expected = fgt::direct(points, points, bandwidth);

    Eigen::MatrixXd actual; 

    if (mode == "direct_tree") {
        actual = fgt::direct_tree(points, points, bandwidth, epsilon);
    } else if (mode == "ifgt") {
        actual = fgt::ifgt(points, points, bandwidth, epsilon);
    } else {
        throw std::invalid_argument("Invalid mode: " + mode);
    }
    return (expected - actual).array().abs().maxCoeff() / actual.size();
}

std::vector<std::vector<double>> bench_bandwidth(std::vector<double> bandwidths, double epsilon, const std::string& filename) {
    //Returns 2D vector with the following format
    // Each row corresponds to a bandwidth value where the entry of each row is
    // 3 trials of direct followed by 3 trials of direct_tree followed by 3 trials of ifgt.
    fgt::Matrix x = load_ascii_test_matrix(filename);

    std::array<std::string, 2> modes = {"direct_tree", "ifgt"};
    std::vector<std::vector<double>> output;

    for (auto& bandwidth : bandwidths) {
        std::vector<double> res_bandwidth;
        for (auto& mode : modes) {
            for (int i = 0; i < niter; i++) {
                res_bandwidth.push_back(timer(mode, bandwidth, epsilon, x));
            }
        }
        output.push_back(res_bandwidth);
    }
    return output;
}

std::vector<std::vector<double>> bench_error(double bandwidth, std::vector<double> epsilons, const std::string& filename) {
    fgt::Matrix x = load_ascii_test_matrix(filename);

    std::array<std::string, 2> modes = {"direct_tree", "ifgt"};
    std::vector<std::vector<double>> output;

    for (auto& epsilon : epsilons) {
        std::vector<double> res_epsilon;
        for (auto& mode : modes) {
            for (int i = 0; i < niter; i++) {
                res_epsilon.push_back(timer(mode, bandwidth, epsilon, x));
            }
        }
        output.push_back(res_epsilon);
    }
    return output;
}

std::vector<std::vector<double>> bench_accuracy(double bandwidth, std::vector<double> epsilons, const std::string& filename) {
    fgt::Matrix x = load_ascii_test_matrix(filename);

    std::array<std::string, 2> modes = {"direct_tree", "ifgt"};
    std::vector<std::vector<double>> output;

    for (auto& epsilon : epsilons) {
        std::vector<double> res_accuracy;
        for (auto& mode : modes) {
            for (int i = 0; i < niter; i++) {
                res_accuracy.push_back(accuracy(mode, bandwidth, epsilon, x));
            }
        }
        output.push_back(res_accuracy);
    }
    return output;
}



PYBIND11_MODULE(fgt_main, m) {
    m.def("timer", &timer, "Run the FMM and time how long it takes",
          py::arg("mode"), py::arg("bandwidth"), py::arg("epsilon"), py::arg("points"));
    m.def("accuracy", &accuracy, "Run the FMM and compare approximation to true value",
          py::arg("mode"), py::arg("bandwidth"), py::arg("epsilon"), py::arg("points"));
    m.def("bench_bandwidth", &bench_bandwidth, "Benchmark different bandwidths",
          py::arg("bandwidths"), py::arg("epsilon"), py::arg("filename"));
    m.def("bench_error", &bench_error, "Benchmark different error tolerance",
          py::arg("bandwidth"), py::arg("epsilons"), py::arg("filename"));
    m.def("bench_accuracy", &bench_accuracy, "Benchmark the true error vs the allowed error",
          py::arg("bandwidth"), py::arg("epsilons"), py::arg("filename"));
}

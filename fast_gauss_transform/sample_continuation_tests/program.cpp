#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <fgt.hpp>
#include <iostream>
#include <string>
#include <Eigen/Dense>
#include <random>
#include <chrono>
#include <fstream>

namespace py = pybind11;

const double DEFAULT_EPSILON = 1e-4;

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

double bench_time(const std::string& mode, double bandwidth, const std::string& filename) {
    double eps = DEFAULT_EPSILON;
    auto x = load_ascii_test_matrix(filename);

    // Timing
    auto tic = std::chrono::high_resolution_clock::now();
    if (mode == "direct") {
        fgt::direct(x, x, bandwidth);
    } else if (mode == "direct_tree") {
        fgt::direct_tree(x, x, bandwidth, eps);
    } else if (mode == "ifgt") {
        fgt::ifgt(x, x, bandwidth, eps);
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

double<float> main(const std::vector<double>& bandwidths) {
    
}



PYBIND11_MODULE(fgt_main, m) {
    m.def("bench_time", &bench_time, "Run the FMM and time how long it takes",
          py::arg("mode"), py::arg("bandwidth"), py::arg("filename"));
}

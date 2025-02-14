#pragma once

#include <fstream>

#include "fgt.hpp"

namespace fgt {
namespace {

const char* TEST_DATA_DIR = "/Users/leonma/Desktop/sample_continuation/fast_gauss_transform/fgt/test/data/";
}

std::string project_source_filename(const std::string& filename) {
    return "/Users/leonma/Desktop/sample_continuation/fast_gauss_transform/fgt/" + filename;
}

Matrix load_ascii_test_matrix(const std::string& filename) {
    std::ifstream file(TEST_DATA_DIR + filename);
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
            msg << "Dimension mismatch (" << cols << ", " << nvalues;
            throw std::runtime_error(msg.str());
        }
        ++rows;
    }
    Matrix matrix(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix(i, j) = data[i * cols + j];
        }
    }
    return matrix;
}

template <typename T>
Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>
load_binary_test_matrix(const std::string& filename, size_t rows, size_t cols) {
    std::ifstream file(TEST_DATA_DIR + filename, std::ios::binary);
    if (!file.is_open()) {
        std::stringstream msg;
        msg << "Unable to open test data file: " << filename;
        throw std::runtime_error(msg.str());
    }
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> data(rows, cols);
    file.read(reinterpret_cast<char*>(data.data()), rows * cols * sizeof(T));
    file.close();
    return data;
}
}

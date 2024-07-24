import numpy as np
import pandas as pd
from setuptools import setup, Extension
import pybind11

# Define the mean vector and covariance matrix
mean_1 = [0, 5, 0]
cov_1 = [[1, 0, 0],
        [0, 3, 0], 
        [0, 0, 1]]  # Diagonal covariance matrix

mean_2 = [7, 0, 0]
cov_2 = [[5, 1, -1],
        [1, 1, 0],
        [-1, 0, 3]]

mean_3 = [0,0,5]
cov_3 = [[2, 1 ,0],
         [1, 2, 0],
         [0, 0, 3]]

# Generate 5000 samples from the multivariate normal distribution
num_samples = 10000
samples = 1/3 * np.random.multivariate_normal(mean_1, cov_1, num_samples) 
+ 1/3 * np.random.multivariate_normal(mean_2, cov_2, num_samples)
+ 1/3 * np.random.multivariate_normal(mean_3, cov_3, num_samples)

# Save the samples to a CSV file
df = pd.DataFrame(samples, columns=['x', 'y', 'z'])
df.to_csv('X.txt', sep=' ', index=False, header=False)


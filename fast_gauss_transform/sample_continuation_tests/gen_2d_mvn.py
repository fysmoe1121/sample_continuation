import numpy as np
import pandas as pd
import fgt_main

# Define the mean vector and covariance matrix
mu_1 = [2, 0]
sigma_1 = [[1, 0], 
           [0, 1]]  

mu_2 = [0, 2]
sigma_2 = [[0.5, 0.5],
           [0.5, 1]]

means = [mu_1, mu_2]
covars = [sigma_1, sigma_2]
weights = [1/3, 2/3]

def generate_data(num_points, weights, means, covars):
    data_points = np.vstack([
        np.random.multivariate_normal(mean, cov, int(weight * num_points))
        for weight, mean, cov in zip(weights, means, covars)])
    return data_points
    
num_points_lst = [100,1_000,4_000, 10_000, 40_000, 100_000, 400_000]
#[1_000, 4_000, 10_000, 40_000, 100_000, 400_000]
bandwidths = [0.1, 0.178, 0.316, 0.562, 0.7, 1]
modes = ["direct_tree", "ifgt"]

rows = []       
'''
for num_points in num_points_lst:
    X = generate_data(num_points, weights, means, covars)
    filename = f'X_{num_points}.txt'
    df_x = pd.DataFrame(X, columns=['x', 'y'])
    #print(df_x)
    df_x.to_csv(filename, sep=' ', index=False, header=False)
'''
    
for num_points in num_points_lst:
    output = fgt_main.bench_bandwidth(bandwidths, 1e-4, f"X_{num_points}.txt")
    for bandwidth_data, bandwidth in zip(output, bandwidths):
        #direct_row = ["direct", num_points, bandwidth] + bandwidth_data[0:3]
        direct_tree_row = ["direct_tree", num_points, bandwidth] + bandwidth_data[0:3]
        ifgt_row = ["ifgt", num_points, bandwidth] + bandwidth_data[3:6]
        #rows.append(direct_row)
        rows.append(direct_tree_row)
        rows.append(ifgt_row)
    print(rows)
        

# Create the DataFrame all at once

df = pd.DataFrame(rows)
df.to_csv('2d_test_out_v3.txt', sep=' ', index=False, header=False)
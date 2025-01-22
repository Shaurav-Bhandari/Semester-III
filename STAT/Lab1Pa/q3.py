import numpy as np
import scipy.stats as stats

population_mean = 1100
population_std = 275
sample_data = [
    852, 927, 902, 1149, 1576, 872, 1177, 1071, 895, 1155, 868, 1083,
    897, 1700, 1398, 996, 1220, 1602, 891, 1088, 1301, 905, 1059, 1069,
    1319, 1073, 1639, 1386, 1607, 1485
]

sample_size = len(sample_data)
sample_mean = np.mean(sample_data)

z_stat = (sample_mean - population_mean) / (population_std / np.sqrt(sample_size))

p_value = 2 * (1 - stats.norm.cdf(abs(z_stat)))

print(f"Sample Mean: {sample_mean}")
print(f"Test Statistic (z): {z_stat}")
print(f"P-value: {p_value}")

alpha = 0.05
if p_value < alpha:
    print("Reject the null hypothesis: The sample is not representative of the population.")
else:
    print("Fail to reject the null hypothesis: The sample can be regarded as representative of the population.")
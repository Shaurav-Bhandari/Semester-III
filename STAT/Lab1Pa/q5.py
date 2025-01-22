import numpy as np
from scipy.stats import ttest_1samp

data = np.array([35, 20, 30, 45, 60, 40, 65, 40, 25, 50])

population_mean = 30

t_stat, p_value = ttest_1samp(data, population_mean)

p_value_one_tailed = p_value / 2

print(f"T-statistic: {t_stat}")
print(f"P-value (one-tailed): {p_value_one_tailed}")

if (t_stat > 0) and (p_value_one_tailed < 0.05):
    print("Reject the null hypothesis: The average time spent is more than 30 minutes.")
else:
    print("Fail to reject the null hypothesis: The average time spent is not significantly more than 30 minutes.")
import numpy as np
from scipy.stats import ttest_ind

manure1 = np.array([18, 20, 36, 50, 49, 36, 34, 49, 41])
manure2 = np.array([29, 28, 26, 35, 30, 44, 46])

t_stat, p_value = ttest_ind(manure1, manure2, equal_var=True)

print(f"T-statistic: {t_stat}")
print(f"P-value: {p_value}")
print(f"Mean of manure 1: {manure1.mean()}")
print(f"Mean of manure 2: {manure2.mean()}")
print(f"Standard deviation of manure 1: {manure1.std()}")
print(f"Standard deviation of manure 2: {manure2.std()}")

if p_value < 0.05:
    print("Reject the null hypothesis: There is a significant difference in yields between the two types of manure.")
else:
    print("Fail to reject the null hypothesis: There is no significant difference in yields between the two types of manure.")
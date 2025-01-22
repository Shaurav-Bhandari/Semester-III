import numpy as np
from scipy.stats import ttest_rel
before_training = np.array([12, 14, 11, 8, 7, 10, 3, 0, 5, 6])
after_training = np.array([15, 16, 10, 7, 5, 12, 10, 2, 3, 8])
t_stat, p_value = ttest_rel(before_training, after_training)
print(f"T-statistic: {t_stat}")
print(f"P-value: {p_value}")
level_of_significance = 0.05
if p_value <= level_of_significance:
    print("Reject the null hypothesis: The training was effective.")
else:
    print("Fail to reject the null hypothesis: The training was ineffective.")
import scipy.stats as stats
import numpy as np

heights = [
    78, 55, 68, 48, 65, 76, 57, 55, 65, 75, 51, 61,
    68, 67, 76, 78, 71, 56, 57, 67, 58, 51, 50, 58,
    50, 77, 55, 48, 70, 55, 58, 70, 56, 52, 74, 61,
    69, 76, 61, 68, 78, 56, 78, 57, 66, 66, 74, 66,
    48, 73, 71, 70, 62, 74, 76, 50, 69, 75, 65, 48
]

mean_height = np.mean(heights)
sem_height = stats.sem(heights)

confidence_level = 0.95
alpha = 1 - confidence_level

z_critical = stats.norm.ppf(1 - alpha / 2)

confidence_interval = (
    mean_height - z_critical * sem_height,
    mean_height + z_critical * sem_height
)

print(f"Mean height: {mean_height}")
print(f"95% Confidence Interval for the mean height:")
for i in confidence_interval:
    print(i)
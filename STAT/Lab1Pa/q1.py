import scipy.stats as stats
import math

sample_size = 150
sample_mean = 47.5
population_mean = 50
population_std = 12
alpha = 0.05

se = population_std / math.sqrt(sample_size)

z_score = (sample_mean - population_mean) / se

p_value = 2 * (1 - stats.norm.cdf(abs(z_score)))

z_critical = stats.norm.ppf(1 - alpha / 2)

print("Decision:")
if abs(z_score) <= z_critical:
    print("The sample mean can be regarded as representative of the population mean at the 5% level of significance.")
else:
    print("The sample mean cannot be regarded as representative of the population mean at the 5% level of significance.")

confidence_interval = (
    sample_mean - z_critical * se,
    sample_mean + z_critical * se
)

print(f"Z-score: {z_score}")
print(f"P-value: {p_value}")
print("Confidence Interval:")
for i in confidence_interval:
    print(i)
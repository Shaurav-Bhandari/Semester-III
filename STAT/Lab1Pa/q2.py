import scipy.stats as stats
import math

n1 = 30
n2 = 30
var1 = 840
var2 = 920
mean1 = 0
mean2 = 0
alpha = 0.05

se = math.sqrt(var1 / n1 + var2 / n2)

z_score = (mean1 - mean2) / se

p_value = 2 * (1 - stats.norm.cdf(abs(z_score)))

z_critical = stats.norm.ppf(1 - alpha / 2)

ci_lower = (mean1 - mean2) - z_critical * se
ci_upper = (mean1 - mean2) + z_critical * se

print(f"Test statistic (z-score): {z_score}")
print(f"P-value: {p_value}")

if p_value < alpha:
    print("The samples do not have equal means at the 5% level of significance.")
else:
    print("The samples have equal means at the 5% level of significance.")

print(f"95% Confidence Interval for the difference of means: ({ci_lower}, {ci_upper})")
import scipy.stats as stats
import math

n1, n2 = 50, 50
p1, p2 = 0.44, 0.50
x1, x2 = p1 * n1, p2 * n2
alpha = 0.05

P = (x1 + x2) / (n1 + n2)

se = math.sqrt(P * (1 - P) * (1/n1 + 1/n2))

z_stat = (p1 - p2) / se

p_value = stats.norm.cdf(z_stat)

z_critical = stats.norm.ppf(1 - alpha/2)
ci_lower = (p1 - p2) - z_critical * math.sqrt((p1 * (1 - p1) / n1) + (p2 * (1 - p2) / n2))
ci_upper = (p1 - p2) + z_critical * math.sqrt((p1 * (1 - p1) / n1) + (p2 * (1 - p2) / n2))

print(f"Test Statistic (z): {z_stat}")
print(f"P-value: {p_value}")

if p_value < alpha:
    print("Reject the null hypothesis: The first population has significantly fewer smokers.")
else:
    print("Fail to reject the null hypothesis: There is no significant difference in smokers.")

print(f"95% Confidence Interval for the difference of proportions: ({ci_lower:.4f}, {ci_upper:.4f})")
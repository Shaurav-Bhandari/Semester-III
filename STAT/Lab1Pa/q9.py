import numpy as np
import pandas as pd

population_size = 5000
genders = np.random.choice(['Male', 'Female'], size = population_size)
heights = np.random.uniform(120, 185, size = population_size)
data = pd.DataFrame({
    'Gender': genders,
    'Height': heights
})

z = 1.96
p = 0.5
q = 1- p
d = 0.05
sample_size = int((z**2 * p * (1 - p)) / d**2)
sample = data.sample(n = sample_size)

from statsmodels.stats.proportion import proportions_ztest
number_of_males = sample['Gender'].value_counts()['Male']
number_of_females = sample['Gender'].value_counts()['Female']

total_sample = number_of_females + number_of_males
z_stat, p_value = proportions_ztest([number_of_males, number_of_females], [number_of_males, number_of_females])

from scipy.stats import ttest_ind
male_heights = sample[sample['Gender'] == 'Male']['Height']
female_heights = sample[sample['Gender'] == 'Female']['Height']
t_stat, p_value = ttest_ind(male_heights, female_heights)
print(f"T-statistic: {t_stat}")
print(f"p-value: {p_value}")
if p <= 0.05:
    print("Reject the null hypothesis")
else:
    print("Fail to reject the null hypothesis")

sample_500 = data.sample(n = 500)
male_heights_small = sample_500[sample_500['Gender'] == 'Male']['Height']
female_heights_small = sample_500[sample_500['Gender'] == 'Female']['Height']

t_stat, p_value = ttest_ind(male_heights, female_heights)

print(f"T-statistic: {t_stat}")
print(f"p-value: {p_value}")

if p <= 0.05:
    print("Reject the null hypothesis")
else:
    print("Fail to reject the null hypothesis")

from statsmodels.stats.proportion import proportion_confint
from statsmodels.stats.weightstats import DescrStatsW
number_of_males = sample['Gender'].value_counts()['Male']
number_of_females = sample['Gender'].value_counts()['Female']
ci_proportion = proportion_confint(number_of_males, number_of_females)
print(f"Confidence interval: {ci_proportion}")

male_count = sample['Gender'].value_counts()['Male']
ci_gender = proportion_confint(male_count, sample_size, alpha=0.05, method='normal')
print(f"95% Confidence Interval for Gender Proportion: {ci_gender}")

male_stats = DescrStatsW(male_heights)
female_stats = DescrStatsW(female_heights)

ci_diff = male_stats.tconfint_mean(alpha=0.05)
print(f"95% Confidence Interval for Male Height: {ci_diff}")
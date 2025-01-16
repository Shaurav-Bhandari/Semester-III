# Install and load required packages
if (!require("tseries")) install.packages("tseries") # For the run test
library(tseries)

# Data: Outcomes from tossing a coin 30 times
outcomes <- c("Head", "Head", "Tail", "Head", "Tail", "Head", "Head", "Tail",
              "Tail", "Head", "Tail", "Head", "Head", "Tail", "Tail", "Head",
              "Head", "Head", "Tail", "Head", "Tail", "Head", "Head", "Tail",
              "Tail", "Head", "Tail", "Tail", "Tail", "Head")

# Convert outcomes to a binary numeric sequence: Head = 1, Tail = 0
binary_outcomes <- ifelse(outcomes == "Head", 1, 0)

# (i) Test for Randomness using Run Test
run_test_result <- runs.test(binary_outcomes, alternative = "two.sided")
print("Run Test for Randomness:")
print(run_test_result)

# (ii) Test for Unbiased Coin using Proportion Test
# Count the number of heads and total trials
num_heads <- sum(binary_outcomes)
num_trials <- length(binary_outcomes)

# Perform a binomial test
binom_test_result <- binom.test(num_heads, num_trials, p = 0.5, alternative = "two.sided", conf.level = 0.99)
print("Binomial Test for Unbiased Coin:")
print(binom_test_result)

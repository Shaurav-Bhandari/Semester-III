# Data entry
# The data is organized by pairs: brand followed by operating time
brands <- c("A", "H", "D", "L", "L", "A", "H", "D", "H", "D", "L", "A", "D", "L", "A", "H")
hours <- c(4.2, 4.8, 4.2, 6.2, 4.6, 5.9, 4.8, 5.2, 5.4, 5.6, 5.6, 4.8, 4.1, 5.7, 4.2, 4.3)

# Create a data frame
laptop_data <- data.frame(
  brand = brands,
  operating_time = hours
)

# Replace abbreviations with full brand names for clarity
laptop_data$brand_name <- factor(laptop_data$brand, 
                               levels = c("A", "H", "D", "L"),
                               labels = c("Acer", "HP", "Dell", "Lenovo"))

# Summary statistics by brand
cat("Summary Statistics by Brand:\n")
summary_stats <- aggregate(operating_time ~ brand_name, data = laptop_data, 
                          FUN = function(x) c(count = length(x), 
                                             mean = mean(x), 
                                             sd = sd(x), 
                                             min = min(x), 
                                             max = max(x)))
print(summary_stats)

# Calculate overall statistics
cat("\nOverall Statistics:\n")
overall_mean <- mean(laptop_data$operating_time)
overall_sd <- sd(laptop_data$operating_time)
cat("Overall Mean:", overall_mean, "\n")
cat("Overall Standard Deviation:", overall_sd, "\n")

# Create boxplot for visual comparison
boxplot(operating_time ~ brand_name, data = laptop_data, 
        main = "Operating Time Comparison by Laptop Brand",
        xlab = "Laptop Brand", ylab = "Operating Time (hours)",
        col = c("lightblue", "lightgreen", "lightpink", "lightyellow"))
abline(h = overall_mean, col = "red", lwd = 2, lty = 2)
text(0.5, overall_mean + 0.1, "Overall Mean", col = "red")

# Check for normality assumption
# Shapiro-Wilk test for each group
cat("\nNormality Tests by Brand:\n")
for (brand in levels(laptop_data$brand_name)) {
  subset_data <- laptop_data$operating_time[laptop_data$brand_name == brand]
  if(length(subset_data) >= 3) {  # Shapiro-Wilk test requires at least 3 observations
    shapiro_result <- shapiro.test(subset_data)
    cat(brand, "- Shapiro-Wilk p-value:", shapiro_result$p.value, 
        ifelse(shapiro_result$p.value > 0.05, "(Normal)", "(Non-normal)"), "\n")
  } else {
    cat(brand, "- Not enough data for Shapiro-Wilk test\n")
  }
}

# Check for overall normality
cat("\nOverall Normality Test:\n")
shapiro_overall <- shapiro.test(laptop_data$operating_time)
print(shapiro_overall)

# Check for homogeneity of variances
cat("\nTest for Homogeneity of Variances:\n")
bartlett_result <- bartlett.test(operating_time ~ brand_name, data = laptop_data)
print(bartlett_result)

# Perform one-way ANOVA at 5% significance level
cat("\nANOVA Results:\n")
anova_result <- aov(operating_time ~ brand_name, data = laptop_data)
anova_summary <- summary(anova_result)
print(anova_summary)

# Compare with the critical F-value at 5% significance level
alpha <- 0.05
df1 <- length(levels(laptop_data$brand_name)) - 1
df2 <- nrow(laptop_data) - length(levels(laptop_data$brand_name))
critical_f <- qf(1 - alpha, df1, df2)
cat("\nCritical F-value at 5% significance level with df1 =", df1, "and df2 =", df2, "is", critical_f, "\n")

# Check if the F-statistic exceeds the critical value
f_statistic <- anova_summary[[1]]["F value"][[1]][1]
p_value <- anova_summary[[1]]["Pr(>F)"][[1]][1]
cat("F-statistic from ANOVA:", f_statistic, "\n")
cat("p-value:", p_value, "\n")

# Decision based on p-value
cat("\nHypothesis Test (α = 0.05):\n")
cat("H₀: All brands have equal mean operating times (μA = μH = μD = μL)\n")
cat("H₁: At least one brand has a different mean operating time\n\n")

if (p_value < alpha) {
  cat("Decision: Reject H₀ (p-value =", p_value, "< α = 0.05)\n")
  cat("Conclusion: There are significant differences in mean operating times between at least two laptop brands at the 5% significance level.\n\n")
  
  # Perform post-hoc Tukey HSD test to identify which groups differ
  cat("Post-hoc Tukey HSD Test (95% Confidence Intervals):\n")
  tukey_result <- TukeyHSD(anova_result, conf.level = 0.95)
  print(tukey_result)
  
  # Plot the Tukey HSD results
  plot(tukey_result, las = 1)
} else {
  cat("Decision: Fail to reject H₀ (p-value =", p_value, "> α = 0.05)\n")
  cat("Conclusion: There is insufficient evidence to conclude that the mean operating times differ between laptop brands at the 5% significance level.\n")
}

# Calculate means and create a means plot
library(ggplot2)
means <- aggregate(operating_time ~ brand_name, data = laptop_data, FUN = mean)
ci <- aggregate(operating_time ~ brand_name, data = laptop_data, 
               FUN = function(x) {
                 se <- sd(x)/sqrt(length(x))
                 return(c(mean = mean(x), 
                         lower = mean(x) - qt(0.975, length(x) - 1) * se,
                         upper = mean(x) + qt(0.975, length(x) - 1) * se))
               })

means_plot <- ggplot(means, aes(x = brand_name, y = operating_time, fill = brand_name)) +
  geom_bar(stat = "identity", width = 0.7) +
  geom_errorbar(aes(ymin = ci$operating_time[,2], ymax = ci$operating_time[,3]), width = 0.2) +
  labs(title = "Mean Operating Times with 95% Confidence Intervals",
       x = "Laptop Brand", y = "Mean Operating Time (hours)") +
  theme_minimal() +
  theme(legend.position = "none")
print(means_plot)

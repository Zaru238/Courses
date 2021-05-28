import math

import numpy as np
import matplotlib.pyplot as plt

# First exercise
def f(x: float):
    return np.cos(x) * np.exp(x)


# Second exercise
x = np.linspace(-2 * np.pi, 2 * np.pi)
y = f(x)

plt.plot(x, y)
plt.savefig("data_plot.pdf", bbox_inches='tight')
plt.clf()

# Third exercise
np.random.seed(42)
normal_distribution = np.random.normal(5, 2, 100000)
uniform_distribution = np.random.uniform(0, 10, 100000)

print("Normal destribution mean is {} and standard deviation is {}".format(
        np.mean(normal_distribution), np.std(normal_distribution)))
print("Uniform destribution mean is {} and standard deviation is {}".format(
        np.mean(uniform_distribution), np.std(uniform_distribution)))

plt.title("Normal distribution_histogram")
plt.hist(normal_distribution, bins=100)
plt.show()
plt.clf()

plt.title("Uniform distribution_histogram")
plt.hist(uniform_distribution, bins=100)
plt.show()
plt.clf()

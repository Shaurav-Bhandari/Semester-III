import numpy as np
import matplotlib.pyplot as plt

def random_walk(steps=1000):
    x, y, z = [0], [0], [0]
    
    for i in range(steps):
        # choose axes
        num_axes = np.random.choice([1, 2, 3])
        axes = np.random.choice(["x", "y", "z"], size=num_axes, replace=False)
        
        # apply random steps
        dx = np.random.choice([-1, 1]) if "x" in axes else 0
        dy = np.random.choice([-1, 1]) if "y" in axes else 0
        dz = np.random.choice([-1, 1]) if "z" in axes else 0
        
        # update positions
        x.append(x[-1] + dx)
        y.append(y[-1] + dy)
        z.append(z[-1] + dz)
    
    return x, y, z

x, y, z = random_walk(1000)

fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')
ax.plot(x, y, z, label="Drunk Man", color="b")

ax.set_title("Drunk Man Walk")
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")

plt.savefig("random-walk.png")
plt.show()

def average_distance(x, y, z):
    distances = []
    
    for a, b, c in zip(x, y, z):
        distance = np.sqrt(a ** 2 + b ** 2 + c ** 2)
        distances.append(distance)
    return sum(distances) / len(distances)

print(average_distance(x, y, z))

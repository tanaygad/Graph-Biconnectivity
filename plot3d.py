import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.interpolate import griddata

# Generate some sample data
X = [9,30,50,70,99,300,500,700,999,3000,5000,7000,9999,30000,50000,70000,99999,300000,500000,700000]
Y = [9,30,50,70,99,300,500,700,999,3000,5000,7000,9999,30000,50000,70000,99999,300000,500000,700000]

np.random.seed(0)

x1 = np.random.rand(20) * 20
y1 = np.random.rand(20) * 20
for i in range(20):
    y1[i] = float(Y[i])
    x1[i] = float(X[i])    
z1 = np.random.rand(20) * 20
# print(x1)
# print(z1)

x2 = np.random.rand(20) * 20
y2 = np.random.rand(20) * 20
z2 = np.random.rand(20) * 20

# Create a regular grid
xi = np.linspace(min(x1.min(), x2.min()), max(x1.max(), x2.max()), 100)
yi = np.linspace(min(y1.min(), y2.min()), max(y1.max(), y2.max()), 100)
xi, yi = np.meshgrid(xi, yi)

# Interpolate z values on the grid for first set of points
zi1 = griddata((x1, y1), z1, (xi, yi), method='linear')

# Interpolate z values on the grid for second set of points
zi2 = griddata((x2, y2), z2, (xi, yi), method='linear')

# Plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot first set of scattered points and surface plot
ax.scatter(x1, y1, z1, c='r', marker='o')
ax.plot_surface(xi, yi, zi1, color='r', alpha=0.5)

# Plot second set of scattered points and surface plot
ax.scatter(x2, y2, z2, c='b', marker='^')
ax.plot_surface(xi, yi, zi2, color='b', alpha=0.5)

ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.show()

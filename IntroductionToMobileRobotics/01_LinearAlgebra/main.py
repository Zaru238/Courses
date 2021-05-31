import math

import numpy as np
import matplotlib.pyplot as plt

def make_tranformation_matrix(x, y, theta):
    return np.array([[np.cos(theta), -np.sin(theta), x],
                    [np.sin(theta), np.cos(theta), y],
                    [0, 0, 1]])

scan = np.loadtxt('laserscan.dat')
angle = np.linspace(-math.pi/2, math.pi/2, scan.shape[0], endpoint='true')

points_finder = np.array([np.cos(angle) * scan, np.sin(angle) * scan, np.ones(scan.shape[0])])

laser_2_robot_transform = make_tranformation_matrix(0.2, 0.0, np.pi)
robot_2_local_transform = make_tranformation_matrix(1, 0.5, np.pi/4)
laser_2_local_transform = robot_2_local_transform.dot(laser_2_robot_transform)

# draw scan points
points_local = laser_2_local_transform.dot(points_finder)
plt.plot(points_local[0], points_local[1],'.k')

#draw laser location in green
laser_local = laser_2_local_transform.dot(([0, 0, 1]))
laser_local_delta = laser_2_local_transform.dot(([0.5, 0, 1])) - laser_local
plt.plot(laser_local[0], laser_local[1],'o', markersize = 3, color='green')
plt.arrow(laser_local[0], laser_local[1],
        laser_local_delta[0], laser_local_delta[1], color = 'green', width = 0.03)

#draw robot location in red
robot_local = robot_2_local_transform.dot([0, 0, 1])
robot_local_delta = robot_2_local_transform.dot([0.5, 0, 1]) - robot_local
plt.plot(robot_local[0], robot_local[1],'o', markersize = 3, color='red')
plt.arrow(robot_local[0], robot_local[1],
        robot_local_delta[0], robot_local_delta[1], color = 'red', width = 0.03)

plt.gca().set_aspect('equal', adjustable='box')
plt.show()

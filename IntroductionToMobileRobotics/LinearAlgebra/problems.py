import numpy as np

# 1.C
def is_orthogonal(mat):
    width = mat.shape[0]
    return np.array_equal(mat.dot(mat.T),np.identity(width))

orthogonal = np.identity(4)
non_orthogonal = np.array(((1, 1), (1,0)))

print("Orthogonal", is_orthogonal(orthogonal))
print("Non-orthogonal", is_orthogonal(non_orthogonal))

# 1.D
problem_matrix = 1/3 * np.array(((2, 2, -1),
                                 (2, -1, 2),
                                 (-1, 2, 2)))

print("Does matrix from exercise is orthogonal ", is_orthogonal(problem_matrix))

#2

def compose_transform(coords, theta):
    x, y = coords
    theta_rad = np.radians(theta)
    return np.array(((np.cos((theta_rad)), -np.sin(theta_rad), x),
                     (np.sin(theta_rad), np.cos(theta_rad), y),
                     (0 ,0, 1)))

def compose_transform_inverse(coords, theta):
    x, y = coords
    theta_rad = np.radians(theta)
    rotation = np.array(((np.cos(theta_rad), -np.sin(theta_rad)),
                         (np.sin(theta_rad), np.cos(theta_rad))))

    answer = np.c_[rotation.T, -rotation.dot((-x, -y))]
    answer = np.r_[answer, np.array((0, 0, 1)).reshape(1, 3)]

    return answer



robot_frame = ((4, 2), 90)

# label_robot_frame = (2, 2, 1)

# robot2world = compose_transform(*robot_frame)

# label_world = robot2world.dot(label_robot_frame)

# print(label_world)


label_world = (2, 4, 1)

world2robot = compose_transform_inverse(*robot_frame)

label_robot = world2robot.dot(label_world)

print(label_robot)

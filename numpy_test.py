import numpy as np

# a = np.array([1, 2, 3])
# print(type(a))
# print(a.shape)
# print(a[0], a[1], a[2])
# a[0] = 5
# print(a)

# b = np.array([[1,2,3],[4,5,6]])
# print(b.shape)
# print(b[0,0],b[0,1],b[1,0])
# print(b)

# a = np.zeros((2,2))
# print(a)

# b = np.ones((1,2))
# print(b)

# c = np.full((2,2), 7)
# print(c)

# d = np.eye(2)
# print(d)

# e = np.random.random((2,2))
# print(e)

a = np.array([[1,2,3,4],[5,6,7,8],[9,10,11,12]])

# array starts index at 0
row_r1 = a[1, :]
row_r2 = a[1:2, :]
print(row_r1, row_r1.shape)
print(row_r2, row_r2.shape)

col_r1 = a[:, 1]
col_r2 = a[:, 1:2]
print(col_r1, col_r1.shape)
print(col_r2, col_r2.shape)


from autograd import grad
from autograd import jacobian
import autograd.numpy as np
#import numpy as np

def test1(x):
    G = np.array([[21,4],[4,15]])
    b = np.array([2,3])
    return 1/2 * np.dot(np.dot(G,x),x) + np.dot(b,x) + 10

def sigmoid(x):
    return 0.5*(np.tanh(x) + 1)

def test0(x):
    return (x + 1) ** 2

def watson(x, i):
    if i == 30:
        return x[0]
    if i == 31:
        return x[1] - x[0] * x[0] - 1

    n = x.size
    t = lambda x: x/29
    sum1 = sum2 = 0

    # since python is indexed from 0, so j is equivalent to j + 1 as index, starting index 1, means starting from 2
    for j in range(1, n):
        sum1 = j * x[j] * pow(t(i), j-1) + sum1

    for j in range(n):
        sum2 = x[j] * pow(t(i), j) + sum2

    return (sum1 - sum2 * sum2 - 1)

def sum_sq_watson(x):
    m = 31
    sum = 0
    for i in range(m):
        temp = watson(x, i)
        sum = temp * temp + sum

    return sum

# x = np.array([1.,2.])
# print(test1(x))

# grad_sigmoid = grad(test1)
# print(grad_sigmoid(x))

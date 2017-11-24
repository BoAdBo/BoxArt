from autograd import grad
from autograd import jacobian
import autograd.numpy as np
import math
from functools import reduce
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
    # m should be 32 since it end in
    m = 32
    sum = 0
    for i in range(1, m):
        temp = watson(x, i)
        sum = temp * temp + sum

    return sum

# x = np.array([1.,2.])
# print(test1(x))

# grad_sigmoid = grad(test1)
# print(grad_sigmoid(x))


# The follow functions are for homework assignment for constraint optimization
# Behold, the goodness of lambda revealed!

class assignment_test1():
    '''simple class for a collection of function and constraints of assigmnet_test1
    Two dimension
    one equality constraint'''

    def f(x):
        # There is something curious about using math.log here, can only be used as numpy.log or np.log, limitation of autograd
        result = np.log(1 + x[0] * x[0]) - x[1]
        return result

    def equality_con():
        # equality constraint
        c = list()
        c.append(
            lambda x: (1 + x[0] * x[0]) * (1 + x[0] * x[0]) + x[1] * x[1] - 4
        )
        return c

    def inequality_con():
        # empty set of inequality
        return list()

class assignment_test2():
    ''' simple class for a collection of function and constraints of assigmnet_test1
    Three dimension, one equality constraint and 6 inequality constraint'''

    def f(x):
        return ((x[0] - 1) * (x[0] - 1)
                + (x[0] - x[1]) * (x[0] - x[1])
                + (x[1] - x[2]) ** 4)

    def equality_con():
        c = list()

        c.append(
            lambda x: x[0] * (1 + x[1] * x[1]) + x[2] ** 4 - 4 - 3 * (2 ** (0.5))
        )

        return c

    def inequality_con():
        # It can only accept x as numpy.ndarray
        c = list()

        n = 3

        i = list(range(n))

        return list(map(lambda i : lambda x: x[i] + 10, i)) + list(map(lambda i : lambda x: 10 - x[i], i))

        # for i in range(n):
        #     c.append(lambda x: x[i] + 10)
        #     c.append(lambda x: 10 - x[i])

        # return c

class assignment_test3():
    # some magic in here my dear
    def f(x):
        return x[0] * x[3] * (x[0] + x[1] + x[2]) + x[2]

    def equality_con():
        c = list()

        c.append(
            lambda x: sum(map(lambda x: x **2, x)) - 40
        )

        return c

    def inequality_con():
        c = list()

        c.append(
            lambda x: reduce(lambda x, y: x*y, x) - 25
        )

        #i = list(range(4))
        #lambda x: x[i] - 1

        # for i in range(4):
        #     c.append(lambda x: x[i] - 1)
        #     c.append(lambda x: 5 - x[i])

        # using carry and map, this is just amazing
        return c + list(map(lambda i: lambda x: x[i] - 1, list(range(4)))) + list(map(lambda i: lambda x: 5 - x[i], list(range(4))))

#f = assignment_test3.inequality_con()



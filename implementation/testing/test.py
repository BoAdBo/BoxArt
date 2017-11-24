from autograd import grad
import numpy as np

# testing non-continuous functions
def test1(x):
    if x > 0:
        return 1.
    else:
        return -1.

def test2(x):
    return x

def test3(x):
    if x < 0:
        return x*x
    else:
        return 0.0

def test4(x):
    return abs(x) - x

g = grad(test3)




import numpy as np
import test_fun
from autograd import grad
# note that these methods all assume a single down curved function


# back or forth to get the initial interval
# Something interesting is that if the given x, is the extreme point(or really close to it), then we need the gamma to be really small in order to reduce error
# In this sense, we keep the alpha low as start, if we want more accurate interval
# And gamma should start out small as well, otherwise, we wouldn't cover the interval, given we might switch to the wrong direction when near the extreme point
def back_forth(f, d, x, alpha, gamma):
    # alpha should be non-negative

    alpha_next = alpha + gamma
    # determine the direction
    if f(x + alpha_next * d) > f(x + alpha * d):
        gamma = - gamma
        # recompute the alpha_next
        alpha_next = alpha + gamma

    while f(x + alpha_next * d) < f(x + alpha * d):
        alpha = alpha_next
        gamma = 2 * gamma  # the constant 2 here shorten the iteration, by increase length
        alpha_next = alpha + gamma

    # found the interval, return it
    return min(alpha_next, alpha), max(alpha_next, alpha)

# note that this method won't work on functions like 1/x which has no extreme point
def search_618(f, d, x, left, right, epsilon):
    # divide the interval into 2 overlapping parts
    if right - left < epsilon:
        return (left + right) / 2
    else:
        tau = 0.618
        a_left = left + (1 - tau) * (right - left)
        a_right = left + tau * (right - left)
        if f(x + a_left * d) > f(x + a_right * d):
            return search_618(f, d, x, a_left, right, epsilon)
        else:
            return search_618(f, d, x, left, a_right, epsilon)

def exact_line_search(f, d, x, epsilon):
    interval = back_forth(f, d, x, epsilon, epsilon)
    return search_618(f, d, x, *interval, epsilon)

# x = -1.
# f = test_fun.test0
# d = - grad(test_fun.test0)(x)
# a = back_forth(f, d, x, 0.0001, 2)
# print(d)
# print(a)
# print(search_618(f, d, x, *a, 0.0001))

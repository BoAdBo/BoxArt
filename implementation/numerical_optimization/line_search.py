import numpy as np
import test_fun
from autograd import grad
from profilehooks import coverage
# note that these methods all assume a single down curved function


# back or forth to get the initial interval
# Something interesting is that if the given x, is the extreme point(or really close to it), then we need the gamma to be really small in order to reduce error
# In this sense, we keep the alpha low as start, if we want more accurate interval
# And gamma should start out small as well, otherwise, we wouldn't cover the interval, given we might switch to the wrong direction when near the extreme point

EPSILON = 10 ** (-10)


# Let initial alpha be relatively large, to avoid the interval being to small, and result in slow iteration, gamma be small, to not miss the extreme point
def back_forth(f, d, x, alpha = 1, gamma = EPSILON):
    # alpha should be non-negative

    alpha_next = alpha + gamma
    # determine the direction
    if f(x + alpha_next * d) > f(x + alpha * d):
        gamma = - gamma
        # recompute the alpha_next
        alpha_next = alpha + gamma

    while f(x + alpha_next * d) < f(x + alpha * d) and (alpha_next > 0):
        alpha = alpha_next
        gamma = 2 * gamma  # the constant 2 here shorten the iteration, by increase length
        alpha_next = alpha + gamma

    # being negative is not necessary a descent direction, prevent this situation, in such cases, it means approaching the extreme point in low gamma

    if alpha_next < 0:
        alpha_next = 0

    # found the interval, return it
    return min(alpha_next, alpha), max(alpha_next, alpha)

# note that this method won't work on functions like 1/x which has no extreme point
def search_618(f, d, x, left, right, epsilon = EPSILON):
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

def exact_line_search(f, d, x, epsilon = EPSILON):
    interval = back_forth(f, d, x)
    return search_618(f, d, x, *interval, epsilon)

def armijo(f, gk, d, x, alpha = 1, rho = 0.25):
    # alpha starts out not small
    # construct a one variable second degree interpolation function in the form ax^2 + bx + c
    # this only works when f(x + alpha * d) = lambda(alpha), lambda: alpha => y, function lambda one variable function is close to second degree
    # as a matter of fact it performed very well in practice

    # If alpha is too little, return
    temp1 = f(x)
    temp2 = np.dot(gk, d) # no need to recompute these two
    # temp2, when  this is too small, very difficult
    # The SR1 method gave the d as inf

    b = temp2
    c = temp1

    temp3 = f(x + alpha * d)
    armijo_cond = temp3 > temp1 + rho * temp2 * alpha # to keep going

    while armijo_cond:

        a = (temp3 - temp1 - temp2 * alpha) / alpha / alpha
        alpha = - b / (2 * a)

        temp3 = f(x + alpha * d)
        armijo_cond = temp3 > temp1 + rho * temp2 * alpha


    # to avoid g(x + delta) too close to g(x) resulting zero, now just added a condition
    # can add some down limit constraint here, to avoid the method converging too early or iteration is too slow, depends on the problem
    # it's possible that alpha becomes negative, causing the next f could be higher, fix by the following
    if alpha < 10**(-10):
        print("alpha_1: ", alpha)
        return 0.1
    elif alpha < 10**(-5):
        print("alpha_2: ", alpha)
        return 0.001

    return alpha


    # when satisfied Armijo condition


# def wolfe(valf, direction, max_iter):
#     (alpha, beta, step, c1, c2) = (0, 1000, 5.0, 0.15, 0.3)
#     i = 0
#     stop_iter = 0
#     stop_val = valf
#     minima = 0
#     val = []
#     objectf = []
#     val.append(valf)
#     objectf.append(func(valf))
#     while i <= max_iter:
#         # first confition
#         leftf = func(valf + step*direction)
#         rightf = func(valf) + c1*dfunc(valf).dot(direction)
#         if leftf > rightf:
#             beta = step
#             step = .5*(alpha + beta)
#             val.append(valf+step*direction)
#             objectf.append(leftf)
#         elif dfunc(valf + step*direction).dot(direction) < c2*dfunc(valf).dot(direction):
#             alpha = step
#             if beta > 100:
#                 step = 2*alpha
#             else:
#                 step = .5*(alpha + beta)
#             val.append(valf+step*direction)
#             objectf.append(leftf)
#         else:
#             val.append(valf+step*direction)
#             objectf.append(leftf)
#             break
#         i += 1
#         stop_val = valf + step*direction
#         stop_iter = i
#         minima = func(stop_val)
#     print(val, objectf)
#     return stop_val, minima, stop_iter, step, val, objectf

# x = -1.
# f = test_fun.test0
# d = - grad(test_fun.test0)(x)
# a = back_forth(f, d, x, 0.0001, 2)
# print(d)
# print(a)
# print(search_618(f, d, x, *a, 0.0001))

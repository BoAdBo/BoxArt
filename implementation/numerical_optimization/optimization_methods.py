# -*- coding: utf-8 -*-
import sys
import numpy as np
from autograd import jacobian
from autograd import grad
import test_fun as fun
from numpy import linalg
from line_search import exact_line_search
from line_search import armijo
import time

EPSILON = 10 ** (-8)

# given that using grad is slow in actual. Give the option to provide self-calculated function g
def sgd(f, g, x, epsilon = EPSILON):
    d = 2 * epsilon

    while linalg.norm(-d) > epsilon:
        d = - g(x)
        alpha = exact_line_search(f, d, x)
        print(x, linalg.norm(-d))
        x = x + alpha * d

    return x


# newton method would require an extra G, not needing line_search
def naive_newton(f, g, G, x, alpha = 1, epsilon = EPSILON):
    g_x = 2 * epsilon

    while linalg.norm(g_x) > epsilon:
        g_x = g(x)
        G_x = G(x)
        d = - np.dot(linalg.inv(G(x)), g_x)
        print(x, linalg.norm(g_x))
        x = x + alpha * d

    return x

# damped_newton adding line_search for newton method
def damped_newton(f, g, G, x, epsilon = EPSILON):
    g_x = 2 * epsilon
    try:
        while linalg.norm(g_x) > epsilon:

            g_x = g(x)
            G_x = G(x)
            d = - np.dot(linalg.inv(G(x)), g_x)
            print(x, linalg.norm(g_x))
            alpha = exact_line_search(f, d, x)
            x = x + alpha * d

    except np.linalg.linalg.LinAlgError as err:
        if 'Singular matrix'in err.message:
            print('\n Singular matrix of G, cannot proceed with damped newton method')
        else:
            pass

    return x

def compound_newton(f, g, G, x, epsilon = EPSILON):
    g_x = 2 * epsilon
    # these parameters can change the world
    epsilon1 = 0.0000001
    epsilon2 = 0.0000001

    while linalg.norm(g_x) > epsilon:
        G_x = G(x)
        g_x = g(x)

        # find direction
        if linalg.cond(G_x) < 1/sys.float_info.epsilon: # matrix is not singular
            d = - np.dot(linalg.inv(G_x), g_x)
            if np.dot(g_x, d) > epsilon1 * linalg.norm(g_x) * linalg.norm(d): # xx < 0, causing g*d > 0
                d = -d
            elif abs(np.dot(g_x, d)) <= epsilon2 * linalg.norm(g_x) * linalg.norm(d):
                d = -g_x
        else:
            d = -g_x

        #print(d)
        print(x, linalg.norm(g_x))
        alpha = exact_line_search(f, d, x, 0.0001)
        print(alpha)
        x = x + alpha * d

    return x

def LM(f, g, G, x, epsilon):
    g_x = 2 * epsilon
    epsilon_v = 10 ** (-10) # getting it very small has great performance, since gradient descent is indeed slow, ineffective
    I = np.eye(np.size(x))

    while linalg.norm(g_x) > epsilon:
        G_x = G(x)
        v = epsilon_v

        G_temp = G_x + v * I
        g_x = g(x)

        while linalg.cond(G_temp) > 1 / sys.float_info.epsilon:
            v = 2 * v
            G_temp = G_x + v

        print("v: ",v)
        d = - np.dot(linalg.inv(G_temp), g_x)
        print(x, linalg.norm(g_x))
        alpha = exact_line_search(f, d, x, 0.0001)
        print(alpha)
        x = x + alpha * d

    return x

def SR1(f, g, x, epsilon):
    g_x = 2 * epsilon
    H_x = np.eye(np.size(x))

    while linalg.norm(g_x) > epsilon:
        g_x = g(x)
        d = - np.dot(H_x, g_x)

        alpha = exact_line_search(f, d, x, 0.0001)

        # save parameters
        s = alpha * d
        y = g(x + s) - g_x

        # compute next H_x and x

        temp = s - np.dot(H_x, y)
        print(x, linalg.norm(g_x))
        print(alpha)
        H_x = H_x + np.outer(temp, temp) / np.dot(temp, y)

        x = x + s
        g_x = y + g_x
    return x

def DFP(f, g, x, epsilon):
    g_x = 2 * epsilon
    H_x = np.eye(np.size(x))

    while linalg.norm(g_x) > epsilon:
        g_x = g(x)
        d = - np.dot(H_x, g_x)

        alpha = exact_line_search(f, d, x, 0.0001)

        #save parameters
        s = alpha * d
        y = g(x + s) - g_x

        #compute next H_x and x
        temp = np.dot(H_x, y)
        print(x, linalg.norm(g_x))
        #print(alpha)
        H_x = H_x + np.outer(s, s) / np.dot(s, y) - np.outer(temp, temp) / np.dot(np.dot(H_x, y), y)
        x = x + s
        g_x = y + g_x

    return x

def BFGS(f, g, x, epsilon):
    g_x = 2 * epsilon
    H_x = np.eye(np.size(x))

    while linalg.norm(g_x) > epsilon:
        g_x = g(x)
        d = - np.dot(H_x, g_x)

        alpha = exact_line_search(f, d, x, 0.0001)

        #save parameters
        s = alpha * d
        y = g(x + s) - g_x

        #compute next H_x and x, two approaches, pick the complex one for performance, after tested, I have to admit they performance difference is not big, even using less variable is faster some time. Anyway, strange.
        temp = np.dot(H_x, y)
        temp2 = (np.outer(s, temp) + np.outer(temp, s)) / np.dot(y, s)
        temp1 = (1 + np.dot(temp, y) / np.dot(y, s)) * (np.outer(s, s) / np.dot(y,s))

        #performance use more variable less recomputation
        # temp1 = np.dot(H_x, y)
        # temp2 = np.dot(y, s)
        # temp3 = np.outer(s, temp1)
        # delta1 = (1 + np.dot(temp1, y) / temp2) * (np.outer(s, s) / temp2)
        # delta2 = (temp3 + np.transpose(temp3)) / temp2

        print(x, linalg.norm(g_x))
        #print(alpha)
        H_x = H_x + temp1 - temp2
        #H_x = H_x + delta1 - delta2
        x = x + s
        g_x = y + g_x

    return x


#x = np.array([0.,0.,0.,0.,0.,0.,0.,0.,0.])
# x = np.zeros(31)
# #x = np.array([-30., 100.])
# f = fun.sum_sq_watson
# g = grad(f)
# G = jacobian(g)

# start = time.time()
# e = BFGS(f, g, x, epsilon = 0.00000001)
# print("This is the end: ", e)
# print(f(e))
# end = time.time()
#print(end-start)

# start = time.time()
# # newton method perform very well on quadratic function
#print("This is the end: ", naive_newton(fun.test1, grad(fun.test1), jacobian(grad(fun.test1)), np.array([-30.0, 100.]), 0.0001))
# end = time.time()
# print(end-start)

#x = np.array([0.,0.,0.,0.,0.,0.,0.,0.,0.])
#x = np.zeros(29)
#x = np.array([-30., 100.])
#f = fun.sum_sq_watson

#start = time.time()
#naive newton can't promise that every step f is descending
#print("This is the end: ", naive_newton(fun.sum_sq_watson, grad(fun.sum_sq_watson), jacobian(grad(fun.sum_sq_watson)), x, 0.0001))
#print("This is the end: ", damped_newton(fun.sum_sq_watson, grad(fun.sum_sq_watson), jacobian(grad(fun.sum_sq_watson)), x, 0.0001))
#e = compound_newton(fun.sum_sq_watson, grad(fun.sum_sq_watson), jacobian(grad(fun.sum_sq_watson)), x, 0.01)
#e = SR1(fun.sum_sq_watson, grad(fun.sum_sq_watson), x, 0.0001)
#e = BFGS(f, grad(f), x, 0.0001)
#e = SR1(fun.test1, grad(fun.test1), x, 0.001)
#print("This is the end: ", e)
#print("End game: ", fun.sum_sq_watson(e))
#gradient descent is incredibly slow in dealing with this function
#print("This is the end: ", sgd(fun.sum_sq_watson, grad(fun.sum_sq_watson), x, 0.0001))
#end = time.time()
#print(end-start)

#print(jacobian(grad(fun.sum_sq_watson))(x))

#x = np.array([-30.0,100.])

#print("This is the end: ", jacobian(grad(fun.test1))(x))

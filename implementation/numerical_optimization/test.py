#import numpy as np
import autograd.numpy as np
import optimization_methods as methods
from autograd import grad
from autograd import jacobian
from test_fun import assignment_test1
from optimization_methods import outer_penalty
from test_fun import assignment_test2
from test_fun import assignment_test3
# #x = np.array([0, 3**0.5])
# #print(assignment_test1.f(x))
# # equality_con when called, return a list of constraint functions
# CE = assignment_test1.equality_con()
# temp_f = assignment_test1.f
# temp_g = grad(temp_f)
# #temp_G = jacobian(temp_g)

# temp_cg = list()
# temp_cG = list()

# for c in CE:
#     temp_cg.append(grad(c))

# for cg in temp_cg:
#     temp_cG.append(jacobian(cg))
#     #print(temp_cG[0](np.array([1.,2.])))

# # construct penalty function
# # construct in equality

# def f(x, sigma):
#     penalty_sum = 0.
#     for c in CE:
#         penalty_sum = c(x) + penalty_sum

#     return temp_f(x) + 1/2 * sigma * penalty_sum * penalty_sum

# def g(x, sigma):
#     # have to decompose the equation for gradient, sigma is not input
#     g_penalty = 0.
#     for i in range(len(CE)):
#         g_penalty = CE[i](x) * temp_cg[i](x) + g_penalty

#     return temp_g(x) + sigma * g_penalty

# # def G(x, sigma):
# #     G_penalty = 0.
# #     for i in range(len(CE)):
# #         #G_penalty = CE[i](x) * temp_cG[i](x) + G_penalty, this is wrong here

# #     return temp_G(x) + sigma * G_penalty

# x = np.array([2.,2.])
# outer_penalty(f, g, G, CE, x)

# #=========================================================================================================
# # The above method has a hard time implementing G(Hesse matrix computation), finding another path
# # equality_con when called, return a list of constraint functions
# CE = assignment_test1.equality_con()

# square_CE = list()

# for c in CE:
#     square_CE.append(lambda x: 1/2 * c(x) ** 2)

# temp_f = assignment_test1.f
# temp_g = grad(temp_f)
# temp_G = jacobian(temp_g)

# temp_cg = list()
# temp_cG = list()

# #test = grad(square_CE[0])

# for c1 in square_CE:
#     temp_cg.append(grad(c1))

# for cg in temp_cg:
#     temp_cG.append(jacobian(cg))
#     #print(temp_cG[0](np.array([1.,2.])))

# def f(x, sigma):
#     penalty_sum = 0.
#     for c in square_CE:
#         penalty_sum = c(x) + penalty_sum

#     return temp_f(x) + sigma * penalty_sum
#     # for c in CE:
#     #     penalty_sum = c(x) + penalty_sum

#     # return temp_f(x) + 1/2 * sigma * penalty_sum * penalty_sum

# def g(x, sigma):
#     # have to decompose the equation for gradient, sigma is not input
#     g_penalty = 0.
#     for c in temp_cg:
#         g_penalty = c(x) + g_penalty

#     return temp_g(x) + sigma * g_penalty
#     # for i in range(len(CE)):
#     #     g_penalty = temp_cg[i](x) + g_penalty

# def G(x, sigma):
#     G_penalty = 0.
#     for c in temp_cG:
#         G_penalty = c(x) + G_penalty

#     #print(G_penalty)
#     return temp_G(x) + sigma * G_penalty


# x = np.array([-2.,2.])
# outer_penalty(f, g, G, CE, x)
# #=========================================================================================================

#=========================================================================================================
# Think of a way to generalize
# There is only one thing to be noted, is that sigma shouldn't be included in the gradient
# which means when we compute gradient, don't differentiate sigma

# compute the gradient as well as hesse, in two parts, one f and the sum of penalty functions
fun = assignment_test2

# equality penalty
def eq_pen(x):
    sum = 0.
    for c in fun.equality_con():
        sum = c(x) **2 + sum
    return sum

# inequality penalty
def in_pen(x):
    sum = 0.
    for c in fun.inequality_con():
        sum = min(c(x), 0) **2 + sum
    return sum

def pen(x):
    return eq_pen(x) + in_pen(x)

g_first = grad(fun.f)
G_first = jacobian(g_first)

g_second = grad(eq_pen)
G_second = jacobian(g_second)

g_third = grad(in_pen)
G_third = jacobian(g_third)

def f(x, sigma):
    return fun.f(x) + 0.5 * sigma * (eq_pen(x) + in_pen(x))

def g(x, sigma):
    return g_first(x) + 0.5 * sigma * (g_second(x) + g_third(x))

def G(x, sigma):
    return G_first(x) + 0.5 * sigma * (G_second(x) + G_third(x))

x = np.array([2., 2., 2.])
#x = np.array([1.,5.,5.,1.])
x = np.array([5000.,50000.,10000.])
e = outer_penalty(f, g, G, pen, x, 1, 10**(-8))
method = 'outer_penalty'
print("The optimal result given by %s: ", method, fun.f(e))
#=========================================================================================================








































#, epsilon=0.00001
# Need to implement methods on constraint problems now


# check the correctness of f, g, G(not good, but for most points, it's sufficient... I assume)

# test_g = lambda x:  ([ # x contains sigma at the last
    
# ])

# def test_g(x, sigma):
#     a = sigma * CE[0](x) * np.array([
#         4 *  x[0] * (1 + x[0] * x[0]),
#         2 * x[1]
#     ])
#     b = np.array([(2 * x[0]) / (1 + x[0] * x[0]), -1])

#     return a + b

# #4 * sigma * x[0] * ((1 + x[0] * x[0]) ** 3 + x[1] **2 + (x[0] * x[1]) ** 2 - 4 - 4 * x[0] **2)
# #((1 + x[0] **2) **2 + x[1] **2 - 4)
# test_g2 = lambda x: ([
#     2 * x[0] / (1 + x[0] * x[0]),
#     -1
# ])

# def test_correct(fun1, fun2):
#     # After testing we know that there some huge error when dealing with large i, large input, something is wrong, not necessary large input, but on specific input, consider it as bugs... undetermined
#     count = 0
#     for i in range(200, 250):
#         #i = i / 100.0
#         x = [i+0.,i+0.]
#         vx = np.array(x)
#         sigma = i
#         #a = fun1(x, sigma)
#         #b = fun2(vx, sigma)
#         a = fun1(vx, sigma)
#         b = fun2(vx, sigma)
#         if np.any(a != b):
#             a = np.array(a)
#             #a[0] = a[0] / 8192
#             #print(np.linalg.norm(a-b))
#             print(a[0]/10**1,b[0]/10**15)
#             count = count + 1
#             print("Something wrong: ", vx, sigma)

#     print(count)

# test_correct(test_g, g)

# # def testing_autograd(x):
# #     return np.log(1 + x * x)

# def testing_autograd(x):
#     return CE[0](x)

# testing_g = grad(testing_autograd)
# x = np.array([245.,245.])
# #a = testing_g(x)
# a = 245 * temp_cg[0](x) * CE[0](x)
# b = 245 * CE[0](x) * np.array([
#     4 * x[0] * (1 + x[0] * x[0]),
#     2 * x[1]
# ])


# #a = np.array(a)
# #b = np.array(b)
# #print(np.linalg.norm(a-b))
# print((a-b))
# print(a)
# print(b)



# # print(count)
# #print(f(vx, sigma))
# # comparing to hand computation

# #print(test_g(x))
# #print(g(vx, sigma))


# # implement it in another way, again using lambda here







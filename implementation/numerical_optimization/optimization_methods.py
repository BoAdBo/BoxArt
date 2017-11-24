from unconstrainted_methods import *

# The following implement the constrainted methods



# provide unconstrainted and constrained methods in one file
# With steepest gradient descent, it's good enough
def outer_penalty(f, g, G, pen, x, sigma = 1, epsilon=EPSILON):
    #print(EPSILON)
    #return
    epsilon1 = 0.01
    norm = 1

    while norm > epsilon:
        f_s = lambda x: f(x, sigma)
        g_s = lambda x: g(x, sigma)
        G_s = lambda x: G(x, sigma)
        #x = sgd(f_s, g_s, x, epsilon1)
        x = compound_newton(f_s, g_s, G_s, x, epsilon1)
        #x = LM(f_s, g_s, G_s, x, epsilon1)
        #x = SR1(f_s, g_s, x, epsilon1)
        #x = BFGS(f_s, g_s, x, epsilon1)
        #x = DFP(f_s, g_s, x, epsilon1)
        # norm = []
        # for c in CE:
        #     norm.append(c(x))

        # norm = np.linalg.norm(norm)
        norm = pen(x) ** 0.5
        print(norm)
        sigma = sigma*10

    return x

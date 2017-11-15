# this script aimed to test the overall performance of different newton method on sum square of watson function
# and output to a file, this is pretty hard, have to format the data very well and have to consider if there is enough space on the sever

import optimization_methods as me
from autograd import grad
from autograd import jacobian
import test_fun as fun
import numpy as np
import time
import cProfile, pstats, sys, signal, io
from profilehooks import coverage
from profilehooks import profile


temp_f = fun.sum_sq_watson
temp_g = grad(temp_f)
temp_G = jacobian(temp_g)
status_out = 'status_report'

def f(x):
    return temp_f(x)

def g(x):
    return temp_g(x)

def G(x):
    return temp_G(x)

def handler(signum, frame):
    print ('Signal handler called with signal', signum)
    

# function_name, output_file, info in string
def status_report(function_name, output_file, info):
    sys.stdout = sys.__stdout__
    print(output_file)
    sys.stdout = open(output_file, 'a')
    print(output_file, ":", info)

def test_newtons(function, function_name, start = 2, to = 31, epsilon = 10 ** (-4)):

    for i in range(start, to):
        x = np.zeros(i)

        current_out_proc = str(i) + function_name + '.proc'

        # this is where the information of iteration goes, the process
        sys.stdout = open(current_out_proc, 'w')

        pr = cProfile.Profile()
        pr.enable()

        e = function(f, g, G, x, epsilon)
        print("the end of the result: ", f(e))

        pr.disable()

        current_out_prof = str(i) + function_name + '.prof'

        # this is where the information of the profile goes
        sys.stdout = open(current_out_prof, 'w')

        # all methods return self, so you can string together commands, just like in ruby, very interesting
        pstats.Stats(pr).sort_stats('time').print_stats('testing_watson')

        info = '\n' + str(i)
        status_report(function_name, status_out, info)

    return 0

def test_quasi_newtons(function, function_name, start = 2, to = 31, epsilon = 10 ** (-4)):
    for i in range(start, to):
        x = np.zeros(i)

        current_out_proc = str(i) + function_name + '.proc'

        # this is where the information of iteration goes, the process
        sys.stdout = open(current_out_proc, 'w')

        pr = cProfile.Profile()
        pr.enable()

        e = function(f, g, x, epsilon)
        print("the end of the result: ", f(e))

        pr.disable()

        current_out_prof = str(i) + function_name + '.prof'

        # this is where the information of the profile goes
        sys.stdout = open(current_out_prof, 'w')

        # all methods return self, so you can string together commands, just like in ruby, very interesting
        pstats.Stats(pr).sort_stats('time').print_stats('testing_watson')

        sys.stdout = open('status_report', 'w')
        print(function_name, 'is done, proceeding!')

    return 0

start = 2
to = 32

# setting pretty relatively high epsilon for newtons

#test_quasi_newtons(me.SR1, 'SR1', start, to, 0.000001)
#test_quasi_newtons(me.DFP, 'DFP', start, to, 0.000001)
#test_quasi_newtons(me.BFGS, 'BFGS', start, to, 0.000001)

#test_newtons(me.naive_newton, 'naive_newton')
signal.signal(signal.SIGALRM, handler)
signal.alarm(1)
test_newtons(me.damped_newton, 'damped_newton', start, to)
test_newtons(me.compound_newton, 'compound_newton', start, to)
test_newtons(me.LM, 'LM', start, to)

signal.alarm(0)

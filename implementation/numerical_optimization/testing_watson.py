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
MAX_TIME = 2000

def f(x):
    return temp_f(x)

def g(x):
    return temp_g(x)

def G(x):
    return temp_G(x)

class OverTime(Exception):
    pass

def put_prof(profile, output_file):
    # this is where the information of the profile goes
    sys.stdout = open(output_file, 'w')

    # all methods return self, so you can string together commands, just like in ruby, very interesting
    pstats.Stats(profile).sort_stats('time').print_stats('testing_watson')# print_stats take argument and return function in testing_watson.py

    return 0


def handler(signum, frame):
    print('Sinal handler, already used time ' + str(MAX_TIME) + ' seconds; Signal number : ', signum, file = sys.__stdout__)
    raise OverTime

# function_name, output_file, info in string
# info should contain information of the interrupted optimization methods, how long
def status_report(output_file, info):
    print(output_file, " for ", info, file = open(output_file, 'a'))

def test_newtons(function, function_name, start = 2, to = 31, epsilon = 10 ** (-4)):

    for i in range(start, to):
        # declare here to allow except to access
        pr = cProfile.Profile()
        current_out_proc = str(i) + function_name + '.proc'
        current_out_prof = str(i) + function_name + '.prof'

        try:
            x = np.zeros(i)

            # this is where the information of iteration goes, the process
            sys.stdout = open(current_out_proc, 'w') # don't need to worry about time exception create loss of data, since it print out as process goes
            #sys.stdout = sys.__stdout__

            pr.enable()
            e = function(f, g, G, x, epsilon)
            print("the end of the result: ", f(e))
            pr.disable()

            put_prof(pr, current_out_prof)

            info = '\n' + str(i) + ' dimension for ' + function_name
            status_report(status_out, info)

        # reset the alarm in the exception
        except OverTime:

            info = ('\n' + str(i) + ' dimension for '
                         + function_name + ' is too slow for this problem. already used up its time '
                         + str(MAX_TIME) + '\n')

            status_report(status_out, info)
            #signal.alarm(MAX_TIME)
            put_prof(pr, current_out_prof)
            signal.setitimer(signal.ITIMER_REAL, MAX_TIME)


    return 0



def test_quasi_newtons(function, function_name, start = 2, to = 31, epsilon = 10 ** (-4)):
    for i in range(start, to):
        # declare here to allow except to access
        pr = cProfile.Profile()
        current_out_proc = str(i) + function_name + '.proc'
        current_out_prof = str(i) + function_name + '.prof'

        try:
            x = np.zeros(i)

            # this is where the information of iteration goes, the process
            sys.stdout = open(current_out_proc, 'w') # don't need to worry about time exception create loss of data, since it print out as process goes
            #sys.stdout = sys.__stdout__

            pr.enable()
            e = function(f, g, x, epsilon)
            print("the end of the result: ", f(e))
            pr.disable()

            put_prof(pr, current_out_prof)

            info = '\n' + str(i) + ' dimension for ' + function_name
            status_report(status_out, info)

        # reset the alarm in the exception
        except OverTime:

            info = ('\n' + str(i) + ' dimension for '
                         + function_name + ' is too slow for this problem. already used up its time '
                         + str(MAX_TIME) + '\n')

            status_report(status_out, info)
            #signal.alarm(MAX_TIME)
            put_prof(pr, current_out_prof)
            signal.setitimer(signal.ITIMER_REAL, MAX_TIME)

    return 0

start = 2
to = 32

# setting pretty relatively high epsilon for newtons

#test_quasi_newtons(me.SR1, 'SR1', start, to, 0.0000001)
#test_quasi_newtons(me.DFP, 'DFP', start, to, 0.000001)
#test_quasi_newtons(me.BFGS, 'BFGS', start, to, 0.000001)

#test_newtons(me.naive_newton, 'naive_newton')
signal.signal(signal.SIGALRM, handler)
signal.setitimer(signal.ITIMER_REAL, MAX_TIME)
test_newtons(me.damped_newton, 'damped_newton', start, to)
test_newtons(me.compound_newton, 'compound_newton', start, to)
test_newtons(me.LM, 'LM', start, to)
signal.alarm(0)

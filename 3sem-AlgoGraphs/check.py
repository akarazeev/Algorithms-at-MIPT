from subprocess import PIPE, Popen
import sys

import re

from os import listdir
from os.path import isfile, join

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def numeric_compare(x, y):
    x = re.findall('\d+', x)
    y = re.findall('\d+', y) 
    return int(x[0]) - int(y[0])

if __name__ == '__main__':

    if len(sys.argv) < 3:
	    print bcolors.FAIL + 'test test_file directory' + bcolors.ENDC

    dirname = sys.argv[2]

    dir_numb = {0, 7, 9, 3, 13, 4, 11, 2, 8}
    dir_numb = {0, 9}

    for i in dir_numb:
        print bcolors.UNDERLINE + 'Algorithm #' + str(i) + bcolors.ENDC
        files = [join(dirname,f) for f in listdir(dirname) if isfile(join(dirname, f))]

        tests = [join(dirname,str(i),'input',f) for f in listdir(join(dirname,str(i),'input')) \
                                                    if isfile(join(dirname, str(i), 'input', f)) and f[0] == 't']
        tests = sorted(tests, cmp=numeric_compare)

        answers = [join(dirname,str(i),'output',f) for f in listdir(join(dirname,str(i),'output')) \
                                                    if isfile(join(dirname, str(i), 'output', f)) and f[0] == 'a']
        answers = sorted(answers, cmp=numeric_compare)

        if len(answers) == 0 or len(tests) == 0:
           print bcolors.FAIL + 'Path to tests is not okay' + bcolors.ENDC

        if not len(answers) == len(tests):
            print bcolors.FAIL + 'Tests directory is not okay' + bcolors.ENDC

        target = sys.argv[1]

        tests_qty = len(tests)

        for f in tests:

            test = open(f).read()
            answer = open(answers[tests.index(f)]).read()

            instance = Popen(target, stdin = PIPE, stdout = PIPE, bufsize = 1)
            instance.stdin.write(str(i) + ' ' + test + '\n')
            instance_answer = instance.stdout.read()

            if instance_answer == answer:
                print '[' + bcolors.OKGREEN + 'PASSED' + bcolors.ENDC + ']' + ' Test #' + str(tests.index(f) + 1)
                tests_qty -= 1
            else:
                print '[' + bcolors.FAIL + 'FAILED' + bcolors.ENDC + ']' + ' Test #' + str(tests.index(f) + 1)
                print '---------------------------------------'
                print 'Test: ' + test
                print 'Expect: ' + answer
                print 'Output: ' + instance_answer
                print '---------------------------------------'

        print str(len(tests) - tests_qty) + '/' + str(len(tests))

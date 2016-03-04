#!/usr/bin/env python

import argparse
import itertools
import os
import shutil
import subprocess
import sys

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('commands', nargs='*', default='build', choices=['build', 'configure', 'clean', 'debug', 'release'])
    parser.add_argument('-f', '--force', action='store_true')
    parser.add_argument('--targets', nargs='*')
    parser.add_argument('--variant', default='debug', choices=['debug', 'release'])
    parser.add_argument('--notestprograms', action='store_const', const='ON', default='OFF')
    parser.add_argument('-o', '--out', default='build')
    parser.add_argument('-t', '--top', default=os.getcwd())
    args = parser.parse_args()

    if 'debug' in args.commands:
        args.commands = [x if x != 'debug' else 'build' for x in args.commands]
        args.variant = 'debug'
    elif 'release' in args.commands:
        args.commands = [x if x != 'release' else 'build' for x in args.commands]
        args.variant = 'release'

    args.out = os.path.abspath(os.path.join(args.out, args.variant.lower()))
    args.variant = args.variant.title()

    if args.targets:
        args.targets = list(itertools.chain.from_iterable([x.split(',') for x in args.targets]))

    if type(args.commands) != list:
        args.commands = [args.commands]

    return args


def configure(args):
    full = ['echo', 'cmake', '-G', 'Ninja',
                '-DCMAKE_BUILD_TYPE={}'.format(args.variant),
                '-DNOTESTPROGRAMS={}'.format(args.notestprograms),
                args.top]
    simple = ['echo', 'cmake', '.']

    try:
        os.makedirs(args.out)
    except OSError:
        pass

    if os.path.exists(os.path.join(args.out, 'CMakeCache.txt')):
        command = simple
    else:
        command = full

    subprocess.check_call(command, cwd=args.out)


def build(args):
    command = ['echo', 'ninja']
    if args.targets:
        command.extend(args.targets)
    if not os.path.exists(os.path.join(args.out,'CMakeCache.txt')):
        configure(args)

    subprocess.check_call(command, cwd=args.out)

def clean(args):
    command = 'echo ninja clean'.split()
    if os.path.exists(args.out):
        subprocess.check_call(command, cwd=args.out)

commands = {
    'configure': configure,
    'build': build,
    'clean': clean
}

if __name__ == '__main__':
    args = parse_args()
    #print args

    print 'in',args.out
    if args.force:
        try:
            os.remove(os.path.join(args.out, 'CMakeCache.txt'))
        except OSError:
            pass
        shutil.rmtree(os.path.join(args.out, 'CMakeFiles'), ignore_errors=True)


    for command in args.commands:
        commands[command](args)

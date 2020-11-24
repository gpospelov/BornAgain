#!/usr/bin/env python3
"""
Reads a BornAgain simulation script, and converts into normal form.

Export to normal form is done by BornAgain's ExportToPython function.
"""

import argparse
import bornagain as ba

def normalize_text(ti):
    c=compile(ti, fname, 'exec')
    ns = {}
    exec(c,ns)
    globals().update(ns)
    s = get_simulation()
    s.setSample(get_sample())
    return ba.generatePyExportTest(s)

def normalize_file(fname, inplace):
    with open(fname, 'rb') as f:
        ti = f.read()
    t = normalize_text(ti)
    if t == ti:
        print(f'Nothing changed in file {fname}')
        return
    t2 = normalize_text(t)
    if t2 != t:
        with open("out1.py", 'w') as f:
            f.write(t)
        with open("out2.py", 'w') as f:
            f.write(t2)
        exit("Script changes under second normalization, see files out1.py and out2.py")

    if inplace:
        with open(fname, 'w') as f:
            f.write(t)
    else:
        print(t)

if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument("simulation_script", type=str)
    parser.add_argument("-i", "--in-place", action="store_true")
    args = parser.parse_args()

    normalize_file(args.simulation_script, args.in_place)

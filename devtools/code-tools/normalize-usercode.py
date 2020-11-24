#!/usr/bin/env python3
"""
Reads a BornAgain simulation script, and converts into normal form.

Export to normal form is done by BornAgain's ExportToPython function.
"""

import argparse
import bornagain as ba

def normalize_script(fname, inplace):
    with open(fname, 'rb') as f:
        ti = f.read()
    c=compile(ti, fname, 'exec')
    ns = {}
    exec(c,ns)
    globals().update(ns)
    s = get_simulation()
    s.setSample(get_sample())
    t = ba.generatePyExportTest(s)
    if t == ti:
        print(f'Nothing changed in file {fname}')
        return
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

    normalize_script(args.simulation_script, args.in_place)

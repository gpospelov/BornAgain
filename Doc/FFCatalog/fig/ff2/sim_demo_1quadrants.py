#!/usr/bin/env python3
"""
Plot form factor.
"""
import bornagain as ba
from bornagain import nm, deg
import bornplot as bp

det = ba.SphericalDetector(200, 5*deg, 2.5*deg, 2.5*deg)
pars = [0, 5, 10, 20]
n = len(pars)
results = []
for i in range(n):
    theta = pars[i]
    title = r'$\vartheta=%d^\circ$' % theta
    ff = ba.FormFactorTruncatedSphere(4.2*nm, 6.1*nm, 0)
    trafo = ba.RotationY(theta*deg)
    data = bp.run_simulation(det, ff, trafo)
    results.append(bp.Result(i, data, title))

bp.make_plot(results, det, "ff_demo_1quadrants")

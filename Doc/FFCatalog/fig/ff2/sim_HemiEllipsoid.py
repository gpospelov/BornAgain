#!/usr/bin/env python3
"""
Plot form factor.
"""
import bornagain as ba
from bornagain import nm, deg
import bornplot as bp

det = ba.SphericalDetector(200, 5*deg, 2.5*deg, 2.5*deg)
n = 4
results = []
for i in range(n):
    omega = 90*i/(n - 1)
    title = r'$\omega=%d^\circ$' % omega
    ff = ba.FormFactorHemiEllipsoid(10*nm, 3.8*nm, 3.2*nm)
    trafo = ba.RotationZ(omega*deg)
    data = bp.run_simulation(det, ff, trafo)
    results.append(bp.Result(i, data, title))

bp.make_plot(results, det, "ff_HemiEllipsoid")

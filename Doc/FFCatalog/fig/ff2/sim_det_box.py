#!/usr/bin/env python3
"""
Plot form factors.
"""
import bornagain as ba
from bornagain import nm, deg
import bornplot as bp

det = ba.SphericalDetector(1000, 5*deg, 2.5*deg, 2.5*deg)
n = 3
results = []
for i in range(n):
    siz = [10, 100, 1000][i]
    title = r'$L_x = %d~nm$' % siz
    ff = ba.FormFactorBox(siz, 10, 10)
    data = bp.run_simulation(det, ff)
    results.append(bp.Result(i, data, title))

bp.make_plot(results, det, "ff_det_box")

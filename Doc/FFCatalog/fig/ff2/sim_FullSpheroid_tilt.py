"""
Plot form factor.
"""
import bornagain as ba
from   bornagain import nanometer, degree
import bornplot as bp

det = bp.Detector( 200, 0, 5, 0, 5 )
n    = 4
results = []
for i in range(n):
    theta=30*i/(n-1)
    title = r'$\vartheta=%d^\circ$' % theta
    ff = ba.FormFactorFullSpheroid(3*nanometer, 13*nanometer)
    trafo = ba.RotationY(theta*degree)
    data = bp.run_simulation(det,ff,trafo)
    results.append( bp.Result(i, data, title) )
    
bp.make_plot( results, det, "ff_FullSpheroid_tilt" )

"""
Plot form factors.
"""
import bornagain as ba
from   bornagain import nanometer, degree
import bornplot as bp

det = bp.Detector( 200, 0, 5, 0, 5 )
n    = 4
results = []
for i in range(n):
    omega=45*i/(n-1)
    title = r'$\omega=%d^\circ$' % omega
    ff = ba.FormFactorTruncatedCube(6.4*nanometer, 1.5*nanometer)
    trafo = ba.RotationZ(omega*degree)
    data = bp.run_simulation(det,ff,trafo)
    results.append( bp.Result(i, data, title) )
    
bp.make_plot( results, det, "ff_TruncatedCube" )

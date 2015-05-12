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
    omega=30*i/(n-1)
    title = r'$\omega=%d^\circ$' % omega
    ff = ba.FormFactorCone6(6*nanometer, 5*nanometer, 60*degree)
    trafo = ba.RotationZ(omega*degree)
    data = bp.run_simulation(det,ff,trafo)
    results.append( bp.Result(i, data, title) )
    
bp.make_plot( results, det, "ff_Cone6" )

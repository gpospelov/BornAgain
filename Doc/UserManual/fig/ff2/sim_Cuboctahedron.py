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
    ff = ba.FormFactorCuboctahedron(8*nanometer, 5*nanometer, 0.5, 60.0*degree)
    trafo = ba.RotationZ(omega*degree)
    data = bp.run_simulation(det,ff,trafo)
    results.append( bp.Result(i, data, title) )
    
bp.make_plot( results, det, "ff_Cuboctahedron" )

"""
Plot form factors.
"""
import bornagain as ba
from   bornagain import nanometer, degree
import bornplot as bp

det = bp.Detector( 200, -5, 5, -5, 5 )
n    = 3
results = []
for i in range(n):
    omega=36*i/(n-1)
    title = r'$\omega=%d^\circ$' % omega
    ff = ba.FormFactorDodecahedron(3.2*nanometer)
    trafo = ba.RotationZ(omega*degree)
    data = bp.run_simulation(det,ff,trafo)
    results.append( bp.Result(i, data, title) )
    
bp.make_plot( results, det, "ff_Dodecahedron" )

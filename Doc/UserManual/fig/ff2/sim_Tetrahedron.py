"""
Plot form factors.
"""
import bornagain as ba
from   bornagain import nanometer, degree
import bornplot as bp

det = bp.Detector( 200, -5, 5, -5, 5 )
n    = 4
results = []
for i in range(n):
    omega=60*i/(n-1)
    title = r'$\omega=%d^\circ$' % omega
    ff = ba.FormFactorTetrahedron(12*nanometer, 8*nanometer, 75*degree)
    trafo = ba.RotationZ(omega*degree)
    data = bp.run_simulation(det,ff,trafo)
    results.append( bp.Result(i, data, title) )
    
bp.make_plot( results, det, "ff_Tetrahedron" )

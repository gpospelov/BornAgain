"""
Plot form factors.
"""
import bornagain as ba
from   bornagain import nanometer, degree
import bornplot2 as bp
import math
import inspect

det = bp.DetPars( 400, -.25, .25, -.25, .25 )
n    = 3
results = []
edge = 30

title = 'face normal'
trafo = ba.RotationY(26.5651*degree)
ff = ba.FormFactorDodecahedron(edge*nanometer)
data = bp.run_simulation(det,ff,trafo)
results.append( bp.Result(0, data, title) )

pool = ff.getParameterPool()
print( pool.getParameterNames() )
pool.setParameterValue('Edge', 10)

title = 'vertex normal'
ff = ba.FormFactorDodecahedron(edge*nanometer)
data = bp.run_simulation(det,ff,trafo)
results.append( bp.Result(1, data, title) )

bp.make_plot( results, det, "tmp" )

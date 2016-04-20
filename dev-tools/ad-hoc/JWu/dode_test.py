"""
Plot form factors.
"""
import bornagain as ba
from   bornagain import nanometer, degree
import bornplot2 as bp
import math

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
pool.setParameter('Edg', 10)

title = 'vertex normal'
trafo = ba.RotationY(-52.6226*degree)
ff = ba.FormFactorDodecahedron(edge*nanometer)
data = bp.run_simulation(det,ff,trafo)
results.append( bp.Result(1, data, title) )

title = 'edge normal'
trafo = ba.RotationY(58.2825*degree)
ff = ba.FormFactorDodecahedron(edge*nanometer)
data = bp.run_simulation(det,ff,trafo)
results.append( bp.Result(2, data, title) )

bp.make_plot( results, det, "tmp" )

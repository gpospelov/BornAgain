#!/usr/bin/env python3

'''
Compute radiation trajectories through multilayer sample
for use in figure that explains the Green function.
'''

d = 20   # detector
s =  3 # source located at -s
T = [ 6, 6 ] # layer thickness
sd = T[0]-s # distance from source to lower interface
DeltaLayer = [ .05, .1 ] # refractive index parameter delta, per layer
x0   = 4
xtot = 60 - x0 # determine angles so that sum dx matches this

PP = [
    [ s, d ],
    [ -sd, T[0], d ],
    [ s, -T[0], T[0], d ],
    [ -sd, T[0], -T[0], T[0], d ],
    [ -sd, -T[1], T[1], T[0], d ],
    [ -sd, -T[1], T[1], -T[1], T[1], T[0], d ],
    [ -sd, -T[1], T[1], T[0], -T[0], T[0], d ],
]

import math, scipy.optimize, sys

def inside( y, mi, ma ):
    return mi<=y and y<=ma

def xsum( a0, P, D ):
    n = len(P)
    if len(D) != n:
        sys.stderr.write( "Bug: inconsistent array lengths\n" )
        exit(1)
    ret = 0
    for i in range(n):
        a = math.acos( math.cos(a0) / (1-D[i]) )
        ret += abs(P[i])/math.tan(a)
    return ret-xtot

for P in PP:
    y = -s
    DeltaPath = []
    for dy in P:
        yold = y
        y += dy
        if yold>=0 and y>=0:
            DeltaPath.append( 0 )
        elif inside(y,-T[0],0) and inside(yold,-T[0],0) :
            DeltaPath.append( DeltaLayer[0] )
        elif inside(y,-T[0]-T[1],-T[0]) and inside(yold,-T[0]-T[1],-T[0]) :
            DeltaPath.append( DeltaLayer[1] )
        else:
            sys.stderr.write( "Invalid input => layer ill defined\n" )
    if y!=d:
        sys.stderr.write( "Invalid input => detector not hit\n" )
        exit(1)

    a0 = scipy.optimize.newton( xsum, .5, args = ( P, DeltaPath ) )
    y = -s
    x =  x0
    print( "%6.3g %6.3g np mv" % ( x, y ) )
    for i in range(len(P)):
        a = math.acos( math.cos(a0) / (1-DeltaPath[i]) )
        x += abs(P[i])/math.tan(a)
        y += P[i]
        print( "%6.3g %6.3g li" % ( x, y ) )
    print( "st\n" )

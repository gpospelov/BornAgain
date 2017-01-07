#!/usr/bin/env python3

'''
Compute radiation trajectories through multilayer sample
for use in figure that explains the Green function.
'''

import math, sys

def inside( y, mi, ma ):
    return mi<=y and y<=ma

def xsum( a0, Y, D ):
    n = len(Y)
    if len(D) != n:
        sys.stderr.write( "Bug: inconsistent array lengths\n" )
        exit(1)
    ret = 0
    for i in range(n):
        ret += Y[i]/(1+D[i])
    return ret

d = 30   # detector
s = 1.5 # source located at -s
T = [ 3, 3 ] # layer thickness
sd = T[0]-s # distance from source to lower interface
DeltaLayer = [ .1, .2 ] # refractive index parameter delta, per layer
xtot = 60 # determine angles so that sum dx matches this

PP = [
    [ s, d ],
    [ -sd, T[0], d ],
    [ s, -T[0], T[0], d ],
    [ -sd, T[0], -T[0], T[0], d ],
    [ -sd, -T[1], T[1], T[0], d ],
    [ -sd, -T[1], T[1], -T[1], T[1], T[0], d ],
    [ -sd, -T[1], T[1], T[0], -T[0], T[0], d ],
]

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
    Y = [ abs(dy) for dy in P ]

    print( xsum( .3, Y, DeltaPath ) )

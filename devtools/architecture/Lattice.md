## Lattices

Typical sample construction with a 3d lattice:
```
    lattice = ba.FCCLattice(30*nm).transformed(rot.getTransform3D())
    peak_shape = ba.MisesFisherGaussPeakShape(peak_intensity, peak_width, zenith, kappa, kappa2)
    iff = ba.InterferenceFunction3DLattice(lattice)
    iff.setPositionVariance(1.)
    iff.setPeakShape(peak_shape)

    layout = ba.ParticleLayout()
    layout.addParticle(particle)
    layout.setTotalParticleSurfaceDensity(.01)
    layout.setInterferenceFunction(iff)
    layout.setWeight(1.0)

    vacuum_layer = ba.Layer(m_vacuum)
    vacuum_layer.addLayout(layout)
```

`bake::FCCLattice` returns a `Lattice3d` with an fcc primitive cell.

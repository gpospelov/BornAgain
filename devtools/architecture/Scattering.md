## How does BornAgain compute scattering?

Code analysis per 17nov, after merge of https://github.com/scgmlz/BornAgain/pull/1104.

### Simulation computes an incoherent sum

We consider a GISAS simulation, handled by class `GISASSimulation < ISimulation2D < ISimulation`
(where `<` indicates inheritance).

The function `GISASSimulation::runSimulation`
- calls `prepareSimulation`;
- loops over parameter combinations, thereby performing an incoherent summation:
  - for each parameter set, `runSingleSimulation`;
- calls `moveDataFromCache` and `transferResultsToIntensityMap` to collect results.

`GISASSimulation::prepareSimulation` seems to be mostly concerned with `SampleBuilder`s.

`ISimulation::runSingleSimulation` handles the multithreaded parallel computation
for batches of detector pixels (`SimulationElement`s). It
- uses `ISimulation2D::generateSingleThreadedComputation` to create instances of `DWBAComputation < IComputation`;
- for each instance, runs `IComputation.run`;
- calls `ISimulation2D::normalize`;
- calls `ISimulation2D::addBackgroundIntensity`.

The `IComputation` constructor creates the member `ProcessedSample m_processed_sample`.

The `DWBAComputation` constructor populates the member `DWBASingleComputation m_single_computation`:
- For each `ProcessedLayout` in `m_processed_sample->layouts()`, the vector `DWBASingleComputation::m_layout_comps` is given a `new ParticleLayoutComputation` member;
- if `m_processed_sample->hasRoughness()`, then `DWBASingleComputation::m_roughness_comp` points to a `new RoughMultiLayerComputation`.

`IComputation::run` calls `DWBAComputation::runProtected`, which for each `SimulationElement` in the batch calls `m_single_computation.compute`.

`DWBASingleComputation::compute` performs an incoherent summation: it increments `SimulationElement::m_intensity` by contributions from each processed particle layouts, and from roughness.

### Scattering from a particle layout

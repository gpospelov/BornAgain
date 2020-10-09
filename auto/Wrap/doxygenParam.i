
// File: index.xml

// File: classINode.xml
%feature("docstring") INode "

Base class for tree-like structures containing parameterized objects.

C++ includes: INode.h
";

%feature("docstring")  INode::INode "INode::INode()
";

%feature("docstring")  INode::INode "INode::INode(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  INode::~INode "virtual INode::~INode()
";

%feature("docstring")  INode::accept "virtual void INode::accept(INodeVisitor *visitor) const =0

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  INode::treeToString "std::string INode::treeToString() const

Returns multiline string representing tree structure below the node. 
";

%feature("docstring")  INode::registerChild "void INode::registerChild(INode *node)
";

%feature("docstring")  INode::getChildren "std::vector< const INode * > INode::getChildren() const

Returns a vector of children (const). 
";

%feature("docstring")  INode::setParent "void INode::setParent(const INode *newParent)
";

%feature("docstring")  INode::parent "const INode * INode::parent() const
";

%feature("docstring")  INode::parent "INode * INode::parent()
";

%feature("docstring")  INode::copyNumber "int INode::copyNumber(const INode *node) const

Returns copyNumber of child, which takes into account existence of children with same name. 
";

%feature("docstring")  INode::displayName "std::string INode::displayName() const

Returns display name, composed from the name of node and it's copy number. 
";

%feature("docstring")  INode::createParameterTree "ParameterPool * INode::createParameterTree() const

Creates new parameter pool, with all local parameters and those of its children. 
";


// File: classINodeVisitor.xml
%feature("docstring") INodeVisitor "

From visitor pattern to achieve double dispatch.

Visitor interface to visit ISample objects.

C++ includes: INodeVisitor.h
";

%feature("docstring")  INodeVisitor::INodeVisitor "INodeVisitor::INodeVisitor()
";

%feature("docstring")  INodeVisitor::~INodeVisitor "virtual INodeVisitor::~INodeVisitor()
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const BasicLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Beam *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ConstantBackground *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ConvolutionDetectorResolution *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Crystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionCosine *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionGate *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionGaussian *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionLogNormal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionTrapezoid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FootprintGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FootprintSquare *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorAnisoPyramid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorBarGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorBarLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorBox *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCantellatedCube *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCone *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCone6 *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCoreShell *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCrystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCuboctahedron *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCylinder *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDWBA *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDWBAPol *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDecoratorMaterial *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDecoratorPositionFactor *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDecoratorRotation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDodecahedron *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDot *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorEllipsoidalCylinder *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorFullSphere *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorFullSpheroid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorGaussSphere *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorHemiEllipsoid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorHollowSphere *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorIcosahedron *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorLongBoxGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorLongBoxLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorPrism3 *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorPrism6 *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorPyramid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCosineRippleBox *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCosineRippleGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCosineRippleLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorSawtoothRippleBox *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorSawtoothRippleGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorSawtoothRippleLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorSphereGaussianRadius *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorSphereLogNormalRadius *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorTetrahedron *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorTruncatedCube *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorTruncatedSphere *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorTruncatedSpheroid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorWeighted *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction1DCauchy *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction1DGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction1DTriangle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction1DVoigt *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction2DCauchy *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction2DGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction2DVoigt *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DCauchy *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DCosine *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DGate *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DTriangle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DVoigt *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DCauchy *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DCone *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DGate *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DVoigt *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const GISASSimulation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const HexagonalLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IAbstractParticle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IClusteredParticles *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IdentityRotation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IFormFactor *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IFormFactorBorn *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IFormFactorDecorator *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IInterferenceFunction *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ILayout *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const INode *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Instrument *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction1DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction2DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction2DParaCrystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction2DSuperLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction3DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionFinite2DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionFinite3DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionHardDisk *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionRadialParaCrystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionTwin *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionNone *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IParticle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IPeakShape *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IRotation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ISample *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IsGISAXSDetector *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Layer *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const LayerInterface *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const LayerRoughness *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const MesoCrystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const MultiLayer *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const OffSpecSimulation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Particle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ParticleComposition *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ParticleCoreShell *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ParticleDistribution *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ParticleLayout *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const PoissonNoiseBackground *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RectangularDetector *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ResolutionFunction2DGaussian *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RotationEuler *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RotationX *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RotationY *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RotationZ *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const SpecularDetector1D *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const SpecularSimulation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const SphericalDetector *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const SquareLattice *)
";

%feature("docstring")  INodeVisitor::depth "int INodeVisitor::depth() const

Returns depth of the visitor in the composite hierarchy. 
";

%feature("docstring")  INodeVisitor::setDepth "void INodeVisitor::setDepth(int depth)

Sets depth of the visitor in the composite hierarchy. 
";


// File: classIParameter.xml
%feature("docstring") IParameter "

Pure virtual base class for parameter wrapper classes  RealParameter, ComponentParameter. Holds a pointer to the wrapped parameter, a name, and a callback function to be called when the parameter is changed. This class is templated on the data type of the wrapped parameter.

C++ includes: IParameter.h
";

%feature("docstring")  IParameter::IParameter "IParameter< T >::IParameter()=delete
";

%feature("docstring")  IParameter::IParameter "IParameter< T >::IParameter(const std::string &name, T *data, const std::string &parent_name, const std::function< void()> &onChange)
";

%feature("docstring")  IParameter::~IParameter "virtual IParameter< T >::~IParameter()=default
";

%feature("docstring")  IParameter::clone "virtual IParameter* IParameter< T >::clone(const std::string &new_name=\"\") const =0
";

%feature("docstring")  IParameter::isNull "virtual bool IParameter< T >::isNull() const

Returns true if wrapped parameter was not initialized with proper real value. 
";

%feature("docstring")  IParameter::getData "T& IParameter< T >::getData() const
";

%feature("docstring")  IParameter::setData "void IParameter< T >::setData(T &data)
";

%feature("docstring")  IParameter::hasSameData "bool IParameter< T >::hasSameData(const IParameter &other)

Returns true if two parameters are pointing to the same raw data. 
";

%feature("docstring")  IParameter::getName "const std::string& IParameter< T >::getName() const
";


// File: classIParameterized.xml
%feature("docstring") IParameterized "

Manages a local parameter pool, and a tree of child pools.

C++ includes: IParameterized.h
";

%feature("docstring")  IParameterized::IParameterized "IParameterized::IParameterized(const std::string &name=\"\")
";

%feature("docstring")  IParameterized::IParameterized "IParameterized::IParameterized(const IParameterized &other)
";

%feature("docstring")  IParameterized::~IParameterized "IParameterized::~IParameterized()
";

%feature("docstring")  IParameterized::parameterPool "ParameterPool* IParameterized::parameterPool() const

Returns pointer to the parameter pool. 
";

%feature("docstring")  IParameterized::createParameterTree "ParameterPool * IParameterized::createParameterTree() const

Creates new parameter pool, with all local parameters and those of its children. 
";

%feature("docstring")  IParameterized::parametersToString "std::string IParameterized::parametersToString() const

Returns multiline string representing available parameters. 
";

%feature("docstring")  IParameterized::registerParameter "RealParameter & IParameterized::registerParameter(const std::string &name, double *parpointer)
";

%feature("docstring")  IParameterized::registerVector "void IParameterized::registerVector(const std::string &base_name, kvector_t *p_vec, const std::string &units=\"nm\")
";

%feature("docstring")  IParameterized::setParameterValue "void IParameterized::setParameterValue(const std::string &name, double value)
";

%feature("docstring")  IParameterized::setVectorValue "void IParameterized::setVectorValue(const std::string &base_name, kvector_t value)
";

%feature("docstring")  IParameterized::parameter "RealParameter * IParameterized::parameter(const std::string &name) const

Returns parameter with given 'name'. 
";

%feature("docstring")  IParameterized::onChange "virtual void IParameterized::onChange()

Action to be taken in inherited class when a parameter has changed. 
";

%feature("docstring")  IParameterized::removeParameter "void IParameterized::removeParameter(const std::string &name)
";

%feature("docstring")  IParameterized::removeVector "void IParameterized::removeVector(const std::string &base_name)
";

%feature("docstring")  IParameterized::setName "void IParameterized::setName(const std::string &name)
";

%feature("docstring")  IParameterized::getName "const std::string& IParameterized::getName() const
";


// File: classIterationStrategy.xml
%feature("docstring") IterationStrategy "

Abstract base class for tree traversal strategies, for use in  INodeVisitor.

For definition of different strategies see https://en.wikipedia.org/wiki/Tree_traversal.

C++ includes: IterationStrategy.h
";

%feature("docstring")  IterationStrategy::clone "virtual IterationStrategy* IterationStrategy::clone() const =0
";

%feature("docstring")  IterationStrategy::first "virtual IteratorMemento IterationStrategy::first(const INode *p_root)=0
";

%feature("docstring")  IterationStrategy::next "virtual void IterationStrategy::next(IteratorMemento &iterator_stack) const =0
";

%feature("docstring")  IterationStrategy::isDone "virtual bool IterationStrategy::isDone(IteratorMemento &iterator_stack) const =0
";


// File: classIteratorMemento.xml
%feature("docstring") IteratorMemento "

Holds all iterator states encountered for SampleTreeIterator.

C++ includes: NodeIterator.h
";

%feature("docstring")  IteratorMemento::IteratorMemento "IteratorMemento::IteratorMemento()
";

%feature("docstring")  IteratorMemento::~IteratorMemento "virtual IteratorMemento::~IteratorMemento()
";

%feature("docstring")  IteratorMemento::push_state "void IteratorMemento::push_state(const IteratorState &state)
";

%feature("docstring")  IteratorMemento::pop_state "void IteratorMemento::pop_state()
";

%feature("docstring")  IteratorMemento::get_state "IteratorState& IteratorMemento::get_state()
";

%feature("docstring")  IteratorMemento::empty "bool IteratorMemento::empty() const
";

%feature("docstring")  IteratorMemento::reset "void IteratorMemento::reset()
";

%feature("docstring")  IteratorMemento::getCurrent "const INode* IteratorMemento::getCurrent()
";

%feature("docstring")  IteratorMemento::next "void IteratorMemento::next()
";

%feature("docstring")  IteratorMemento::size "size_t IteratorMemento::size() const
";


// File: classIteratorState.xml
%feature("docstring") IteratorState "

Holds state of iterator at single level for SampleTreeIterator.

C++ includes: NodeIterator.h
";

%feature("docstring")  IteratorState::IteratorState "IteratorState::IteratorState(const INode *single_element)
";

%feature("docstring")  IteratorState::IteratorState "IteratorState::IteratorState(std::vector< const INode * > samples)
";

%feature("docstring")  IteratorState::~IteratorState "virtual IteratorState::~IteratorState()
";

%feature("docstring")  IteratorState::getCurrent "const INode* IteratorState::getCurrent() const
";

%feature("docstring")  IteratorState::isEnd "bool IteratorState::isEnd() const
";

%feature("docstring")  IteratorState::next "void IteratorState::next()
";


// File: classNodeIterator.xml
%feature("docstring") NodeIterator "

Iterator through  INode tree of objects.

Usage example: SampleTreeIterator<Strategy> it(&sample); it.first(); while( !it.is_done() ) {  INode *p_sample = it.get_current(); it.next(); }

C++ includes: NodeIterator.h
";

%feature("docstring")  NodeIterator::NodeIterator "NodeIterator< Strategy >::NodeIterator(const INode *root)
";

%feature("docstring")  NodeIterator::~NodeIterator "virtual NodeIterator< Strategy >::~NodeIterator()
";

%feature("docstring")  NodeIterator::first "void NodeIterator< Strategy >::first()
";

%feature("docstring")  NodeIterator::next "void NodeIterator< Strategy >::next()
";

%feature("docstring")  NodeIterator::getCurrent "const INode * NodeIterator< Strategy >::getCurrent()
";

%feature("docstring")  NodeIterator::isDone "bool NodeIterator< Strategy >::isDone() const
";

%feature("docstring")  NodeIterator::depth "int NodeIterator< Strategy >::depth() const
";


// File: structNodeMeta.xml
%feature("docstring") NodeMeta "

Metadata of one model node.

C++ includes: INode.h
";


// File: structParaMeta.xml
%feature("docstring") ParaMeta "

Metadata of one model parameter.

C++ includes: INode.h
";


// File: classParameterPool.xml
%feature("docstring") ParameterPool "

Container with parameters for  IParameterized object.

C++ includes: ParameterPool.h
";

%feature("docstring")  ParameterPool::ParameterPool "ParameterPool::ParameterPool()

Constructs an empty parameter pool. 
";

%feature("docstring")  ParameterPool::~ParameterPool "ParameterPool::~ParameterPool()
";

%feature("docstring")  ParameterPool::clone "ParameterPool * ParameterPool::clone() const

Returns a literal clone. 
";

%feature("docstring")  ParameterPool::copyToExternalPool "void ParameterPool::copyToExternalPool(const std::string &prefix, ParameterPool *other_pool) const

Copies parameters of given pool to  other pool, prepeding  prefix to the parameter names. 
";

%feature("docstring")  ParameterPool::clear "void ParameterPool::clear()

Clears the parameter map. 
";

%feature("docstring")  ParameterPool::size "size_t ParameterPool::size() const

Returns number of parameters in the pool. 
";

%feature("docstring")  ParameterPool::empty "bool ParameterPool::empty() const
";

%feature("docstring")  ParameterPool::addParameter "RealParameter & ParameterPool::addParameter(RealParameter *newPar)

Adds parameter to the pool, and returns reference to the input pointer.

Returning the input pointer allows us to concatenate function calls like pool->addParameter( new RealParameter(...) ).setLimits(-1,+1).setFixed().setUnit(\"nm\") 
";

%feature("docstring")  ParameterPool::parameter "RealParameter * ParameterPool::parameter(const std::string &name)

Returns parameter with given  name. 
";

%feature("docstring")  ParameterPool::parameter "const RealParameter * ParameterPool::parameter(const std::string &name) const

Returns parameter with given  name. 
";

%feature("docstring")  ParameterPool::parameters "const std::vector<RealParameter*> ParameterPool::parameters() const

Returns full vector of parameters. 
";

%feature("docstring")  ParameterPool::getMatchedParameters "std::vector< RealParameter * > ParameterPool::getMatchedParameters(const std::string &pattern) const

Returns nonempty vector of parameters that match the  pattern ('*' allowed), or throws. 
";

%feature("docstring")  ParameterPool::getUniqueMatch "RealParameter * ParameterPool::getUniqueMatch(const std::string &pattern) const

Returns the one parameter that matches the  pattern (wildcards '*' allowed), or throws. 
";

%feature("docstring")  ParameterPool::setParameterValue "void ParameterPool::setParameterValue(const std::string &name, double value)

Sets parameter value. 
";

%feature("docstring")  ParameterPool::setMatchedParametersValue "int ParameterPool::setMatchedParametersValue(const std::string &wildcards, double value)

Sets value of the nonzero parameters that match  pattern ('*' allowed), or throws. 
";

%feature("docstring")  ParameterPool::setUniqueMatchValue "void ParameterPool::setUniqueMatchValue(const std::string &pattern, double value)

Sets value of the one parameter that matches  pattern ('*' allowed), or throws. 
";

%feature("docstring")  ParameterPool::parameterNames "std::vector< std::string > ParameterPool::parameterNames() const
";

%feature("docstring")  ParameterPool::removeParameter "void ParameterPool::removeParameter(const std::string &name)

Removes parameter with given name from the pool. 
";


// File: classPostorderStrategy.xml
%feature("docstring") PostorderStrategy "

Traverse tree; visit children before their parents.

C++ includes: IterationStrategy.h
";

%feature("docstring")  PostorderStrategy::PostorderStrategy "PostorderStrategy::PostorderStrategy()
";

%feature("docstring")  PostorderStrategy::clone "PostorderStrategy * PostorderStrategy::clone() const
";

%feature("docstring")  PostorderStrategy::first "IteratorMemento PostorderStrategy::first(const INode *p_root)
";

%feature("docstring")  PostorderStrategy::next "void PostorderStrategy::next(IteratorMemento &iterator_stack) const
";

%feature("docstring")  PostorderStrategy::isDone "bool PostorderStrategy::isDone(IteratorMemento &iterator_stack) const
";


// File: classPreorderStrategy.xml
%feature("docstring") PreorderStrategy "

Traverse tree; visit parents before their children.

C++ includes: IterationStrategy.h
";

%feature("docstring")  PreorderStrategy::PreorderStrategy "PreorderStrategy::PreorderStrategy()
";

%feature("docstring")  PreorderStrategy::clone "PreorderStrategy * PreorderStrategy::clone() const
";

%feature("docstring")  PreorderStrategy::first "IteratorMemento PreorderStrategy::first(const INode *p_root)
";

%feature("docstring")  PreorderStrategy::next "void PreorderStrategy::next(IteratorMemento &iterator_stack) const
";

%feature("docstring")  PreorderStrategy::isDone "bool PreorderStrategy::isDone(IteratorMemento &iterator_stack) const
";


// File: classRealParameter.xml
%feature("docstring") RealParameter "

Wraps a parameter of type double. In addition to name and on-change callback held by the parent class  IParameter, this class holds Limits, Attributes (currently only fixed or not), and a  Unit.

C++ includes: RealParameter.h
";

%feature("docstring")  RealParameter::RealParameter "RealParameter::RealParameter(const std::string &name, double *par, const std::string &parent_name=\"\", const std::function< void()> &onChange=std::function< void()>(), const RealLimits &limits=RealLimits::limitless(), const Attributes &attr=Attributes::free())
";

%feature("docstring")  RealParameter::~RealParameter "virtual RealParameter::~RealParameter()=default
";

%feature("docstring")  RealParameter::clone "RealParameter * RealParameter::clone(const std::string &new_name=\"\") const
";

%feature("docstring")  RealParameter::setValue "void RealParameter::setValue(double value)

Sets value of wrapped parameter and emit signal. 
";

%feature("docstring")  RealParameter::value "double RealParameter::value() const

Returns value of wrapped parameter. 
";

%feature("docstring")  RealParameter::setLimits "RealParameter & RealParameter::setLimits(const RealLimits &limits)
";

%feature("docstring")  RealParameter::limits "RealLimits RealParameter::limits() const
";

%feature("docstring")  RealParameter::setLimited "RealParameter & RealParameter::setLimited(double lower, double upper)
";

%feature("docstring")  RealParameter::setPositive "RealParameter & RealParameter::setPositive()
";

%feature("docstring")  RealParameter::setNonnegative "RealParameter & RealParameter::setNonnegative()
";

%feature("docstring")  RealParameter::setUnit "RealParameter & RealParameter::setUnit(const std::string &name)
";

%feature("docstring")  RealParameter::unit "std::string RealParameter::unit() const
";


// File: classUnit.xml
%feature("docstring") Unit "

A physical unit.

C++ includes: Unit.h
";

%feature("docstring")  Unit::Unit "Unit::Unit(const std::string &name=\"\")
";

%feature("docstring")  Unit::setUnit "void Unit::setUnit(const std::string &name)
";

%feature("docstring")  Unit::getName "const std::string& Unit::getName() const
";


// File: namespace_0d16.xml


// File: namespaceNodeUtils.xml
%feature("docstring")  NodeUtils::nodeToString "std::string NodeUtils::nodeToString(const INode &node)

Returns multiline string representing tree structure starting from given node. 
";

%feature("docstring")  NodeUtils::nodePath "std::string NodeUtils::nodePath(const INode &node, const INode *root=nullptr)

Returns path composed of node's displayName, with respect to root node. 
";


// File: IParameter_8h.xml


// File: IParameterized_8cpp.xml


// File: IParameterized_8h.xml


// File: IterationStrategy_8cpp.xml


// File: IterationStrategy_8h.xml


// File: ParameterPool_8cpp.xml


// File: ParameterPool_8h.xml


// File: RealParameter_8cpp.xml


// File: RealParameter_8h.xml


// File: Unit_8h.xml


// File: INode_8cpp.xml
%feature("docstring")  nodeMetaUnion "NodeMeta nodeMetaUnion(const std::vector< ParaMeta > &base, const NodeMeta &other)
";


// File: INode_8h.xml
%feature("docstring")  nodeMetaUnion "NodeMeta nodeMetaUnion(const std::vector< ParaMeta > &base, const NodeMeta &other)
";


// File: INodeVisitor_8cpp.xml
%feature("docstring")  VisitNodesPreorder "void VisitNodesPreorder(const INode &node, INodeVisitor &visitor)
";

%feature("docstring")  VisitNodesPostorder "void VisitNodesPostorder(const INode &node, INodeVisitor &visitor)
";


// File: INodeVisitor_8h.xml
%feature("docstring")  VisitNodesPreorder "void VisitNodesPreorder(const INode &node, INodeVisitor &visitor)
";

%feature("docstring")  VisitNodesPostorder "void VisitNodesPostorder(const INode &node, INodeVisitor &visitor)
";


// File: NodeIterator_8cpp.xml


// File: NodeIterator_8h.xml


// File: NodeUtils_8cpp.xml


// File: NodeUtils_8h.xml


// File: dir_a1f38e94e849d0203a55ad5a19f2f15a.xml


// File: dir_a98fb20d64e2aea67a6e042d91197081.xml


// File: dir_d452a16c8784395bb8c21da516e88a7f.xml


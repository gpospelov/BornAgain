%template(swig_dummy_type_inode_vector) std::vector<INode*>;
%template(swig_dummy_type_const_inode_vector) std::vector<const INode*>;
%template(IParameterReal) IParameter<double>; // needed to avoid warning 401?
%template(ParameterSampleVector) std::vector<ParameterSample>;

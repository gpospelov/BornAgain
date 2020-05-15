#### How to make an API change that involves a form factor

This note shall help when you
* add a form factor
* remove a form factor
* change a form factor's argument list

After adding or removing a form factor, the following files need to be updated:
* Core/Basics/BornAgainNamespace.h
* Core/Parametrization/INodeVisitor.h (in two places)
* Core/includeIncludes/HardParticles.h
* Wrap/swig/libBornAgainCore.i (in two places: #include and %include)

If the form factor is supported by the GUI, then also:
* GUI/coregui/Models/GUIDomainSampleVisitor.h
* GUI/coregui/Models/GUIDomainSampleVisitor.cpp

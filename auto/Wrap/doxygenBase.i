
// File: index.xml

// File: classExceptions_1_1ClassInitializationException.xml
%feature("docstring") Exceptions::ClassInitializationException "";

%feature("docstring")  Exceptions::ClassInitializationException::ClassInitializationException "Exceptions::ClassInitializationException::ClassInitializationException(const std::string &message)
";


// File: classCloneableVector.xml
%feature("docstring") CloneableVector "

The objects pointed to must posses a clone() function.

A vector of unique pointers to objects that are cloneable.

Equips vector<unique_ptr<T>> with copy constructor. For use with polymorphic objects, or in pimpl idiom.

C++ includes: CloneableVector.h
";

%feature("docstring")  CloneableVector::CloneableVector "CloneableVector< T >::CloneableVector()
";

%feature("docstring")  CloneableVector::CloneableVector "CloneableVector< T >::CloneableVector(const CloneableVector &other)
";

%feature("docstring")  CloneableVector::push_back "void CloneableVector< T >::push_back(T *t)
";

%feature("docstring")  CloneableVector::emplace_back "void CloneableVector< T >::emplace_back(std::unique_ptr< T > &&t)
";


// File: classExceptions_1_1DivisionByZeroException.xml
%feature("docstring") Exceptions::DivisionByZeroException "";

%feature("docstring")  Exceptions::DivisionByZeroException::DivisionByZeroException "Exceptions::DivisionByZeroException::DivisionByZeroException(const std::string &message)
";


// File: classExceptions_1_1DomainErrorException.xml
%feature("docstring") Exceptions::DomainErrorException "";

%feature("docstring")  Exceptions::DomainErrorException::DomainErrorException "Exceptions::DomainErrorException::DomainErrorException(const std::string &message)
";


// File: classExceptions_1_1ExistingClassRegistrationException.xml
%feature("docstring") Exceptions::ExistingClassRegistrationException "";

%feature("docstring")  Exceptions::ExistingClassRegistrationException::ExistingClassRegistrationException "Exceptions::ExistingClassRegistrationException::ExistingClassRegistrationException(const std::string &message)
";


// File: classExceptions_1_1FileIsBadException.xml
%feature("docstring") Exceptions::FileIsBadException "";

%feature("docstring")  Exceptions::FileIsBadException::FileIsBadException "Exceptions::FileIsBadException::FileIsBadException(const std::string &message)
";


// File: classExceptions_1_1FileNotIsOpenException.xml
%feature("docstring") Exceptions::FileNotIsOpenException "";

%feature("docstring")  Exceptions::FileNotIsOpenException::FileNotIsOpenException "Exceptions::FileNotIsOpenException::FileNotIsOpenException(const std::string &message)
";


// File: classExceptions_1_1FormatErrorException.xml
%feature("docstring") Exceptions::FormatErrorException "";

%feature("docstring")  Exceptions::FormatErrorException::FormatErrorException "Exceptions::FormatErrorException::FormatErrorException(const std::string &message)
";


// File: classICloneable.xml
%feature("docstring") ICloneable "

Interface for polymorphic classes that should not be copied, except by explicit cloning.

Child classes of  ICloneable must provide clone().

C++ includes: ICloneable.h
";

%feature("docstring")  ICloneable::ICloneable "ICloneable::ICloneable()=default
";

%feature("docstring")  ICloneable::~ICloneable "virtual ICloneable::~ICloneable()=default
";

%feature("docstring")  ICloneable::ICloneable "ICloneable::ICloneable(const ICloneable &)=delete
";

%feature("docstring")  ICloneable::ICloneable "ICloneable::ICloneable(ICloneable &&)=default
";

%feature("docstring")  ICloneable::clone "virtual ICloneable* ICloneable::clone() const =0
";

%feature("docstring")  ICloneable::transferToCPP "virtual void ICloneable::transferToCPP()

Used for Python overriding of clone (see swig/tweaks.py) 
";


// File: classExceptions_1_1LogicErrorException.xml
%feature("docstring") Exceptions::LogicErrorException "";

%feature("docstring")  Exceptions::LogicErrorException::LogicErrorException "Exceptions::LogicErrorException::LogicErrorException(const std::string &message)
";


// File: classExceptions_1_1NotImplementedException.xml
%feature("docstring") Exceptions::NotImplementedException "";

%feature("docstring")  Exceptions::NotImplementedException::NotImplementedException "Exceptions::NotImplementedException::NotImplementedException(const std::string &message)
";


// File: classExceptions_1_1NullPointerException.xml
%feature("docstring") Exceptions::NullPointerException "";

%feature("docstring")  Exceptions::NullPointerException::NullPointerException "Exceptions::NullPointerException::NullPointerException(const std::string &message)
";


// File: classExceptions_1_1OutOfBoundsException.xml
%feature("docstring") Exceptions::OutOfBoundsException "";

%feature("docstring")  Exceptions::OutOfBoundsException::OutOfBoundsException "Exceptions::OutOfBoundsException::OutOfBoundsException(const std::string &message)
";


// File: classExceptions_1_1RuntimeErrorException.xml
%feature("docstring") Exceptions::RuntimeErrorException "";

%feature("docstring")  Exceptions::RuntimeErrorException::RuntimeErrorException "Exceptions::RuntimeErrorException::RuntimeErrorException(const std::string &message)
";


// File: classSafePointerVector.xml
%feature("docstring") SafePointerVector "

The objects pointed to must support the  ICloneable interface.

A vector of pointers, owned by *this, with methods to handle them safely.

C++ includes: SafePointerVector.h
";

%feature("docstring")  SafePointerVector::SafePointerVector "SafePointerVector< T >::SafePointerVector()
";

%feature("docstring")  SafePointerVector::SafePointerVector "SafePointerVector< T >::SafePointerVector(const SafePointerVector &other)
";

%feature("docstring")  SafePointerVector::SafePointerVector "SafePointerVector< T >::SafePointerVector(SafePointerVector &&other)
";

%feature("docstring")  SafePointerVector::~SafePointerVector "SafePointerVector< T >::~SafePointerVector()
";

%feature("docstring")  SafePointerVector::size "size_t SafePointerVector< T >::size() const
";

%feature("docstring")  SafePointerVector::empty "bool SafePointerVector< T >::empty() const
";

%feature("docstring")  SafePointerVector::push_back "void SafePointerVector< T >::push_back(T *pointer)
";

%feature("docstring")  SafePointerVector::begin "iterator SafePointerVector< T >::begin()
";

%feature("docstring")  SafePointerVector::begin "const_iterator SafePointerVector< T >::begin() const
";

%feature("docstring")  SafePointerVector::end "iterator SafePointerVector< T >::end()
";

%feature("docstring")  SafePointerVector::end "const_iterator SafePointerVector< T >::end() const
";

%feature("docstring")  SafePointerVector::deleteElement "bool SafePointerVector< T >::deleteElement(T *pointer)
";

%feature("docstring")  SafePointerVector::back "T* SafePointerVector< T >::back()
";

%feature("docstring")  SafePointerVector::back "const T* SafePointerVector< T >::back() const
";

%feature("docstring")  SafePointerVector::clear "void SafePointerVector< T >::clear()
";


// File: classExceptions_1_1UnknownClassRegistrationException.xml
%feature("docstring") Exceptions::UnknownClassRegistrationException "";

%feature("docstring")  Exceptions::UnknownClassRegistrationException::UnknownClassRegistrationException "Exceptions::UnknownClassRegistrationException::UnknownClassRegistrationException(const std::string &message)
";


// File: namespacealgo.xml
%feature("docstring")  algo::almostEqual "bool algo::almostEqual(double a, double b)

Returns true if two doubles agree within machine epsilon. 
";

%feature("docstring")  algo::min_value "double algo::min_value(const Iterator &begin, const Iterator &end, const Evaluator &evaluate)

Returns the minimum value of function evaluate as applied to the elements of an iterator range. 
";

%feature("docstring")  algo::max_value "double algo::max_value(const Iterator &begin, const Iterator &end, const Evaluator &evaluate)

Returns the maximum value of function evaluate as applied to the elements of an iterator range. 
";

%feature("docstring")  algo::concat "std::vector< T > algo::concat(const std::vector< T > &v1, const std::vector< T > &v2)

Returns the concatenation of two std::vectors. 
";


// File: namespaceExceptions.xml
%feature("docstring")  Exceptions::LogExceptionMessage "void Exceptions::LogExceptionMessage(const std::string &)
";


// File: namespacePhysConsts.xml


// File: namespaceUnits.xml
%feature("docstring")  Units::rad2deg "double Units::rad2deg(double angle)
";

%feature("docstring")  Units::deg2rad "double Units::deg2rad(double angle)
";


// File: MathConstants_8h.xml


// File: PhysicalConstants_8h.xml


// File: Units_8h.xml


// File: CloneableVector_8h.xml


// File: Complex_8h.xml
%feature("docstring")  mul_I "complex_t mul_I(complex_t z)

Returns product I*z, where I is the imaginary unit. 
";

%feature("docstring")  exp_I "complex_t exp_I(complex_t z)

Returns exp(I*z), where I is the imaginary unit. 
";


// File: Exceptions_8cpp.xml


// File: Exceptions_8h.xml


// File: ICloneable_8h.xml


// File: SafePointerVector_8h.xml


// File: Algorithms_8h.xml


// File: Assert_8h.xml


// File: dir_628593db0cdce5a76fb85526ae5aa762.xml


// File: dir_53458346a71374f205070d8bd3d865f1.xml


// File: dir_38a5ec4dd9a60e867dacdb92549a13e0.xml


// File: dir_ddfc3031126aa7182b75ced37b3eee2b.xml


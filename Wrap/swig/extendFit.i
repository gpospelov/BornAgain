
// FitParameterSet iterator

%pythoncode %{
class FitParameterSetIterator(object):

    def __init__(self, fitParameters):
        self.fitParameters = fitParameters
        self.index = -1

    def __iter__(self):
        return self

    def next(self):
        self.index += 1
        if self.index < self.fitParameters.size():
            return self.fitParameters[self.index]
        else:
            raise StopIteration

    def __next__(self):
        return self.next()
%}

// FitParameterSet accessors

%extend FitParameterSet {
    const IFitParameter* __getitem__(std::string name) const
    {
        return (*($self))[name];
    }
    const IFitParameter* __getitem__(size_t index) const
    {
        return (*($self))[index];
    }

%pythoncode {
    def __iter__(self):
        return FitParameterSetIterator(self)
}
};


%pythoncode %{
class ParametersIterator(object):

    def __init__(self, parameters):
        self.parameters = parameters
        self.index = -1

    def __iter__(self):
        return self

    def next(self):
        self.index += 1
        if self.index < self.parameters.size():
            return self.parameters[self.index]
        else:
            raise StopIteration

    def __next__(self):
        return self.next()
%}

// Parameters accessors
namespace Fit {

%extend Parameters {
    const Parameter& __getitem__(std::string name) const
    {
        return (*($self))[name];
    }
    const Parameter& __getitem__(size_t index) const
    {
        return (*($self))[index];
    }

%pythoncode %{
def __iter__(self):
    return ParametersIterator(self)
%}
};

}

// --- Setting up Minimizer callback ---

%pythoncode %{
class CallableWrapper(PyCallback):
    def __init__(self, f):
        super(CallableWrapper, self).__init__()
        self.f_ = f
    def call(self, obj):
        return self.f_(obj)
%}

namespace Fit {

%extend Minimizer {
%pythoncode %{
    def test_callback(self, args):
        if callable(args):
            wrp = CallableWrapper(args)
            result = self.test_callback_cpp(wrp)

%}
};

}


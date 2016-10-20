
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
    const FitParameter* __getitem__(std::string name) const
    {
        return (*($self))[name];
    }
    const FitParameter* __getitem__(size_t index) const
    {
        return (*($self))[index];
    }

%pythoncode {
    def __iter__(self):
        return FitParameterSetIterator(self)
}
};



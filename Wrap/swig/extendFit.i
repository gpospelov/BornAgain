%extend IParameterized {
    virtual void registerParameter(
        const std::string &name, int64_t parpointer,
        const AttLimits& limits = AttLimits::limitless())
    {
        return (*($self)).registerParameter(name, (double*)parpointer, limits);
    }
};

 // introduced because of FitCylindersAndPrisms example
%extend FitSuiteParameters {
    const FitParameter* __getitem__(std::string name) const
    {
        return (*($self))[name];
    }
    const FitParameter* __getitem__(size_t index) const
    {
        return (*($self))[index];
    }
};

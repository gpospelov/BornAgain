namespace Geometry {
    %extend BasicVector3D<double> {
        BasicVector3D<double> __add__(const BasicVector3D<double>& rhs) const
        {
            return *($self)+rhs;
        }
        BasicVector3D<double> __mul__(double c) const
        {
            return *($self)*c;
        }
        BasicVector3D<double> __rmul__(double c) const
        {
            return *($self)*c;
        }
    };
}

%extend OutputData<double> {
    double __getitem__(unsigned int i)
    {
        return (*($self))[i];
    }
    double __setitem__(unsigned int i, double value)
    {
        (*($self))[i] = value;
        return (*($self))[i];
    }
};

%extend FixedBinAxis {
    double __getitem__(unsigned int i)
    {
        return (*($self))[i];
    }
};

%extend VariableBinAxis {
    double __getitem__(unsigned int i)
    {
        return (*($self))[i];
    }
};

%extend ISampleBuilder {
    virtual void registerParameter(
        const std::string &name, int64_t parpointer,
        const AttLimits& limits = AttLimits::limitless())
    {
        return (*($self)).registerParameter(name, (double*)parpointer, limits);
    }
    virtual void setParameterValue(const std::string &name, double value)
    {
        dynamic_cast<IParameterized*>($self)->setParameterValue(name, value);
    }
};

// necessary to export this since Python does not support dynamic casting
%extend Histogram2D {
    static Histogram2D* dynamicCast(IHistogram* pHistogram)
    {
        return dynamic_cast<Histogram2D*>(pHistogram);
    }
};

// necessary to export this since Python does not support dynamic casting
%extend Histogram1D {
    static Histogram1D* dynamicCast(IHistogram* pHistogram)
    {
        return dynamic_cast<Histogram1D*>(pHistogram);
    }
};

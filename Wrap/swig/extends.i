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
    double __getitem__(unsigned int i) {
        return (*($self))[i];
    }

    double __setitem__(unsigned int i, double value) {
        (*($self))[i] = value;
        return (*($self))[i];
    }
};

%extend FixedBinAxis {
    double __getitem__(unsigned int i) {
        return (*($self))[i];
    }

    /*  double __setitem__(unsigned int i, double value) {
        (*($self))[i] = value;
        return (*($self))[i];
        }*/
};


%extend VariableBinAxis {
    double __getitem__(unsigned int i) {
        return (*($self))[i];
    }

    /*  double __setitem__(unsigned int i, double value) {
        (*($self))[i] = value;
        return (*($self))[i];
        } */
};


%extend IAxis {
    bool __ne__(const IAxis& rhs)
    {
        return !(*$self == rhs);
    }
/*
    double __getitem__(unsigned int i) {
      return (*($self))[i];
    }

    double __setitem__(unsigned int i, double value) {
      (*($self))[i] = value;
      return (*($self))[i];
    }
*/
};


%include "stdint.i"

%extend IParameterized {
    virtual void registerParameter(const std::string &name, int64_t parpointer, const AttLimits& limits = AttLimits::limitless())
    {
        return (*($self)).registerParameter(name, (double*)parpointer, limits);
    }

    /* virtual void registerParameter(const std::string &name, int parpointer, const AttLimits& limits = AttLimits::limitless())
    {
        return (*($self)).registerParameter(name, (double*)parpointer, limits);
    } /**/

    /*virtual void registerParameter(const std::string &name, int parpointer, const AttLimits& limits = AttLimits::limitless())
      {
      return (*($self)).registerParameter(name, (double*)parpointer, limits);
      }*/

    /*virtual std::string addParametersToExternalPool(std::string path, int64_t external_pool,
      int copy_number = -1) const
      {
          return ($self)->addParametersToExternalPool(path, ()external_pool.get(), copy_number);
      }/**/
};

%extend ISampleBuilder {
  /*virtual void registerParameter(const std::string &name, double* parpointer, const AttLimits& limits = AttLimits::limitless())
    {
        return (*($self)).registerParameter(name, parpointer, limits);
    } /**/

    virtual void registerParameter(const std::string &name, int64_t parpointer, const AttLimits& limits = AttLimits::limitless())
    {
      return (*($self)).registerParameter(name, (double*)parpointer, limits);
    }/**/


    /*virtual std::string addParametersToExternalPool(std::string path, ParameterPool* external_pool,
                                                    int copy_number = -1) const
    {
        return dynamic_cast<const IParameterized*>($self)->addParametersToExternalPool(path, external_pool, copy_number);
    }/**/

    /*virtual void registerParameter(const std::string &name, int parpointer, const AttLimits& limits = AttLimits::limitless())
    {
        return (*($self)).registerParameter(name, (double*)parpointer, limits);
	}/**/

    /*virtual void registerParameter(const std::string &name, int parpointer, const AttLimits& limits = AttLimits::limitless())
      {
      return (*($self)).registerParameter(name, (double*)parpointer, limits);
      }*/
    virtual void setParameterValue(const std::string &name, double value)
    {
        dynamic_cast<IParameterized*>($self)->setParameterValue(name, value);
    }
};

/* %extend ISampleBuilder {
   virtual std::string addParametersToExternalPool(
   std::string path,
   ParameterPool *external_pool,
   int copy_number=-1) const
   {
   return (*($self)).addParametersToExternalPool(path, external_pool, copy_number);
   }
   };
*/

/*

  %extend ICompositeSample {
  virtual void registerChild(boost::shared_ptr<ISample> sample)
  {
  ($self)->registerChild(sample.get());
  }

  virtual void deregisterChild(boost::shared_ptr<ISample> sample)
  {
  ($self)->deregisterChild(sample.get());
  }
  };

  %extend ISampleVisitor {
  virtual void visit(boost::shared_ptr<ISample> sample)
  {
  ($self)->visit(sample.get());
  }
  };


  %extend ISampleIterator {
  virtual IteratorMemento first(boost::shared_ptr<ISample> p_root)
  {
  return ($self)->first(p_root.get());
  }
  };

  %extend SampleIteratorPreorderStrategy {
  virtual IteratorMemento first(boost::shared_ptr<ISample> p_root)
  {
  return ($self)->first(p_root.get());
  }
  };

  %extend SampleIteratorPostOrderStrategy {
  virtual IteratorMemento first(boost::shared_ptr<ISample> p_root)
  {
  return ($self)->first(p_root.get());
  }
  };
*/


// used to return numpy array
/*
%extend Histogram1D {
    PyObject* getBinCenters() const
    {
        return ($self)->getBinCentersNumpy();
    }

    PyObject* getBinValues() const
    {
        return ($self)->getBinValuesNumpy();
    }

    PyObject* getBinErrors() const
    {
        return ($self)->getBinErrorsNumpy();
    }
}
/**/


 /*
%extend IFitObserver {
    void notify(std::shared_ptr<IObservable> subject)
    {
        ($self)->notify(subject.get());
    }
};
/**/

 // introduced because of FitCylindersAndPrisms example
%extend FitSuiteParameters {
    const FitParameter* __getitem__(std::string name) const
    {
        return (*($self))[name];
    }

    /* void __setitem__(std::string name, const FitParameter* val)
    {
        (*($self))[name] = *val_;
        }*/

    const FitParameter* __getitem__(size_t index) const
    {
        return (*($self))[index];
    }

    /*    void __setitem__(size_t index, const FitParameter* val)
    {
        (*($self))[index] = *val;
        }*/
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

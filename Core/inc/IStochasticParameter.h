#ifndef ISTOCHASTICPARAMETER_H
#define ISTOCHASTICPARAMETER_H

class IStochasticParameter
{
public:
    virtual ~IStochasticParameter() {}
    virtual void setToRandom()=0;
    virtual void setToAverage()=0;
};

#endif // ISTOCHASTICPARAMETER_H

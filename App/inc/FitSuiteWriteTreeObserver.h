#ifndef FITSUITEWRITETREEOBSERVER_H
#define FITSUITEWRITETREEOBSERVER_H

#include "IObserver.h"
#include "OutputData.h"

//! Save results of each fit iteration to the disk in the form of ROOT tree
class FitSuiteWriteTreeObserver : public IObserver
{
public:
    FitSuiteWriteTreeObserver(const std::string &file_name = std::string("fitsuite.root"));
    void update(IObservable *subject);
    virtual ~FitSuiteWriteTreeObserver(){ }

private:
    std::string m_file_name; //! canvas name were to draw
    OutputData<double> *m_prev_data;
};



#endif // FITSUITEWRITETREEOBSERVER_H



#ifndef INSTRUMENTMODEL_H
#define INSTRUMENTMODEL_H

#include "SessionModel.h"

class InstrumentModel : public SessionModel
{
    Q_OBJECT

public:
    explicit InstrumentModel(QObject *parent = 0);
    ~InstrumentModel(){}

};




#endif

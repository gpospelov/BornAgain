#ifndef INSTRUMENTMODEL_H
#define INSTRUMENTMODEL_H

#include "SessionModel.h"
#include <QStringList>

class BA_CORE_API_ InstrumentModel : public SessionModel
{
    Q_OBJECT

public:
    explicit InstrumentModel(QObject *parent = 0);
    ~InstrumentModel(){}

    virtual InstrumentModel *createCopy(ParameterizedItem *parent=0);

    QMap<QString, ParameterizedItem *> getInstrumentMap() const;

};




#endif

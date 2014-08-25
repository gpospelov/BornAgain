#ifndef GUIEXAMPLESFACTORY_H
#define GUIEXAMPLESFACTORY_H

#include <QMap>
#include <QString>

class ParameterizedItem;
class InstrumentModel;
class SampleModel;

//! Class that generates GUI model from
class BA_CORE_API_ GUIExamplesFactory
{
public:
    static bool isValidExampleName(const QString &name);

    static ParameterizedItem *createSampleItems(const QString &name, SampleModel *sampleModel);
    static ParameterizedItem *createInstrumentItems(const QString &name, InstrumentModel *instrumentModel);


private:
    static QMap<QString, QString> m_name_to_registry;
    //!< correspondance of GUI example name and name from StandardSamples registry
};


#endif


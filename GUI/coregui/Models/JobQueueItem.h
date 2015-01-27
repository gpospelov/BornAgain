// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobQueueItem.h
//! @brief     Defines class JobQueueData
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef JOBQUEUEITEM_H
#define JOBQUEUEITEM_H

#include <QString>

//! Simple JobQueueItem with name and jobId which is handled by JobQueueModel
//!
//! See also JobItem which contains real information about the job.
class JobQueueItem
{
public:
    JobQueueItem(QString identifier) : m_identifier(identifier){}

    QString getIdentifier() const { return m_identifier; }
    void setIdentifier(QString identifier) { m_identifier = identifier; }

private:
    QString m_identifier;
};


#endif

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/IMessageService.h
//! @brief     Declares abstract IMessageService interface
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef IMESSAGESERVICE_H
#define IMESSAGESERVICE_H

//! @class IMessageService
//! @brief Abstract class for messaging in our GUI


class IMessageService {
public:
    IMessageService(){}
    virtual ~IMessageService(){}
};

#endif


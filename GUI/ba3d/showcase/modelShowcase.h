// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/showcase/modelShowcase.h
//! @brief     Defines ModelShowcase class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_MODEL_SHOWCASE_H
#define BA3D_MODEL_SHOWCASE_H

#include <ba3d/model/model.h>
#include <ba3d/model/particles.h>

//------------------------------------------------------------------------------

class ModelShowcase : public ba3d::Model {
public:
  using Particle = ba3d::particle::Particle;
  using kind     = ba3d::particle::kind;

  ModelShowcase();
  void showKind(kind);

private:
  Particle *p;
};

//------------------------------------------------------------------------------
#endif

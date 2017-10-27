// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/IMaterialImpl.h
//! @brief     Defines and implements material implementation interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IMATERIALIMPL_H_
#define IMATERIALIMPL_H_

#include "INamed.h"
#include "Vectors3D.h"
#include "Complex.h"
#include "EigenCore.h"

class Transform3D;
class WavevectorInfo;

//! A wrapper for homogeneous and wavelength-independent materials
//! @ingroup materials

class BA_CORE_API_ BaseMaterialImpl : public INamed
{
public:
    //! Constructs basic material with name and magnetization
    BaseMaterialImpl(const std::string& name, kvector_t magnetization);

    virtual ~BaseMaterialImpl();

    //! Returns pointer to a copy of material
    virtual BaseMaterialImpl* clone() const = 0;

    //! Constructs a material with inverted magnetization
    BaseMaterialImpl* inverted() const;

    virtual complex_t refractiveIndex(double wavelength) const = 0;
    virtual complex_t refractiveIndex2(double wavelength) const = 0;

    //! Indicates whether the interaction with the material is scalar.
    //! This means that different polarization states will be diffracted equally
    bool isScalarMaterial() const {return m_magnetization == kvector_t {};}

    bool isMagneticMaterial() const {return !isScalarMaterial();}

    //! Returns the magnetization (in A/m)
    kvector_t magnetization() const {return m_magnetization;}

    //! Returns underlying material data
    virtual complex_t materialData() const = 0;

    //! Returns \pi/(wl*wl) - sld, with wl being the wavelength
    virtual complex_t scalarSubtrSLD(const WavevectorInfo& wavevectors) const = 0;

#ifndef SWIG
    //! Returns \pi/(wl*wl) - sld matrix with magnetization corrections. wl denotes the wavelength
    Eigen::Matrix2cd polarizedSubtrSLD(const WavevectorInfo& wavevectors) const;
#endif

    BaseMaterialImpl* transformedMaterial(const Transform3D& transform) const;

    //! Prints object data
    virtual void print(std::ostream &ostr) const = 0;

private:
    //! Sets the magnetization (in A/m)
    void setMagnetization(kvector_t magnetization)
    {
        m_magnetization = magnetization;
    }

    kvector_t m_magnetization; //!< magnetization
};

#endif /* IMATERIALIMPL_H_ */

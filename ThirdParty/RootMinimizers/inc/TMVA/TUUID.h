#ifndef TUUID_H
#define TUUID_H


#include "TMVA/Types.h"

namespace BA_ROOT {

class TUUID {
public:

    TUUID();

    void GetUUID(UChar_t uuid[16]) const;

protected:
    UInt_t    fTimeLow;               // 60 bit time, lower 32 bits
};

}
#endif


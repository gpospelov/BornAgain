#ifndef TUUID_H
#define TUUID_H


#include "TMVA/Types.h"

class TUUID {
public:

    void GetUUID(UChar_t uuid[16]) const;

protected:
    UInt_t    fTimeLow;               // 60 bit time, lower 32 bits
};


#endif


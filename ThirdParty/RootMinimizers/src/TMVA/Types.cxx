// @(#)root/tmva $Id$
// Author: Andreas Hoecker, Joerg Stelzer, Helge Voss

/**********************************************************************************
 * Project: TMVA - a Root-integrated toolkit for multivariate data analysis       *
 * Package: TMVA                                                                  *
 * Class  : Types                                                                 *
 * Web    : http://tmva.sourceforge.net                                           *
 *                                                                                *
 * Description:                                                                   *
 *      Implementation                                                            *
 *                                                                                *
 * Authors (alphabetical):                                                        *
 *      Andreas Hoecker <Andreas.Hocker@cern.ch> - CERN, Switzerland              *
 *      Joerg Stelzer   <Joerg.Stelzer@cern.ch>  - CERN, Switzerland              *
 *      Helge Voss      <Helge.Voss@cern.ch>     - MPI-K Heidelberg, Germany      *
 *                                                                                *
 * Copyright (c) 2005:                                                            *
 *      CERN, Switzerland                                                         *
 *      U. of Victoria, Canada                                                    *
 *      MPI-K Heidelberg, Germany                                                 *
 *                                                                                *
 * Redistribution and use in source and binary forms, with or without             *
 * modification, are permitted according to the terms listed in LICENSE           *
 * (http://mva.sourceforge.net/license.txt)                                       *
 **********************************************************************************/

#include <map>
#include <iostream>
#if __cplusplus > 199711L
#include <mutex>
#endif

#include "TMVA/Types.h"
//#include "MsgLogger.h"

#if __cplusplus > 199711L
std::atomic<BA_TMVA::Types*> BA_TMVA::Types::fgTypesPtr{0};
static std::mutex gTypesMutex;
#else
BA_TMVA::Types* BA_TMVA::Types::fgTypesPtr = 0;
#endif

//_______________________________________________________________________
BA_TMVA::Types::Types()
//   : fLogger( new MsgLogger("Types") )
{
   // constructor
}

BA_TMVA::Types::~Types()
{
   // destructor
//   delete fLogger;
}

//_______________________________________________________________________
BA_TMVA::Types& BA_TMVA::Types::Instance()
{
   // the the single instance of "Types" if existin already, or create it  (Signleton)
//#if __cplusplus > 199711L
//  if(!fgTypesPtr) {
//    Types* tmp = new Types();
//    Types* expected = 0;
//    if(!fgTypesPtr.compare_exchange_strong(expected,tmp)) {
//      //Another thread already did it
//      delete tmp;
//    }
//  }
//  return *fgTypesPtr;
//#else
   return fgTypesPtr ? *fgTypesPtr : *(fgTypesPtr = new Types());
//#endif
}
//_______________________________________________________________________
void   BA_TMVA::Types::DestroyInstance()
{
   // "destructor" of the single instance
#if __cplusplus > 199711L
   if (fgTypesPtr != 0) { delete fgTypesPtr.load(); fgTypesPtr = 0; }
#else
   if (fgTypesPtr != 0) { delete fgTypesPtr; fgTypesPtr = 0; }
#endif
}


//_______________________________________________________________________
Bool_t BA_TMVA::Types::AddTypeMapping( Types::EMVA method, const std::string& methodname )
{
//#if __cplusplus > 199711L
//   std::lock_guard<std::mutex> guard(gTypesMutex);
//#endif
   std::map<std::string, EMVA>::const_iterator it = fStr2type.find( methodname );
   if (it != fStr2type.end()) {
//       Log() << kFATAL
//             << "Cannot add method " << methodname
//             << " to the name->type map because it exists already" << Endl;
       std::cout << kFATAL
             << "TMVA::Types::AddTypeMapping() -> Fatal. Cannot add method " << methodname
             << " to the name->type map because it exists already" << std::endl;
      return kFALSE;
   }

   fStr2type[methodname] = method;
   return kTRUE;
}

//_______________________________________________________________________
BA_TMVA::Types::EMVA BA_TMVA::Types::GetMethodType( const std::string& method ) const
{
//#if __cplusplus > 199711L
//   std::lock_guard<std::mutex> guard(gTypesMutex);
//#endif
   // returns the method type (enum) for a given method (string)
   std::map<std::string, EMVA>::const_iterator it = fStr2type.find( method );
   if (it == fStr2type.end()) {
//       Log() << kFATAL << "Unknown method in map: " << method << Endl;
       std::cout << kFATAL << "TMVA::Types::GetMethodType-> Fatal. Unknown method in map: " << method << std::endl;
      return kVariable; // Inserted to get rid of GCC warning...
   }
   else return it->second;
}

//_______________________________________________________________________
std::string BA_TMVA::Types::GetMethodName( BA_TMVA::Types::EMVA method ) const
{
//#if __cplusplus > 199711L
//   std::lock_guard<std::mutex> guard(gTypesMutex);
//#endif
   std::map<std::string, EMVA>::const_iterator it = fStr2type.begin();
   for (; it!=fStr2type.end(); it++) if (it->second == method) return it->first;
//   Log() << kFATAL << "Unknown method index in map: " << method << Endl;
   std::cout << kFATAL << "TMVA::Types::GetMethodName() -> Fatal. Unknown method index in map: " << method << std::endl;
   return "";
}

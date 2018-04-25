// @(#)root/tmva $Id$
// Author: Andreas Hoecker, Joerg Stelzer, Helge Voss

/**********************************************************************************
 * Project: TMVA - a Root-integrated toolkit for multivariate data analysis       *
 * Package: TMVA                                                                  *
 * Class  : Types                                                                 *
 * Web    : http://tmva.sourceforge.net                                           *
 *                                                                                *
 * Description:                                                                   *
 *      GLobal types (singleton class)                                            *
 *                                                                                *
 * Authors (alphabetical):                                                        *
 *      Andreas Hoecker <Andreas.Hocker@cern.ch> - CERN, Switzerland              *
 *      Peter Speckmayer <Peter.Speckmayer@cern.ch>  - CERN, Switzerland          *
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

#ifndef ROOT_TMVA_Types
#define ROOT_TMVA_Types

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Types                                                                //
//                                                                      //
// Singleton class for Global types used by TMVA                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include <map>
#if __cplusplus > 199711L
#include <atomic>
#endif

//#ifndef ROOT_Rtypes
//#include "Rtypes.h"
//#endif

//#ifndef ROOT_TString
//#include "TString.h"
//#endif

#include <string>
#include <map>
typedef unsigned int   UInt_t;      //Unsigned integer 4 bytes (unsigned int)
typedef int            Int_t;       //Signed integer 4 bytes (int)
typedef bool           Bool_t;      //Boolean (0=false, 1=true) (bool)
typedef double         Double_t;    //Double 8 bytes
typedef float          Float_t;     //Float 4 bytes (float)
typedef long           Long_t;      //Signed long integer 8 bytes (long)
typedef long double    LongDouble_t;//Long Double
typedef long long          Long64_t; //Portable signed long integer 8 bytes
typedef unsigned long  ULong_t;     //Unsigned long integer 4 bytes (unsigned long)
typedef unsigned char  UChar_t;     //Unsigned Character 1 byte (unsigned char)


const Bool_t kTRUE  = true;
const Bool_t kFALSE = false;

//extern void Info(const char *location, const char *msgfmt, ...)
//#if defined(__GNUC__) && !defined(__CINT__)
//__attribute__((format(printf, 2, 3)))
//#endif
//;
//extern void Warning(const char *location, const char *msgfmt, ...)
//#if defined(__GNUC__) && !defined(__CINT__)
//__attribute__((format(printf, 2, 3)))
//#endif
//;
//extern void Error(const char *location, const char *msgfmt, ...)
//#if defined(__GNUC__) && !defined(__CINT__)
//__attribute__((format(printf, 2, 3)))
//#endif
//;

namespace BA_ROOT {

class TNamed {
public:
    TNamed() {}

    TNamed(const std::string &name, const std::string &title) {
        m_name = name;
        m_title = title;
    }

    void SetName(const std::string &name) { m_name = name; }
    void SetTitle(const std::string &title) { m_title = title; }

    std::string GetName() const { return m_name; }

private:
    std::string m_name;
    std::string m_title;
};

//class TObject : public TNamed {};
}

namespace BA_TMVA {

   typedef UInt_t TMVAVersion_t;

//   class MsgLogger;

   // message types for MsgLogger
   // define outside of Types class to facilite access
   enum EMsgType {
      kDEBUG   = 1,
      kVERBOSE = 2,
      kINFO    = 3,
      kWARNING = 4,
      kERROR   = 5,
      kFATAL   = 6,
      kSILENT  = 7
   };

   enum HistType { kMVAType = 0, kProbaType = 1, kRarityType = 2, kCompareType = 3 };


   class Types {

   public:

      // available MVA methods
      enum EMVA {
         kVariable    = 0,
         kCuts           ,
         kLikelihood     ,
         kPDERS          ,
         kHMatrix        ,
         kFisher         ,
         kKNN            ,
         kCFMlpANN       ,
         kTMlpANN        ,
         kBDT            ,
         kDT             ,
         kRuleFit        ,
         kSVM            ,
         kMLP            ,
         kBayesClassifier,
         kFDA            ,
         kBoost          ,
         kPDEFoam        ,
         kLD             ,
         kPlugins        ,
         kCategory       ,
         kMaxMethod
      };

      // available variable transformations
      enum EVariableTransform {
         kIdentity = 0,
         kDecorrelated,
         kNormalized,
         kPCA,
         kRearranged,
         kGauss,
         kUniform,
         kMaxVariableTransform
      };

      // type of analysis
      enum EAnalysisType {
         kClassification = 0,
         kRegression,
         kMulticlass,
         kNoAnalysisType,
         kMaxAnalysisType
      };

      enum ESBType {
         kSignal = 0,  // Never change this number - it is elsewhere assumed to be zero !
         kBackground,
         kSBBoth,
         kMaxSBType,
         kTrueType
      };

      enum ETreeType {
         kTraining = 0,
         kTesting,
         kMaxTreeType,  // also used as temporary storage for trees not yet assigned for testing;training...
         kValidation,   // these are placeholders... currently not used, but could be moved "forward" if
         kTrainingOriginal     // ever needed
      };

      enum EBoostStage {
         kBoostProcBegin=0,
         kBeforeTraining,
         kBeforeBoosting,
         kAfterBoosting,
         kBoostProcEnd
      };

   public:

      static Types& Instance();
      static void   DestroyInstance();
      ~Types();

//      Types::EMVA   GetMethodType( const TString& method ) const;
//      TString       GetMethodName( Types::EMVA    method ) const;

//      Bool_t        AddTypeMapping(Types::EMVA method, const TString& methodname);

      Types::EMVA   GetMethodType( const std::string& method ) const;
      std::string       GetMethodName( Types::EMVA    method ) const;

      Bool_t        AddTypeMapping(Types::EMVA method, const std::string& methodname);

   private:

      Types();
#if __cplusplus > 199711L
      static std::atomic<Types*> fgTypesPtr;
#else
      static Types* fgTypesPtr;
#endif

   private:

      std::map<std::string, BA_TMVA::Types::EMVA> fStr2type; // types-to-text map
//      mutable MsgLogger* fLogger;   // message logger
//      MsgLogger& Log() const { return *fLogger; }

   };
}

#endif

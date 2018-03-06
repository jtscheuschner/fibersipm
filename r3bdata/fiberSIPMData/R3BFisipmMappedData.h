#ifndef R3BFISIPMMAPPEDDATA_H
#define R3BFISIPMMAPPEDDATA_H

#include "TObject.h"

// for the data analysis of the s438b PSPX detectors. 
// Introduced by Ralf, Jan 2016

class R3BFisipmMappedData : public TObject
{
  public:
    // Default Constructor
    R3BFisipmMappedData();

    // Standard Constructor
    R3BFisipmMappedData(UChar_t detector, UInt_t sipm, UInt_t coarse, UInt_t fine, Bool_t leading);

    // Destructor
    virtual ~R3BFisipmMappedData() { }

    // Getters
    inline const UChar_t& GetDetector() const { return fDetector; }
    inline const UChar_t& GetChannel()  const { return fSiPM;  }
    inline const UInt_t&  GetCoarse()   const { return fcoarse;   }
    inline const UInt_t&  GetFine()     const { return ffine;   }
    inline const Bool_t&  IsLeading()   const { return fleading;     }
    //    inline const UInt_t&  GetFineTrailing()   const { return ftftime;     }

  private:
    UChar_t fDetector; // 0..4
    UChar_t fSiPM   ;  // 0..64
    UInt_t  fcoarse;
    UInt_t  ffine;
    Bool_t  fleading;
    /* UInt_t  flctime; */
    /* UInt_t  flftime; */
 
  public:
    ClassDef(R3BFisipmMappedData, 4)
};

#endif

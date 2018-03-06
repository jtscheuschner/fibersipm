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
    R3BFisipmMappedData(UChar_t detector, UInt_t mppc, UInt_t energy, UInt_t time, Bool_t leading);

    // Destructor
    virtual ~R3BFisipmMappedData() { }

    // Getters
    inline const UChar_t& GetDetector() const { return fDetector; }
    inline const UChar_t& GetChannel()  const { return fSiPM;  }
    inline const UInt_t&  GetCoarseLeading()   const { return flctime;   }
    inline const UInt_t&  GetFineLeading()   const { return flftime;   }
    inline const Bool_t&  IsLeading()     const { return fleading;     }
    //    inline const UInt_t&  GetFineTrailing()   const { return ftftime;     }

  private:
    UChar_t fDetector; // 0..4
    UChar_t fSiPM   ;  // 0..64
    UInt_t  flctime;
    UInt_t  flftime;
    Bool_t  fleading;
    /* UInt_t  flctime; */
    /* UInt_t  flftime; */
 
  public:
    ClassDef(R3BFisipmMappedData, 4)
};

#endif

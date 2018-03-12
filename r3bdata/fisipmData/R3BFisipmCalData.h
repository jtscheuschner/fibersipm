#ifndef R3BFISIPMCALDATA_H
#define R3BFISIPMCALDATA_H

#include "TObject.h"

// for the data analysis of the s438b PSPX detectors. 
// Introduced by Ralf, Jan 2016

class R3BFisipmCalData : public TObject
{
 public:
  // Default Constructor
  R3BFisipmCalData();
  
  // Standard Constructor
  R3BFisipmCalData(UChar_t detector,  // UInt_t fiber_n,
		   UInt_t channel,
		   Float_t TOT_1   ,  // Float_t TOT_2, 
		   Float_t time_l1 ,  // Float_t time_l2,
		   Float_t time_tz1 );//, Float_t time_t2);
    
  // Destructor
  virtual ~R3BFisipmCalData() { }
  
  // Getters
  inline const UChar_t& GetDetector()   const { return fDetector; }
  inline const UChar_t& GetSiPM()   const { return fSiPM; }
  //  inline const UInt_t&  GetFiber()      const { return fFiber_n;  }
  inline const UInt_t&  GetTOT()      const { return fTOT_1;  }
  //  inline const UInt_t&  GetTOT_2()      const { return fTOT_2;  }
  inline const Float_t& GetTime_l()    const { return fTime_l1;  }
  //  inline const Float_t& GetTime_l2()    const { return fTime_l2;   }
  inline const Float_t& GetTime_t()    const { return fTime_t1;    }
  //  inline const Float_t& GetTime_t2()    const { return fTime_t2;  }
  
 private:
  UChar_t fDetector;
  UInt_t fSiPM;
  UInt_t  fTOT_1;  
  Float_t fTime_l1;   // 0xfff is energy data, Anything in 0xfffff000 indicates an error or overflow
  Float_t fTime_t1;   

    
 public:
    ClassDef(R3BFisipmCalData, 2)
      };

#endif

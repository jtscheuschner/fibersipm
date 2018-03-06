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
  R3BFisipmCalData(UChar_t detector, //UInt_t fiber_n, 
		   UInt_t SiPM_1, UInt_t SiPM_2,
		   /* Float_t TOT_1, Float_t TOT_2,  */
		   Float_t time_l1, Float_t time_l2,
		   Float_t time_t1, Float_t time_t2);
    
  // Destructor
  virtual ~R3BFisipmCalData() { }
  
  // Getters
  inline const UChar_t& GetDetector()   const { return fDetector; }
  //  inline const UInt_t&  GetFiber()      const { return fFiber_n;  }
  inline const UInt_t&  GetSiPM()      const { return fSiPM;  }
  //  inline const UInt_t&  GetSiPM()      const { return fSiPM_2;  }
  //inline const UInt_t&  GetTOT_1()      const { return fTOT_1;  }
  //inline const UInt_t&  GetTOT_2()      const { return fTOT_2;  }
  inline const Float_t& GetTime_l1()    const { return fTime_l;  }
  // inline const Float_t& GetTime_l2()    const { return fTime_l2;   }
  inline const Float_t& GetTime_t1()    const { return fTime_t;    }
  //inline const Float_t& GetTime_t2()    const { return fTime_t2;  }
  
 private:
  UChar_t fDetector;
  //  UInt_t  fFiber_n;
  UInt_t  fSiPM;
  // UInt_t  fSiPM_2;
  /* UInt_t  fTOT_1;   */
  /* UInt_t  fTOT_2;   */
  Float_t fTime_l;   // 0xfff is energy data, Anything in 0xfffff000 indicates an error or overflow
  //  Float_t fTime_l2;
  Float_t fTime_t;   
  //  Float_t fTime_t2;   
    
 public:
    ClassDef(R3BFisipmCalData, 2)
      };

#endif

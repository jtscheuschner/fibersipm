#ifndef R3BFISIPMHITDATA_H
#define R3BFISIPMHITDATA_H

#include "TObject.h"

// for the data analysis of the s438b PSPX detectors. 
// Introduced by Ralf, Jan 2016
// adapted by Joachim March 2016

class R3BFisipmHitData : public TObject
{
 public:
  // Default Constructor
  R3BFisipmHitData();
  
  // Standard Constructor
  R3BFisipmHitData(UInt_t detector, UInt_t fiber, Float_t xpos, 
		Float_t tot_1, Float_t tot_2,                               //tot
		Float_t time_1, Float_t time_2);                                  //time
    
  // Destructor
  virtual ~R3BFisipmHitData() { }
  
  // Getters
  inline const UChar_t& GetDetector()       const { return fDetector; }
  inline const UInt_t&  GetFiber()          const { return fFiber_n;  }
  inline const Float_t& GetFiber_Xpos()     const { return fFiber_Xpos;  }
  inline const Float_t& GetTOT_1()     const { return fTOT_1;  }
  inline const Float_t& GetTOT_2()  const { return fTOT_2;   }
  inline const Float_t& GetTime_1()       const { return fTime_1;    }
  inline const Float_t& GetTime_2()    const { return fTime_2;  }
  
 private:
  UChar_t fDetector;
  UInt_t  fFiber_n;
  Float_t fFiber_Xpos; 
  Float_t fTOT_1;   // 0xfff is tot data, Anything in 0xfffff000 indicates an error or overflow
  Float_t fTOT_2;
  Float_t fTime_1;   
  Float_t fTime_2;   
    
 public:
    ClassDef(R3BFisipmHitData, 2)
      };

#endif

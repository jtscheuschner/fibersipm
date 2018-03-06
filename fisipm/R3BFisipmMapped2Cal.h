// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                           R3BFiberSipmMapped2Cal                        -----
// -----                    Created  21-01-2016 by R. Plag                 -----
// -----		adapted to FiberSipm march to ? by j. tscheuschner	   -----
// -----                                                                   -----
// -----------------------------------------------------------------------------
/* Convert Mapped data to Cal data
 */

#ifndef R3BFIBERSIPMMAPPED2CAL_H
#define R3BFIBERSIPMMAPPED2CAL_H

#include "FairTask.h"

class TClonesArray;
class R3BEventHeader;

class R3BFibersipmMapped2Cal : public FairTask
{
  public:
    R3BFibersipmMapped2Cal();
    R3BFibersipmMapped2Cal(const char* name, Int_t iVerbose);
    virtual ~R3BFibersipmMapped2Cal();

    virtual InitStatus Init();

    virtual void Exec(Option_t* option);

    virtual void FinishEvent();
    virtual void FinishTask();
    void SetCalibFile     (TString file=""){fCalibfile =file;};
    //    void SetGainMatchingFile(TString file){fMatchingfile=file;};

 private:
    
    TString fCalibfile;
    R3BEventHeader *fHeader;    // do we need that?
    TClonesArray* fMappedItems; // holding input data
    TClonesArray* fCalItems;    // holding output data
    TClonesArray* fCalibration; // holding slopes and offsets
    
    // calibration parameters, might be recreated in another way soon
    const static UInt_t fNDet = 1;
    const static UInt_t fNChannels = 32;
    //const static UInt_t fNMPPC = fNDet*fNChannels;  // FIXME: commented out because of error with ROOT 5 dictionary
a.u. or so
    //    void ReadGainMatching(TString matchingfile);

  public:
    ClassDef(R3BFibersipmMapped2Cal, 3)
};

#endif

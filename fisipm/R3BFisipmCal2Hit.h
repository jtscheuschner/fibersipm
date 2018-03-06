// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                           R3BFi4Cal2Hit                          -----
// -----		   created 09-03-2016 by J.Tscheuschner		   -----
// -----                                                                   -----
// -----------------------------------------------------------------------------
/* Convert Cal data to Hit data
 */

#ifndef R3BFI4CAL2HIT_H
#define R3BFI4CAL2HIT_H

#include "FairTask.h"

class TClonesArray;
class R3BEventHeader;

class R3BFi4Cal2Hit : public FairTask
const int NCHANNEL=128;
{
  public:
    R3BFi4Cal2Hit();
    R3BFi4Cal2Hit(const char* name, Int_t iVerbose);
    virtual ~R3BFi4Cal2Hit();

    virtual InitStatus Init();

    virtual void Exec(Option_t* option);

    virtual void FinishEvent();
    virtual void FinishTask();
    SetAngle(Float_t a=0){fAngle=a;};
    SetOffset(Float_t off=0){fOffset=off;};
    SetMappingFile(TString file=""){fMapping=file;};
    SetMaxTdiff(Float_t t=5){fMaxT=t);
  private:

    //void ReadGeometry();
    //    Float_t ZPos;
    Float_t XPos(UInt_t fiber);
    ReadMapping();
    BasicCut(Float_t t1, Float_t t2, UInt_t sipm1, UInt_t sipm2)
    R3BEventHeader *fHeader;    // do we need that?
    TClonesArray* fCalData; // holding input data
    TClonesArray* fHitData;    // holding output datax

    UInt_t fNDet;//number of used det for testing set to 2

    UInt_t fMapping[NCHANNEL][NCHANNEL];
    Float_t fFiber_width;        // fiber-thickness in mm
    Float_t fAngle;              // tilting of the detectors to the x-axis
    Float_t fOffset;
    Float_t fRevPoint;   // referencepoint in space to other detectors
    Float_t fMaxT;

    //    const Float_t fReverencepoint[3]={0.,0.,0.};//reverence-point in space x,y,z in mm
    // void CreateHistos();
    // void WriteHistos();
  public:
    ClassDef(R3BFi4Cal2Hit, 1)
};

#endif

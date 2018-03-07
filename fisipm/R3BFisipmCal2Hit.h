// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                           R3BFisipmCal2Hit                          -----
// -----		   created 09-03-2016 by J.Tscheuschner		   -----
// -----                                                                   -----
// -----------------------------------------------------------------------------
/* Convert Cal data to Hit data
 */

#ifndef R3BFISIPMCAL2HIT_H
#define R3BFISIPMCAL2HIT_H

#include "FairTask.h"

const int NCHANNEL=128;

class TClonesArray;
class R3BEventHeader;

class R3BFisipmCal2Hit : public FairTask

{
  public:
    R3BFisipmCal2Hit();
    R3BFisipmCal2Hit(const char* name, Int_t iVerbose);
    virtual ~R3BFisipmCal2Hit();

    virtual InitStatus Init();

    virtual void Exec(Option_t* option);

    virtual void FinishEvent();
    virtual void FinishTask();
    Float_t fFiber_width;        // fiber-thickness in mm
    Float_t fAngle;              // tilting of the detectors to the x-axis
    Float_t fOffset;
    Float_t fRevPoint;   // referencepoint in space to other detectors
    Float_t fMaxT;
    TString fMappingfile;

    Bool_t BasicCut(Float_t t1, Float_t t2, UInt_t sipm1, UInt_t sipm2);
    void ReadMapping();
    void SetAngle(Float_t a=0){fAngle=a;};
    void SetFiberWidth(Float_t w=0.2){fFiber_width=w;};
    void SetMappingFile(TString file=""){fMappingfile=file;};
    void SetMaxTdiff(Float_t t=5){fMaxT=t;};
    void SetOffset(Float_t off=0){fOffset=off;};
    
 private:

    //void ReadGeometry();
    //    Float_t ZPos;
    Float_t XPos(UInt_t fiber);
    R3BEventHeader *fHeader;    // do we need that?
    TClonesArray* fCalData; // holding input data
    //    TClonesArray* fCalData2; // holding input data
    TClonesArray* fHitData;    // holding output datax

    UInt_t fNDet;//number of used det for testing set to 2

    UInt_t fMapping[NCHANNEL][NCHANNEL];

    //    const Float_t fReverencepoint[3]={0.,0.,0.};//reverence-point in space x,y,z in mm
    // void CreateHistos();
    // void WriteHistos();
  public:
    ClassDef(R3BFisipmCal2Hit, 1)
};

#endif

// Configuration macro for setting common cuts and processes for G3, G4 and Fluka.
// Specific cuts and processes to G3 or G4 should be set in the g3Config.C, g4Config.C or flConfig.C

void SetCuts()
{
    cout << "[SetCuts]: Setting Cuts ..." << endl;

    const Double_t cut1 = 1.0E-4;  // GeV --> 100 keV
    const Double_t cut2 = 1.0E-3;  // GeV --> 1 MeV
    const Double_t tofmax = 1.E10; // seconds

    gMC->SetCut("CUTGAM", cut1);   /** gammas (GeV)*/
    gMC->SetCut("CUTELE", cut2);   /** electrons (GeV)*/
    gMC->SetCut("CUTNEU", cut1);   /** neutral hadrons (GeV)*/
    gMC->SetCut("CUTHAD", cut2);   /** charged hadrons (GeV)*/
    gMC->SetCut("CUTMUO", cut2);   /** muons (GeV)*/
    gMC->SetCut("BCUTE", cut2);    /** electron bremsstrahlung (GeV)*/
    gMC->SetCut("BCUTM", cut2);    /** muon and hadron bremsstrahlung(GeV)*/
    gMC->SetCut("DCUTE", cut2);    /** delta-rays by electrons (GeV)*/
    gMC->SetCut("DCUTM", cut2);    /** delta-rays by muons (GeV)*/
    gMC->SetCut("PPCUTM", cut2);   /** direct pair production by muons (GeV)*/
    gMC->SetCut("TOFMAX", tofmax); /**time of flight cut in seconds*/
}

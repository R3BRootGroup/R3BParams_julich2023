
#include <iostream>
#include <string>
#include "math.h"
using namespace std;

void make_foot_mapping_and_calpar(){


   FairRuntimeDb* rtdb = FairRuntimeDb::instance();
   

    TString dir = gSystem->Getenv("VMCWORKDIR");
    TString mapdir = dir + "/../R3BParams_julich2023/foot/";
    TString mapfilename = mapdir + "foot_mapping.par";
    mapfilename.ReplaceAll("//", "/");
    
    FairParAsciiFileIo* parIo1 = new FairParAsciiFileIo(); // Ascii
    parIo1->open(mapfilename, "in");
    rtdb->setFirstInput(parIo1);
    rtdb->print();
    
    auto *fMap_Par = (R3BFootMappingPar*)rtdb->getContainer("footMappingPar");
   
    auto *fStrip_Par = (R3BFootCalPar*)rtdb->getContainer("footCalPar");

    UInt_t runId = 1;
    rtdb->initContainers(runId);

    //fStrip_Par->printParams();
    
    int numPars=2;
    int fNumDets=2;
    int fNumStrips=640;
    fStrip_Par->SetNumDets(fNumDets);
    fStrip_Par->SetNumStrips(fNumStrips);
    fStrip_Par->GetStripCalParams()->Set(numPars * fNumStrips * fNumDets);
       
       
    TString filename = "test15july_50V.root";
       
  TFile *datafile = new TFile(filename,"read");
  TTree *tree = (TTree*)datafile->Get("h101");
  
  UInt_t FOOT1,FOOT2,FOOT3,FOOT4,FOOT5,FOOT6,FOOT7,FOOT8,FOOT9,FOOT10;
  UInt_t FOOT11,FOOT12,FOOT13,FOOT14,FOOT15,FOOT16,FOOT17,FOOT18,FOOT19,FOOT20;
  UInt_t FOOT1E[640],FOOT2E[640],FOOT3E[640],FOOT4E[640],FOOT5E[640],FOOT6E[640],FOOT7E[640],FOOT8E[640],FOOT9E[640],FOOT10E[640];
  UInt_t FOOT11E[640],FOOT12E[640],FOOT13E[640],FOOT14E[640],FOOT15E[640],FOOT16E[640],FOOT17E[640],FOOT18E[640],FOOT19E[640],FOOT20E[640];
  UInt_t FOOT1I[640],FOOT2I[640],FOOT3I[640],FOOT4I[640],FOOT5I[640],FOOT6I[640],FOOT7I[640],FOOT8I[640],FOOT9I[640],FOOT10I[640];
  UInt_t FOOT11I[640],FOOT12I[640],FOOT13I[640],FOOT14I[640],FOOT15I[640],FOOT16I[640],FOOT17I[640],FOOT18I[640],FOOT19I[640],FOOT20I[640];
  UInt_t Trigger;

  tree->SetBranchAddress("TRIGGER",&Trigger);
  tree->SetBranchAddress("FOOT1",&FOOT1);
  tree->SetBranchAddress("FOOT2",&FOOT2);
  tree->SetBranchAddress("FOOT3",&FOOT3);
  tree->SetBranchAddress("FOOT4",&FOOT4);
  tree->SetBranchAddress("FOOT5",&FOOT5);
  tree->SetBranchAddress("FOOT6",&FOOT6);
  tree->SetBranchAddress("FOOT7",&FOOT7);
  tree->SetBranchAddress("FOOT8",&FOOT8);
  tree->SetBranchAddress("FOOT9",&FOOT9);
  tree->SetBranchAddress("FOOT10",&FOOT10);
  tree->SetBranchAddress("FOOT11",&FOOT11);
  tree->SetBranchAddress("FOOT12",&FOOT12);
  tree->SetBranchAddress("FOOT13",&FOOT13);
  tree->SetBranchAddress("FOOT14",&FOOT14);
  tree->SetBranchAddress("FOOT15",&FOOT15);
  tree->SetBranchAddress("FOOT16",&FOOT16);
  tree->SetBranchAddress("FOOT17",&FOOT17);
  tree->SetBranchAddress("FOOT18",&FOOT18);
  tree->SetBranchAddress("FOOT19",&FOOT19);
  tree->SetBranchAddress("FOOT20",&FOOT20);
  tree->SetBranchAddress("FOOT1E",&FOOT1E);
  tree->SetBranchAddress("FOOT2E",&FOOT2E);
  tree->SetBranchAddress("FOOT3E",&FOOT3E);
  tree->SetBranchAddress("FOOT4E",&FOOT4E);
  tree->SetBranchAddress("FOOT5E",&FOOT5E);
  tree->SetBranchAddress("FOOT6E",&FOOT6E);
  tree->SetBranchAddress("FOOT7E",&FOOT7E);
  tree->SetBranchAddress("FOOT8E",&FOOT8E);
  tree->SetBranchAddress("FOOT9E",&FOOT9E);
  tree->SetBranchAddress("FOOT10E",&FOOT10E);
  tree->SetBranchAddress("FOOT11E",&FOOT11E);
  tree->SetBranchAddress("FOOT12E",&FOOT12E);
  tree->SetBranchAddress("FOOT13E",&FOOT13E);
  tree->SetBranchAddress("FOOT14E",&FOOT14E);
  tree->SetBranchAddress("FOOT15E",&FOOT15E);
  tree->SetBranchAddress("FOOT16E",&FOOT16E);
  tree->SetBranchAddress("FOOT17E",&FOOT17E);
  tree->SetBranchAddress("FOOT18E",&FOOT18E);
  tree->SetBranchAddress("FOOT19E",&FOOT19E);
  tree->SetBranchAddress("FOOT20E",&FOOT20E);
  tree->SetBranchAddress("FOOT1I",&FOOT1I);
  tree->SetBranchAddress("FOOT2I",&FOOT2I);
  tree->SetBranchAddress("FOOT3I",&FOOT3I);
  tree->SetBranchAddress("FOOT4I",&FOOT4I);
  tree->SetBranchAddress("FOOT5I",&FOOT5I);
  tree->SetBranchAddress("FOOT6I",&FOOT6I);
  tree->SetBranchAddress("FOOT7I",&FOOT7I);
  tree->SetBranchAddress("FOOT8I",&FOOT8I);
  tree->SetBranchAddress("FOOT9I",&FOOT9I);
  tree->SetBranchAddress("FOOT10I",&FOOT10I);
  tree->SetBranchAddress("FOOT11I",&FOOT11I);
  tree->SetBranchAddress("FOOT12I",&FOOT12I);
  tree->SetBranchAddress("FOOT13I",&FOOT13I);
  tree->SetBranchAddress("FOOT14I",&FOOT14I);
  tree->SetBranchAddress("FOOT15I",&FOOT15I);
  tree->SetBranchAddress("FOOT16I",&FOOT16I);
  tree->SetBranchAddress("FOOT17I",&FOOT17I);
  tree->SetBranchAddress("FOOT18I",&FOOT18I);
  tree->SetBranchAddress("FOOT19I",&FOOT19I);
  tree->SetBranchAddress("FOOT20I",&FOOT20I);


  //Hist definition
  TH2D *h2_EnergyVSStripId[20];
  for(Int_t i=0 ; i<20 ; i++){
    h2_EnergyVSStripId[i] = new TH2D(Form("h%d",i+1),Form("h%d",i+1),640,1,641,5000,0,5000);
  }
  
  for(Int_t i=0 ; i<tree->GetEntries() ; i++){

    tree->GetEntry(i);

    if(Trigger==1){
    
      if(i%100 == 0){
	std::clog << "Analysis Info    :   " << i*100/tree->GetEntries() << " % event treated" << "\r";
      }

      for(Int_t j=0 ; j<640 ; j++){
      
	//Raw data
	h2_EnergyVSStripId[0]->Fill(FOOT1I[j],FOOT1E[j]);
	h2_EnergyVSStripId[1]->Fill(FOOT2I[j],FOOT2E[j]);
	h2_EnergyVSStripId[2]->Fill(FOOT3I[j],FOOT3E[j]);
	h2_EnergyVSStripId[3]->Fill(FOOT4I[j],FOOT4E[j]);
	h2_EnergyVSStripId[4]->Fill(FOOT5I[j],FOOT5E[j]);
	h2_EnergyVSStripId[5]->Fill(FOOT6I[j],FOOT6E[j]);
	h2_EnergyVSStripId[6]->Fill(FOOT7I[j],FOOT7E[j]);
	h2_EnergyVSStripId[7]->Fill(FOOT8I[j],FOOT8E[j]);
	h2_EnergyVSStripId[8]->Fill(FOOT9I[j],FOOT9E[j]);
	h2_EnergyVSStripId[9]->Fill(FOOT10I[j],FOOT10E[j]);
	h2_EnergyVSStripId[10]->Fill(FOOT11I[j],FOOT11E[j]);
	h2_EnergyVSStripId[11]->Fill(FOOT12I[j],FOOT12E[j]);
        h2_EnergyVSStripId[12]->Fill(FOOT13I[j],FOOT13E[j]);
        h2_EnergyVSStripId[13]->Fill(FOOT14I[j],FOOT14E[j]);
        h2_EnergyVSStripId[14]->Fill(FOOT15I[j],FOOT15E[j]);
        h2_EnergyVSStripId[15]->Fill(FOOT16I[j],FOOT16E[j]);
        h2_EnergyVSStripId[16]->Fill(FOOT17I[j],FOOT17E[j]);
        h2_EnergyVSStripId[17]->Fill(FOOT18I[j],FOOT18E[j]);
        h2_EnergyVSStripId[18]->Fill(FOOT19I[j],FOOT19E[j]);
        h2_EnergyVSStripId[19]->Fill(FOOT20I[j],FOOT20E[j]);
        
      }
    }
  }
  //std::clog << std::endl;



h2_EnergyVSStripId[15]->Draw("col");


  for(int d=0;d<fNumDets;d++){
  TH1D *h1_Energy;
  TF1 *Fit_Gaus = new TF1("Gaus","gaus",1,5000);
  for(Int_t i=0 ; i<fNumStrips ; i++){
    h1_Energy = h2_EnergyVSStripId[d+14]->ProjectionY(Form("EnergyStrip_%d",i+1),i+1,i+1);
    if(h1_Energy->Integral()>10){
      Fit_Gaus->SetParameter(1,300);   
      Fit_Gaus->SetParameter(2,3.);
      h1_Energy->Fit(Fit_Gaus,"QR");

     
      int nbstrip = numPars * i + d * numPars * fNumStrips;
     
    
      fStrip_Par->SetStripCalParams(Fit_Gaus->GetParameter(1), nbstrip);
      fStrip_Par->SetStripCalParams(Fit_Gaus->GetParameter(2), nbstrip + 1);
      //}
    }
  }
  }
  

   
   
   fMap_Par->setChanged();
   fStrip_Par->setChanged();
    
    //fStrip_Par->printParams();
    
    
      //2-Ascii file with the Calibartion Parameters
  FairParAsciiFileIo* parIo2 = new FairParAsciiFileIo();
  parIo2->open("foot_CalPar_20230715_50V.par","out");
  rtdb->setOutput(parIo2);
  
    /* Save parameters (if needed) -------------------------- */
  rtdb->saveOutput();
   
}

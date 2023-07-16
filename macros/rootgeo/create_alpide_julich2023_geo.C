//
//   ----- Macro for generating ALPIDE geometry for the cern 2022 test
//
//         Author: Jose Luis <joseluis.rodriguez.sanchez@usc.es>
//
//         Last Update: 28/10/22 (Jose Luis)
//
//         Comments:
//

#include "TGeoManager.h"
#include "TMath.h"
#include <iomanip>
#include <iostream>

void create_alpide_julich2023_geo(const char *geoTag = "202210") {
  // --------------------------------------------------------------------------
  // Use this macro to create root files with the different configurations
  // and positions of the vacuum chamber.
  //
  // Execute macro:  root -l
  //                 .L create_beamtracking_alpide_geo.C
  //                 create_beamtracking_alpide_geo()
  // --------------------------------------------------------------------------

  TGeoRotation *fRefRot = NULL;
  TGeoManager *gGeoMan = NULL;

  // -------   Load media from media file   -----------------------------------
  FairGeoLoader *geoLoad = new FairGeoLoader("TGeo", "FairGeoLoader");
  FairGeoInterface *geoFace = geoLoad->getGeoInterface();
  TString geoPath = gSystem->Getenv("VMCWORKDIR");
  TString medFile = geoPath + "/geometry/media_r3b.geo";
  geoFace->setMediaFile(medFile);
  geoFace->readMedia();
  gGeoMan = gGeoManager;
  // --------------------------------------------------------------------------

  // -------   Geometry file name (output)   ----------------------------------
  TString geoFileName = geoPath + "/geometry/tracking_alpide_cern_";
  geoFileName = geoFileName + geoTag + ".geo.root";
  // --------------------------------------------------------------------------

  // -----------------   Get and create the required media    -----------------
  FairGeoMedia *geoMedia = geoFace->getMedia();
  FairGeoBuilder *geoBuild = geoLoad->getGeoBuilder();

  FairGeoMedium *mVac = geoMedia->getMedium("vacuum");
  if (!mVac)
    Fatal("Main", "FairMedium vacuum not found");
  geoBuild->createMedium(mVac);
  TGeoMedium *pMedVac = gGeoMan->GetMedium("vacuum");
  if (!pMedVac)
    Fatal("Main", "Medium vacuum not found");

  FairGeoMedium *mCu = geoMedia->getMedium("copper");
  if (!mCu)
    Fatal("Main", "FairMedium copper not found");
  geoBuild->createMedium(mCu);
  TGeoMedium *pMed1 = gGeoMan->GetMedium("copper");
  if (!pMed1)
    Fatal("Main", "Medium copper not found");

  FairGeoMedium *mAl = geoMedia->getMedium("aluminium");
  if (!mAl)
    Fatal("Main", "FairMedium aluminium not found");
  geoBuild->createMedium(mAl);
  TGeoMedium *pMed2 = gGeoMan->GetMedium("aluminium");
  if (!pMed2)
    Fatal("Main", "Medium aluminium not found");

  FairGeoMedium *mSteel = geoMedia->getMedium("Steel");
  if (!mSteel)
    Fatal("Main", "FairMedium Steel not found");
  geoBuild->createMedium(mSteel);
  TGeoMedium *pMed3 = gGeoMan->GetMedium("Steel");
  if (!pMed3)
    Fatal("Main", "Medium Steel not found");

  FairGeoMedium *mMylar = geoMedia->getMedium("mylar");
  if (!mMylar)
    Fatal("Main", "FairMedium mylar not found");
  geoBuild->createMedium(mMylar);
  TGeoMedium *pMed4 = gGeoMan->GetMedium("mylar");
  if (!pMed4)
    Fatal("Main", "Medium mylar not found");

  FairGeoMedium *mH2 = geoMedia->getMedium("H2");
  if (!mH2)
    Fatal("Main", "FairMedium H2 not found");
  geoBuild->createMedium(mH2);
  TGeoMedium *pMed5 = gGeoMan->GetMedium("H2");
  if (!pMed5)
    Fatal("Main", "Medium H2 not found");

  FairGeoMedium *mSi = geoMedia->getMedium("silicon");
  if (!mSi)
    Fatal("Main", "FairMedium silicon not found");
  geoBuild->createMedium(mSi);
  TGeoMedium *pMedSi = gGeoMan->GetMedium("silicon");
  if (!pMedSi)
    Fatal("Main", "Medium silicon not found");

  FairGeoMedium *mGold = geoMedia->getMedium("gold");
  if (!mGold)
    Fatal("Main", "FairMedium gold not found");
  geoBuild->createMedium(mGold);
  TGeoMedium *pMedGold = gGeoMan->GetMedium("gold");
  if (!pMedGold)
    Fatal("Main", "Medium gold not found");

  FairGeoMedium *mKapton = geoMedia->getMedium("kapton");
  if (!mKapton)
    Fatal("Main", "FairMedium kapton not found");
  geoBuild->createMedium(mKapton);
  TGeoMedium *pMed41 = gGeoMan->GetMedium("kapton");
  if (!pMed41)
    Fatal("Main", "Medium kapton not found");

  FairGeoMedium *mCCooling = geoMedia->getMedium("carboncooling");
  if (!mCCooling)
    Fatal("Main", "FairMedium carboncooling not found");
  geoBuild->createMedium(mCCooling);
  TGeoMedium *pMed42 = gGeoMan->GetMedium("carboncooling");
  if (!pMed42)
    Fatal("Main", "Medium carboncooling not found");

  FairGeoMedium *mPolyamide = geoMedia->getMedium("polyamide");
  if (!mPolyamide)
    Fatal("Main", "FairMedium polyamide not found");
  geoBuild->createMedium(mPolyamide);
  TGeoMedium *pMed43 = gGeoMan->GetMedium("polyamide");
  if (!pMed43)
    Fatal("Main", "Medium polyamide not found");

  // --------------------------------------------------------------------------

  // --------------   Create geometry and top volume  -------------------------
  gGeoMan = (TGeoManager *)gROOT->FindObject("FAIRGeom");
  gGeoMan->SetName("TrackingAlpidegeom");
  TGeoVolume *top = new TGeoVolumeAssembly("TOP");
  gGeoMan->SetTopVolume(top);
  // --------------------------------------------------------------------------

  TGeoShape *outbox = new TGeoBBox("s_box", 8. / 2., 8. / 2., 45.);

  TGeoVolume *pWorld = new TGeoVolume("VCWorld", outbox, pMedVac);

  TGeoCombiTrans *t0 = new TGeoCombiTrans(0., 0., 0., fRefRot);

  TGeoRotation *arot = new TGeoRotation();
  arot->RotateY(90.);
  arot->RotateX(90.);

  //----- Add the box as Mother Volume
  top->AddNode(pWorld, 0, t0);

  Double_t dx, dy, dz;
  Double_t thx, thy, thz;
  Double_t phx, phy, phz;



  int nbdet = 6;
  float thSmask = 0.0015;  // two
  float thAlBand = 0.0005; // two
  float thKapton = 0.0045; // Polyamide: 29 jun 2021 -> Oleg
  float thGlue = 0.0002;   // two
  float thAlpide = 0.0050; // one
  float thFleece = 0.0010; // two, carbon
  float thcooling = 0.0140;

  // Initial position
  dz = -6.;

  auto mask = gGeoManager->MakeBox("mask", pMedSi, 1.5, thSmask / 2., 3.0);
  auto AlBand = gGeoManager->MakeBox("Al", pMed2, 1.5, thAlBand / 2., 3.0);
  auto KBand = gGeoManager->MakeBox("Kapton", pMed43, 1.5, thKapton / 2., 3.0);
  auto glue = gGeoManager->MakeBox("Glue", pMed43, 1.5, thGlue / 2., 3.0);
  auto fleece = gGeoManager->MakeBox("Fleece", pMedSi, 1.5, thFleece / 2., 3.0);
  auto Cooling =
      gGeoManager->MakeBox("Cooling", pMed42, 1.5, thcooling / 2., 3.0);
  auto Alpide =
      gGeoManager->MakeBox("Alpide", pMedSi, 1.5 / 2., thAlpide / 2., 3.0 / 2.);

  Char_t buffer[126];
  TGeoVolume *Plane[nbdet];
  for (Int_t i = 0; i < nbdet; i++) {
    sprintf(buffer, "Multilayer_%i", i + 1);
    Plane[i] = gGeoManager->MakeBox(buffer, pMedVac, 1.51,
                                    thSmask * 2. + thcooling + thAlBand * 2. +
                                        thKapton + thGlue * 2. + thAlpide +
                                        thFleece * 2.,
                                    3.01);
  }

  mask->SetLineColor(kGreen);
  mask->SetVisLeaves(kTRUE);
  glue->SetLineColor(kBlue);
  glue->SetVisLeaves(kTRUE);
  Alpide->SetLineColor(kOrange);
  Alpide->SetVisLeaves(kTRUE);
  AlBand->SetLineColor(kGray);
  AlBand->SetVisLeaves(kTRUE);
  KBand->SetLineColor(28);
  KBand->SetVisLeaves(kTRUE);
  Cooling->SetLineColor(kOrange + 3);
  Cooling->SetVisLeaves(kTRUE);
  fleece->SetLineColor(kGray);
  fleece->SetVisLeaves(kTRUE);

  for (Int_t n = 0; n < 1; n++) {
    float fdz = 0.;

    fdz += -thAlBand - thAlpide / 2.0 - thKapton - thGlue - thSmask / 2.0;
    auto pMatrixd0 = new TGeoCombiTrans("", 0., fdz, 0., fRefRot);
    //Plane[n]->AddNode(mask, 1, pMatrixd0);

    fdz += thSmask / 2.0 + thGlue / 2.0;
    pMatrixd0 = new TGeoCombiTrans("", 0., fdz, 0., fRefRot);
    //Plane[n]->AddNode(glue, 1, pMatrixd0);

    fdz += thGlue / 2.0 + thAlBand / 2.0;
    pMatrixd0 = new TGeoCombiTrans("", 0., fdz, 0., fRefRot);
    //Plane[n]->AddNode(AlBand, 1, pMatrixd0);

    fdz += thAlBand / 2.0 + thKapton / 2.0;
    pMatrixd0 = new TGeoCombiTrans("", 0., fdz, 0., fRefRot);
    //Plane[n]->AddNode(KBand, 1, pMatrixd0);

    fdz += thKapton / 2.0 + thAlBand / 2.0;
    pMatrixd0 = new TGeoCombiTrans("", 0., fdz, 0., fRefRot);
    //Plane[n]->AddNode(AlBand, 1, pMatrixd0);

    fdz += thAlBand / 2.0 + thGlue / 2.0;
    pMatrixd0 = new TGeoCombiTrans("", 0., fdz, 0., fRefRot);
    //Plane[n]->AddNode(glue, 1, pMatrixd0);

    fdz += thGlue / 2.0 + thAlpide / 2.0;
    pMatrixd0 = new TGeoCombiTrans("", 0., fdz, 0., fRefRot);
    Plane[n]->AddNode(Alpide, 1, pMatrixd0);

    // fdz += thAlpide / 2.0 + thFleece / 2.0;
    // pMatrixd0 = new TGeoCombiTrans("", 0., 0., fdz, fRefRot);
    // Plane[n]->AddNode(fleece, 1, pMatrixd0);

    // fdz += thFleece / 2.0 + thcooling / 2.0;
    // pMatrixd0 = new TGeoCombiTrans("", 0., 0., fdz, fRefRot);
    // Plane[n]->AddNode(Cooling, 1, pMatrixd0);

    // fdz += thcooling / 2.0 + thFleece / 2.0;
    // pMatrixd0 = new TGeoCombiTrans("", 0., 0., fdz, fRefRot);
    // Plane[n]->AddNode(fleece, 1, pMatrixd0);

    //pMatrixd0 = new TGeoCombiTrans("", 0., 0., dz, arot);
    //pWorld->AddNode(Plane[n], 1 + n, pMatrixd0);

    //dz += (n % 2) == 0 ? 3.0 : 1.5;
  }

  float poszdet[6]={-43.85,-39.35,-35.35,35.35,39.35,43.85};
  for (Int_t n = 0; n < nbdet; n++) {

    auto pMatrixd0 = new TGeoCombiTrans("", 0., 0., poszdet[n], arot);
    pWorld->AddNode(Plane[0], 1 + n, pMatrixd0);

    //dz += (n % 2) == 0 ? 3.0 : 1.5;
  }

  // ---------------   Finish   -----------------------------------------------
  gGeoMan->CloseGeometry();
  gGeoMan->CheckOverlaps(0.001);
  gGeoMan->PrintOverlaps();
  gGeoMan->Test();

  TFile *geoFile = new TFile(geoFileName, "RECREATE");
  top->Write();
  top->Draw();
  geoFile->Close();
  std::cout << "\033[34m Creating geometry:\033[0m "
            << "\033[33m" << geoFileName << " \033[0m" << std::endl;
  //gApplication->Terminate();
}

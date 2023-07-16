typedef struct EXT_STR_h101_t {
  EXT_STR_h101_unpack_t unpack;
  EXT_STR_h101_TPAT_t unpacktpat;
  EXT_STR_h101_WRMASTER_t wrmaster;
  EXT_STR_h101_ROLU_onion_t rolu;
  EXT_STR_h101_FOOT_onion_t foot;
} EXT_STR_h101;

void online_foot(const Int_t nev = -1) {
  TStopwatch timer;
  timer.Start();

  FairLogger::GetLogger()->SetLogScreenLevel("info");
  FairLogger::GetLogger()->SetColoredLog(true);

  //auto t = std::time(nullptr);
  //auto tm = *std::localtime(&t);
  //std::ostringstream oss;
  //oss << std::put_time(&tm, "%Y%m%d_%H%M%S");

  // TString filename = "--stream=krpc003:9003";
  TString filename = "--stream=frs074:9003";
  //TString filename = "~/lmd/julich2023/run003.lmd";
  TString outputpath = "./";
  TString outputFileName = outputpath + "foot_analysis_today.root";

  const Int_t fRunId = 1;
  Bool_t Cal_level =
      true; // set true if there exists a file with the calibration parameters

  Bool_t fRolu = true; // Rolu detector
  Bool_t NOTstoremappeddata =
      false; // if true, don't store mapped data in the root file
  Bool_t NOTstorecaldata =
      false; // if true, don't store cal data in the root file
  Bool_t NOTstorehitdata =
      false; // if true, don't store hit data in the root file

  // Online server configuration --------------------------
  Int_t refresh = 10; // Refresh rate for online histograms
  Int_t port = 8886;
  TString dir = gSystem->Getenv("VMCWORKDIR");

  // FOOT parameter file
  TString pardir = dir + "/../R3BParams_julich2023/";
  TString footparfilename = pardir + "foot/foot_CalPar_20230715_0V.par";
  footparfilename.ReplaceAll("//", "/");

  // TString ntuple_options = "RAW,time-stitch=1000";
  TString ntuple_options = "RAW";
  TString ucesb_dir = getenv("UCESB_DIR");
  TString upexps_dir = ucesb_dir + "/../upexps/";
  TString ucesb_path;
  ucesb_path = upexps_dir + "/202307_juelich/202307_juelich --allow-errors";
  ucesb_path.ReplaceAll("//", "/");

  // Load ucesb structure ---------------------------------
  EXT_STR_h101 ucesb_struct;

  // Create online run ------------------------------------
  FairRunOnline *run = new FairRunOnline();
  R3BEventHeader *EvntHeader = new R3BEventHeader();
  run->SetEventHeader(EvntHeader);
  run->SetRunId(1);
  run->SetSink(new FairRootFileSink(outputFileName));
  run->ActivateHttpServer(refresh, port);

  // Create source using ucesb for input ------------------
  R3BUcesbSource *source =
      new R3BUcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct,
                         sizeof(ucesb_struct));
  source->SetMaxEvents(nev);

  // Add readers ------------------------------------------
  source->AddReader(new R3BUnpackReader(&ucesb_struct.unpack,
                                        offsetof(EXT_STR_h101, unpack)));
  auto unpacktrloii = new R3BTrloiiTpatReader(
      &ucesb_struct.unpacktpat, offsetof(EXT_STR_h101, unpacktpat));
  // unpacktrloii->SetTrigger(1);
  // unpacktrloii->SetTpatRange(4,4);
  source->AddReader(unpacktrloii);

  source->AddReader(new R3BWhiterabbitMasterReader(
      (EXT_STR_h101_WRMASTER *)&ucesb_struct.wrmaster,
      offsetof(EXT_STR_h101, wrmaster), 0x100));

  auto unpackrolu =
      new R3BRoluReader((EXT_STR_h101_ROLU_onion *)&ucesb_struct.rolu,
                        offsetof(EXT_STR_h101, rolu));
  unpackrolu->SetNbDet(1);
  unpackrolu->SetOnline(NOTstoremappeddata);
  source->AddReader(unpackrolu);

  auto unpackfoot =
      new R3BFootSiReader(&ucesb_struct.foot, offsetof(EXT_STR_h101, foot));
  // unpackfoot->SetNbDetectors(2);

  // Add readers ------------------------------------------
  unpackfoot->SetOnline(NOTstoremappeddata);
  source->AddReader(unpackfoot);

  run->SetSource(source);

  // Runtime data base ------------------------------------
  FairRuntimeDb *rtdb = run->GetRuntimeDb();

  if (Cal_level) {
    // Load parameters --------------------------------------
    // FOOT mapping

    // Root file
    Bool_t kParameterMerged = kFALSE;
    auto parIo1 = new FairParRootFileIo(kParameterMerged);
    TList *parList1 = new TList();

    if (fRolu) {
      parList1->Add(new TObjString(pardir + "rolu/roluTcalPar_v1.root"));
      parIo1->open(parList1, "in");
      rtdb->setFirstInput(parIo1);
    }

    FairParAsciiFileIo *parIo2 = new FairParAsciiFileIo(); // Ascii file
    parIo2->open(footparfilename, "in");
    if (fRolu) {
      rtdb->setSecondInput(parIo2);
      rtdb->addRun(fRunId);

      rtdb->getContainer("RoluTCalPar");
      rtdb->setInputVersion(fRunId, (char *)"RoluTCalPar", 1, 1);
    } else
      rtdb->setFirstInput(parIo2);

    rtdb->print();

    if (fRolu) {
      auto roluMapped2Cal = new R3BRoluMapped2Cal();
      roluMapped2Cal->SetNofModules(1, 4);
      roluMapped2Cal->SetTrigger(-1);
      roluMapped2Cal->SetOnline(NOTstorecaldata);
      run->AddTask(roluMapped2Cal);

      R3BRoluCal2Hit *roluCal2Hit = new R3BRoluCal2Hit("RoluCal2Hit", 1);
      roluCal2Hit->SetNofModules(1, 4);
      run->AddTask(roluCal2Hit);
    }

    // Add analysis task ------------------------------------
    R3BFootMapped2StripCal *Map2Cal = new R3BFootMapped2StripCal();
    Map2Cal->SetThresholdSigma(2.);
    Map2Cal->SetOnline(NOTstorecaldata);
    run->AddTask(Map2Cal);

    R3BFootStripCal2Hit *Cal2Hit = new R3BFootStripCal2Hit();
    Cal2Hit->SetOnline(NOTstorehitdata);
    Cal2Hit->SetClusterEnergy(60.);
    run->AddTask(Cal2Hit);
  }

  // Add online task --------------------------------------
  R3BFootOnlineSpectra *online = new R3BFootOnlineSpectra();
  // online->SetTpat(1);
  online->SetNbDet(2);
  // online->SetTrigger(3);
  run->AddTask(online);

  if (fRolu) {
    auto roluOnline = new R3BOnlineSpectraBMON_S494();
    // -1 = no trigger selection
    roluOnline->SetTrigger(-1);
    // if 0, no tpat selection
    roluOnline->SetTpat(0, 0);
    // roluOnline->SetBmon(500,0.1,-9,-6);
    run->AddTask(roluOnline);
  }

  // Initialize -------------------------------------------
  run->Init();

  // Informations about portnumber and main data stream.
  cout << "\n\n" << endl;
  cout << "Data stream is: " << filename << endl;
  cout << "FOOT online port server: " << port << endl;
  cout << "\n\n" << endl;
  //
  // Run --------------------------------------------------
  run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);

  // Finish -----------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  Float_t cpuUsage = ctime / rtime;
  cout << "CPU used: " << cpuUsage << endl;
  std::cout << std::endl << std::endl;
  std::cout << "Macro finished succesfully." << std::endl;
  std::cout << "Output file is " << outputFileName << std::endl;
  std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s"
            << std::endl
            << std::endl;
  // gApplication->Terminate();
}

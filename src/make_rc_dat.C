#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;

// Declare constants
static const double pi = 3.14159;
static const double deg2rad = pi/180.;
static const double Mp = 0.9384;  // GeV

// Declare variables
ifstream externalsOut;
ofstream radCorrFile;
string   externalsOutName, radCorrFileName;
string externalsOutPath ("output/externals/");
string radCorrOutPath   ("output/rad-corr-data/");

double E0, Ep, theta, sigmaBorn, sigmaRad, corrFactor, dummy, w2;

// Invariant mass
double calc_W2(double E0, double Ep, double theta) {
  return pow(Mp, 2.) + 2.*Mp*(E0 - Ep) - 4.*E0*Ep*pow(sin(0.5*theta*deg2rad), 2.);
}

int main(int argc,char** argv) {

  // Define the output path
  // Read in the input file
  //cout << "\n Enter the name of the externals output file to read (*.out): ";
  //cin  >> externalsOutName;
  externalsOutName=argv[1];
  externalsOutPath.append(externalsOutName.c_str());
  externalsOut.open(externalsOutPath.c_str());
  if (!externalsOut) {
    cerr << "\n Error reading externals output file! \n" << endl;
    exit(1);
  }
  // Open the output data file
  //cout << "\n Enter the name of the data file to create (*.dat): ";
  //cin  >> radCorrFileName;
  radCorrFileName=argv[2];
  radCorrOutPath.append(radCorrFileName.c_str());
  radCorrFile.open(radCorrOutPath.c_str());
  if (!radCorrFile) {
    cerr << "\n Output data file could not be opened! \n" << endl;
    exit(1);
  }

  dummy = 0.0; E0 = 0.0; Ep = 0.0; theta = 0.0; 
  sigmaBorn = 0.0; sigmaRad = 0.0; corrFactor = 0.0;
  w2 = 0.0;
   while (!externalsOut.eof()) {
  // while (externalsOut >> E0 >> Ep >> theta >> dummy >> dummy >> sigmaBorn >> sigmaRad
  // 	 >> dummy >> dummy >> dummy >> dummy >> dummy >> dummy
  // 	 >> dummy >> dummy >> dummy) {
    
  //   externalsOut >> E0 >> Ep >> theta >> dummy >> dummy >> sigmaBorn >> sigmaRad
  //		 >> dummy >> dummy >> dummy >> dummy >> dummy >> dummy
  // 		 >> dummy >> dummy >> dummy >> dummy;
     externalsOut >> E0 >> Ep >> theta >> dummy >> dummy >> sigmaBorn >> dummy
  		 >> dummy >> sigmaRad >> dummy >> dummy >> dummy >> dummy;

    if (externalsOut.eof()) break;
    corrFactor = sigmaBorn / sigmaRad;
    w2=calc_W2(E0,Ep,theta);
    if(w2>=0){
      radCorrFile << fixed << setprecision(3) << E0 << "\t"
             << scientific << setprecision(8) << w2 << "\t" 
             << fixed << setprecision(3) <<theta << "\t" 
  	     << scientific << setprecision(8) << sigmaBorn << "\t" 
             << sigmaRad << "\t" << corrFactor << endl;
    }
  } 

  externalsOut.close(); 
  radCorrFile.close();
  return 0;

}  // main


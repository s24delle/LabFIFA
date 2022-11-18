//time meas = 20237 sec
#include <iostream>
#include <fstream>
#include <string>
#include <TRandom3.h>
#include <TApplication.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <fstream>
#include <TMath.h>
#include <Math/Minimizer.h>
#include <Math/Factory.h>
#include <Math/Functor.h>

using namespace std;


int main(){

  TApplication app("app",0,NULL);
  
  ifstream file("Sodio_calibrazione.dat");
  if(!file.good()){
    cout << "Error during data file reading" << endl;
  }

  TH1D h("h","Conteggi", 2048,0,2048);
  int count;   //è il numero di conteggi misurati per ogni canale
  int channel = 1;
  while(file>>count){
    for(int i=0; i<count; i++){
    h.Fill(channel);
    i++;
    }
    channel++;
  }
  file.close();


  //TF1 f("f","[0]*TMath::Gaus(x,[1],[2],1)   +   pol1(3)  +[5]*TMath::Gaus(x,[6],[7],1)     ",1450,2048);
  //oppure al posto di pol1(3) si può scrivere l'equazione della retta 

   TF1 f1("f1","[0]*TMath::Gaus(x,[1],[2],1)   ",550,900);
   TF1 f3("f3","  pol1(3)      ",550,900);
  

  //TF1 f("f","[0]*TMath::Gaus(x,[1],[2],1)   +   TMath::Landau(0) +[5]*TMath::Gaus(x,[6],[7],1)     + [8]*x",1450,2048);

  TF1 f("f","f1+f3",550,900);

  f.SetParameter(1,700);
  f.SetParLimits(1,600,800);
  f.SetParameter(2,1);
f.SetParName(1,"Mean");
f.SetParName(2,"Sigma");
 

  TCanvas c1;
  h.Draw();

  h.Fit("f","R");

  f1.FixParameter(0,f.GetParameter(0));
  f1.FixParameter(1,f.GetParameter(1));
  f1.FixParameter(2,f.GetParameter(2));
  f1.SetLineColor(3);
  f1.Draw("same");

 

  f3.FixParameter(3,f.GetParameter(3));
  f3.FixParameter(4,f.GetParameter(4));
  f3.SetLineColor(5);
 f3.Draw("same");

  //TCanvas c2;
 
 /*
 TLegend legend(1,0.6,0.4,0.8);
 legend.SetHeader("","C");
 legend.AddEntry("f","Histogram fit","l");
   legend.AddEntry("f1","Gaussian fit","l");
   legend.AddEntry("f3","Noise fit","l");
   legend.Draw();
 */

  cout << "Integrale: " << f.Integral(550,850) << endl;
  cout << "Integrale: " << f1.Integral(550,850) << endl;
  cout << "Integrale: " << f3.Integral(550,850) << endl;







  app.Run(true);


}

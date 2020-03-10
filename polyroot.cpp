#include <iostream>
#include <string> //string data type 
#include <fstream> //file reading
#include <vector> //vector 
#include <cstdlib> //system("cls")
#include <algorithm>    // std::reverse
#include <cmath> //abs()



using namespace std; 

bool checkRS (double r, double s, double deltaR, double deltaS);
vector<double> getCoeff (string _fileName); 
vector< vector <double>> getRoots(int _degree, vector<double> _coeff);


int main (int argc, char *argv[])
{
  int degree; //degree of the polynomial 
  string fileName = ""; 
  switch(argc)
  {
    case 1: 
      getline(cin, fileName); 
      cout<<"File name: "<<fileName<<endl; 
      break; 
    case 2: 
      fileName = argv[1]; 
      cout<<"File name: "<<fileName<<endl; 
      break; 
    default: 
      cout<<"Invalid Input!"<<endl; 
      exit(1);  
      break; 

  }


  //once we get the file name, pass this as parameter so we can open the file and get the coefficients 
  vector<double> coeff = getCoeff(fileName); 

  reverse(coeff.begin(),coeff.end()); 
  degree = coeff[coeff.size()-1];
  coeff.pop_back(); 
  system("cls"); 
  string poly_out[coeff.size()];
  int poly_outSize = sizeof(poly_out)/sizeof(poly_out[0]); //get the size of an array


  //Display the given polynomial to solve
  cout<<"Polynomial: "<<endl; 
  for(int i = 0; i<poly_outSize; i++) 
  {
    poly_out[i] = to_string(coeff[i]) + " x^" + to_string(coeff.size()-(i+1)); 

  }
  for(int i=0;i<poly_outSize;i++)
  {
    cout<<poly_out[i]<<endl; 
  }

  cout<<"----------------"<<endl; 

  for (int i=0; i<coeff.size();i++)
  {
    cout<<coeff[i]<<endl;
  }

//end of first output 
vector <vector<double>> roots = getRoots(degree, coeff); //get roots using returnR


  return 0; 
} 



   /*Insert algorithm here*/
vector< vector <double>> getRoots(int _degree, vector<double> _coeff)
{
  //variable declaration 
  double degree = _degree; 
  double r = 0 , s = 0; 


  double prevR = 0, prevS = 0; 
  double denom = 0; 
  double deltaR = 0, deltaS = 0; 

  vector<double> coeff = _coeff; 

  reverse(coeff.begin(),coeff.end()); //reverse again for convenience 

  //calculate for initial values for r and s 
  r = coeff[1]/coeff[0]; 
  s = coeff[2]/coeff[0];


  while(!checkRS(r, s, deltaR, deltaS)) 
  {
    prevR = r;
    prevS = s; 
    r = r + deltaR; 
    s = s + deltaS; 
    cout<<"-------------"<<endl;
    cout<<r<<endl;
    cout<<s<<endl; 
    double b[coeff.size()] = {0.0};
    double c[coeff.size()] = {0.0}; 

 
      /*GET bn*/
       for (int n = coeff.size()-1; n>-1; n--)
       {
          double temp_rBn = 0; 
          double temp_sBn = 0; 

          temp_rBn = (n+1<=coeff.size()-1)? r*b[n+1]:0.0; 
          temp_sBn = (n+2<=coeff.size()-1)? s*b[n+2]:0.0;  
          b[n] = coeff[n]  + temp_rBn + temp_sBn;
        }
      /*GET cn*/
      for (int n = coeff.size()-1; n>-1; n--)
      {
          double temp_rBn = 0; 
          double temp_sBn = 0; 

          temp_rBn = (n+1<=coeff.size()-1)? r*c[n+1]:0.0; 
          temp_sBn = (n+2<=coeff.size()-1)? s*c[n+2]:0.0;  
          c[n] = b[n]  + temp_rBn + temp_sBn;

      }
      /*DISPLAY bn*/
      cout<<"-------------"<<endl; 
      cout<<"b[n]: "<<endl; 

      for(int n = 0; n<coeff.size();n++)
      {
          cout<<b[n]<<endl;
      }
      /*DISPLAY cn*/
      cout<<"-------------"<<endl;
      cout<<"c[n]: "<<endl; 
      for(int n = 0; n<coeff.size();n++)
      {
        cout<<c[n]<<endl;
      }
      denom = (c[2]*c[2])-(c[1]*c[3]); 
      deltaR = (b[0]*c[3] - b[1]*c[2]) / denom ;
      deltaS = (b[1]*c[1] - b[0]*c[2]) / denom  ;

      if ((deltaR+r == r) && (deltaS +s) == s)
        break; 
      // cout<<"-------------"<<endl; 
      // cout<<"deltaR + R :"<<endl; 
      // cout<<deltaR+r<<endl; 
      // cout<<"-------------"<<endl; 
      // cout<<"deltaS + S :"<<endl; 
      // cout<<deltaS+s<<endl; 
    


  } 



  










  vector <vector <double>> roots(degree, vector <double> (2, 0)); 
  return roots;  

}
  


 



 




 




//functions 


vector<double> getCoeff (string _fileName)
{
  ifstream inFile; 
  string fileName = _fileName;  
  vector<double> _coeff; 
  double degree; 



  inFile.open(fileName);

  if(!inFile) //Check if the file can be opened
  {
    cerr<<"Unable to open "<<fileName<<endl; 
    exit(1);    

  }


  else 
  {

    try
    {
      while(inFile>>degree)
      {
        _coeff.push_back(degree);   
      }
    }
    catch(int e)
    {
      cout<<"Exception occured with error no: "<<e<<endl; 
      exit(1);

    }

  }


  return _coeff; 

} 


bool checkRS (double r, double s, double deltaR, double deltaS)
{
  return (deltaR/r>0 && deltaS/s>0); 

}





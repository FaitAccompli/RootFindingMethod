#include <iostream>
#include <string> //string data type 
#include <fstream> //file reading
#include <vector> //vector 
#include <cstdlib> //system("cls")
#include <algorithm>  // std::reverse
#include <cmath> //abs()
#include <iomanip> //setprecision();


using namespace std; 

bool checkRS (long double r, long double s, long double deltaR, long double deltaS);
bool isEven(int degree);
vector<long double> getCoeff (string _fileName); 
vector< vector <long double>> getRoots(int _degree, vector<long double> _coeff);
long double calculatePosRoot(long double r, long double s, long double discriminant);
long double calculateNegRoot(long double r, long double s, long double discriminant);

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
  vector<long double> coeff = getCoeff(fileName); 
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
//end of first output 




vector <vector<long double>> roots = getRoots(degree, coeff); //get roots using return
for( int i = 0; i<roots.size(); i++)
{
    for(int j=0; j<roots[i].size(); j++)
    {
      cout<<fixed<<setprecision(10)<<roots[i][j];
      cout<<","; 

    }
    cout<<"\n"; 

}


  return 0; 
} 

/*Insert algorithm here*/











vector< vector <long double>> getRoots(int _degree, vector<long double> _coeff)
{
//variable declaration 
  int degree = _degree; 
  vector <vector <long double>> roots(degree, vector <long double> (2, 0)); 
  long double r = 0 , s = 0; 
  long double prevR = 0, prevS = 0; 
  long double denom = 0; 
  long double deltaR = 0, deltaS = 0; 
  vector<long double> coeff (_coeff);

 

  //calculate for initial values for r and s 
  r = coeff[1]/coeff[0]; 
  s = coeff[2]/coeff[0];
  //reverse again for convenience 
  reverse(coeff.begin(),coeff.end());
  for(int i=0; i<coeff.size(); i++) cout<<coeff[i]<<endl; 


  int limit = (isEven(degree)? (degree) : ((degree-1)/2)+2);

  for (int i = 0; i<limit; i++) //2 
  {
    long double b[coeff.size()] = {0.0};
    long double c[coeff.size()] = {0.0}; 
 
    /*------------------WHILE-------------------*/
    while(!checkRS(r, s, deltaR, deltaS)) //while this is false (deltaR/r>0 && deltaS/s>0); 
    {

      r = r + deltaR; 
      s = s + deltaS; 
      cout<<"-------------"<<endl;
      cout<<r<<endl;
      cout<<s<<endl; 


      if(prevR == r && prevS == s)
        break; 


        /*GET bn*/
         for (int n = coeff.size()-1; n>-1; n--)
         {
            long double temp_rBn = 0; 
            long double temp_sBn = 0; 

            temp_rBn = (n+1<=coeff.size()-1)? r*b[n+1]:0.0; 
            temp_sBn = (n+2<=coeff.size()-1)? s*b[n+2]:0.0;  
            b[n] = coeff[n]  + temp_rBn + temp_sBn;
          }
        /*GET cn*/
        for (int n = coeff.size()-1; n>-1; n--)
        {
            long double temp_rBn = 0; 
            long double temp_sBn = 0; 

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
        
        cout<<"c[n]: "<<endl; 
        for(int n = 0; n<coeff.size();n++)
        {
          cout<<c[n]<<endl;
        }
        denom = (c[2]*c[2])-(c[1]*c[3]); 
        deltaR = (b[0]*c[3] - b[1]*c[2]) / denom ;
        deltaS = (b[1]*c[1] - b[0]*c[2]) / denom  ;
        

        prevR = r; 
        prevS = s; 
    
    
      
    } 
    /*----------------END WHILE-------------------*/


      // if(sizeof(b)/sizeof(b[0]) == 1 && b[0] == 0 && sizeof(c)/sizeof(c[0])  == 1 && c[0] == 0)
      // {
      //   roots[i][0] = roots[i-1][0];
      //   roots[i+1][1] = roots[i-2][0];
      //   i++;   

      // } 
      cout<<"i: "<<i<<endl;

   
      long double discriminant = (r*r)+(4.000*s); 
      if (coeff.size() == 3 && discriminant >= 0)
      {

        roots[i][0] = (-coeff[1]-sqrtl((coeff[1]*coeff[1])-(4*coeff[0]*coeff[2])))/(2*coeff[2]); 
        roots[i][1] = 0;
        roots[i+1][0] = (-coeff[1]+sqrtl((coeff[1]*coeff[1])-(4*coeff[0]*coeff[2])))/(2*coeff[2]); 
        roots[i+1][1] = 0; 
        i++; 
        
      }
      else if (coeff.size() == 3 && discriminant < 0)
      {

        roots[i][0] = (-coeff[1]-sqrtl((coeff[1]*coeff[1])-(-4*coeff[0]*coeff[2])))/(2*coeff[2]); 
        roots[i][1] = 0;
        roots[i+1][0] = (-coeff[1]+sqrtl((coeff[1]*coeff[1])-(-4*coeff[0]*coeff[2])))/(2*coeff[2]); 
        roots[i+1][1] = 0; 
        i++; 
        
      }
      else if (coeff.size() == 2)
      {
        roots[i][0] = -coeff[0]/coeff[1];  
        roots[i][1] = 0; 
        i++; 

      }
      else if (discriminant < 0 || coeff.size() == 0)
      {
        cout<<"here"<<endl;
        roots[i][0] = r/2; 
        roots[i][1] = calculateNegRoot(r, s, discriminant); 
        roots[i+1][0] = r/2; 
        roots[i+1][1] = calculatePosRoot(r, s, discriminant); 
        i++; 
    

      }
      else if (discriminant > 0)
      {
        roots[i][0] = calculateNegRoot(r, s, discriminant);
        roots[i][1] = 0;
        roots[i+1][0] = calculatePosRoot(r, s, discriminant);
        roots[i+1][1] = 0; 
        i++; 
      }
      else if (discriminant  == 0)
      {
        
        roots[i][0] = calculatePosRoot(r, s, discriminant);
        roots[i][1] = 0;
        roots[i+1][0] = calculatePosRoot(r, s, discriminant);
        roots[i+1][1] = 1; 
        i++;

      } 

    
    //vector.resize();
    coeff.resize(coeff.size()-2,0);
    //-60 8 -11 2 1    
    //0 0 0
    //0  
    for(int i = 0; i < coeff.size(); i++)
    {
      coeff[i] =  b[i+2]; 
      //-15 2 1
    }   
    cout<<"NEW COEFF"<<endl;
    for(int i = 0; i< coeff.size(); i++)
    {
      cout<<coeff[i]<<endl; 

    }



    r = 0;
    s = 0;
    prevR = 0;
    prevS = 0; 
    denom = 0; 
    deltaR = 0;
    deltaS = 0;
   

  }



  return roots;  

}
  


 



 



//functions 
bool isEven(int degree) 
{
  return (degree%2==0);  

}
long double calculatePosRoot(long double r, long double s, long double discriminant)
{

  if (discriminant >= 0) //real
    return (r + sqrtl(r+(4.000*s)))/2; 

  else //imaginary
    return (sqrtl(r+(-4.000*s)))/2; 


  
}
long double calculateNegRoot(long double r, long double s, long double discriminant)
{
  if (discriminant>=0) //real
    return (r - sqrtl(r+(4.000*s)))/2;

  else //imaginary
    return (-1*sqrtl(r+(-4.000*s)))/2; 
}



vector<long double> getCoeff (string _fileName)
{
  ifstream inFile; 
  string fileName = _fileName;  
  vector<long double> _coeff; 
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


bool checkRS (long double r, long double s, long double deltaR, long double deltaS)
{
  return (deltaR/r>0 && deltaS/s>0); 
}





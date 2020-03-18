#include <iostream>
#include <string> //string data type 
#include <fstream> //file reading
#include <vector> //vector 
#include <cstdlib> //system("cls")
#include <algorithm>  // std::reverse
#include <cmath> //sqrtl()
#include <iomanip> //setprecision();
#include <complex> //complex <double>


using namespace std; 


bool checkRS (long double errorR, long double errorS);
vector<long double>  getCoeff (string fileName);
vector<long double> divideByLeadingCoefficient (vector <long double> coeff);
vector<long double> getQuadratic (vector <long double> coeff);
vector<long double>  getNewCoeff(vector <long double> coeff);  
long double getRoots(vector<long double> coeff, long double roots[][2] , int i); 
long double calculatePosRoot(long double r, long double s, long double discriminant);
long double calculateNegRoot(long double r, long double s, long double discriminant); 
void outputPolynomial (vector<long double> coeff);
complex<long double> useHorner (vector<long double> coeff, complex<long double> x);



int main (int argc, char *argv[])
{
  int degree; //degree of the polynomial 
  string fileName = ""; 
  switch(argc)
  {
    case 1: 
      cout<<"File name: "<<fileName<<endl; 
      getline(cin, fileName); 
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
  int _degree = degree; 
  coeff.pop_back(); 
  vector<long double> coeffForEval = divideByLeadingCoefficient(coeff); //we need a copy of the original coefficients for evaluation
  system("cls"); 

  //diplay polynomial 
  outputPolynomial(coeff); 
  

  long double  roots[degree][2]; // degree number of rows and 2 columns 

                        

 for(int i=degree; i > 2; i=i-2, degree = degree -2) 
 {

    coeff = divideByLeadingCoefficient(coeff); //make sure that the leading coefficient is 
    coeff = getQuadratic(coeff); // r s -15 2 1
    getRoots(coeff, roots, i); // 2 pairs 
    coeff = getNewCoeff(coeff);    // r s -15 2 1 --> 1 2 -15 s r--> after pop_back 2x -->  1 2 -15 --> -15 2 1
    reverse(coeff.begin(), coeff.end());
 }    

 if (degree == 2) 
    getRoots(coeff, roots, degree);
 

 else if (degree == 1)
    roots[0][0] = (-1*coeff[1])/(coeff[0]); 




 // output roots 
 cout << endl << "Roots: " << endl;
 for(int i=0; i<_degree; i++)
 {
     cout << "(" << fixed << setprecision(6) << roots[i][0] << ", " << fixed << setprecision(6) <<roots[i][1] << ")" << endl;
 }


//evaluating polynomials at identified roots 
 cout << endl << "Evaluating polynomial at identified roots: " << endl;
 for(int i = 0; i<coeffForEval.size()-1; i++)
 {
        complex<long double> x(roots[i][0],roots[i][1]); 
        cout << "f(" << roots[i][0] << ", " << roots[i][1] << ") = " << real(useHorner(coeffForEval, x)) << endl;
 }



  return 0; 
} 






/*Functions*/
vector<long double>  getCoeff (string fileName) //function that gets the degree and numerical coefficiations of the polynomial
{
  ifstream inFile; 
  vector<long double>  _coeff; 
  long double values; 

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
      while(inFile>>values)
      {
        _coeff.push_back(values);   
      }
    }
    catch(int e)
    {
      cout<<"Exception occured with error no: "<<e<<endl; 
      exit(1);

    }
  }
  inFile.close(); 
  return _coeff; 
} 



void outputPolynomial (vector<long double> coeff) //function that outputs that input polynomial 
{
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
  

}


vector<long double>  divideByLeadingCoefficient (vector<long double> coeff)//function that divides the coefficients by the leading coefficient
{
  long double divisor = coeff[0]; 
  for(int i=0; i<coeff.size(); i++)
  {
    coeff[i] = coeff[i]/divisor; 
  }
  return coeff;  
}


vector<long double>  getQuadratic (vector<long double> coeff)
{
  long double r, s ; 
  long double denom = 0; 
  long double deltaR = 0;
  long double deltaS = 0; 
  long double errorR = 1; 
  long double errorS = 1; 

  //calculate for initial values for r and s 
  r = coeff[1]/coeff[0]; 
  s = coeff[2]/coeff[0];
  reverse(coeff.begin(), coeff.end()); //for convenience in calculations 
  
  long double b[coeff.size()] = {0.0};
  long double c[coeff.size()] = {0.0}; 
 
    /*------------------WHILE-------------------*/
  while(checkRS(errorR, errorS)) //while this is false (deltaR/r>0 && deltaS/s>0); 
  {

    r = r + deltaR; 
    s = s + deltaS; 

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

    denom = (c[2]*c[2])-(c[1]*c[3]); 
    deltaR = (b[0]*c[3] - b[1]*c[2]) / denom ;
    deltaS = (b[1]*c[1] - b[0]*c[2]) / denom  ;

    errorR = fabs(100 * (deltaR / r));
    errorS = fabs(100 * (deltaS / s));

      
  } 

  /*END OF WHILE*/

  // if (((b[2]*b[2] - b[1]*b[3]) == 0) || (b[3] == 0))
  // {
  //     cout << "The system has no convergence"<< endl;
  //     exit(1); 
  // }





  for(int i=0; i<coeff.size(); i++) //we want to return a vector containing r and s  and the new polynomial to divide
  {


    if(i==0)
    {
      coeff[i] = r; 
      coeff[i+1] = s;
      i++; 
    }
    else 
      coeff[i] = b[i]; 

  }

  return coeff; 

}


bool checkRS (long double errorR, long double errorS)
{
  long double stopError = 1/1e6; 

  return (errorR > stopError || errorS > stopError ); 
}




long double getRoots(vector<long double> coeff, long double roots[][2], int i)
{

  //-15 2 1 
  long double r = (coeff.size()!=3)?coeff[0]: -1*coeff[1]; //store r 
  long double s = (coeff.size()!=3)?coeff[1]: -1*(coeff[2]); //store s  
  long double discriminant = (r*r)+(4*s); 
  long double realRoot[2]; 
  long double imaginaryRoot[2];  


  if(discriminant>=0)
  {
    realRoot[0] = calculateNegRoot(r, s, discriminant); 
    imaginaryRoot[0] = 0;
    realRoot[1] = calculatePosRoot(r, s, discriminant); 
    imaginaryRoot[1] = 0;  

  }
  else 
  {
    realRoot[0] = r/2; 
    imaginaryRoot[0] = calculateNegRoot(r, s, discriminant);
    realRoot[1] = r/2; 
    imaginaryRoot[1] = calculatePosRoot(r, s, discriminant); ;  
  }


  roots[i-1][0] = realRoot[0];   
  roots[i-1][1] = imaginaryRoot[0];
  roots[i-2][0] = realRoot[1];
  roots[i-2][1] = imaginaryRoot[1];


  return **roots; 

}

long double calculatePosRoot(long double r, long double s, long double discriminant)
{

  if (discriminant >= 0) //real
    return (r + sqrt(discriminant))/2; 

  else //imaginary
    return (sqrt(-discriminant))/2; 


  
}
long double calculateNegRoot(long double r, long double s, long double discriminant)
{
  if (discriminant>=0) //real
    return (r- sqrt(discriminant))/2;

  else //imaginary
    return (-1*sqrt(-discriminant))/2; 
}


vector<long double> getNewCoeff(vector<long double> coeff)
{
  reverse(coeff.begin(), coeff.end());  
  coeff.pop_back(); 
  coeff.pop_back(); 
  reverse(coeff.begin(), coeff.end()); 
  return coeff; 
}



complex <long double> useHorner (vector<long double> coeff, complex<long double> x)
{
  //Evaluating polynomial at identified roots using Horner's Method
  complex<long double> answer(0); 
  for(int i = 0; i<coeff.size(); i++)
  {
     answer = answer*x+coeff[i]; 
  }

  return (!isnan(real(answer)) || !isnan(imag(answer)))?answer:0;
}






















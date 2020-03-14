#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>    // std::reverse
#include <complex>


using namespace std; 

bool checkRS (double r, double s, double deltaR, double deltaS);

int main (int argc, char *argv[])
{
	ifstream inFile; 
	string fileName=""; 
	vector<double> coeff; 
	double degree; 

	if(argc == 2)
	{
		fileName = argv[1]; 
		cout<<"File name: "<<fileName<<endl; 

	}
	else if (argc == 1)
	{
		getline(cin, fileName); 
		cout<<"File name: "<<fileName<<endl; 
	}
	else{
		cout<<"Invalid Input"<<endl; 
  }

	


	inFile.open(fileName);

	if(!inFile) //Check if we the file can be opened
	{
		cerr<<"Unable to open "<<fileName<<endl; 
		exit(1);  	

	}
  else 
  {
    while(inFile>>degree)
    {
      coeff.push_back(degree);   
    }
    reverse(coeff.begin(),coeff.end()); 
    degree = coeff[coeff.size()-1];
    coeff.pop_back(); 
    system("cls"); 
    string poly_out[coeff.size()];
    int poly_outSize = sizeof(poly_out)/sizeof(poly_out[0]);
    cout<<"Polynomial: "<<endl; 
    for(int i = 0; i<poly_outSize; i++) 
    {
        poly_out[i] = to_string(coeff[i])+"x^"+to_string(coeff.size()-(i+1)); 

    }

    for(int i=0;i<poly_outSize;i++)
    {
      cout<<poly_out[i]<<endl; 
    }

  }


  cout<<"----------------"<<endl; 

  for (int i=0; i<coeff.size();i++)
  {
    cout<<coeff[i]<<endl;
  }





  


  /*--------------------*/
  // if (inFile.peek() == EOF) //Check if file is empty
  // {
  //   cout << "The file is empty. Exiting..." << endl;
  //   system("pause");
  //   return (0);
  // }
  // if(isdigit(inFile.peek())) //check if first element is a digit. 
  // {
  //   inFile>>degree; 
  //   for(int i=degree; i > 0 ; i--)
  //   {
  //     inFile >> coeff[i];
  //     cout<<"here";
  //   }
  // }
  // else
  // {
  //   cerr << "You inputted an invalid file."
  //        << "Check proper input format" << endl;
  //   system("pause");
  //   exit(1);
  // }

  //  /*--------------------*/


 //  

 //  	//OUTPUT

	 /*Insert algorithm here*/

  double r(0), s(0); 
  double prevR(0), prevS(0); 

  r = coeff[1]/coeff[0]; 
  s = coeff[2]/coeff[0]; 
  cout<<"-------------"<<endl;
  cout<<r<<endl;
  cout<<s<<endl; 
  reverse(coeff.begin(),coeff.end()); //reverse again for convenience 
  double b[coeff.size()] = {0.0};
  double c[coeff.size()] = {0.0}; 
 



  for (int n = coeff.size()-1; n>-1; n--)
  {
    double temp_rBn = 0; 
    double temp_sBn = 0; 

    temp_rBn = (n+1<=coeff.size()-1)? r*b[n+1]:0.0; 
    temp_sBn = (n+2<=coeff.size()-1)? s*b[n+2]:0.0;  
    b[n] = coeff[n]  + temp_rBn + temp_sBn;

  }


  for (int n = coeff.size()-1; n>-1; n--)
  {
    double temp_rBn = 0; 
    double temp_sBn = 0; 

    temp_rBn = (n+1<=coeff.size()-1)? r*c[n+1]:0.0; 
    temp_sBn = (n+2<=coeff.size()-1)? s*c[n+2]:0.0;  
    c[n] = b[n]  + temp_rBn + temp_sBn;

  }

  cout<<"-------------"<<endl; 
  cout<<"b[n]: "<<endl; 
  for(int n = 0; n<coeff.size();n++)
  {
    cout<<b[n]<<endl;
  }
  cout<<"-------------"<<endl;
  cout<<"c[n]: "<<endl; 
  for(int n = 0; n<coeff.size();n++)
  {
    cout<<c[n]<<endl;
  }

  double denom = (c[2]*c[2])-(c[1]*c[3]); 
  double deltaR = (b[0]*c[3] - b[1]*c[2]) / denom ;
  double deltaS = (b[1]*c[1] - b[0]*c[2]) / denom  ;

  cout<<"-------------"<<endl; 
  cout<<"deltaR + R :"<<endl; 
  cout<<deltaR+r<<endl; 
  cout<<"-------------"<<endl; 
  cout<<"deltaS + S :"<<endl; 
  cout<<deltaS+s<<endl; 

  while(!checkRS(r, s, deltaR, deltaS))
  {
    prevR = r;
    prevS = s; 
    r = deltaR + r;
    s = deltaS + s;

    if (prevR != r && prevS != s)
    {
      for(int n=0;n<coeff.size();n++)
      {
        b[n] = 0; 
        c[n] = 0; 
      }
    /*-------------------------------*/
      for (int n = coeff.size()-1; n>-1; n--)
      {
        double temp_rBn = 0; 
        double temp_sBn = 0; 

        temp_rBn = (n+1<=coeff.size()-1)? r*b[n+1]:0.0; 
        temp_sBn = (n+2<=coeff.size()-1)? s*b[n+2]:0.0;  
        b[n] = coeff[n]  + temp_rBn + temp_sBn;

      }


      for (int n = coeff.size()-1; n>-1; n--)
      {
        double temp_rBn = 0; 
        double temp_sBn = 0; 

        temp_rBn = (n+1<=coeff.size()-1)? r*c[n+1]:0.0; 
        temp_sBn = (n+2<=coeff.size()-1)? s*c[n+2]:0.0;  
        c[n] = b[n]  + temp_rBn + temp_sBn;

      }

      cout<<"-------------"<<endl; 
      cout<<"b[n]: "<<endl; 
      for(int n = 0; n<coeff.size();n++)
      {
        cout<<b[n]<<endl;
      }
      cout<<"-------------"<<endl;
      cout<<"c[n]: "<<endl; 
      for(int n = 0; n<coeff.size();n++)
      {
        cout<<c[n]<<endl;
      }
    /*-------------------------------*/
      denom = (c[2]*c[2])-(c[1]*c[3]); 
      deltaR = (b[0]*c[3] - b[1]*c[2]) / denom ;
      deltaS = (b[1]*c[1] - b[0]*c[2]) / denom  ;

      cout<<"-------------"<<endl; 
      cout<<"deltaR + R :"<<endl; 
      cout<<deltaR+r<<endl; 
      cout<<"-------------"<<endl; 
      cout<<"deltaS + S :"<<endl; 
      cout<<deltaS+s<<endl; 

    }





  }







	return 0; 
} 




bool checkRS (double r, double s, double deltaR, double deltaS)
{
  return (deltaR/r>0 && deltaS/s>0); 

} 
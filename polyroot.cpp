#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <complex>

using namespace std; 

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
		cout<<"Please specify filename: "; 
		getline(cin, fileName); 
		cout<<"File name: "<<fileName<<endl; 
	}
	else 
		cout<<"Invalid Input"<<endl; 

	


	inFile.open(fileName);

	if(!inFile) //Check if we the file can be opened
	{
		cerr<<"Unable to open "<<fileName<<endl; 
		exit(1);  	

	}
	if (inFile.peek() == EOF) //Check if file is empty
  	{
    	cout << "The file is empty. Exiting..." << endl;
    	system("pause");
    	return (0);
  	}


  	if(isdigit(inFile.peek())) //check if first element is a digit. 
  	{
  		inFile>>degree; 
  		for(int i=degree; i > 0 ; i--)
  		{
  			inFile >> coeff[i];
  		}
  	}
  	else
  	{
  		cerr << "You inputted an invalid file."
      	<< "Check proper input format" << endl;
    	system("pause");
    	exit(1);
  	}



  	/*Insert algorithm here*/


  	//OUTPUT
  	system('CLS'); 
  	string poly_out[coeff.size()];
  	cout<<"Polynomial: "<<endl; 
  	for(int i = 0; i<poly_out.siz(); i++) 
  	{
  			poly_out[i] = to_string(coeff[i])+"x^"+to_string(coeff.size()-1); 

  	}

  	for(int i=0;i<poly_out.size();i++)
  	{

  		cout<<poly_out[i]<<endl; 
  	}

	




	return 0; 
} 
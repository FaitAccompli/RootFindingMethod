# RootsOfPolynomials
CE33 Project 1 
Project 1: Roots of Polynomials 
I. Objective
As stated in the project specifications, the main objective of this project is to be able to implement algorithms for finding all roots of polynomials with real-valued coefficients. 

II. Project Flowchart


III. Bairstow’s Method
	For this project, the developers decided to use Bairstow’s method for finding all the roots of a given polynomial with real-valued coefficients. According to Wolfram MathWorld, Bairstow’s method is “a procedure for finding the quadratic factors for the complex conjugate roots of a polynomial with real coefficients”[1]. Below is a step-by-step discussion on how this method works and is available online[2], this was used by the developers as a basis in coding the different functions in order to get all the roots. 
Given a polynomial, 

fn(x) = a0 + a1x + a2x2 + ... +anxn(1)

Bairstow’s method divides the polynomial by a quadratic function of the form,

x2 -rx -s(2)

	After dividing, the resulting quotient will be a polynomial fn-2(x)of the form, 

fn-2(x) = b2 +b3x + b4x2 + ... +bn-1xn-3 + bnxn-2(3)
	
With a remainder R(x) which is a linear function, 

R(x) = b1(x - r) + b0 (4)

	The following recurrence relations can be obtained given that the quotient and the remainder resulted from standard synthetic division: 
	
bn = an(5)
bn-1 = an-1 + rbn(6)
bi = ai + rbi+1 + sbi+2    for i =n-2 to 0(7)

	If x2 -rx -s is an exact factor then the remained R(x) is zero and the real or complex roots of x2 -rx -s are the roots of the function. In some sources, the initial values for r and s are randomized but in this implementation, the initial values for r and s were based on the coefficients of the polynomials in order to reduce the number of iterations. 

r = a1/a0(8)
s = a2/a0(9)

	However, it is imperative to obtain a better approximation of r and s by introducing Δr and Δs in order to get (r+Δr, s+Δs). The percentage of approximate errors can be calculated using the formula below, 

| εa,r| =rt x 100(10)
| εa,s| =ss x 100(11)

	After this, a stopping error is introduced. This makes sure that if | εa,r|> εsor | εa,s|> εsthen the process is repeated with the new guesses (r+Δr, s+Δs).

	To find all the roots of fn(x), it is important to consider the following possibilities:
If the quotient polynomial has a degree equal to 3 or higher then Bairstow’s Method can be applied again to the said quotient polynomial using the previous values of r and s as the starting guesses. 
If the quotient is a quadratic function then use the quadratic function to obtain the remaining two roots. 
If the quotient is a linear function of the form ax+b=0 then the remaining single root is equal tox=(-b/a)


IV. Function Implementation
This section delves into the overall flow of the program and the ten functions used to implement Bairstow’s Method. It is an iterative method that finds both the real and complex roots of a polynomial. This is based on a technique that utilizes repetitive synthetic division of the polynomial by a quadratic equation. The functions below are arranged based on how they were called in the program. 
	First, it was imperative that the program should be able to extract the necessary values from the input text file. As seen in the code snippet below, the program takes advantage of the integer type variable argc and the pointer to a character array variable *argv[], in order to check if the user inputted a filename or not. The argc variable was passed as an argument to the switch case in order to check three different cases. Bear in mind that this program was initially developed without using DevC++ rather it was compiled using g++ via terminal. This was later revised to also work on DevC++ since it was required to send the .dev file as well for submission. Therefore, the program can both run using DevC++ and via command line interface (CLI). The variable argc indicates the number of inputs the user typed in the CLI,  so if the user runs the executable file without indicating the file name, argc would have a value of 1 and the program will prompt the user to input a filename. On the other hand, if the user runs the executable file with a filename, argc would have a value of 2 and will display the corresponding output. The default case happens when more than two inputs were given by the user, this will result in the program exiting due to invalid input. Check case outputs below. 

Fig. 1. Case 1 - User did not specify filename 

Fig. 2. Case 2 - User specified a  filename 


Fig. 3. Default Case - User specified more than 2 inputs (added hello.txt)

.	For users who used DevC++, the program will fall under case 1 immediately since no text file was specified as input at the start. See Fig. 4. 


Fig. 4. Case 1 - User compiled and executed the program in  DevC++ 
The pointer to a character array argv was used to indicate the specific input the developers wanted to pass as a parameter. As seen in the code below under case 2, argv[1] was called since the second element of the argv array contained the filename. 

  int degree; //degree of the polynomial 
  string fileName = ""; 
  switch(argc)
  {
    case 1: 
      cout<<"File name: "<<fileName<<endl; 
      if(!getline(cin, fileName))
      {
        cout<<"Invalid Input! Exiting ...";
        return 0; 
      }
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

	After successfully obtaining the filename, the next step is to be able to read the text file and store those values inside a variable, in this case a vector of type long double was used. As seen in the code below, the function getCoeff() was called and the variable fileName was passed as an argument. The aforementioned function will be discussed later in more detail. Assuming that the numerical values were stored correctly inside the vector coeff the reverse function was used to reverse the arrangement of the elements stored in the vector. This was used in order to make it more convenient for the developers to implement Bairstow’s method later on. Since the vector was reversed, the last element should contain the degree of the polynomial. The degree was stored to another integer variable called _degree in order to create another copy since later on the degree variable will be manipulated. Next, the pop_back() function was used in order to remove the last element since the developers were already able to store the degree of the polynomial inside a variable. This was to make sure that the vector coeff only contained the numerical coefficients of the polynomial. Another vector variable was also initialized so that the developers can store a copy of the original polynomial whose leading coefficient is equal to one. A copy was needed since the vector coeff will be manipulated when it undergoes Bairstow’s Method. 

//once we get the file name, pass this as parameter so we can open the file and get the coefficients 
vector<long double> coeff = getCoeff(fileName);
reverse(coeff.begin(),coeff.end()); 

degree = coeff[coeff.size()-1];
int _degree = degree; 
coeff.pop_back(); 
vector<long double> coeffForEval = divideByLeadingCoefficient(coeff); //we need a copy of the original coefficients for evaluation
system("cls"); 

Lastly, when the coefficients are stored correctly the program will call the outputPolynomial() function and output  the given polynomial arranged from highest degree to lowest degree. See function call below. 
    
//display polynomial 
outputPolynomial(coeff); 

vector<long double>  getCoeff (string fileName)
This function accepts the filename as an argument and extracts the degree and numerical coefficients of the polynomial in a text file. As seen in the code below, the function c_str() was used in order to return a pointer to the c-string representation of the string object's value. This was to make sure that ifstream inFile can successfully open the filename without throwing any exceptions. Next, once the file was opened, an if-condition was used to check if the file can be opened or not. If the text file cannot be opened, the program exits with a value of 1 which just means unsuccessful termination. However, if the program successfully opens the text file, the ifstream inFile will continue reading through the text file while considering whitespaces as breakpoints and then will stop until a variable other than a long double is read. Notice in the code that the values being read are stored in the variable values and are stored again in the vector _coeff. Once the input file stream finishes reading, the file is then closed and the function returns a long double vector containing the numerical coefficients together with the degree of the polynomial. 

vector<long double>  getCoeff (string fileName) 
{
  ifstream inFile; 
  vector<long double>  _coeff; 
  long double values; 
  inFile.open(fileName.c_str());

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
	
vector<long double> divideByLeadingCoefficient (vector <long double> coeff)
This function accepts a long double vector as an argument and then divides the numerical coefficients by the leading coefficient. This makes sure that the leading coefficient is equal to one in order to simplify the process of finding the roots. This is an important step since Bairstow’s Method assumes that the leading coefficient is equal to one. As seen in the code below, the first element which contains the leading coefficient is used as the divisor. The for loop is used to go through each element of the vector coeff and divide these elements by the divisor. After this, the function returns a simplified vector with a leading coefficient equal to one. 

vector<long double>  divideByLeadingCoefficient (vector<long double> coeff)
{
  long double divisor = coeff[0]; 
  for(int i=0; i<coeff.size(); i++)
  {
    coeff[i] = coeff[i]/divisor; 
  }
  return coeff;  
}

void outputPolynomial (vector<long double> coeff);
This function accepts a long double vector that contains the coefficients of the polynomial and outputs them from highest degree to lowest degree. As seen in the code below, the for-loop is used to loop through each element. Each element is affixed with " x^" in order to fulfill one of the output requirements stated in the specifications. Notice the code snippet “coeff.size()-(i+1)”, this is to make sure that the degree corresponds to the correct numerical coefficient while making efficient use of the i variable. This basically removed the need to initialize a different variable for this task. See Fig. 5 for sample output. 

void outputPolynomial (vector<long double> coeff) //function that outputs that input polynomial 
{
  cout<<"Polynomial: "<<endl; 
  for(int i = 0; i<coeff.size(); i++) 
  {
    cout<<coeff[i]<<" x^"<<coeff.size()-(i+1)<<endl; 
  }

}

Fig. 5. Sample output of the given polynomial together with their respective numerical coefficients.

After successfully reading the text file, storing the necessary values and outputting the given polynomial, the program will now use Bairstow’s Method in finding both the real and complex roots of a polynomial. Before explaining the different functions that pertain to this method in detail, it would be best to check how Bairstow’s method works in section III since the algorithms used here were only interpretations of the method written in C++. 
First, in order to simplify the process, the developers made sure that the leading coefficient of the given polynomial is equal to 1 before proceeding with Bairstow’s method. For this task, the dividByLeadingCoefficient( ) function is used. Subsequently, the getQuadratic() function is called  so that the variables r and s and the numerical coefficients of the quotient are obtained. The process on how this is done will be explained further in this report. After obtaining the r, s and the numerical coefficients of the quotient, the program can now calculate for a pair of roots using the quadratic formula. Lastly, after obtaining a pair of roots, the program needs to manipulate the coeff variable so that the process can be repeated until the degree of the polynomial is no longer greater than 2, this is in compliance with one of  the three possibilities mentioned in section III. See the code interpretation of the process below. 

 for(int i=degree; i > 2; i=i-2, degree = degree -2) 
 {
  coeff = divideByLeadingCoefficient(coeff); //make sure that the leading coefficient is 1
  coeff = getQuadratic(coeff); // r s -15 2 1, this gets the coefficients of our quadratic equation
  getRoots(coeff, roots, i); // 2 pair, we get the roots by pair here
  coeff = getNewCoeff(coeff);    // r s -15 2 1 --> 1 2 -15 s r--> after pop_back 2x -->  1 2 -15 --> -15 2 1
  reverse(coeff.begin(), coeff.end());
 }    

	When the degree of the polynomial is equal to 2, the polynomial takes the form of eqn. 2: x2 -rx -s. Therefore, the roots can easily be obtained using the quadratic equation. For this, the getRoots() function is called. Details regarding this function will be discussed further in this section. See code interpretation of the process below. 

 if (degree == 2)  //this is for the quadratic equation, execute getRoots function
  getRoots(coeff, roots, degree);
 
	When the degree is equal to 1, then it becomes a binomial with the form ax+b=0. The remaining single root is then equal tox=(-b/a). As seen in the code below, coeff[1] represents the constant (b) and coeff[0] represents the numerical coefficient of x (a). The developers immediately assigned the root of the linear equation as roots[0][0] since the program assigns the arrangement of roots based on the i variable used in the for loop which has an initial value equal to the degree of the polynomial. It is safe to assume that once the program reaches the point where the degree variable is equal to 1, we are already getting the last root. Note that not all polynomials will get a linear equation at the end, this only applies for odd-degree polynomials. See code interpretation of the process below.  

 else if (degree == 1) 
  roots[0][0] = (-1*coeff[1])/(coeff[0]); 

	After successfully obtaining the roots, part of the output specifications is to be able to display these roots. For this task, a simple for loop is used in order to loop through each element of the roots array. Earlier in the program, the degree variable was stored inside another variable named _degree. This was done to make sure that a copy of the degree of the polynomial is available since the degree variable gets deducted by 2 every iteration inside the for loop (see the iteration portion of the for loop). The roots are displayed using cout. The fixed command is used in order to make sure that the roots are represented with exactly as many digits in the decimal part as specified in the precision field, in this case 10. This also makes sure that displayed value has no exponent part. See Fig. 6 below. 
 // output roots 
 cout << endl << "Roots: " << endl;
 for(int i=0; i<_degree; i++)
 {
  cout << "(" << fixed << setprecision(10) << roots[i][0] << ", " << fixed << setprecision(10) <<roots[i][1] << ")" << endl;
 }


Fig. 6.Displaying the roots of the polynomial with precision 10

As seen in Fig. 6 above, setting the precision to 10 made the roots not as exact as expected. The roots for this particular test case should be -1, 4, and -3. However, setting the precision to 6 will yield the expected output. The developers decided to use 10 since the specifications said that the precision should be at least 10. See Fig. 7 for the roots of the polynomial for this particular test case with a precision equal to 6. 

Fig. 7.Displaying the roots of the polynomial with precision 6

vector<long double>  getQuadratic (vector<long double> coeff)
As mentioned, the developers used a for loop in order to reiterate Bairstow’s method if the degree is still greater than 2. Initially, the divideByLeadingCoefficient() function was called in order to make sure that the leading coefficient was equal to one. Next, the function getQuadratic() was then called in order to obtain the r and s values that will be used later on to solve for a pair of roots and lastly to obtain the quotient polynomial after applying synthetic division. Note that for this project implementation, the developers did not need to perform actual synthetic division rather a recurrence relationship was utilized (see eqn. 3). Moving on to the function specifications, this function accepts a long double vector coeff and returns a long double vector as well.
As seen in the code snippet below, the initial values for r and s were derived based on the eqns. 8 and 9 respectively.

r = a1/a0(8)
s = a2/a0(9)

  r = coeff[1]/coeff[0]; 
  s = coeff[2]/coeff[0];
After obtaining the r and s values, the reverse() function was used for convenience in calculating. Next, vectors b and c were initialized with a size based on the vector size of coeff containing just zeroes. Variables b and c were arrays at first but since arrays should be declared using compile-time constants it was important to change these variables into vectors instead since the size of those variables are dependent on the input and cannot be predetermined before compilation. 

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
  
  vector<long double>b(coeff.size(), 0);
  vector<long double>c(coeff.size(), 0); 
 
Moving on, a while loop was used in order to make sure that the best approximation for r and s is obtained since the values solved earlier were only the initial values. Check function checkRS() below in order to get an in-depth discussion on how it works. The process of obtaining the values for bn and cnare similar only that bnis derived from an, which in our case, is coeff and cn is derived from bn. For this part, eqn. 7 was used. Notice that the formulas before eqn. 7 can also be used, but in order to make efficient use of resources, the developers made the equation more general by using conditional operators. If the indices are out of bounds, the values are automatically assigned a value of zero. After that, the Δr and Δs is calculated using the obtained values for bn and cn. These values are then used to calculate for the error values that are needed as arguments for function checkRS(). The errorR and errorS values are based on eqns. 10 and 11. The aforementioned variables are basically the tolerance value for r and s respectively. Finally, the developers want to store the final r and s values and the new polynomial to divide. That is why they made efficient use of the coeff vector already available to them. The returned long double vector will contain the r and s values and the new polynomial after division.  

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
    for (int n = coeff.size()-1; n>-1; n--) //this is for the b_n and c_n equations
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

    errorR = fabs(100 * (deltaR / r)); //this part is for the tolerance value of r
    errorS = fabs(100 * (deltaS / s)); //this part is for the tolerance value of s
  } 

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
As seen in section III, it is imperative to obtain a better approximation of r and s by introducing Δr and Δs in order to get (r+Δr, s+Δs). This is the purpose of the checkRS() function. This function accepts a long double variable errorR and a long double errorS which was calculated using eqns. 10 and 11. These values were calculated inside the getQuadratic() function. Basically what this function does is return a boolean true or false that helps determine if the algorithm was able to solve for values of r and s within a certain error tolerance. This function is used by the getQuadratic() function in order to check if the r and s values obtained are already the best approximation of r and s based on a certain threshold set by the developers. The calculation for the r and s in the getQuadratic() function will continue as long as the errorR or errorS values are still greater than the stopError value of 1/1,000,000. This ensures that the program obtains a really reliable approximation of r and s that will be used further in the program. 

bool checkRS (long double errorR, long double errorS) //we check the r and S values with respect to the stoperor set
{
  long double stopError = 1/1e6; 
  return (errorR > stopError || errorS > stopError ); 
}

long double getRoots(vector<long double> coeff, long double roots[][2], int i) 
After the getQuadratic() function is called the coeff vector now contains the r, s and the numerical coefficients of the quotient. This is the reason why the developers decided to use vectors instead of arrays so that the program can make efficient use of its dynamic sizing. The developers were able to include the r and s values in the return statement by using the vector’s first two elements as temporary storage. Suppose given a polynomial,

f(x) = x4 + 2x3 - 11x2 + 8x - 60

After this polynomial encounters its first iteration with the getQuadratic() function, the coeff variable will contain the calculated r and s and the numerical coefficients of the quotient arranged as follows: [r, s, -15, 2, 1]. The conditional operators found in the code below are used in order to store the correct values of r and s since the arrangements of r and s changes once the degree becomes less than or equal to 2. Once the r and s values are correctly stored, the discriminant is then calculated. Note that the real component and the imaginary component of the roots are stored separately since the developers aim to calculate and store them separately as the real root and the imaginary root. The discriminant helps the program anticipate the nature of the roots:

When the discriminant > 0, there will be 2 real roots 
 When the discriminant = 0, there will be 1 real root
When the discriminant < 0, there will be 2 complex roots  

The process is the same when calculating for roots with a discriminant greater than 0 and roots with a discriminant equal to 0. Since the inputs here have a degree equal to 2, the expected number of roots always come in pairs. For the aforementioned case, the imaginary component is immediately set to zero and the real roots are calculated using the calculateNegRoot() and calculatePosRoot() functions. The aforementioned functions simply use the quadratic equation. 
When the discriminant is less than 0, 2 complex roots are expected. As seen in the code below, the real roots are easily calculated by dividing the r value by 2. For the imaginary roots, the calculateNegRoot() and calculatePosRoot() functions are used. These functions will be explained in detail further in this report. 
Once the real roots and the imaginary roots are successfully obtained, they are then stored inside the roots array. This is the reason why the degree variable is reduced by 2 every iteration since a pair of roots is always obtained in the getRoots() function. See code interpretation of the process below. 

long double getRoots(vector<long double> coeff, long double roots[][2], int i) 
{

  //-15 2 1  //negative sign is added because the equation we used is x^2-rx-s so that means we take the innateness of the r and s values
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
    imaginaryRoot[1] = calculatePosRoot(r, s, discriminant); 
  }

  roots[i-1][0] = realRoot[0];   
  roots[i-1][1] = imaginaryRoot[0];
  roots[i-2][0] = realRoot[1];
  roots[i-2][1] = imaginaryRoot[1];


  return **roots; 

}

long double calculateNegRoot(long double r, long double s, long double discriminant)

The calculateNegRoot() function accepts a long double r, a long double s, and a long double discriminant as arguments and calculates the negative root of a quadratic function. This function checks the value of the discriminant, if the discriminant is greater than or equal to 0 then the roots are real, and imaginary otherwise. Under the if condition, the return statement simply uses the quadratic equation to get the negative root. On the other hand, the else statement has a slightly modified return statement. Notice how a negative sign is added to the discriminant in the formula. This makes sure that the function does not return a NaN value from calculating the square root of a negative number. See code interpretation of the process below. 

long double calculateNegRoot(long double r, long double s, long double discriminant) // the - root
{
  if (discriminant>=0) //real
    return (r- sqrt(discriminant))/2;

  else //imaginary
    return (-1*sqrt(-discriminant))/2; 
}

long double calculatePosRoot(long double r, long double s, long double discriminant)
The calculatePosRoot() function accepts a long double r, a long double s, and a long double discriminant as arguments and calculates the positive root of a quadratic function. This function checks the value of the discriminant, if the discriminant is greater than or equal to 0 then the roots are real, and imaginary otherwise. Under the if condition, the return statement simply uses the quadratic equation to get the positive root. On the other hand, the else statement has a slightly modified return statement. Notice how a negative sign is added to the discriminant in the formula. This makes sure that the function does not return a NaN value from calculating the square root of a negative number. The developers decided to separate the process of calculating the positive root and the negative to make the program readable and easier to debug. See code interpretation of the process below. 

long double calculatePosRoot(long double r, long double s, long double discriminant) //the + root
{
  if (discriminant >= 0) //real
    return (r + sqrt(discriminant))/2; 

  else //imaginary
    return (sqrt(-discriminant))/2;  
}


vector<long double> getNewCoeff(vector<long double> coeff) 
This function accepts a vector long double coeff as argument and returns a long double vector. Suppose given a polynomial,

           f(x) = x4 + 2x3 - 11x2 + 8x - 60

After this polynomial encounters its first iteration with the getQuadratic() function, the coeff variable will contain the calculated r and s and the numerical coefficients of the quotient arranged as follows: [r, s, -15, 2, 1]. After the reverse function, the new arrangement will then be [1, 2, -15, s, r]. The double pop_back() function calls are used to remove the r and s values located at the last and second to the last elements of the coeff vector. What now remains are the elements arranged as follows: [1, 2, -15]. The coeff vector is again reversed and is now arranged as follows: [-15, 2, 1]. The objective of this function is to obtain the new coefficient after the initial Bairstow’s method iteration and to make sure that the numerical coefficients are still arranged correctly. See code interpretation of the process below. 

vector<long double> getNewCoeff(vector<long double> coeff) //we get new coefficients here after initial bairstow's theorem iteration
{
  reverse(coeff.begin(), coeff.end());  
  coeff.pop_back(); 
  coeff.pop_back(); 
  reverse(coeff.begin(), coeff.end()); 
  return coeff; 
}


complex <long double> useHorner (vector<long double> coeff, complex<long double> x)
	After displaying the roots, the final output specification is to be able to evaluate the polynomials at identified roots. Notice that in the code snippet below, it loops through all the values of roots but before using these values as arguments to the useHorner() function, the complex header allows the program to define complex numbers. This is the reason why the developers decided to use the real and imaginary components so that later on they can be easily defined using the complex header. 

 cout << endl << "Evaluating polynomial at identified roots: " << endl; //here we output the polynomials we want based on the roots we obtained
 for(int i = 0; i<coeffForEval.size()-1; i++)
 {
  complex<long double> x(roots[i][0],roots[i][1]); 
  cout << "f(" << roots[i][0] << ", " << roots[i][1] << ") = " << real(useHorner(coeffForEval, x)) << endl;
 }
	The function useHorner() accepts a long double vector coeff and a complex long double x and returns a complex long double value. Horner’s method for polynomial evaluation has O(n) time complexity[3]. The C++ implementation was derived from geeksforgeeks discussion about Horner’s method[3].  


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


V. Outputs 
 	The program was then tested using seven different cases. Below are the corresponding outputs. 

















Filename: p1.txt
3
-12
-13
0
1
roots: -3, -1, 4
OUTPUT


Filename: p2.txt
5  1.25  -3.875  2.125  2.75  -3.5  1
This is the 5th degree polynomial x^5 - 3.5 x^4  + 2.75 x^3 + 2.125 x^2  - 3.875x +1.25
roots are 2, -1, 1 +/- 0.5, 0.5















OUTPUT



Filename: p3.txt
3
2
-10
0
1

roots are -3.25789701, 0.20080976, 3.05708726

OUTPUT


Filename: p4.txt
5
0
1.875
0
-8.75
0
7.875
Legendre polynomial of order 5
roots: 0, +/- 0.538469310105683, +/-0.906179845938664

OUTPUT


Filename: p5.txt
4
1
2
3
2
1

this is ( x^2 + x + 1 )^2
roots are -0.5 +/- sqrt(3/4) each occurring twice

OUTPUT


Filename: p6.txt
11
-1
0
0
0
0
0
0
0
0
0
0
1
roots: exp(i 2 pi n/11), n = 0..10











OUTPUT

Filename: p7.txt
27
0
-4.18448746204376221
0
525.850591063499451
0
-19561.6419875621796
0
338136.954356431961
0
-3287442.61179864407
0
19903970.7223445177
0
-79615882.8893780708
0
217616746.56430006
0
-412831769.217569232
0
543199696.338906884
0
-486293061.484354734
0
282549723.471146822
0
-96066905.9801899195
0
14505829.1081198454
Legendre polynomial of order 27






















OUTPUT




VI. References 
[1]“Bairstow's Method.” From Wolfram MathWorld, mathworld.wolfram.com/BairstowsMethod.html.
. 
[2]Bairstow Method, nptel.ac.in/content/storage2/courses/122104019/numerical-analysis/Rathish-kumar/ratish-1/f3node9.html?fbclid=IwAR3TRo0bQAYCtPfNyD8Ph7j1NMJbSYu9DA0p8Q7eBphbH5XquyNl9xKRsPo.

[3]“Horner's Method for Polynomial Evaluation.” GeeksforGeeks, 5 July 2018, www.geeksforgeeks.org/horners-method-polynomial-evaluation/.


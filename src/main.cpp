#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath> // pow(base, exp) base**exp

using namespace std;

//get the command line arguments and returns an array which inclueds the parameters
double* get_input(char** argv, int &size)
{
	double * arr = NULL;
	int i = 1;
	while(argv[i] != NULL)
	{
		arr = (double*) realloc (arr, i * sizeof(double)); //dynamically reallocate the array if there is a command line argument
		arr[i-1] = atof(argv[i]); // assign it to array
		i++;
	}
	size = i-1;
	//if no parameter is given
	if(arr == NULL)
	{
		cout << "please enter command line values" << endl;
	}
	else
	{
		return arr;
	}
}

//helper function for writing the array
void print_array(double* arr, int size)
{
	for (int i=0; i<size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

//this function takes the input array, the value x, and the number of degree, then compute the f(x)
double func(double* arr, double x, int degree)
{
	double fx = 0;
	for (int i=0; i< degree; i++)
	{
		fx = fx + arr[i] * pow(x, degree - i - 1); //x^degree-i-1
	}
	//cout << x << ": " << fx << endl;
	return fx;
}

//bisection method that is used to find the root
double bisection(double* arr, int input_num)
{
	double x0 = arr[input_num-3];
	double x1 = arr[input_num-2];
	double tol = arr[input_num-1];
	int degree = input_num - 3;
    double ort;
 	int iteration = 0;
    while (fabs(x1-x0) >= tol)
    {
    	//cout << "ort: " << ort << endl;
        ort = (x0+x1)/2; // find the average value
		if (func(arr, ort, degree) * func(arr, x0, degree) <= 0) //if signs are different (x0 and ort)
		{
            x1 = ort; //assign x1 to ort
        }
        else
		{
            x0 = ort; // assign ort to x0
        }
        iteration ++;      
    }
    cout << "Using bisection method, " << iteration << " iteration needed. And the root is: " << ort << endl;
    return ort;
}

//secant method
double secant(double* arr, int input_num)
{
	double x0 = arr[input_num-3];
	double x1 = arr[input_num-2];
	double tol = arr[input_num-1];
	int degree = input_num - 3;	
	double ort;
	int iteration = 0;
	while(fabs(x1-x0) >= tol)
	{
	 	ort = (func(arr, x1, degree) * x0 - func(arr, x0, degree) * x1) / (func(arr, x1, degree) - func(arr, x0, degree)); //find the (x0 * f(x1) - x1 * f(x0)) / (f(x1) - f(x0))
	 	x0 = x1;
	 	x1 = ort;
	 	iteration ++;
	}
	cout << "Using secant method, " << iteration << " iteration needed. And the root is: " << ort << endl;
	return ort ;
}

//hybrid method that uses the bisection method in the first 2 
double hybrid(double* arr, int input_num)
{
	double result = 0;
	double x0 = arr[input_num-3];
	double x1 = arr[input_num-2];
	double tol = arr[input_num-1];
	int degree = input_num - 3;
    double ort;
 	int iteration = 0;	
	while(fabs(x1-x0) >= tol)
	{
		//first two iteration using bisection mathod
		if(iteration < 2)
		{
	        ort = (x0+x1)/2;
			if (func(arr, ort, degree) * func(arr, x0, degree) <= 0)
			{
	            result = ort;
	            x1 = ort;
	        }
	        else
			{
	            result = ort;
	            x0 = ort;
	        }			
		}
		//then use secant method
		else
		{
		 	ort = (func(arr, x1, degree) * x0 - func(arr, x0, degree)*x1) / (func(arr, x1, degree)-func(arr, x0, degree)) ;
		 	x0 = x1;
		 	x1 = ort;			
		}
	 	iteration ++;
	}
	cout << "Using hybrid method, " << iteration << " iteration needed. And the root is: " << ort << endl;
	return ort;
}

int main(int argc, char** argv) 
{
	int input_num = 0;
	double* arr = get_input(argv, input_num);
	double result = bisection(arr, input_num);
	double res2 = secant(arr, input_num);
	double res3 = hybrid(arr, input_num);
	return 0;
}

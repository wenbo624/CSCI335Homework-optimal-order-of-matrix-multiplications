//Name: Wen Bo
//Date: 5/13/2019
//Assignment: CSCI335 Assignment5
//This project outputs the optimal number of multiplication and its ordering.


#include "matrix.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <string>
using namespace std;

//This function returns a vector containing matrix sizes.
void MatrixSize(const string & input_file, vector<int> & vi)
{
	int num;
	ifstream in_file;
	in_file.open(input_file);

	while(in_file >> num)
	{
		vi.push_back(num);
	}	

	in_file.close();

}

/**
* Compute optimal ordering of matrix multiplication.
* c contains the number of colnums for each of the n matrices.
* c[0] is the number of rows in matrix 1.
* The minimum number of multiplications is left in m[1][n].
* Actual ordering is computed via another procedure using lastChange.
* m and lastChange are indexed starting at 1, instead of 0.
* Note: Entries below main diagonals of m and lastChange 
* atr meaningless and uninitialized.
*/
template <typename Object>
void optMatrix(const vector<int> & c, matrix<Object> & m, matrix<Object> & lastChange)
{
	int n = c.size() - 1;

	for(int left = 1; left <= n; left++)
		m[left][left] = 0;
		

	for(int k = 1; k< n; k++) // k is right - left
		for(int left = 1; left <= n - k; left++)
		{
			//for each position
			int right = left + k;
			m[left][right] = std::numeric_limits<int>::max();
			for(int i = left; i < right; i++)
			{
				int thisCost = m[left][i] + m[i + 1][right] + c[left - 1] * c[i] * c[right];
				if(thisCost < m[left][right]) //Update min
				{
					m[left][right] = thisCost;
					lastChange[left][right] = i;
				}
			}
		}
	
}

/**This function returns the index of the position 
*  where to insert parentheses.
*/
int FindtheIndex(const string & s, int pos)
{
	
	string n = to_string(pos);
	for(size_t i = 0; i < s.size(); i++)
	{
		string check="";
		check += s[i];
		
		if(check == n)
		{
			return i;
		}
	}
	return 1;
}

//This function returns the ordering string of the optimal multiplication.
void orderString(string & astr, int firsti, int lasti, matrix<int> lastChange)
{
	
	int times = lastChange[firsti][lasti];

	//Left equals to right
	if(lasti - firsti < 1)
	{
		return;
	}
	//Left is greater than right -- need to find the optimal order
	else if(lasti - firsti  == 1)
	{
		astr.insert(FindtheIndex(astr, firsti) - 1, "(");
		astr.insert(FindtheIndex(astr, lasti) + 1, ")");
	}
	else
	{
		astr.insert(FindtheIndex(astr, firsti) - 1, "(");
		astr.insert(FindtheIndex(astr, lasti) + 1, ")");

		//Find the optimal order of M[left][i] and M[i+1][right]
		orderString(astr, firsti, times, lastChange);
		orderString(astr, times + 1, lasti, lastChange);
	}

}

int main(int argc, char **argv) {
 	if (argc != 2) {
 		cout << "Usage: " << argv[0] << " <document-file> " << endl;
		return 0;
  	}
  
  	const string document_filename(argv[1]);
  	
  	//Store the matrice size 
  	vector<int> msize;
  	MatrixSize(document_filename, msize);

  	int thesize = msize.size();

  	matrix<int> matrix1(thesize, thesize);
  	matrix<int> matrix2(thesize, thesize);

   	optMatrix(msize, matrix1, matrix2);
  	
  	cout << "The optimal number of multiplications is " << matrix1[1][thesize - 1] << endl;

  	//Create the original martice string without parentheses
  	string marStr;
  	for(int i = 1; i < thesize; i++)
  	{
  		marStr += "A";
  		marStr += to_string(i);

  	}

  	orderString(marStr, 1, thesize - 1, matrix2);
  	cout << "The optimal ordering is "<< marStr << endl;
  	
  	return 0;

  }

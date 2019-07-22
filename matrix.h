//Name: Wen Bo
//Date: 5/13/2019
//Assignment: CSCI335 Assignment5
//The header file for the implementation of the matrix.(From textbook Pg45)

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
using namespace std;

template <typename Object>
class matrix
{
	public:

		matrix( int rows, int cols ) : array( rows )
		{
			for( auto & thisRow : array )
				thisRow.resize( cols );
		}

		matrix( vector<vector<Object> > v ) : array{ v }
			{ }
		matrix( vector<vector<Object> > && v ) : array{ std::move(v) }
			{ }

		const vector<Object> & operator[]( int row ) const
			{ return array[row]; }
		vector<Object> & operator[]( int row )
			{ return array[row]; }

		int numrows() const
			{ return array.size(); }
		int numcols() const
			{ return numrows() ? array[0].size() : 0; }

	private:
		vector<vector<Object> > array;
};

#endif
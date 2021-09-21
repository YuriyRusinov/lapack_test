#include <algorithm>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>

#include <cblas.h>
#include "LMatrix.h"

using std::cerr;
using std::endl;
using std::min;
using std::max;
using std::string;
using std::stringstream;
using std::range_error;
using std::out_of_range;

LMatrix::LMatrix(int n, int m, double* values)
    : m_nRows(n),
    m_nColumns(m),
    m_values( (n * m) > 0 ? vector< double > (m*n) : vector<double>() ) {

    if( values != nullptr ) {
        int nr = sizeof(values)/sizeof(double);
        int nn = min( n*m, nr );
        for( int i=0; i<nn; i++ ) {
            m_values[i] = values[i];
        }
        for( int i=nn+1; i<n*m; i++ ) {
            m_values[i] = 0.0;
        }
    }
    else {
        for ( int i=0; i<n*m; i++ ) {
            m_values[i] = 0.0;
        }
    }
}

LMatrix::LMatrix( const LMatrix& M )
    : m_nRows ( M.m_nRows ),
    m_nColumns ( M.m_nColumns ),
    m_values( m_nRows*m_nColumns > 0 ? vector< double > (m_nRows*m_nColumns) : vector< double >() ) {
    int nn = m_nRows*m_nColumns;
    for(int i=0; i<nn; i++) {
        m_values[i] = M.m_values[i];
    }
}

LMatrix::LMatrix( LMatrix&& M ) 
    : m_nRows( M.m_nRows ),
    m_nColumns( M.m_nColumns ),
    m_values( M.m_values ) {
    M.m_nRows = 0;
    M.m_nColumns = 0;
    M.m_values.clear();//= nullptr;
}

LMatrix& LMatrix::operator=( const LMatrix& M ) {
    if( this != &M ) {
        m_nRows = M.m_nRows;
        m_nColumns = M.m_nColumns;
        int nr = M.m_values.size();//sizeof(M.m_values)/sizeof(double);
        if( nr ) {
            m_values = vector< double >(nr);
            for(int i=0; i<nr; i++)
                m_values[i] = M.m_values[i];
        }
        else
            m_values = vector< double >();
    }
    return *this;
}

LMatrix& LMatrix::operator=( LMatrix&& M ) {
    if( this != &M ) {
        m_nRows = M.m_nRows;
        M.m_nRows = 0;
        m_nColumns = M.m_nColumns;
        M.m_nColumns = 0;
        m_values = M.m_values;
        M.m_values.clear();
    }
    return *this;
}

LMatrix::~LMatrix() {
}

double& LMatrix::operator() (int i, int j) {
    if( i < 0 || i > m_nRows-1 || j < 0 || j > m_nColumns-1 ) {
        stringstream err_str;
        err_str << __PRETTY_FUNCTION__ << " Invalid matrix indices";
        throw out_of_range(err_str.str().c_str());
    }

    return m_values[i*m_nRows+j];
}

const double& LMatrix::operator() (int i, int j) const {
    if( i < 0 || i > m_nRows-1 || j < 0 || j > m_nColumns-1 ) {
        stringstream err_str;
        err_str << __PRETTY_FUNCTION__ << " Invalid matrix indices";
        throw out_of_range(err_str.str().c_str());
    }

    return m_values[i*m_nRows+j];
}

const double* LMatrix::getAddr(int i, int j) const {
    if( i < 0 || i > m_nRows-1 || j < 0 || j > m_nColumns-1 ) {
        stringstream err_str;
        err_str << __PRETTY_FUNCTION__ << " Invalid matrix indices " << i << " of " << m_nRows << " " << j << " of " << m_nColumns;
        throw out_of_range(err_str.str().c_str());
    }

    int shift = i*m_nRows+j;
    return m_values.data()+shift;
}

int LMatrix::rowCount() const {
    return m_nRows;
}

int LMatrix::columnCount() const {
    return m_nColumns;
}

LMatrix& LMatrix::operator+= ( const LMatrix& M ) {
    if( m_nRows != M.m_nRows || m_nColumns != M.m_nColumns )
        throw range_error("Invalid matrix sizes");
 
    int nn = m_nRows*m_nColumns;
/*    for(int i=0; i<nn; i++)
        m_values[i] += M.m_values[i];
*/
    cblas_daxpy( nn, 1.0, M.m_values.data(), 1, m_values.data(), 1 );
    return *this;
}

LMatrix& LMatrix::operator-= ( const LMatrix& M ) {
    if( m_nRows != M.m_nRows || m_nColumns != M.m_nColumns )
        throw range_error("Invalid matrix sizes");

    int nn = m_nRows*m_nColumns;
/*    for(int i=0; i<nn; i++)
        m_values[i] -= M.m_values[i];
*/
    cblas_daxpy( nn, -1.0, M.m_values.data(), 1, m_values.data(), 1 );

    return *this;
}

LMatrix& LMatrix::operator*= ( const LMatrix& M ) {
    if( M.m_nRows != m_nColumns )
        throw range_error("Invalid matrix sizes");
    double* tvals = new double[ m_nRows * M.m_nColumns ];
    double alpha = 1.0;
    double beta = 0.0;
    cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans, m_nRows, M.m_nColumns, m_nColumns, alpha, m_values.data(), m_nColumns, M.m_values.data(), M.m_nColumns, beta, tvals, m_nRows );
    m_nColumns = M.m_nColumns;
    m_values.clear();
    for(int i=0; i<m_nRows * M.m_nColumns; i++)
        m_values[i] = tvals[i];
    delete [] tvals;
    return *this;
}

LMatrix& LMatrix::linearSolve( LMatrix& X ) {
    return *this;
}

const double* LMatrix::getValues() const {
    return m_values.data();
}

void LMatrix::insertRow(int nr) {
    if( nr > m_nRows )
        return;
    if( nr == m_nRows )
        for(int j=0; j<m_nColumns; j++)
            m_values.push_back(0.0);
    else
        m_values.insert( m_values.begin()+nr, m_nColumns, 0.0);
    m_nRows++;
}

void LMatrix::removeRow(int nr) {
    if( nr > m_nRows-1 )
        return;
    if( nr == m_nRows-1 )
        for(int j=0; j<m_nColumns; j++)
            m_values.pop_back();
    else
        m_values.erase( m_values.begin()+nr, m_values.begin()+nr+m_nColumns );
    m_nRows--;
}

void LMatrix::insertColumn(int nc) {

}

void LMatrix::removeColumn(int nc) {

}

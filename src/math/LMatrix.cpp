#include <algorithm>
#include <stdexcept>

#include <cblas.h>
#include "LMatrix.h"

using std::min;
using std::max;
using std::range_error;
using std::out_of_range;

LMatrix::LMatrix(int n, int m, double* values)
    : m_nRows(n),
    m_nColumns(m),
    m_values( (n * m) > 0 ? new double [m*n] : nullptr ) {

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
    m_values( m_nRows*m_nColumns > 0 ? new double [m_nRows*m_nColumns] : nullptr ) {
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
    M.m_values = nullptr;
}

LMatrix& LMatrix::operator=( const LMatrix& M ) {
    if( this != &M ) {
        m_nRows = M.m_nRows;
        m_nColumns = M.m_nColumns;
        int nr = sizeof(M.m_values)/sizeof(double);
        if( m_values != nullptr )
            delete [] m_values;
        if( nr ) {
            m_values = new double[nr];
            for(int i=0; i<nr; i++)
                m_values[i] = M.m_values[i];
        }
        else
            m_values = nullptr;
    }
    return *this;
}

LMatrix& LMatrix::operator=( LMatrix&& M ) {
    if( this != &M ) {
        m_nRows = M.m_nRows;
        M.m_nRows = 0;
        m_nColumns = M.m_nColumns;
        M.m_nColumns = 0;
        if( m_values )
            delete [] m_values;
        m_values = M.m_values;
        M.m_values = nullptr;
    }
    return *this;
}

LMatrix::~LMatrix() {
    if( m_values )
        delete m_values;
}

double& LMatrix::operator() (int i, int j) {
    if( i < 0 || i > m_nRows-1 || j < 0 || j > m_nColumns-1 )
        throw out_of_range("Invalid matrix indices");

    return m_values[i*m_nRows+j];
}

const double& LMatrix::operator() (int i, int j) const {
    if( i < 0 || i > m_nRows-1 || j < 0 || j > m_nColumns-1 )
        throw out_of_range("Invalid matrix indices");

    return m_values[i*m_nRows+j];
}

double* const LMatrix::getAddr(int i, int j) const {
    if( i < 0 || i > m_nRows-1 || j < 0 || j > m_nColumns-1 )
        throw out_of_range("Invalid matrix indices");

    int shift = i*m_nRows+j;
    return m_values+shift;
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
    cblas_daxpy( nn, 1.0, M.m_values, 1, m_values, 1 );
    return *this;
}

LMatrix& LMatrix::operator-= ( const LMatrix& M ) {
    if( m_nRows != M.m_nRows || m_nColumns != M.m_nColumns )
        throw range_error("Invalid matrix sizes");

    int nn = m_nRows*m_nColumns;
/*    for(int i=0; i<nn; i++)
        m_values[i] -= M.m_values[i];
*/
    cblas_daxpy( nn, -1.0, M.m_values, 1, m_values, 1 );

    return *this;
}

LMatrix& LMatrix::operator*= ( const LMatrix& M ) {
    if( M.m_nRows != m_nColumns )
        throw range_error("Invalid matrix sizes");
    double* tvals = new double[ m_nRows * M.m_nColumns ];
    double alpha = 1.0;
    double beta = 0.0;
    cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans, m_nRows, M.m_nColumns, m_nColumns, alpha, m_values, m_nColumns, M.m_values, M.m_nColumns, beta, tvals, m_nRows );
    m_nColumns = M.m_nColumns;
    delete [] m_values;
    m_values = tvals;
    return *this;
}

LMatrix& LMatrix::linearSolve( LMatrix& X ) {
    return *this;
}

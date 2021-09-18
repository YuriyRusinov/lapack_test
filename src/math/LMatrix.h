/* @brief Class of matrices for Lapack
 * @author Yury Rusinov
 *
 *
 */

#pragma	once

class LMatrix {
public:
    LMatrix(int n=0, int m=0, double* values=nullptr);
    LMatrix( const LMatrix& M );
    LMatrix( LMatrix&& M );
    LMatrix& operator=( const LMatrix& M );
    LMatrix& operator=( LMatrix&& M );
    ~LMatrix();

    double& operator() (int i, int j);
    const double& operator() (int i, int j) const;

    double* const getAddr(int i, int j) const;

    int rowCount() const;
    int columnCount() const;

    LMatrix& operator+= ( const LMatrix& M );
    LMatrix& operator-= ( const LMatrix& M );
    LMatrix& operator*= ( const LMatrix& M );

    LMatrix& linearSolve( LMatrix& X );
private:
    int m_nRows;
    int m_nColumns;

    double* m_values;
};

/* @brief Class of matrices for Lapack
 * @author Yury Rusinov
 *
 *
 */

#pragma	once

#include <vector>

using std::vector;

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

    const double* getAddr(int i, int j) const;
    const double* getValues() const;

    void insertRow(int nr);
    void removeRow(int nr);
    void insertColumn(int nc);
    void removeColumn(int nc);

    int rowCount() const;
    int columnCount() const;

    LMatrix& operator+= ( const LMatrix& M );
    LMatrix& operator-= ( const LMatrix& M );
    LMatrix& operator*= ( const LMatrix& M );

    LMatrix& linearSolve( LMatrix& X );

private:
    int m_nRows;
    int m_nColumns;

    vector<double> m_values;
};

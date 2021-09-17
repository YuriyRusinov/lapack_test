/*
 * =====================================================================================
 *        Class:  MatrixModel
 *  Description:  Class of Models for graphical matrices view
 *       Author:  Yury Rusinov
 * =====================================================================================
 */
#pragma	once

#include <QAbstractItemModel>

class MatrixModel : public QAbstractItemModel {
public:
    /* ====================  LIFECYCLE     ======================================= */
    MatrixModel (QObject* parent = nullptr);
    virtual ~MatrixModel();

    /* ====================  ACCESSORS     ======================================= */

    /* ====================  MUTATORS      ======================================= */

    /* ====================  OPERATORS     ======================================= */

protected:
    /* ====================  METHODS       ======================================= */

    /* ====================  DATA MEMBERS  ======================================= */

private:
    /* ====================  METHODS       ======================================= */

    /* ====================  DATA MEMBERS  ======================================= */
    Q_OBJECT
}; /* -----  end of class MatrixModel  ----- */


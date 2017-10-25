#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QTextStream>
#include <QFile>
#include <QComboBox>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QCheckBox>
#include <QString>
#include <QChar>

namespace Ui {
class MainWindow;
}

class int_paint {
public:
    QString ID; //no usage other than programming
    QString unit;
    QString substrate; // area that is being painted
    char UOM; // unit of measure
    int quantity;
    double lf_conversion; //linear feet conversion
    int sq_per_gal; //square feet per gal
    double coats;
    char f_or_s;
    double flat_per_unit;
    double semi_per_unit;
    int multiplier; //dependant on number of apartments
    double subtotal_flat;
    double subtotal_semi;
    int waste;
    double waste_total_flat; //subtotal * waste (waste must be entered as an int representing a %, conv it to decimal)
    double waste_total_semi;// ^
    double total_flat;//waste_total * multiplier
    double total_semi;// ^
};


//bottom part:
// add rentals, exclude overhead on this one
//overhead goes BEFORE rentals
//profit goes on top of everything


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void prep_info();
    void clone(QString copy_of);

signals:
void send_to_int_paint(QString Usubstrate, QString UQuantity, char UOM,int UCoats, char UFlat_or_semi);


private slots:

    void on_actionExit_triggered();

    void on_actionOpen_Project_triggered();

    void on_actionSave_triggered();

    void on_touchup_toggled(bool checked);

    void on_Quantity_editingFinished();

    void on_New_substrate_clicked();

    void on_Substrate_editingFinished();
    
    void on_UOM_currentTextChanged(const QString &arg1);
    
    void on_Coats_editingFinished();
    
    void on_Material_type_currentTextChanged(const QString &arg1);
    
    void on_Paint_Type_currentTextChanged(const QString &arg1);

    void on_tabWidget_tabBarDoubleClicked(int index);

protected:
    Ui::MainWindow *ui; // I need the other class to be able to access this. Without that I can't make it work.
};

class interior_paint : public MainWindow
{

    Q_OBJECT

public:
    interior_paint();
    ~interior_paint(); //de-allocates all memory allocate to int_paint by operator new.
    interior_paint(const interior_paint&); //copy constructor
    bool is_empty(); //inline implementation
    bool is_full();//inline implementation
    int search(const QString key);//returns location if item in listl; otherwise return -1
    void increase_size();
    void calculate();
private slots:
    void insert_to_database(QString Usubstrate, QString UQuantity, char UUOM,int UCoats, char UFlat_or_semi);

private:
    int count;
    int size;
    int_paint *int_DB;
};

#endif // MAINWINDOW_H

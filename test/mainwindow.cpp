#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mydialog.h"

#include <QFileDialog>
#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QTextEdit>
#include <QtWidgets>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

{ // Setting up the items I need
    QComboBox * Unit_list = new QComboBox();
    QPushButton New_substrate;
    QPushButton Calculate;
    QCheckBox *touchup;
    QGridLayout * Main_Edit = new QGridLayout();
    QLineEdit *Substrate = new QLineEdit();
    QAbstractSpinBox *Coats = new QAbstractSpinBox();
    QComboBox * Material_Type = new QComboBox();
    QComboBox * Paint_Type = new QComboBox();
    QComboBox * UOM = new QComboBox();
    QLineEdit *Quantity = new QLineEdit();
    QWidget *Main_Page = new QWidget;
    QWidget * Interior_Paint_Page = new QWidget;
    QStackedWidget * Main = new QStackedWidget;
    QTabWidget * Unit_tab = new QTabWidget;
    QLabel * Flat_Gls = new QLabel();
    QLabel * Semi_Gls = new QLabel();
    QVBoxLayout * idk = new QVBoxLayout();
    New_substrate.setText("New Group");
    Calculate.setText("Calculate");
    Main->addWidget(Main_Page);
    Main->addWidget(Interior_Paint_Page);
    Unit_list->setEditable(true);
    Unit_list->insertPolicy();
    Main_Edit->addWidget(Substrate,0,0);
    Main_Edit->addWidget(UOM,0,1);
    Main_Edit->addWidget(Coats,0,2);
    Main_Edit->addWidget(Material_Type,0,3);
    Main_Edit->addWidget(Quantity,0,4);
    UOM->addItem("Select...");
    UOM->addItem("Sq Ft");
    UOM->addItem("Ln Ft");
    UOM->addItem("Ea");
    Material_Type->addItem("Select...");
    Paint_Type->addItem("Select...");
    Paint_Type->addItem("Flat");
    Paint_Type->addItem("Semi");
    Paint_Type->addItem("Both");
}
 int location = 0;
}

interior_paint::interior_paint()
{
    QFile file("callstats_data.txt");
    size = 20;
    count = 0;
    int_DB = new int_paint[size + 1];
    connect(ui->Calculate,
            SIGNAL(MainWindow::send_to_int_paint(QString Usubstrate, QString UQuantity, QString UUOM,int UCoats)),
            this,
            SLOT(interior_paint::insert_to_database(QString Usubstrate, QString UQuantity, QString UUOM,int UCoats)));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        if (is_full() == 1) {
            increase_size();
        }
        else {
            in >> int_DB[count].ID;
            in >> int_DB[count].unit;
            in >> int_DB[count].substrate;
            in >> int_DB[count].UOM;
            in >> int_DB[count].quantity;
            in >> int_DB[count].lf_conversion;
            in >> int_DB[count].sq_per_gal;
            in >> int_DB[count].coats;
            in >> int_DB[count].flat_per_unit;
            in >> int_DB[count].semi_per_unit;
            in >> int_DB[count].multiplier;
            in >> int_DB[count].subtotal_flat;
            in >> int_DB[count].subtotal_semi;
            in >> int_DB[count].waste;
            in >> int_DB[count].waste_total_flat;
            in >> int_DB[count].waste_total_semi;
            in >> int_DB[count].total_flat;
            in >> int_DB[count].total_semi;
            count++;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

interior_paint::~interior_paint()
{
    delete[] int_DB;
    int_DB = 0;

}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_actionOpen_Project_triggered()
{/*
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),QString(),tr("Text Files (*.txt)"));
    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
        }
        QDataStream in(&file);
        information.clear();
        in >> information; //information is the file. the file should have a custom (.info) and information.clear()
        file.close(); //needs to be implemented.
    } */
}

void MainWindow::on_actionSave_triggered()
{/*
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));
    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)){
        QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
        return;
        } else {
            QDataStream out(&file);
            out << information;
            file.close();
        }
    }
*/
}


void MainWindow::on_New_substrate_clicked() // this button creates a new group below. this should be automated at a later date
{


}

void MainWindow::on_touchup_toggled(bool checked)
{
    if(checked == true){
        int coats_value =ui->Coats->value();
        ui->Coats->setValue(coats_value+.2);
    }
}


void MainWindow::on_Quantity_editingFinished()
{
    if ((ui->Substrate->text().isEmpty() && ui->Quantity->text().isEmpty() && ui->Material_type->currentText() == "Select..." && ui->UOM->currentText() == "Select..." && ui->Coats->value() == 0 && ui->Paint_Type->currentText() == "Select...")){
        ui->Flat_Gls->setText("0.00");
        ui->Semi_Gls->setText("0.00");
    }
   else {
        prep_info();
    }
}


void MainWindow::on_Substrate_editingFinished()
{
    if ((ui->Substrate->text().isEmpty() && ui->Quantity->text().isEmpty() && ui->Material_type->currentText() == "Select..." && ui->UOM->currentText() == "Select..." && ui->Coats->value() == 0 && ui->Paint_Type->currentText() == "Select...")){
        ui->Flat_Gls->setText("0.00");
        ui->Semi_Gls->setText("0.00");
    }
    else {
         prep_info();
     }
}

void MainWindow::on_UOM_currentTextChanged(const QString &arg1)
{
    if ((ui->Substrate->text().isEmpty() && ui->Quantity->text().isEmpty() && ui->Material_type->currentText() == "Select..." && ui->UOM->currentText() == "Select..." && ui->Coats->value() == 0 && ui->Paint_Type->currentText() == "Select...")){
        ui->Flat_Gls->setText("0.00");
        ui->Semi_Gls->setText("0.00");
    }
    else {
         prep_info();
     }
}

void MainWindow::on_Coats_editingFinished()
{
    if ((ui->Substrate->text().isEmpty() && ui->Quantity->text().isEmpty() && ui->Material_type->currentText() == "Select..." && ui->UOM->currentText() == "Select..." && ui->Coats->value() == 0 && ui->Paint_Type->currentText() == "Select...")){
        ui->Flat_Gls->setText("0.00");
        ui->Semi_Gls->setText("0.00");
    }
    else {
         prep_info();
     }
    
}

void MainWindow::on_Material_type_currentTextChanged(const QString &arg1)
{
    if ((ui->Substrate->text().isEmpty() && ui->Quantity->text().isEmpty() && ui->Material_type->currentText() == "Select..." && ui->UOM->currentText() == "Select..." && ui->Coats->value() == 0 && ui->Paint_Type->currentText() == "Select...")){
        ui->Flat_Gls->setText("0.00");
        ui->Semi_Gls->setText("0.00");
    }
    else {
         prep_info();
     }
}

void MainWindow::on_Paint_Type_currentTextChanged(const QString &arg1)
{
    if ((ui->Substrate->text().isEmpty() && ui->Quantity->text().isEmpty() && ui->Material_type->currentText() == "Select..." && ui->UOM->currentText() == "Select..." && ui->Coats->value() == 0 && ui->Paint_Type->currentText() == "Select...")){
        ui->Flat_Gls->setText("0.00");
        ui->Semi_Gls->setText("0.00");
    }
    else {
         prep_info();
     }
}
void MainWindow:: prep_info(){
    QString Usubstrate;
    QString UQuantity;
    char UUOM;
    char UFlat_or_Semi;
    int UCoats;
    Usubstrate = ui->Substrate->text();
    UQuantity =ui->Quantity->text();
    QString UOM_info = ui->UOM->currentText();
    if(UOM_info == "Sq Ft"){
       UUOM = 'S';
    } else if (UOM_info == "Ln Ft"){
        UUOM = 'L';
    } else if (UOM_info == "Ea"){
        UUOM = 'E';
    }
    QString Desision = ui->Paint_Type->currentText();
    if(Desision == "Flat"){
        UFlat_or_Semi = 'F';
    }
    else if (Desision == "Semi"){
        UFlat_or_Semi = 'S';
    }
    else if (Desision == "Both"){
        UFlat_or_Semi = 'B';
    }
    UCoats = ui->Coats->value();

   emit send_to_int_paint(Usubstrate, UQuantity, UUOM, UCoats, UFlat_or_Semi);
}

void clone(QString copy_of){
    if(copy_of == "Unit"){

    }
    else if (copy_of == "Int_Paint"){

    }
}

void interior_paint::insert_to_database(QString Usubstrate, QString UQuantity, char UUOM,int UCoats, char UFlat_or_Semi){
    int i = 0; // When I get the button that creates more working, I need to find a way to pass exactly WHERE the number is.
    // most likely I need a counter for that.
    int_DB[i].substrate = Usubstrate;
    int_DB[i].quantity = UQuantity.toInt();
    int_DB[i].UOM = UUOM;
    int_DB[i].coats = UCoats;
    int_DB[i].sq_per_gal = 300;
    int_DB[i].waste = .1;
    int_DB[i].f_or_s = UFlat_or_Semi;

    calculate();
}

void interior_paint::calculate(){
    for (int i = 0; i < size - 1; i++) {
        if (int_DB[i].UOM == 'L'){
            int_DB[i].lf_conversion = (int_DB[i].quantity * 5) / 12;
        }
        else {
            int_DB[i].lf_conversion = 0;
        }
        if (int_DB[i].f_or_s == 'F'){
            int_DB[i].flat_per_unit = (int_DB[i].quantity / int_DB[i].sq_per_gal) * int_DB[i].coats;
            int_DB[size].subtotal_flat += int_DB[i].flat_per_unit;
        }
        else if (int_DB[i].f_or_s == 'S'){
            int_DB[i].semi_per_unit = (int_DB[i].quantity / int_DB[i].sq_per_gal) * int_DB[i].coats;
            int_DB[size].subtotal_semi += int_DB[i].semi_per_unit;
        }
        else if (int_DB[i].f_or_s == 'B'){
            int temp = (int_DB[i].quantity / int_DB[i].sq_per_gal) * int_DB[i].coats;
            int_DB[i].flat_per_unit = temp / 2;
            int_DB[i].semi_per_unit = temp / 2;
        }

   }

}



interior_paint::interior_paint(const interior_paint& Org)//copy constructor
{
    (*this).size = Org.size;
    this->count = Org.count;

    int_DB = new int_paint[size];

    for (int i = 0; i<count; i++)
    {
        int_DB[i] = Org.int_DB[i];
    }
}

bool interior_paint::is_empty()
{
    return count == 0;
}

bool interior_paint::is_full()
{
    return count == size;
}

int interior_paint::search(const QString key)
{
    for (int i = 0; i < count; i++) {
        if (key == int_DB[i].ID) {
            return i;
        }
    }
    return -1;
}

void interior_paint::increase_size()
{
    size++;
    int_paint *temp = new int_paint[size];

    for (int i = 0; i<count; i++)
    {
        temp[i] = int_DB[i];
    }

    delete[] int_DB;
    int_DB = temp;
}

void MainWindow::on_tabWidget_tabBarDoubleClicked(int index)
{
 MyDialog rename;
 rename.setModal(true);
 rename.exec();
 QString new_name = rename.result();
 ui->Unit_tab->setTabText(index, new_name);
}

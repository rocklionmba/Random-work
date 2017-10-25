#include "mainwindow.h"
#include <QApplication>
#include <QTextStream>
#include <QTextEdit>
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
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow test;

    test.show();
    return a.exec();
}

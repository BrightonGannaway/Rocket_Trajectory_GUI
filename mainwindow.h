#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtCharts>
#include <QLineEdit>
#include <vector>
#include <map>
#include <QString>

#include "SpacePort.h"




QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addPoint(qreal x, qreal y);
    void addPointVectort2dDouble(std::vector<std::vector<double>> &points);
    void updateChart();
    void clearChart();
    void displayNewInputField(QLineEdit* inputField, QString placeHolderText, QString titleText, QVBoxLayout* layout);



public slots:
    void build_v (QString v);
    void build_Mf (QString Mf);
    void build_Mc (QString Mc);
    void build_mdot (QString mdot);
    void build_theta_L (QString theta_L);
    void build_s (QString s);
    void build_Cd (QString);

    void buildRocket();
    void launchRocket(bool refuel);


private:
    Ui::MainWindow *ui;

    //chart objects
    QSplineSeries *series;
    QChart *chart;

    std::map<std::string, QLineEdit*> symbolToInputField;

    std::vector<std::vector<double>> currentMatrixPoints;

    //input fields
    QLineEdit* exitVelocityInputField;
    QLineEdit* fullMassInputField;
    QLineEdit* fuelMassInputField;
    QLineEdit* launchAngleInputField;
    QLineEdit* massFlowRateInputField;
    QLineEdit* crossSectionalArealaunchAngleInputField;
    QLineEdit* DragcoefficientInputField;


    //buttons
    QPushButton* buildRocketBtn;
    QPushButton* launchRocketBtn;
};
#endif // MAINWINDOW_H

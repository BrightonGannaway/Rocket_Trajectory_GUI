#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "ConcreteBuilderRocket.cpp"

//Qtcharts classes

#include <QtCharts/QSplineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

ConcreteBuilderRocket* builder = new ConcreteBuilderRocket();


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //general configuration
    setWindowTitle("Rocket Trajector");


    //main window configuration
    QWidget *centralWidget = new QWidget();
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    //chart settings
    series = new QSplineSeries();
    series->setName("Random Points");

    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, 1000); //TODO: Set dynamic range with minimum
    chart->axes(Qt::Horizontal).first()->setRange(0, 2000); //TODO: Set dynamic range with minimum
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(Constants::Runtime::RUNSECONDS * 1000);
    chart->setVisible(true);
    chart->show();


    QChartView *chartView = new QChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setVisible(true);
    chartView->show();


    //button configuring
    QVBoxLayout *verticlWidgetSidePanelLayout = new QVBoxLayout();
    QScrollArea *scrollArea = new QScrollArea();

    //adding a simple input field for testing
    //QLabel *testTitle = new QLabel("\nTesting Title");

    exitVelocityInputField = new QLineEdit();
    fullMassInputField = new QLineEdit();
    fuelMassInputField = new QLineEdit();
    launchAngleInputField = new QLineEdit();
    massFlowRateInputField = new QLineEdit();
    crossSectionalArealaunchAngleInputField = new QLineEdit();
    DragcoefficientInputField = new QLineEdit();
    displayNewInputField(exitVelocityInputField,"m/s", "\nExit Velocity", verticlWidgetSidePanelLayout);
    displayNewInputField(fullMassInputField, "g", "Full Mass", verticlWidgetSidePanelLayout);
    displayNewInputField(fuelMassInputField, "g", "Fuel Mass", verticlWidgetSidePanelLayout);
    displayNewInputField(massFlowRateInputField, "g/s","Mass Flow Rate", verticlWidgetSidePanelLayout);
    displayNewInputField(launchAngleInputField, "degrees", "Launch Angle", verticlWidgetSidePanelLayout);
    displayNewInputField(crossSectionalArealaunchAngleInputField, "m^2", "Cross Sectional Area", verticlWidgetSidePanelLayout);
    displayNewInputField(DragcoefficientInputField, "Cd", "Drag Coefficient", verticlWidgetSidePanelLayout);
    //input field attachments. mainwindow is connected to a builder adding each input for time effeciency (it saves microseconds).
    //upon 'build' the builder sends a completed rocket to spaceport where mainwindow can use its methods to visualize rocket trajectories
    connect(exitVelocityInputField, &QLineEdit::textEdited, this, &MainWindow::build_v);
    connect(fullMassInputField, &QLineEdit::textEdited, this, &MainWindow::build_Mf);
    connect(fuelMassInputField, &QLineEdit::textEdited, this, &MainWindow::build_Mc);
    connect(launchAngleInputField, &QLineEdit::textEdited, this, &MainWindow::build_theta_L);
    connect(massFlowRateInputField, &QLineEdit::textEdited, this, &MainWindow::build_mdot);
    connect(crossSectionalArealaunchAngleInputField, &QLineEdit::textEdited, this, &MainWindow::build_s);
    connect(DragcoefficientInputField, &QLineEdit::textEdited, this, &MainWindow::build_Cd);

    //combo box for display options
    QComboBox* displayOptions = new QComboBox();

    buildRocketBtn = new QPushButton("Build Rocket");
    connect(buildRocketBtn, &QPushButton::clicked, this, &MainWindow::buildRocket);
    launchRocketBtn = new QPushButton("Launch!");
    launchRocketBtn->setEnabled(false);
    connect(launchRocketBtn, &QPushButton::clicked, this, &MainWindow::launchRocket);

    verticlWidgetSidePanelLayout->addWidget(buildRocketBtn);
    verticlWidgetSidePanelLayout->addWidget(launchRocketBtn);

    verticlWidgetSidePanelLayout->addStretch();
    scrollArea->setLayout(verticlWidgetSidePanelLayout);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(chartView, 3);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(qreal x, qreal y) {
    series->append(x, y);
}

void MainWindow::addPointVectort2dDouble(std::vector<std::vector<double>> &points) {

    QList<QPointF> Qpoints;

    for (std::vector<double> point : points) {
        QPointF dot(point[0], point[1]);
        Qpoints.append(dot);
    }

    series->append(Qpoints);
    Qpoints.clear();

}

void MainWindow::updateChart() {
    chart->update();
}

void MainWindow::clearChart() {
    series->clear();
}



void MainWindow::displayNewInputField(QLineEdit* inputField, QString placeHolderText, QString titleText, QVBoxLayout* layout) {
    inputField->setPlaceholderText(placeHolderText);
    inputField->setValidator(new QDoubleValidator(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), 15, this));
    layout->addWidget(new QLabel(titleText));
    layout->addWidget(inputField);
}

void MainWindow::build_v (QString v) {
    builder->SetV(v.toDouble());
};
void MainWindow::build_Mf (QString Mf) {
    builder->SetMf(Mf.toDouble());
};
void MainWindow::build_Mc (QString Mc){
    builder->SetMc(Mc.toDouble());
};
void MainWindow::build_mdot (QString mdot){
    builder->SetMdot(mdot.toDouble());
};
void MainWindow::build_theta_L (QString theta_L){
    builder->SetThetaL(theta_L.toDouble());
};
void MainWindow::build_s (QString s){
    builder->SetS(s.toDouble());
};
void MainWindow::build_Cd (QString Cd){
    builder->SetCd(Cd.toDouble());
};

void MainWindow::buildRocket() {
    if (!exitVelocityInputField->text().isEmpty() &&
        !fullMassInputField->text().isEmpty() &&
        !fuelMassInputField->text().isEmpty() &&
        !launchAngleInputField->text().isEmpty() &&
        !massFlowRateInputField->text().isEmpty() &&
        !crossSectionalArealaunchAngleInputField->text().isEmpty() &&
        !DragcoefficientInputField->text().isEmpty())
    {
        //refreshing rocket as stuff changes during launch
        builder->SetV(exitVelocityInputField->text().toDouble());
        builder->SetMf(fullMassInputField->text().toDouble());
        builder->SetMc(fuelMassInputField->text().toDouble());
        builder->SetMdot(massFlowRateInputField->text().toDouble());
        builder->SetThetaL(launchAngleInputField->text().toDouble());
        builder->SetS(crossSectionalArealaunchAngleInputField->text().toDouble());
        builder->SetCd(DragcoefficientInputField->text().toDouble());

        //resets position
        builder->SetX(0);
        builder->SetY(0);

        builder->sendToSpacePort();
        launchRocketBtn->setEnabled(true);

    } else {
        launchRocketBtn->setEnabled(false);
    }
}

void MainWindow::launchRocket(bool refeul = true) { //refuel bool needed as rocket fuel does get depleted

    clearChart();
    std::vector<std::vector<double>> points = SpacePort::launchRocketandPlotTrajectory();
    currentMatrixPoints = points;
    addPointVectort2dDouble(currentMatrixPoints);
    updateChart();
}


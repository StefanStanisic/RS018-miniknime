#include "mainwindow.h"
#include "secondwindow.h"
#include "mknormalization.h"
#include "mknode.h"
#include "mkmlpregression.h"
#include "mkcsvreader.h"
#include "mkpartition.h"
#include "mknodespec.h"
#include "mktestnode2_2.h"
#include "uicontroler.h"
#include "dlib-19.16/dlib-19.16/dlib/any.h"
#include "QFrame"
#include "QLabel"
#include "QPushButton"
#include "QLayout"
#include <QHBoxLayout>
#include <QtWidgets>
#include <QApplication>
#include <vector>
#include <iostream>



int main(int argc, char *argv[])
{
    UIControler();
    QApplication app(argc, argv);

    std::cout<<"hi"<<std::endl;

    QWidget mainWidget;
    QHBoxLayout *horizontalLayout = new QHBoxLayout(&mainWidget);
    horizontalLayout->addWidget(new MainWindow);
    auto sw=new secondwindow;
    UIControler::setSecondWindow(sw);
    horizontalLayout->addWidget(sw);
    QPlainTextEdit *textArea = new QPlainTextEdit;
    textArea->setPlaceholderText("Here will be description of the algorithm you choose.");
    textArea->setMinimumSize(400, 400);
    horizontalLayout->addWidget(textArea);

    mainWidget.setWindowTitle(QObject::tr("MiniKnime Proba"));
    mainWidget.show();

// example workflow
// --------------------------------------------------
    MKCSVReader reader {};
    reader.readFromCSV("./datasets/auto-mpg.csv");

    MKNormalization norm {};
    reader.m_outputs[0].establishConnection(norm.m_inputs[0]);

    norm.process_data();

    MKPartition part {};
    norm.m_outputs[0].establishConnection((part.m_inputs[0]));
    part.process_data();

    MKMLPRegression net {};
    part.m_outputs[0].establishConnection(net.m_inputs[0]);
    part.m_outputs[1].establishConnection(net.m_inputs[1]);

    net.trainNet(6, 3, 3);

// --------------------------------------------------

    return app.exec();
}

void localTest001(){
    //    ->s1->
    // d1        d2
    //    ->s2->


    MKTestNode2_2 double1 {};
    MKTestNode1_1 single1 {};
    MKTestNode1_1 single2 {};
    MKTestNode2_2 double2 {};
    double1.m_outputs[0].establishConnection(single1.m_inputs[0]);
    double1.m_outputs[1].establishConnection(single2.m_inputs[0]);
    single1.m_outputs[0].establishConnection(double2.m_inputs[0]);
    single2.m_outputs[0].establishConnection(double2.m_inputs[1]);
    //s1.m_outputs[1].establishConnection(s2.m_inputs[1]);
    double1.sendInvalidationPulse();
    double1.process_data();
}

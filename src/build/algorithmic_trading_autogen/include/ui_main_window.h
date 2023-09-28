/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "graph_widget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tab;
    QWidget *interpolation;
    QHBoxLayout *horizontalLayout;
    s21::GraphWidget *i_graph_widget;
    QFrame *i_set_frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *i_hide_button;
    QPushButton *i_clear_button;
    QPushButton *i_file_button;
    QFrame *i_add_graph_frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_8;
    QLabel *label;
    QSpinBox *i_points_spin_box;
    QPushButton *CS_button;
    QPushButton *N_button;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpinBox *N_degree_spin_ag;
    QFrame *i_time_frame;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_7;
    QDateTimeEdit *i_date_time_edit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QSpinBox *N_degree_spin_val;
    QPushButton *calc_button;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLabel *CS_value_label;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *N_value_label;
    QSpacerItem *verticalSpacer;
    QLabel *i_file_info_lable;
    QWidget *approximation;
    QHBoxLayout *horizontalLayout_10;
    s21::GraphWidget *a_graph_widget;
    QFrame *a_set_frame;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *a_hide_button;
    QPushButton *a_clear_button;
    QPushButton *a_file_button;
    QFrame *approximate_frame;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    QSpinBox *a_days_spin;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_5;
    QSpinBox *a_degree_spin;
    QPushButton *approximate_button;
    QSpacerItem *verticalSpacer_2;
    QLabel *a_file_info_lable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(94, 92, 100);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(3, 3, 3, 3);
        tab = new QTabWidget(centralwidget);
        tab->setObjectName(QString::fromUtf8("tab"));
        interpolation = new QWidget();
        interpolation->setObjectName(QString::fromUtf8("interpolation"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(interpolation->sizePolicy().hasHeightForWidth());
        interpolation->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(interpolation);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        i_graph_widget = new s21::GraphWidget(interpolation);
        i_graph_widget->setObjectName(QString::fromUtf8("i_graph_widget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(i_graph_widget->sizePolicy().hasHeightForWidth());
        i_graph_widget->setSizePolicy(sizePolicy1);
        i_graph_widget->setMinimumSize(QSize(50, 50));
        i_graph_widget->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(i_graph_widget);

        i_set_frame = new QFrame(interpolation);
        i_set_frame->setObjectName(QString::fromUtf8("i_set_frame"));
        i_set_frame->setFrameShape(QFrame::StyledPanel);
        i_set_frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(i_set_frame);
        verticalLayout->setSpacing(9);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        i_hide_button = new QPushButton(i_set_frame);
        i_hide_button->setObjectName(QString::fromUtf8("i_hide_button"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(i_hide_button->sizePolicy().hasHeightForWidth());
        i_hide_button->setSizePolicy(sizePolicy2);
        i_hide_button->setMaximumSize(QSize(30, 16777215));
        i_hide_button->setStyleSheet(QString::fromUtf8("background-color: rgb(229, 165, 10);"));

        horizontalLayout_7->addWidget(i_hide_button);

        i_clear_button = new QPushButton(i_set_frame);
        i_clear_button->setObjectName(QString::fromUtf8("i_clear_button"));
        i_clear_button->setStyleSheet(QString::fromUtf8("background-color: rgb(57, 61, 117);"));

        horizontalLayout_7->addWidget(i_clear_button);

        i_file_button = new QPushButton(i_set_frame);
        i_file_button->setObjectName(QString::fromUtf8("i_file_button"));
        i_file_button->setStyleSheet(QString::fromUtf8("background-color: rgb(57, 61, 117);"));

        horizontalLayout_7->addWidget(i_file_button);


        verticalLayout->addLayout(horizontalLayout_7);

        i_add_graph_frame = new QFrame(i_set_frame);
        i_add_graph_frame->setObjectName(QString::fromUtf8("i_add_graph_frame"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(i_add_graph_frame->sizePolicy().hasHeightForWidth());
        i_add_graph_frame->setSizePolicy(sizePolicy3);
        i_add_graph_frame->setFrameShape(QFrame::StyledPanel);
        i_add_graph_frame->setFrameShadow(QFrame::Raised);
        i_add_graph_frame->setLineWidth(10);
        verticalLayout_2 = new QVBoxLayout(i_add_graph_frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_8 = new QLabel(i_add_graph_frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_2->addWidget(label_8);

        label = new QLabel(i_add_graph_frame);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        i_points_spin_box = new QSpinBox(i_add_graph_frame);
        i_points_spin_box->setObjectName(QString::fromUtf8("i_points_spin_box"));

        verticalLayout_2->addWidget(i_points_spin_box);

        CS_button = new QPushButton(i_add_graph_frame);
        CS_button->setObjectName(QString::fromUtf8("CS_button"));
        CS_button->setStyleSheet(QString::fromUtf8("background-color: rgb(57, 61, 117);"));

        verticalLayout_2->addWidget(CS_button);

        N_button = new QPushButton(i_add_graph_frame);
        N_button->setObjectName(QString::fromUtf8("N_button"));
        N_button->setStyleSheet(QString::fromUtf8("background-color: rgb(57, 61, 117);"));

        verticalLayout_2->addWidget(N_button);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(i_add_graph_frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        N_degree_spin_ag = new QSpinBox(i_add_graph_frame);
        N_degree_spin_ag->setObjectName(QString::fromUtf8("N_degree_spin_ag"));

        horizontalLayout_6->addWidget(N_degree_spin_ag);


        verticalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout->addWidget(i_add_graph_frame);

        i_time_frame = new QFrame(i_set_frame);
        i_time_frame->setObjectName(QString::fromUtf8("i_time_frame"));
        sizePolicy3.setHeightForWidth(i_time_frame->sizePolicy().hasHeightForWidth());
        i_time_frame->setSizePolicy(sizePolicy3);
        i_time_frame->setFrameShape(QFrame::StyledPanel);
        i_time_frame->setFrameShadow(QFrame::Raised);
        i_time_frame->setLineWidth(10);
        verticalLayout_3 = new QVBoxLayout(i_time_frame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_7 = new QLabel(i_time_frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_3->addWidget(label_7);

        i_date_time_edit = new QDateTimeEdit(i_time_frame);
        i_date_time_edit->setObjectName(QString::fromUtf8("i_date_time_edit"));

        verticalLayout_3->addWidget(i_date_time_edit);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(i_time_frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        N_degree_spin_val = new QSpinBox(i_time_frame);
        N_degree_spin_val->setObjectName(QString::fromUtf8("N_degree_spin_val"));

        horizontalLayout_5->addWidget(N_degree_spin_val);


        verticalLayout_3->addLayout(horizontalLayout_5);

        calc_button = new QPushButton(i_time_frame);
        calc_button->setObjectName(QString::fromUtf8("calc_button"));
        calc_button->setStyleSheet(QString::fromUtf8("background-color: rgb(57, 61, 117);"));

        verticalLayout_3->addWidget(calc_button);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(i_time_frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        CS_value_label = new QLabel(i_time_frame);
        CS_value_label->setObjectName(QString::fromUtf8("CS_value_label"));

        horizontalLayout_4->addWidget(CS_value_label);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(i_time_frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        N_value_label = new QLabel(i_time_frame);
        N_value_label->setObjectName(QString::fromUtf8("N_value_label"));

        horizontalLayout_3->addWidget(N_value_label);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(i_time_frame);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        i_file_info_lable = new QLabel(i_set_frame);
        i_file_info_lable->setObjectName(QString::fromUtf8("i_file_info_lable"));

        verticalLayout->addWidget(i_file_info_lable);


        horizontalLayout->addWidget(i_set_frame);

        tab->addTab(interpolation, QString());
        approximation = new QWidget();
        approximation->setObjectName(QString::fromUtf8("approximation"));
        horizontalLayout_10 = new QHBoxLayout(approximation);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        a_graph_widget = new s21::GraphWidget(approximation);
        a_graph_widget->setObjectName(QString::fromUtf8("a_graph_widget"));
        sizePolicy1.setHeightForWidth(a_graph_widget->sizePolicy().hasHeightForWidth());
        a_graph_widget->setSizePolicy(sizePolicy1);

        horizontalLayout_10->addWidget(a_graph_widget);

        a_set_frame = new QFrame(approximation);
        a_set_frame->setObjectName(QString::fromUtf8("a_set_frame"));
        a_set_frame->setFrameShape(QFrame::StyledPanel);
        a_set_frame->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(a_set_frame);
        verticalLayout_6->setSpacing(9);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        a_hide_button = new QPushButton(a_set_frame);
        a_hide_button->setObjectName(QString::fromUtf8("a_hide_button"));
        sizePolicy2.setHeightForWidth(a_hide_button->sizePolicy().hasHeightForWidth());
        a_hide_button->setSizePolicy(sizePolicy2);
        a_hide_button->setMaximumSize(QSize(30, 16777215));
        a_hide_button->setStyleSheet(QString::fromUtf8("background-color: rgb(229, 165, 10);"));

        horizontalLayout_8->addWidget(a_hide_button);

        a_clear_button = new QPushButton(a_set_frame);
        a_clear_button->setObjectName(QString::fromUtf8("a_clear_button"));
        a_clear_button->setStyleSheet(QString::fromUtf8("background-color: rgb(57, 61, 117);"));

        horizontalLayout_8->addWidget(a_clear_button);

        a_file_button = new QPushButton(a_set_frame);
        a_file_button->setObjectName(QString::fromUtf8("a_file_button"));
        a_file_button->setStyleSheet(QString::fromUtf8("background-color: rgb(57, 61, 117);"));

        horizontalLayout_8->addWidget(a_file_button);


        verticalLayout_6->addLayout(horizontalLayout_8);

        approximate_frame = new QFrame(a_set_frame);
        approximate_frame->setObjectName(QString::fromUtf8("approximate_frame"));
        approximate_frame->setFrameShape(QFrame::StyledPanel);
        approximate_frame->setFrameShadow(QFrame::Raised);
        approximate_frame->setLineWidth(10);
        verticalLayout_5 = new QVBoxLayout(approximate_frame);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_9 = new QLabel(approximate_frame);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_2->addWidget(label_9);

        a_days_spin = new QSpinBox(approximate_frame);
        a_days_spin->setObjectName(QString::fromUtf8("a_days_spin"));

        horizontalLayout_2->addWidget(a_days_spin);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_5 = new QLabel(approximate_frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_9->addWidget(label_5);

        a_degree_spin = new QSpinBox(approximate_frame);
        a_degree_spin->setObjectName(QString::fromUtf8("a_degree_spin"));

        horizontalLayout_9->addWidget(a_degree_spin);


        verticalLayout_5->addLayout(horizontalLayout_9);

        approximate_button = new QPushButton(approximate_frame);
        approximate_button->setObjectName(QString::fromUtf8("approximate_button"));
        approximate_button->setStyleSheet(QString::fromUtf8("background-color: rgb(57, 61, 117);"));

        verticalLayout_5->addWidget(approximate_button);


        verticalLayout_6->addWidget(approximate_frame);

        verticalSpacer_2 = new QSpacerItem(20, 310, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_2);

        a_file_info_lable = new QLabel(a_set_frame);
        a_file_info_lable->setObjectName(QString::fromUtf8("a_file_info_lable"));

        verticalLayout_6->addWidget(a_file_info_lable);


        horizontalLayout_10->addWidget(a_set_frame);

        tab->addTab(approximation, QString());

        verticalLayout_4->addWidget(tab);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(whatsthis)
        centralwidget->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        i_hide_button->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        i_clear_button->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        i_file_button->setText(QCoreApplication::translate("MainWindow", "File", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Add Graph", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Number of points", nullptr));
        CS_button->setText(QCoreApplication::translate("MainWindow", "Cubic Spline", nullptr));
        N_button->setText(QCoreApplication::translate("MainWindow", "Newton polynomial", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Newton's degree", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Value at a specific time", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Newton's degree", nullptr));
        calc_button->setText(QCoreApplication::translate("MainWindow", "Calculate", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Cubic Spline:", nullptr));
        CS_value_label->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Newton:", nullptr));
        N_value_label->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        i_file_info_lable->setText(QCoreApplication::translate("MainWindow", "No file [0]", nullptr));
        tab->setTabText(tab->indexOf(interpolation), QCoreApplication::translate("MainWindow", "Interpolation", nullptr));
        a_hide_button->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        a_clear_button->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        a_file_button->setText(QCoreApplication::translate("MainWindow", "File", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "number of days", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "polynomial degree", nullptr));
        approximate_button->setText(QCoreApplication::translate("MainWindow", "Approximate", nullptr));
        a_file_info_lable->setText(QCoreApplication::translate("MainWindow", "No file [0]", nullptr));
        tab->setTabText(tab->indexOf(approximation), QCoreApplication::translate("MainWindow", "Approximation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H

/********************************************************************************
** Form generated from reading UI file 'frontend_class.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRONTEND_CLASS_H
#define UI_FRONTEND_CLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Frontend_class
{
public:
    QAction *actionLoad_Listt;
    QAction *actiontest;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QProgressBar *progressBar;
    QPushButton *pushButton_3;
    QTableWidget *tableWidget;
    QTabWidget *tabWidget;
    QWidget *tab_4;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_min;
    QGridLayout *gridLayout_8;
    QDoubleSpinBox *spinBoxdouble_min;
    QGroupBox *groupBox_max;
    QGridLayout *gridLayout_5;
    QDoubleSpinBox *spinBoxdouble_max;
    QLabel *label_7;
    QFrame *frame;
    QGridLayout *gridLayout_6;
    QPushButton *Autofill;
    QPushButton *deleteparameter;
    QPushButton *addParameter;
    QPushButton *override;
    QTableWidget *System_param_table;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QPushButton *reload_db;
    QPushButton *Taxonomie_load;
    QTableWidget *tableWidget_2;
    QSpacerItem *verticalSpacer;
    QFrame *frame_2;
    QGridLayout *gridLayout_4;
    QRadioButton *Opt_Network;
    QRadioButton *Opt_wighted_combination;
    QRadioButton *Opt_Precision;
    QLineEdit *Opt_wight_funktion;
    QLabel *label_8;
    QRadioButton *Opt_Error;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Frontend_class)
    {
        if (Frontend_class->objectName().isEmpty())
            Frontend_class->setObjectName(QStringLiteral("Frontend_class"));
        Frontend_class->resize(881, 711);
        actionLoad_Listt = new QAction(Frontend_class);
        actionLoad_Listt->setObjectName(QStringLiteral("actionLoad_Listt"));
        actionLoad_Listt->setCheckable(true);
        actiontest = new QAction(Frontend_class);
        actiontest->setObjectName(QStringLiteral("actiontest"));
        centralWidget = new QWidget(Frontend_class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 0, 0, 1, 1);

        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setSortingEnabled(true);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));

        gridLayout->addWidget(tableWidget, 2, 0, 1, 3);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_3 = new QGridLayout(tab_4);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox_min = new QGroupBox(tab_4);
        groupBox_min->setObjectName(QStringLiteral("groupBox_min"));
        gridLayout_8 = new QGridLayout(groupBox_min);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        spinBoxdouble_min = new QDoubleSpinBox(groupBox_min);
        spinBoxdouble_min->setObjectName(QStringLiteral("spinBoxdouble_min"));
        spinBoxdouble_min->setDecimals(10);
        spinBoxdouble_min->setMaximum(10000);
        spinBoxdouble_min->setSingleStep(0.01);

        gridLayout_8->addWidget(spinBoxdouble_min, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_min, 0, 0, 1, 1);

        groupBox_max = new QGroupBox(tab_4);
        groupBox_max->setObjectName(QStringLiteral("groupBox_max"));
        gridLayout_5 = new QGridLayout(groupBox_max);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        spinBoxdouble_max = new QDoubleSpinBox(groupBox_max);
        spinBoxdouble_max->setObjectName(QStringLiteral("spinBoxdouble_max"));
        spinBoxdouble_max->setDecimals(10);
        spinBoxdouble_max->setMaximum(10000);

        gridLayout_5->addWidget(spinBoxdouble_max, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_max, 0, 1, 1, 1);

        label_7 = new QLabel(tab_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAcceptDrops(false);
        label_7->setWordWrap(true);

        gridLayout_3->addWidget(label_7, 1, 0, 1, 2);

        frame = new QFrame(tab_4);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        Autofill = new QPushButton(frame);
        Autofill->setObjectName(QStringLiteral("Autofill"));

        gridLayout_6->addWidget(Autofill, 2, 2, 1, 1);

        deleteparameter = new QPushButton(frame);
        deleteparameter->setObjectName(QStringLiteral("deleteparameter"));

        gridLayout_6->addWidget(deleteparameter, 2, 1, 1, 1);

        addParameter = new QPushButton(frame);
        addParameter->setObjectName(QStringLiteral("addParameter"));

        gridLayout_6->addWidget(addParameter, 2, 0, 1, 1);

        override = new QPushButton(frame);
        override->setObjectName(QStringLiteral("override"));

        gridLayout_6->addWidget(override, 2, 3, 1, 1);


        gridLayout_3->addWidget(frame, 2, 0, 1, 2);

        System_param_table = new QTableWidget(tab_4);
        if (System_param_table->columnCount() < 5)
            System_param_table->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        System_param_table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        System_param_table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        System_param_table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        System_param_table->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        System_param_table->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        System_param_table->setObjectName(QStringLiteral("System_param_table"));
        System_param_table->setMaximumSize(QSize(16777215, 16777215));
        System_param_table->verticalHeader()->setVisible(false);

        gridLayout_3->addWidget(System_param_table, 3, 0, 1, 2);

        tabWidget->addTab(tab_4, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tab_2->setStyleSheet(QStringLiteral(""));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 5, 0, 1, 2, Qt::AlignTop);

        reload_db = new QPushButton(tab_2);
        reload_db->setObjectName(QStringLiteral("reload_db"));

        gridLayout_2->addWidget(reload_db, 1, 0, 1, 1, Qt::AlignLeft);

        Taxonomie_load = new QPushButton(tab_2);
        Taxonomie_load->setObjectName(QStringLiteral("Taxonomie_load"));

        gridLayout_2->addWidget(Taxonomie_load, 1, 1, 1, 1, Qt::AlignRight);

        tableWidget_2 = new QTableWidget(tab_2);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setMinimumSize(QSize(0, 130));
        tableWidget_2->setMaximumSize(QSize(16777215, 130));

        gridLayout_2->addWidget(tableWidget_2, 6, 0, 1, 2, Qt::AlignTop);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 7, 0, 1, 2);

        frame_2 = new QFrame(tab_2);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        Opt_Network = new QRadioButton(frame_2);
        Opt_Network->setObjectName(QStringLiteral("Opt_Network"));

        gridLayout_4->addWidget(Opt_Network, 4, 0, 1, 1);

        Opt_wighted_combination = new QRadioButton(frame_2);
        Opt_wighted_combination->setObjectName(QStringLiteral("Opt_wighted_combination"));

        gridLayout_4->addWidget(Opt_wighted_combination, 5, 0, 1, 1);

        Opt_Precision = new QRadioButton(frame_2);
        Opt_Precision->setObjectName(QStringLiteral("Opt_Precision"));

        gridLayout_4->addWidget(Opt_Precision, 2, 0, 1, 1);

        Opt_wight_funktion = new QLineEdit(frame_2);
        Opt_wight_funktion->setObjectName(QStringLiteral("Opt_wight_funktion"));

        gridLayout_4->addWidget(Opt_wight_funktion, 5, 1, 1, 1);

        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_4->addWidget(label_8, 0, 0, 1, 1);

        Opt_Error = new QRadioButton(frame_2);
        Opt_Error->setObjectName(QStringLiteral("Opt_Error"));

        gridLayout_4->addWidget(Opt_Error, 1, 0, 1, 1);


        gridLayout_2->addWidget(frame_2, 10, 0, 1, 2);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 3);

        Frontend_class->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(Frontend_class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Frontend_class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Frontend_class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Frontend_class->setStatusBar(statusBar);

        retranslateUi(Frontend_class);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Frontend_class);
    } // setupUi

    void retranslateUi(QMainWindow *Frontend_class)
    {
        Frontend_class->setWindowTitle(QApplication::translate("Frontend_class", "Frontend_class", nullptr));
        actionLoad_Listt->setText(QApplication::translate("Frontend_class", "Import list", nullptr));
        actiontest->setText(QApplication::translate("Frontend_class", "test", nullptr));
        pushButton->setText(QApplication::translate("Frontend_class", "Search Algorithmus", nullptr));
        pushButton_3->setText(QApplication::translate("Frontend_class", "databaseeditor", nullptr));
        groupBox_min->setTitle(QApplication::translate("Frontend_class", "MIN", nullptr));
        groupBox_max->setTitle(QApplication::translate("Frontend_class", "MAX", nullptr));
        label_7->setText(QApplication::translate("Frontend_class", "Variables support: min/max OR 1 infix string with other variables at Min\n"
"!use with caution!dont build endless loops!", nullptr));
        Autofill->setText(QApplication::translate("Frontend_class", "Autofill", nullptr));
        deleteparameter->setText(QApplication::translate("Frontend_class", "Remove Parameter", nullptr));
        addParameter->setText(QApplication::translate("Frontend_class", "Add Parameter", nullptr));
        override->setText(QApplication::translate("Frontend_class", "Override all", nullptr));
        QTableWidgetItem *___qtablewidgetitem = System_param_table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Frontend_class", "Other Variables", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = System_param_table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Frontend_class", "Min", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = System_param_table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Frontend_class", "Max", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = System_param_table->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Frontend_class", "Equation", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = System_param_table->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("Frontend_class", "Description", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("Frontend_class", "Systemparameter", nullptr));
        label_6->setText(QApplication::translate("Frontend_class", "Chose Values (x,y,...) EMPTY for everything", nullptr));
        reload_db->setText(QApplication::translate("Frontend_class", "reload Database", nullptr));
        Taxonomie_load->setText(QApplication::translate("Frontend_class", "load other Taxonomie", nullptr));
        Opt_Network->setText(QApplication::translate("Frontend_class", "Network utilization", nullptr));
        Opt_wighted_combination->setText(QApplication::translate("Frontend_class", "Find optima of f()=", nullptr));
        Opt_Precision->setText(QApplication::translate("Frontend_class", "Precision", nullptr));
#ifndef QT_NO_TOOLTIP
        Opt_wight_funktion->setToolTip(QApplication::translate("Frontend_class", "<html><head/><body><p>Example:</p><p>Pre*2+U<br/>=&gt;minimize (Precision in ms)*2+(Network utilisation)</p><p>=&gt;possible Parameter are in Systemparameter tab</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("Frontend_class", "Optimalize", nullptr));
        Opt_Error->setText(QApplication::translate("Frontend_class", "no optimization", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Frontend_class", "Taxonomie", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Frontend_class: public Ui_Frontend_class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRONTEND_CLASS_H

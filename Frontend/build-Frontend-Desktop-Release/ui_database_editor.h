/********************************************************************************
** Form generated from reading UI file 'database_editor.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASE_EDITOR_H
#define UI_DATABASE_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Database_Editor_Class
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget_2;
    QTableWidget *tableWidget;
    QPushButton *add_db_element;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *load;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *update_db_element;
    QPushButton *init_database;
    QPushButton *delete_db_element;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *copy;

    void setupUi(QWidget *Database_Editor_Class)
    {
        if (Database_Editor_Class->objectName().isEmpty())
            Database_Editor_Class->setObjectName(QStringLiteral("Database_Editor_Class"));
        Database_Editor_Class->resize(935, 492);
        gridLayout = new QGridLayout(Database_Editor_Class);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget_2 = new QTableWidget(Database_Editor_Class);
        if (tableWidget_2->columnCount() < 4)
            tableWidget_2->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (tableWidget_2->rowCount() < 1)
            tableWidget_2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 3, __qtablewidgetitem7);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setMinimumSize(QSize(0, 60));
        tableWidget_2->setMaximumSize(QSize(16777215, 70));
        tableWidget_2->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableWidget_2, 2, 0, 1, 10, Qt::AlignTop);

        tableWidget = new QTableWidget(Database_Editor_Class);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableWidget, 3, 0, 1, 10);

        add_db_element = new QPushButton(Database_Editor_Class);
        add_db_element->setObjectName(QStringLiteral("add_db_element"));

        gridLayout->addWidget(add_db_element, 1, 7, 1, 1);

        comboBox = new QComboBox(Database_Editor_Class);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 4, 1, 1);

        load = new QPushButton(Database_Editor_Class);
        load->setObjectName(QStringLiteral("load"));

        gridLayout->addWidget(load, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 6, 1, 1);

        update_db_element = new QPushButton(Database_Editor_Class);
        update_db_element->setObjectName(QStringLiteral("update_db_element"));

        gridLayout->addWidget(update_db_element, 1, 8, 1, 1);

        init_database = new QPushButton(Database_Editor_Class);
        init_database->setObjectName(QStringLiteral("init_database"));

        gridLayout->addWidget(init_database, 1, 5, 1, 1);

        delete_db_element = new QPushButton(Database_Editor_Class);
        delete_db_element->setObjectName(QStringLiteral("delete_db_element"));

        gridLayout->addWidget(delete_db_element, 1, 9, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        copy = new QPushButton(Database_Editor_Class);
        copy->setObjectName(QStringLiteral("copy"));

        gridLayout->addWidget(copy, 0, 7, 1, 1);


        retranslateUi(Database_Editor_Class);

        QMetaObject::connectSlotsByName(Database_Editor_Class);
    } // setupUi

    void retranslateUi(QWidget *Database_Editor_Class)
    {
        Database_Editor_Class->setWindowTitle(QApplication::translate("Database_Editor_Class", "Database Editor", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Database_Editor_Class", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Database_Editor_Class", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Database_Editor_Class", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Database_Editor_Class", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("Database_Editor_Class", "New Row", nullptr));

        const bool __sortingEnabled = tableWidget_2->isSortingEnabled();
        tableWidget_2->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->item(0, 0);
        ___qtablewidgetitem5->setText(QApplication::translate("Database_Editor_Class", "asldkhh", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->item(0, 1);
        ___qtablewidgetitem6->setText(QApplication::translate("Database_Editor_Class", "asldkh", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_2->item(0, 3);
        ___qtablewidgetitem7->setText(QApplication::translate("Database_Editor_Class", "sdw", nullptr));
        tableWidget_2->setSortingEnabled(__sortingEnabled);

        add_db_element->setText(QApplication::translate("Database_Editor_Class", "add element", nullptr));
        comboBox->setItemText(0, QApplication::translate("Database_Editor_Class", "Networks", nullptr));
        comboBox->setItemText(1, QApplication::translate("Database_Editor_Class", "Quarz", nullptr));
        comboBox->setItemText(2, QApplication::translate("Database_Editor_Class", "Algorithms", nullptr));
        comboBox->setItemText(3, QApplication::translate("Database_Editor_Class", "Taxonomie", nullptr));
        comboBox->setItemText(4, QApplication::translate("Database_Editor_Class", "Parameter", nullptr));

        load->setText(QApplication::translate("Database_Editor_Class", "load", nullptr));
        update_db_element->setText(QApplication::translate("Database_Editor_Class", "update element", nullptr));
        init_database->setText(QApplication::translate("Database_Editor_Class", "recreate Database Tabel", nullptr));
        delete_db_element->setText(QApplication::translate("Database_Editor_Class", "delete element", nullptr));
        copy->setText(QApplication::translate("Database_Editor_Class", "copy all", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Database_Editor_Class: public Ui_Database_Editor_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASE_EDITOR_H

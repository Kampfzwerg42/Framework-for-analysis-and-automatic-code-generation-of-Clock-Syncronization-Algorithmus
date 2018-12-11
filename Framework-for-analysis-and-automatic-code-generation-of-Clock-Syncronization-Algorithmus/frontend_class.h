#ifndef FRONTEND_CLASS_H
#define FRONTEND_CLASS_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCheckBox>
#include "database_editor_class.h"
#include "backend/backend.h"
#include "backend/database.h"
#include "sortabletablewidgetitem.h"

namespace Ui {
class Frontend_class;
}

class Frontend_class : public QMainWindow
{
    Q_OBJECT

public:
    explicit Frontend_class(QWidget *parent = 0);
    ~Frontend_class();

private slots:
    void on_pushButton_2_clicked();

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void opendatabase_editor();

    void on_Taxonomie_load_clicked();

    void load_database();

    void on_reload_db_clicked();

    void on_deleteparameter_clicked();

    void on_addParameter_clicked();

    void on_Autofill_clicked();

    void on_System_param_table_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_spinBoxdouble_min_valueChanged(const QString &arg1);

    void on_spinBoxdouble_max_valueChanged(const QString &arg1);

    void on_override_clicked();

private:
    Ui::Frontend_class *ui;
    Database_Editor_Class *db_editor;
    database *algos_db;
    backend *calculater;
    bool loaded_database;
    QStringList Systemparameter   =Systemparameter_default;
    QStringList Algorithms_colum_lables_db_calculation_needed=Algorithms_colum_lables_db_calculation_needed_default;
};
#endif // FRONTEND_CLASS_H

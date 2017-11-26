#ifndef DATABASE_EDITOR_CLASS_H
#define DATABASE_EDITOR_CLASS_H

#include "variables_for_frontend.h"
#include "backend/database.h"
//#include "frontend_definitions.h"

#include <QWidget>
#include <QFileDialog>
#include <QInputDialog>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class Database_Editor_Class;
}

class Database_Editor_Class : public QWidget
{
    Q_OBJECT

public:
    explicit Database_Editor_Class(QWidget *parent = 0);
    explicit Database_Editor_Class(database *db, QWidget *parent = 0);
    ~Database_Editor_Class();

private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_init_database_clicked();

    void on_add_db_element_clicked();

    void on_delete_db_element_clicked();

    void on_update_db_element_clicked();

    void on_load_clicked();

    void reload_database();

    void on_copy_clicked();

private:
    Ui::Database_Editor_Class *ui;
    database *algos_db;
    database *load_db;
    bool protect_algos_db=0;
    bool load_form_file=0;
    QString file_tabel_name;
};

#endif // DATABASE_EDITOR_CLASS_H

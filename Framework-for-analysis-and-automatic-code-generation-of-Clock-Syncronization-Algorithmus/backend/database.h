#ifndef DATABASE_H
#define DATABASE_H

#include <QMessageBox>
#include <qstringlist.h>
#include <qstring.h>
#include <sqlite3.h>
#include "variables_for_backend.h"

using namespace std;

class database
{
public:
    database(QString Path);
    ~database();
    int table_create(QString name, QStringList ValueNames, QStringList ValueTypes);
    int table_load(QString name, QList<QStringList> *Values);
    int table_add(QString name, QStringList ValueNames, QStringList Values);
    int table_delete(QString name,QString IDValueName, QString IDValue);
    int table_update(QString name,QString IDValueName, QString IDValue, QStringList ValueNames, QStringList Values);
private:
    sqlite3 *db;
    int rc;

    static int callback_db(void *data, int argc, char **argv, char **azColName){
           int i;
           QStringList temp=*(new QStringList);
           for(i = 0; i<argc; i++){
               temp += argv[i] ? argv[i] : "NULL";
           }
           ((QList<QStringList>*)(data))->append(temp);
           return 0;
    }
    static int get_column_callback(void *data_col, int argc, char **argv, char **azColName){
           QString temp;
           temp = argv[1] ? argv[1] : "NULL";
           ((QStringList*)(data_col))->append(temp);
           return 0;
    }
};

#endif // DATABASE_H

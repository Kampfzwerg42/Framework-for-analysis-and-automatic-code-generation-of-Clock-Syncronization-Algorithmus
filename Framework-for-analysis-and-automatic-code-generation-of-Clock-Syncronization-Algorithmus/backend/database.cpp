#include "database.h"

database::database(QString path)
{
    /* Open database */
    rc = sqlite3_open(path.toLatin1().data(), &db);

    if( rc ) {
        QMessageBox messageBox;
        messageBox.critical(0,"SQL error",sqlite3_errmsg(db));
        messageBox.setFixedSize(500,200);
        //ERROR
    }
}
database::~database()
{
   sqlite3_close(db);
}

int database::table_create(QString name, QStringList ValueNames, QStringList ValueTypes)
{
       char *zErrMsg = 0;

       QString sql = "DROP TABLE "+name+" ;";
       rc = sqlite3_exec(db, sql.toLatin1().data(), callback_db, 0, &zErrMsg);

       /* Create SQL statement */
       sql = "CREATE TABLE "+name+" (";
       QStringList::iterator it = ValueNames.begin();
       QStringList::iterator it2 = ValueTypes.begin();
       sql += *it+" "+ *it2;
       ++it;
       ++it2;
       for (;it != ValueNames.end(),it2 != ValueTypes.end(); ++it,++it2)
       {
           sql += ","+ *it+" "+ *it2;
       }
       sql+=" );";

       /* Execute SQL statement */
       rc = sqlite3_exec(db, sql.toLatin1().data(), callback_db, 0, &zErrMsg);

       if( rc != SQLITE_OK ){
          QMessageBox messageBox;
          messageBox.critical(0,"SQL error",zErrMsg);
          messageBox.setFixedSize(500,200);
          sqlite3_free(zErrMsg);
          return -1;
       } else {
          fprintf(stdout, "Table created successfully\n");
       }
       return 0;
}

int database::table_load(QString name, QList<QStringList> *Values)
{

    char *zErrMsg = 0;

    /* Create SQL statement */

    QStringList *temp=new QStringList;

    QString sql = "PRAGMA table_info("+name+");";
    rc = sqlite3_exec(db, sql.toLatin1().data(), get_column_callback, temp, &zErrMsg);

    if( rc != SQLITE_OK ) {
      QMessageBox messageBox;
      messageBox.critical(0,"SQL error",zErrMsg);
      messageBox.setFixedSize(500,200);
      sqlite3_free(zErrMsg);
      return -1;
    } else {
      fprintf(stdout, "Operation done successfully\n");
    }

    Values->append(*temp);

    sql = "SELECT * from "+name;

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.toLatin1().data(), callback_db, Values, &zErrMsg);

    if( rc != SQLITE_OK ) {
      QMessageBox messageBox;
      messageBox.critical(0,"SQL error",zErrMsg);
      messageBox.setFixedSize(500,200);
      sqlite3_free(zErrMsg);
      return -1;
    } else {
      fprintf(stdout, "Operation done successfully\n");
    }
    return 0;
}

int database::table_add(QString name, QStringList ValueNames, QStringList Values)
{
   char *zErrMsg = 0;
   /* Create SQL statement */
   QString sql = "INSERT INTO "+name+" (";
   QStringList::iterator it = ValueNames.begin();
   sql += *it;
   ++it;
   for (;it != ValueNames.end(); ++it)
   {
       sql += ","+ *it;
   }
   sql+=" ) ";

   sql += "VALUES (";
   it = Values.begin();
   sql += *it;
   ++it;
   for (;it != Values.end(); ++it)
   {
       sql += ","+ *it;
   }
   sql+=" );";
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.toLatin1().data(), callback_db, 0, &zErrMsg);

   if( rc != SQLITE_OK ) {
     QMessageBox messageBox;
     messageBox.critical(0,"SQL error",zErrMsg);
     messageBox.setFixedSize(500,200);
     sqlite3_free(zErrMsg);
     return -1;
   } else {
     fprintf(stdout, "Operation done successfully\n");
   }
   return 0;
}

int database::table_delete(QString name,QString IDValueName, QString IDValue)
{
   char *zErrMsg = 0;
   /* Create SQL statement */
   QString sql = "DELETE from "+name+" where "+IDValueName+"="+IDValue+"; ";
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.toLatin1().data(), callback_db, 0, &zErrMsg);

   if( rc != SQLITE_OK ) {
     QMessageBox messageBox;
     messageBox.critical(0,"SQL error",zErrMsg);
     messageBox.setFixedSize(500,200);
     sqlite3_free(zErrMsg);
     return -1;
   } else {
     fprintf(stdout, "Operation done successfully\n");
   }
   return 0;
}

int database::table_update(QString name,QString IDValueName, QString IDValue, QStringList ValueNames, QStringList Values)
{
   char *zErrMsg = 0;
   /* Create SQL statement */
   QString sql = "UPDATE "+name+" set ";
   QStringList::iterator it = ValueNames.begin();
   QStringList::iterator it2 = Values.begin();
   sql += *it+" = "+ *it2;
   ++it;
   ++it2;
   for (;it != ValueNames.end(),it2 != Values.end(); ++it,++it2)
   {
       sql += ","+ *it+" = "+ *it2;
   }
   sql+=" where "+IDValueName+"="+IDValue+"; ";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.toLatin1().data(), callback_db, 0, &zErrMsg);

   if( rc != SQLITE_OK ) {
     QMessageBox messageBox;
     messageBox.critical(0,"SQL error",zErrMsg);
     messageBox.setFixedSize(500,200);
     sqlite3_free(zErrMsg);
     return -1;
   } else {
     fprintf(stdout, "Operation done successfully\n");
   }
   return 0;
}

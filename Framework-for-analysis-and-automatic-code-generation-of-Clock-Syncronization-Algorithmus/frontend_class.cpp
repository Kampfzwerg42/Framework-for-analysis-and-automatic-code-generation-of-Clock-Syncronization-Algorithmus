#include "frontend_class.h"
#include "ui_frontend_class.h"

Frontend_class::Frontend_class(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Frontend_class)
{
    ui->setupUi(this);

    ui->progressBar->hide();

    algos_db=new database(path_to_database_algos);

    db_editor = new Database_Editor_Class(); // Be sure to destroy your window somewhere

    calculater=new backend();

    on_Autofill_clicked();
    load_database();
}
Frontend_class::~Frontend_class()
{
    delete calculater;
    delete db_editor;
    delete algos_db;
    delete ui;
}

void Frontend_class::load_database()
{
    QList<QStringList> cells=*(new QList<QStringList>);
    if (algos_db->table_load("Algorithms",&cells)==0)
    {

        int Algorithms_colum_count_for_software=cells[0].length()-Algorithms_colum_lables_db_calculation_needed.length();
        ui->tableWidget_2->setColumnCount(Algorithms_colum_count_for_software);

        QStringList pos_values={};
        QStringList headers={};
        cells[0][0]="";
        ui->tableWidget_2->setRowCount(3);
        for( int j = 0, j_real=0 ; j_real < cells[0].length() ; ++j_real ){
            if (!Algorithms_colum_lables_db_calculation_needed.contains(cells[0][j_real]))
            {
                pos_values.append("");
                headers.append(cells[0][j_real]);
                ui->tableWidget_2->setItem( 0 , j , new QTableWidgetItem( "EMPTY" ) );
                ++j;
            }
        }
        for( int i = 1 ; i < cells.length() ; ++i )
        {
            for( int j = 0, j_real=0 ; j_real < cells[0].length() ; ++j_real ){
                if (!Algorithms_colum_lables_db_calculation_needed.contains(cells[0][j_real]))
                {
                    QStringList list1 = pos_values[j].split(",");
                    if (!(list1.contains(cells[i][j_real])))
                    {
                        if(!pos_values[j].isEmpty())
                            pos_values[j]+=",";
                        pos_values[j]+=cells[i][j_real];
                    }
                    ++j;
                }
            }

        }
        for( int j = 0 ; j < ui->tableWidget_2->columnCount() ; ++j ){
            ui->tableWidget_2->setItem( 2 , j , new QTableWidgetItem( pos_values[j] ) );
        }

        ui->tableWidget_2->setHorizontalHeaderLabels(headers);

        ui->tableWidget_2->setItem( 0 , 0 , new QTableWidgetItem( "Algorithm Values" ) );
        ui->tableWidget_2->setItem( 2 , 0 , new QTableWidgetItem( "Possible Values" ) );

        ui->tableWidget_2->resizeColumnsToContents();

    }
}
void Frontend_class::opendatabase_editor()
{
//   db_editor = new Database_Editor_Class(algos_db); // Be sure to destroy your window somewhere
   db_editor->show();
   // ...
}
void Frontend_class::on_pushButton_2_clicked()
{

}

void Frontend_class::on_comboBox_2_currentIndexChanged(const QString &arg1)
{

}

void Frontend_class::on_pushButton_clicked()
{
    QList<QStringList> cells=*(new QList<QStringList>);
    algos_db->table_load("Algorithms",&cells);
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    QStringList Headers=cells[0];
    Headers.append(Algorithms_colum_lables_special);

    for(int k=0;k<Headers.length();++k)
    {
        for(int i=0;i<Algorithms_colum_lables_db_calculation_needed.length();++i)
        {
            if(Headers[k]==Algorithms_colum_lables_db_calculation_needed[i])
            {
                Headers[k]=Algorithms_colum_lables_db_calculation_needed_display[i];
            }
        }
    }
    ui->tableWidget->setColumnCount(Headers.length());

    ui->tableWidget->setHorizontalHeaderLabels(Headers);

    QStringList Paramnames=Systemparameter;
    QList<double> ParamValues={};
    QStringList ParamValues_nan={};
    QList<double> ParamValuesmin={};
    QList<double> ParamValuesmax={};

    for(int i=0;i<Systemparameter.length();++i)
    {
        bool ok;
        double value=ui->System_param_table->item(i,1)->text().toDouble(&ok);
        if (ok)ParamValuesmin.append(value);
        else ParamValuesmin.append(NAN);
        value=ui->System_param_table->item(i,2)->text().toDouble(&ok);
        if (ok)ParamValuesmax.append(value);
        else ParamValuesmax.append(NAN);
        ParamValues.append(NAN);
        ParamValues_nan.append("");
    }

    for(int i=0;i<ui->System_param_table->rowCount();++i)
    {
        if ( ! ui->System_param_table->item(i,0)->text().isEmpty()
          && ! Systemparameter.contains(ui->System_param_table->item(i,0)->text()))
        {
            Paramnames.append(ui->System_param_table->item(i,0)->text());

            bool ok;
            double value=ui->System_param_table->item(i,1)->text().toDouble(&ok);
            if ((ui->System_param_table->item(i,3)->text().isEmpty())||(ui->System_param_table->item(i,3)->text()=="EMPTY"))
            {
                value=ui->System_param_table->item(i,1)->text().toDouble(&ok);
                if (ok)
                {
                    ParamValuesmin.append(value);
                    ParamValues.append(value);
                }
                else
                {
                    ParamValuesmin.append(0);
                    ParamValues.append(0);
                }

                value=ui->System_param_table->item(i,2)->text().toDouble(&ok);
                if (ok)ParamValuesmax.append(value);
                else ParamValuesmax.append(std::numeric_limits<double>::max());

                ParamValues_nan.append("");
            }
            else
            {
                ParamValues.append(NAN);

                value=ui->System_param_table->item(i,1)->text().toDouble(&ok);
                if (ok)ParamValuesmin.append(value);
                else ParamValuesmin.append(std::numeric_limits<double>::min());

                value=ui->System_param_table->item(i,2)->text().toDouble(&ok);
                if (ok)ParamValuesmax.append(value);
                else ParamValuesmax.append(std::numeric_limits<double>::max());

                ParamValues_nan.append(ui->System_param_table->item(i,3)->text());
            }
        }
    }

    ui->progressBar->show();
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(cells.length());
    for( int i = 1 ; i < cells.length() ; ++i )
    {
        ui->progressBar->setValue(i);

        bool algo_is_valid=1;
        // Columns
        int Algorithms_colum_count_for_software=cells[0].length()-Algorithms_colum_lables_db_calculation_needed.length();
        for( int j = 1 ; j < Algorithms_colum_count_for_software ; ++j ){
            QStringList list1 = ui->tableWidget_2->item(0,j)->text().split(",");
            int j_for_real=cells[0].indexOf(ui->tableWidget_2->horizontalHeaderItem(j)->text());
            if (!(ui->tableWidget_2->item(0,j)->text()=="EMPTY")&&!(list1.contains((cells[i][j_for_real]),Qt::CaseInsensitive))&&(cells[0][j_for_real]!=Algorithms_colum_lables_db[0]))
            {
                algo_is_valid=0;
            }
        }
        if (algo_is_valid){
            bool valid_parameter=false;
            //search Optima
            //set Optimal Params for Algorithmus
            QString optimization_string="";
            if (ui->Opt_Precision->isChecked())optimization_string=Systemparameter[1];
            if (ui->Opt_Network->isChecked())optimization_string=Systemparameter[3];
            if (ui->Opt_wighted_combination->isChecked())optimization_string=ui->Opt_wight_funktion->text();
            for(int k=0;k<cells[0].length();++k)
            {
                for(int j=0;j<Algorithms_colum_lables_db_calculation_needed.length();++j)
                {
                    if(cells[0][k]==Algorithms_colum_lables_db_calculation_needed[j])
                    {
                        ParamValues_nan[j]=cells[i][k];
                    }
                }
            }

            if (!optimization_string.isEmpty())
            {
                QList<double> Param_calculated=calculater->Optimization(optimization_string,Paramnames,ParamValuesmin,ParamValuesmax,ParamValues_nan,&valid_parameter);
                if (!Param_calculated.isEmpty()) ParamValues=Param_calculated;
            }

            QString Param_column="";
            for(int params=0;params<Paramnames.length();++params)
            {
                if(!Systemparameter.contains(Paramnames[params]))
                {
                    if (!Param_column.isEmpty()) Param_column+=";";
                    Param_column+=Paramnames[params]+"="+calculater->calculate(Paramnames[params],Paramnames,ParamValues,ParamValues_nan);
                }
            }

            //Show optima Parameter
            ui->tableWidget->insertRow(0);
            SortableTableWidgetItem *item = new SortableTableWidgetItem(Param_column);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            if (valid_parameter)
            {
                item->setValidity(valid_parameter);
                item->setBackgroundColor(Qt::green);
            }
            else
            {
                item->setValidity(valid_parameter);
                item->setBackgroundColor(Qt::red);
            }
            ui->tableWidget->setItem( 0 , ui->tableWidget->columnCount()-1 , item );

            //calculate entries
            for( int j = 0 ; j < cells[i].length() ; ++j ){
                QString content_text=cells[i][j];
                if (Algorithms_colum_lables_db_calculation_needed.contains(cells[0][j]))
                {
                    content_text=calculater->calculate(content_text,Paramnames,ParamValues,ParamValues_nan);
                }
                item = new SortableTableWidgetItem(content_text);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                if (valid_parameter)
                {
                    item->setValidity(valid_parameter);
                    item->setBackgroundColor(Qt::green);
                }
                else
                {
                    item->setValidity(valid_parameter);
                    item->setBackgroundColor(Qt::red);
                }
                ui->tableWidget->setItem( 0 , j , item );
            }

            //calculate sorting
            QString content_text="0";
            if (!optimization_string.isEmpty())
                content_text=calculater->calculate(optimization_string,Paramnames,ParamValues,ParamValues_nan);
            item = new SortableTableWidgetItem(content_text);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            if (valid_parameter)
            {
                item->setValidity(valid_parameter);
                item->setBackgroundColor(Qt::green);
            }
            else
            {
                item->setValidity(valid_parameter);
                item->setBackgroundColor(Qt::red);
            }
            ui->tableWidget->setItem( 0 , ui->tableWidget->columnCount()-2 , item );
        }
    }
    ui->progressBar->hide();
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->sortByColumn(ui->tableWidget->columnCount()-2,Qt::AscendingOrder);

}

void Frontend_class::on_pushButton_3_clicked()
{
opendatabase_editor();
}

void Frontend_class::on_Taxonomie_load_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,    tr("Load Database"), "",
                                                    tr("Database File (*.db);;All Files (*)"));
    delete algos_db;
    algos_db=new database(fileName);

    load_database();
}

void Frontend_class::on_reload_db_clicked()
{
    load_database();
}

void Frontend_class::on_deleteparameter_clicked()
{
    if (ui->System_param_table->currentRow()>=Systemparameter.length())
        ui->System_param_table->removeRow(ui->System_param_table->currentRow());
}

void Frontend_class::on_addParameter_clicked()
{
    ui->System_param_table->insertRow(Systemparameter.length());
    ui->System_param_table->setItem(Systemparameter.length(),0, new QTableWidgetItem( "" ));
    ui->System_param_table->setItem(Systemparameter.length(),1, new QTableWidgetItem( "1.00" ));
    ui->System_param_table->setItem(Systemparameter.length(),2, new QTableWidgetItem( "1.00" ));
    ui->System_param_table->setItem(Systemparameter.length(),3, new QTableWidgetItem( "" ));
}

void Frontend_class::on_Autofill_clicked()
{
    //load systemparameter from Taxonomies
    QList<QStringList> cells_taxonomie=*(new QList<QStringList>);
    Systemparameter.clear();
    Algorithms_colum_lables_db_calculation_needed.clear();
    if (algos_db->table_load("Taxonomie",&cells_taxonomie)==0)
    {
        for( int i = 1 ; i < cells_taxonomie.length() ; ++i )
        {
            if(!cells_taxonomie[i][2].isEmpty() && cells_taxonomie[i][2]!="EMPTY")
            {
                if (cells_taxonomie[i][2][0].isLetter())
                {
                    if(Systemparameter.contains(cells_taxonomie[i][2]))
                    {
                        QMessageBox messageBox;
                        messageBox.critical(0,"Multiple Systemparameter:",cells_taxonomie[i][2]);
                        messageBox.setFixedSize(500,200);
                    }
                    else
                    {
                        Systemparameter.append(cells_taxonomie[i][2]);
                        Algorithms_colum_lables_db_calculation_needed.append(cells_taxonomie[i][0]);
                    }
                }
            }
        }
    }
    QList<QStringList> cells=*(new QList<QStringList>);
    for( int i = 0 ; i < Systemparameter.length() ; ++i )
    {
        if(ui->System_param_table->findItems(Systemparameter[i],Qt::MatchExactly).isEmpty())
        {
            ui->System_param_table->insertRow(i);
            QTableWidgetItem *item = new QTableWidgetItem( Systemparameter[i] );
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->System_param_table->setItem(i,0,item);
            ui->System_param_table->setItem(i,1, new QTableWidgetItem( "-" ));
            ui->System_param_table->setItem(i,2, new QTableWidgetItem( "-" ));
            item = new QTableWidgetItem( "no change" );
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->System_param_table->setItem(i,3, item);

//            ui->System_param_table->setItem(i,ui->System_param_table->columnCount()-1, new QTableWidgetItem( Systemparameter_desc[i] ));
        }
    }
    if (algos_db->table_load("Parameter",&cells)==0)
    {
        for( int i = 1 ; i < cells.length() ; ++i )
        {
            if(ui->System_param_table->findItems(cells[i][0],Qt::MatchExactly).isEmpty())
            {
                ui->System_param_table->insertRow(Systemparameter.length());
                ui->System_param_table->setItem(Systemparameter.length(),0, new QTableWidgetItem( cells[i][0] ));
                ui->System_param_table->setItem(Systemparameter.length(),1, new QTableWidgetItem( cells[i][2] ));
                ui->System_param_table->setItem(Systemparameter.length(),2, new QTableWidgetItem( cells[i][3] ));
                ui->System_param_table->setItem(Systemparameter.length(),3, new QTableWidgetItem( cells[i][4] ));

                ui->System_param_table->setItem(Systemparameter.length(),ui->System_param_table->columnCount()-1, new QTableWidgetItem( cells[i][1] ));
            }
            else if(ui->System_param_table->findItems(cells[i][0],Qt::MatchExactly)[0]->row()<Systemparameter.length())
            {
                //load description for systemparameter
                int line=ui->System_param_table->findItems(cells[i][0],Qt::MatchExactly)[0]->row();
                ui->System_param_table->setItem(line,1, new QTableWidgetItem( cells[i][2] ));
                ui->System_param_table->setItem(line,2, new QTableWidgetItem( cells[i][3] ));

                ui->System_param_table->setItem(line,ui->System_param_table->columnCount()-1, new QTableWidgetItem( cells[i][1] ));
            }
        }
    }
    ui->System_param_table->resizeColumnsToContents();
}

void Frontend_class::on_System_param_table_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    bool oldStatemax = ui->spinBoxdouble_max->blockSignals(true);
    bool oldStatemin = ui->spinBoxdouble_min->blockSignals(true);
    if (ui->System_param_table->item(currentRow,3)->text().isEmpty())
    {
        ui->spinBoxdouble_min->setValue(ui->System_param_table->item(currentRow,1)->text().toDouble());
        ui->spinBoxdouble_max->setValue(ui->System_param_table->item(currentRow,2)->text().toDouble());
        ui->groupBox_min->setTitle("MIN "+ui->System_param_table->item(currentRow,0)->text());
        ui->groupBox_max->setTitle("MAX "+ui->System_param_table->item(currentRow,0)->text());
    }
    else
    {
        bool ok;
        double value=ui->System_param_table->item(currentRow,1)->text().toDouble(&ok);
        if (ok) ui->spinBoxdouble_min->setValue(value);
        else  ui->spinBoxdouble_min->setValue(std::numeric_limits<double>::min());
        value=ui->System_param_table->item(currentRow,2)->text().toDouble(&ok);
        if (ok) ui->spinBoxdouble_max->setValue(value);
        else  ui->spinBoxdouble_max->setValue(std::numeric_limits<double>::max());
        ui->groupBox_min->setTitle("Min condition "+ui->System_param_table->item(currentRow,0)->text());
        ui->groupBox_max->setTitle("Max condition "+ui->System_param_table->item(currentRow,0)->text());
    }
    ui->spinBoxdouble_max->blockSignals(oldStatemax);
    ui->spinBoxdouble_min->blockSignals(oldStatemin);
}

void Frontend_class::on_spinBoxdouble_min_valueChanged(const QString &arg1)
{
    ui->System_param_table->item(ui->System_param_table->currentRow(),1)->setText(arg1);
    ui->System_param_table->resizeColumnsToContents();
}

void Frontend_class::on_spinBoxdouble_max_valueChanged(const QString &arg1)
{
    ui->System_param_table->item(ui->System_param_table->currentRow(),2)->setText(arg1);
    ui->System_param_table->resizeColumnsToContents();
}

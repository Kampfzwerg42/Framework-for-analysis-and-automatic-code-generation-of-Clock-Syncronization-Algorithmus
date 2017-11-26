#include "database_editor_class.h"
#include "ui_database_editor.h"

Database_Editor_Class::Database_Editor_Class(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Database_Editor_Class)
{
    ui->setupUi(this);
    algos_db=new database(path_to_database_algos);
}

Database_Editor_Class::Database_Editor_Class(database *db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Database_Editor_Class)
{
    ui->setupUi(this);
    algos_db=db;
    protect_algos_db=1;
}

Database_Editor_Class::~Database_Editor_Class()
{
    delete ui;
    if (protect_algos_db==0)
        delete algos_db;
    if(load_form_file)
        delete load_db;
}

void Database_Editor_Class::on_tableWidget_cellClicked(int row, int column)
{
    if(load_form_file)
    {
        for( int j = 0 ; j < ui->tableWidget_2->columnCount() ; ++j ){
            ui->tableWidget_2->setItem( 0 , j , new QTableWidgetItem( "EMPTY"));
            for( int i = 0 ; i < ui->tableWidget->columnCount() ; ++i ){
                if(ui->tableWidget->horizontalHeaderItem(i)->text()==ui->tableWidget_2->horizontalHeaderItem(j)->text())
                {
                    ui->tableWidget_2->setItem( 0 , j , new QTableWidgetItem( ui->tableWidget->item(row,i)->text()));
                    break;
                }
            }
        }
    }
    else for( int j = 0 ; j < ui->tableWidget_2->columnCount() ; ++j ){
            ui->tableWidget_2->setItem( 0 , j , new QTableWidgetItem( ui->tableWidget->item(row,j)->text()));
    }
}

void Database_Editor_Class::reload_database()
{
    QList<QStringList> cells=*(new QList<QStringList>);

    algos_db->table_load(ui->comboBox->currentText(),&cells);


    QList<QStringList> cells2=*(new QList<QStringList>);
    if (load_form_file){
        load_db->table_load(file_tabel_name,&cells2);
    }
    else
    {
        cells2=cells;
    }

    int cells2_length=cells2[0].length();
    int cells_length=cells[0].length();

    if(ui->comboBox->currentText()=="Taxonomie"){
        //dont show types column(ever TEXT)
        cells2_length-=1;
        cells_length-=1;
    }
    ui->tableWidget->setColumnCount(cells2_length);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clear();

    ui->tableWidget_2->setColumnCount(cells_length);

    //set up tabels
    ui->tableWidget->setHorizontalHeaderLabels(cells2[0]);
    ui->tableWidget_2->setHorizontalHeaderLabels(cells[0]);
    ui->tableWidget_2->setRowCount(1);
    int j;
    for( j = 0 ; j < ui->tableWidget_2->columnCount() ; ++j ){
        if (ui->tableWidget_2->item(0,j)==0){
            break;
        }
    }
    if (j<ui->tableWidget_2->columnCount()){
        for( int j = 0 ; j < ui->tableWidget_2->columnCount() ; ++j ){
                ui->tableWidget_2->setItem( 0 , j , new QTableWidgetItem( "EMPTY" ) );
        }
    }
    for( int i = cells2.length()-1; i>0 ; --i )
    {
        ui->tableWidget->insertRow( 0 );

        // Columns
        for( int j = 0 ; j < cells2_length ; ++j ){
                QTableWidgetItem *item = new QTableWidgetItem(cells2[i][j]);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                ui->tableWidget->setItem( 0 , j , item );
        }
    }
    ui->tableWidget->resizeColumnsToContents();
    for(int i=0;i<ui->tableWidget->columnCount();++i)
    {
        ui->tableWidget_2->setColumnWidth(i,ui->tableWidget->columnWidth(i));
    }

}

void Database_Editor_Class::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(load_form_file)
        delete load_db;
    load_form_file=false;
    reload_database();
}

void Database_Editor_Class::on_init_database_clicked()
{
    if(ui->comboBox->currentText()=="Algorithms") {
        QList<QStringList> cells=*(new QList<QStringList>);
        if (algos_db->table_load("Taxonomie",&cells)==0)
        {
            QStringList columns={};
            QStringList types={};
            for (int i=1;i<cells.length();++i)
            {
                columns+=cells[i][0];
                types+=cells[i][2];
            }
            algos_db->table_create(ui->comboBox->currentText(), columns, types);
        }
    }
    else if(ui->comboBox->currentText()=="Taxonomie"){
        algos_db->table_create(ui->comboBox->currentText(), Taxonomie_colum_lables, Taxonomie_colum_types);
        //init Table with standard Taxonomie
        for (int i=0;i<Algorithms_colum_lables_db.length();++i)
        {
            QStringList Values=Taxonomie_colum_lables;
            for(int i=0;i<Values.length();++i)
            {
                Values[i]=(QString)"\'"+"\'";
            }
            Values[0]="\'"+Algorithms_colum_lables_db[i]+"\'";
            Values[1]=(QString)"\'"+"\'";
            if (i==0)
            {
                Values[Values.length()-1]=(QString)"\'"+"TEXT PRIMARY KEY NOT NULL"+"\'";
            }
            else
            {
                Values[Values.length()-1]=(QString)"\'"+"TEXT"+"\'";
            }
            if (Algorithms_colum_lables_db_calculation_needed_default.contains(Algorithms_colum_lables_db[i]))
            {
                Values[2]="\'"+Systemparameter_default[Algorithms_colum_lables_db_calculation_needed_default.indexOf(Algorithms_colum_lables_db[i])]+"\'";
            }
            algos_db->table_add(ui->comboBox->currentText(),Taxonomie_colum_lables, Values);
        }
    }
    else if(ui->comboBox->currentText()=="Parameter"){
        algos_db->table_create(ui->comboBox->currentText(), Parameter_colum_lables, Parameter_colum_types);
    }
    reload_database();
}

void Database_Editor_Class::on_add_db_element_clicked()
{
    QList<QStringList> cells=*(new QList<QStringList>);
    algos_db->table_load(ui->comboBox->currentText(),&cells);

    QStringList Values={};
    for( int i = 0 ; i < ui->tableWidget_2->columnCount() ; ++i )
    {
        Values+="\'"+ui->tableWidget_2->item(0,i)->text()+"\'";
    }

    if(ui->comboBox->currentText()=="Taxonomie"){
        Values+=(QString)"\'"+"TEXT"+"\'";
        for(int i=0;i<Algorithms_colum_lables_db_calculation_needed_default.length();i++)
        {
            algos_db->table_delete(ui->comboBox->currentText(),cells[0][0], "\'"+Algorithms_colum_lables_db_calculation_needed_default[i]+"\'");
        }
    }
    algos_db->table_add(ui->comboBox->currentText(),cells[0], Values);
    if(ui->comboBox->currentText()=="Taxonomie"){
        for(int i=0;i<Algorithms_colum_lables_db_calculation_needed_default.length();i++)
        {
            int j=0;
            for(j=0;j<cells.length();++j)
            {
                if(cells[j][0]==Algorithms_colum_lables_db_calculation_needed_default[i])break;
            }
            for(int k=0;k<cells[j].length();++k)
            {
                cells[j][k]="\'"+cells[j][k]+"\'";
            }

            algos_db->table_add(ui->comboBox->currentText(),cells[0], cells[j]);
        }
    }
    reload_database();
}

void Database_Editor_Class::on_copy_clicked()
{
    for( int i = ui->tableWidget->rowCount()-1; i >= 0 ; --i ){
        on_tableWidget_cellClicked(i,0);
        on_add_db_element_clicked();
    }
}

void Database_Editor_Class::on_delete_db_element_clicked()
{
    QList<QStringList> cells=*(new QList<QStringList>);
    algos_db->table_load(ui->comboBox->currentText(),&cells);

    QString Value;
    Value="\'"+ui->tableWidget_2->item(0,0)->text()+"\'";

    if((ui->comboBox->currentText()=="Taxonomie")
        && !((ui->tableWidget_2->item(0,0)->text()!=Algorithms_colum_lables_db[0])
            && !Algorithms_colum_lables_db_calculation_needed_default.contains(ui->tableWidget_2->item(0,0)->text())))
            return ;

    algos_db->table_delete(ui->comboBox->currentText(),cells[0][0], Value);


    reload_database();
}

void Database_Editor_Class::on_update_db_element_clicked()
{
    QList<QStringList> cells=*(new QList<QStringList>);
    algos_db->table_load(ui->comboBox->currentText(),&cells);

    QStringList Values={};
    for( int i = 1 ; i < ui->tableWidget_2->columnCount() ; ++i )
    {
        Values+="\'"+ui->tableWidget_2->item(0,i)->text()+"\'";
    }

    QString Value;
    Value="\'"+ui->tableWidget_2->item(0,0)->text()+"\'";

    QStringList temp=cells[0];
    temp.removeFirst();
    if(ui->comboBox->currentText()=="Taxonomie"){
        temp.removeLast();
    }
    algos_db->table_update(ui->comboBox->currentText(),cells[0][0], Value,temp,Values);
    reload_database();
}

void Database_Editor_Class::on_load_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,    tr("Load Database"), "",
                                                    tr("Database File (*.db);;All Files (*)"));
    load_db=new database(fileName);
    bool ok;
    file_tabel_name = QInputDialog::getText(this, tr("Tabel Name vor Database to load"),
                                            tr("Tabel name:"), QLineEdit::Normal,
                                            ui->comboBox->currentText(), &ok);
    load_form_file=true;
    reload_database();
}

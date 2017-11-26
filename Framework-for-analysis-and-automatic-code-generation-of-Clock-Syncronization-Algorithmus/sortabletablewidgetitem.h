#ifndef SORTABLETABLEWIDGETITEM_H
#define SORTABLETABLEWIDGETITEM_H

#include <QTableWidgetItem>

class SortableTableWidgetItem : public QTableWidgetItem
{
public:
    SortableTableWidgetItem(const QString &text):QTableWidgetItem(text){}
    void setValidity(bool validity){
        if (validity)
            this->setFlags(this->flags() | Qt::ItemIsUserCheckable);
        else
            this->setFlags(this->flags() ^ Qt::ItemIsUserCheckable);
    }
    bool Validity(void) const{
        return (bool)(this->flags() & Qt::ItemIsUserCheckable);
    }

    virtual bool operator < (const QTableWidgetItem &other) const
    {
        bool ok=(bool)(this->flags() & Qt::ItemIsUserCheckable);
        bool ok_other=(bool)(other.flags() & Qt::ItemIsUserCheckable);

        if(ok_other&&!ok)
            return false;
        if(!ok_other&&ok)
            return true;

        double value=this->text().toDouble(&ok);
        double value_other=other.text().toDouble(&ok_other);
        if(ok_other&&ok)
            return (value < value_other);
        if(ok_other&&!ok)
            return false;
        if(!ok_other&&ok)
            return true;
        return (this->text() < other.text());
    }
};


#endif // SORTABLETABLEWIDGETITEM_H

#include "vectors.h"

qreal mathVector::dot(mathVector &other)
{
    if (this->length()!=other.length())
    {
        //error
        return NAN;
    }
    qreal dot_value=0;
    for (int i=0;i<this->length();++i)
    {
        dot_value+=this->at(i)*other.at(i);
    }
    return dot_value;
}

qreal mathVector::norm()
{
    qreal norm_value=0;
    for (int i=0;i<this->length();++i)
    {
        if (this->at(i)>=0)norm_value+= this->at(i);
        else norm_value-=this->at(i);
    }
    return norm_value;
}

qreal mathVector::euklid_norm()
{
    qreal norm_value=0;
    for (int i=0;i<this->length();++i)
    {
        if (this->at(i)>=0)norm_value+= pow(this->at(i),2);
        else norm_value-=pow(this->at(i),2);
    }
    return qSqrt(norm_value);
}

mathVector* mathVector::normalize()
{
    qreal norm_value=this->norm();
    for (int i=0;i<this->length();++i)
    {
        this[i]=this->at(i)/norm_value;
    }
    return this;
}



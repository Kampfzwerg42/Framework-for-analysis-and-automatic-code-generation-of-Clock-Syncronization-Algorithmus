#ifndef VARIABLES_FOR_BACKEND_H
#define VARIABLES_FOR_BACKEND_H

#include <qstring.h>

const QList<QChar> operator_list={'+','-','/','*','^','(',')','<','>'};
//[={=(
//Infix             Meaning             Postfix

//(x<y)             Minimum of x y      x y <
//(x>y)             Maximum of x y      x y >
//min/max is lower as +/-

const QList<QChar> number_list={'1','2','3','4','5','6','7','8','9','0','.'};

//used for calculate gradient: xnew=x+x*epsylon_divider;gradient_x=(f(...x...)-f(...xnew...))/xnew-x
const double epsylon_divider=0.0001;
//if relativ minimal epsylon value (if x=>0)
const double epsylon_min=0.000001;

//penality for violate constraints:Mult*(violation/(violated limit))^2
const double PenalityMultiplier=1000000;

const QString path_to_base_directory = "../../";
const QString path_to_database_algos = path_to_base_directory+"/databases/database_algos.db";

#endif // VARIABLES_FOR_BACKEND_H

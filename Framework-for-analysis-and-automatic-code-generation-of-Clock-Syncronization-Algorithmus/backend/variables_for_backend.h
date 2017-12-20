#ifndef VARIABLES_FOR_BACKEND_H
#define VARIABLES_FOR_BACKEND_H

#include <qstring.h>

const QList<QChar> operator_list={'+','-','/','*','^','(',')','<','>'};
//[={=(
//Infix             Meaning             Postfix

//(x<y)             Minimum of x y      x y <
//(x>y)             Maximum of x y      x y >
//min/max is lower as +/-

//xe+y  xe-y

const QList<QChar> number_list={'1','2','3','4','5','6','7','8','9','0','.'};

//used for calculate gradient: xnew=x+x*epsylon_divider;gradient_x=(f(...x...)-f(...xnew...))/(xnew-x)
const double epsylon_divider=0.0000001;
//absulute minium for epsylon, used if x=0 or near 0
const double epsylon_min=0.00000000000001;
//epsylon added to division to eliminate division by 0
const double epsylon_div_save=0.0000000001;

//lerningrate of Optimization a.k. Gradient multiplier
const double ny=0.001;
//lerningrate of Optimization a.k. Gradient multiplier
const int max_rounds=100;
//lerningrate of Optimization a.k. momentum term multiplier
const double ny_momentum=0.9;

//Startvalue for alpha
const double alpha_start=1;
//lastvalue for beta->turn to 0
const double beta_min=0.25;
//Maxvalue for gradient(change of parameter per round)
const double max_variable_change=100;

//penality for violate constraints:Mult*(violation/(violated limit))^2
const double PenalityMultiplier_base=1;

//penality for violate constraints:(Mult_time*time)^mutl_time_pot*(violation/(violated limit))^2
const double PenalityMultiplier_time=0.5;
const double PenalityMultiplier_time_pot=2;

const QString path_to_base_directory = "../../";
const QString path_to_database_algos = path_to_base_directory+"/databases/database_algos.db";

#endif // VARIABLES_FOR_BACKEND_H

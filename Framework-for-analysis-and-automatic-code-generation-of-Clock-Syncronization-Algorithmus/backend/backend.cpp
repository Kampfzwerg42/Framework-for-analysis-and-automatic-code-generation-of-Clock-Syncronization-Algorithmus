#include "backend.h"

backend::backend()
{
    database algos(path_to_database_algos);
}

bool backend::IsOperator(QChar c)
{
    return operator_list.contains(c);
}
bool backend::IsNumber(QChar c)
{
    return number_list.contains(c);
}

int backend::operator_precedence(QChar c)
{
    if (c=='>')
        return 2;
    if (c=='<')
        return 2;
    if (c=='+')
        return 4;
    if (c=='-')
        return 4;
    if (c=='*')
        return 8;
    if (c=='/')
        return 8;
    if (c=='^')
        return 16;
    if (c=='(')
        return -99;
    if (c==')')
        return -1;


    return 0;
}

double backend::randomnumber(double min, double max)
{
    return ((((double)qrand()/RAND_MAX) * (max-min)) + min);
}

QString backend::InfixToPostfix(QString infix)
{
    //generate special Prefix(spaces seperates every operand/operator Numbers begin with N Operators with O Variables with V)(bast*false+1->Vbast Vfalse O* N1 O+)
    QStack<QChar> s;
    QString postfix = "";
    infix.remove(" ");
    infix.replace('[','(');
    infix.replace('{','(');
    infix.replace(']',')');
    infix.replace('}',')');
    //start special case for +/- as sign
    bool start=true;
    bool automulti=false;
    for(int i = 0; i< infix.length(); ++i)
    {
        if ((infix.at(i)=="(")||(!start && IsOperator(infix.at(i))))
        {
            if (infix.at(i)!='(')
            {
                while (!s.isEmpty()&&!(operator_precedence(infix.at(i)) > operator_precedence(s.top())))
                {
                    postfix+="O";
                    postfix+=s.pop();
                    postfix+=" ";
                }
            }
            else if (automulti)
            {
                s.push('*');
            }

            automulti=false;
            if (infix.at(i)==')')
            {
                automulti=true;
                if (s.top()=='(')
                {
                    s.pop();
                }
                else
                {
                    QMessageBox messageBox;
                    messageBox.critical(0,"Infix to Postfix error","')' without '('");
                    messageBox.setFixedSize(500,200);
                    return "";
                }
            }
            else
            {
                s.push(infix.at(i));
                start=true;
            }
        }
        else
        {
            QString sign="";
            if ((i<infix.length())&&(infix.at(i)=="-"))
            {
                sign="-";
                i++;
            }
            else if ((i<infix.length())&&(infix.at(i)=="+"))
            {
                i++;
            }
            else if ((i<infix.length())&&IsOperator(infix.at(i))){
                QMessageBox messageBox;
                messageBox.critical(0,"Infix to Postfix error","to many Operators at one Point");
                messageBox.setFixedSize(500,200);
                return "";
            }
            if ((i<infix.length())&&IsNumber(infix.at(i)))
            {
                //take hole number
                postfix+="N"+sign;
                for(; (i<infix.length()) && IsNumber(infix.at(i)) ; ++i) postfix+=infix.at(i);
                --i;
                postfix+=" ";
                start=false;
                automulti=true;
            }
            else //variable
            {
                if (automulti)
                {
                    s.push('*');
                }
                postfix+="V"+sign;
                while((i<infix.length())&&(!IsOperator(infix.at(i)))&&((infix.at(i)!=" "))){
                    postfix+=infix.at(i);
                    i+=1;
                }
                --i;
                postfix+=" ";
                start=false;
                automulti=true;
            }
        }
    }
    while (!s.isEmpty())
    {
        if (s.top()=='(')
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Infix to Postfix error",") expected");
            messageBox.setFixedSize(500,200);
            return "";
        }
        postfix+="O";
        postfix+=s.pop();
        if (!s.empty())
            postfix+=" ";
    }
    postfix.replace(" +"," ");
    return postfix;
}

QString backend::calculate(QString text,QStringList VarNames,QList<double> Vars,QStringList Vars_nan)
{
    //make sting calculateable -> infix to postfix
    QString postfix=InfixToPostfix(text);

    postfix.replace(" +"," ");
    return calculate_intern(postfix,VarNames,Vars,Vars_nan).remove(0,1);
}

QString backend::calculate_intern(QString text,QStringList VarNames,QList<double> Vars,QStringList Vars_nan)
{
    QStack<QString> Stack;

    bool break_loop;
    QStringList postfix_list=text.split(" ", QString::SkipEmptyParts);
    for (int i=postfix_list.length()-1;i>=0;--i)
    {
        break_loop=false;
        if (postfix_list[i].at(0)=='O')
        {
            Stack.push(postfix_list[i]);
        }
        else
        {
            if (postfix_list[i].at(0)=='V')
            {
                QString temp=postfix_list[i];
                temp.remove(0,1);
                double multipier=1;
                if (IsOperator(temp.at(0)))
                {
                    if (temp.at(0)=='-')
                        multipier=-1;
                    temp.remove(0,1);
                }
                //set Variables
                if (VarNames.contains(temp))
                {
                    if (!isnan(Vars[VarNames.indexOf(temp)]))
                        postfix_list[i]="N" + QString::number(Vars[VarNames.indexOf(temp)]*multipier);
                    else
                    {
                        break_loop=true;
                        QString postfix_var=InfixToPostfix(Vars_nan[VarNames.indexOf(temp)]);

                        QStringList postfix_list_var=postfix_var.split(" ", QString::SkipEmptyParts);
                        postfix_list.removeAt(i);
                        for (int k=0;k<postfix_list_var.length();++k)
                        {
                            postfix_list.insert(i,postfix_list_var[k]);
                            ++i;
                        }
                    }
                }
            }
            if (!break_loop)
            {//postfix_list[i].at(0)=='N'
                QString Operand_str=postfix_list[i];
                while ((!Stack.isEmpty())&&(Stack.top().at(0)!='O'))
                {
                    if ((Operand_str.at(0)=='N')&&(Stack.top().at(0)=='N')){
                        //calculatable
                        double Operand1=Operand_str.remove(0,1).toDouble();
                        double Operand2=Stack.pop().remove(0,1).toDouble();
                        QString Operator=Stack.pop().remove(0,1);
                        if (Operator=="<")
                        {
                            if (Operand1>Operand2)Operand1=Operand2;
                        }
                        else if (Operator==">")
                        {
                            if (Operand1<Operand2)Operand1=Operand2;
                        }
                        else if (Operator=="+")
                        {
                            Operand1+=Operand2;
                        }
                        else if (Operator=="-")
                        {
                            Operand1-=Operand2;
                        }
                        else if (Operator=="*")
                        {
                            Operand1*=Operand2;
                        }
                        else if (Operator=="/")
                        {
                            Operand1/=Operand2;
                        }
                        else if (Operator=="^")
                        {
                            Operand1=qPow(Operand1,Operand2);
                        }
                        else
                        {
                            QMessageBox messageBox;
                            messageBox.critical(0,"Calculate error","unknown Operator %s",Operator);
                            messageBox.setFixedSize(500,200);
                            return "";
                        }
                        Operand_str="N"+QString::number(Operand1);
                    }
                    else
                    {
                        //Not Calculatable Variables
                        QString temp=Stack.pop();
                        if (Stack.isEmpty())
                        {
                            QMessageBox messageBox;
                            messageBox.critical(0,"Calculate error","something is missing");
                            messageBox.setFixedSize(500,200);
                            return "";
                        }
                        Operand_str="V"+Operand_str.remove(0,1)+Stack.pop().remove(0,1)+temp.remove(0,1);
                    }
                }
                Stack.push(Operand_str);
            }
        }
    }
    QString temp="E0";
    if (!Stack.empty())
        temp=Stack.pop();
//    temp.remove(0,1);
    if (!Stack.empty())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Calculate error","somthing remained on Stack");
        messageBox.setFixedSize(500,200);
    }
    return temp;
}

QList<double> backend::Optimization(QString text,QStringList Paramnames,QList<double> ParamValuesmin,QList<double> ParamValuesmax,QStringList Vars_nan,bool *parameter_valid)
{
    QList<double> ParamValues=ParamValuesmin;
    QList<int> Param_number_extra_condition={};
    QList<int> Param_number_extra_condition_not_availible={};
    QList<int> Param_number_used_variables={};
    QString postfix="";

    //pre optimization
    {
        //check for all Variables with equations if all nessesary variables are availible
        for (int i=0;i<Vars_nan.length();++i)
        {
            if (!Vars_nan[i].isEmpty())
            {
                ParamValues[i]=NAN;
                QString calculatedValue=calculate_intern(InfixToPostfix(Paramnames[i]),Paramnames,ParamValues,Vars_nan);
                if (calculatedValue.at(0)=='V')
                {
                    //some Parameter for condition missing?/can't calculate condition
                    Param_number_extra_condition_not_availible.append(i);
                }
                else
                {
                    //all ok
                    Param_number_extra_condition.append(i);
                }
            }
            else
            {
                //start with all variables at 50%
                ParamValues[i]=(ParamValuesmin[i]+ParamValuesmax[i])/2;
            }
        }

        //create f'(function with penalitys for violate constraints)
        QString newtext=text;
        Paramnames.append("PenalityMultiplier");
        ParamValues.append(PenalityMultiplier);
        ParamValuesmin.append(PenalityMultiplier);
        ParamValuesmax.append(PenalityMultiplier);
        Vars_nan.append("");
        for(int i=0;i<Param_number_extra_condition.length();++i)
        {
            //check if variable has some constrains
            if(!isnan(ParamValuesmin[Param_number_extra_condition[i]])||!isnan(ParamValuesmax[Param_number_extra_condition[i]]))
            {
                newtext+="+PenalityMultiplier*[";
                //new variables needed: MIN_I;MAX_I;Mult(const for all);IS_I=Vars_name[i]
                if(!isnan(ParamValuesmin[Param_number_extra_condition[i]]))
                {
                    //MIN:
                    Paramnames.append("MIN_"+QString::number(i));
                    ParamValues.append(ParamValuesmin[Param_number_extra_condition[i]]);
                    ParamValuesmin.append(ParamValuesmin[Param_number_extra_condition[i]]);
                    ParamValuesmax.append(ParamValuesmin[Param_number_extra_condition[i]]);
                    Vars_nan.append("");
                    newtext+="([MIN_"+QString::number(i)+"<"+Paramnames[Param_number_extra_condition[i]]+"]/MIN_"+QString::number(i)+"-1)^2";
                }

                //check if variable has both constrains
                if(!isnan(ParamValuesmin[Param_number_extra_condition[i]])&&!isnan(ParamValuesmax[Param_number_extra_condition[i]]))
                {
                    newtext+=">";
                }

                if(!isnan(ParamValuesmax[Param_number_extra_condition[i]]))
                {
                    //MAX:
                    Paramnames.append("MAX_"+QString::number(i));
                    ParamValues.append(ParamValuesmax[Param_number_extra_condition[i]]);
                    ParamValuesmin.append(ParamValuesmax[Param_number_extra_condition[i]]);
                    ParamValuesmax.append(ParamValuesmax[Param_number_extra_condition[i]]);
                    Vars_nan.append("");
                    newtext+="([MAX_"+QString::number(i)+">"+Paramnames[Param_number_extra_condition[i]]+"]/MAX_"+QString::number(i)+"-1)^2";
                }

                newtext+="]";

                //  Mult*[([MIN_I<IS_I]/MIN_I-1)^2>([MAX_I>IS_I]/MAX_I-1)^2]
                //=>Mult*max[(min[MIN_I;IS_I]/MIN_I-1)^2;(max[MAX_I;IS_I]/MAX_I-1)^2]
            }
        }

        postfix=InfixToPostfix(newtext);

        //create used variables/defiing Poststring
        QStringList postfix_list=postfix.split(" ", QString::SkipEmptyParts);
        for (int i=postfix_list.length()-1;i>=0;--i)
        {
            if (postfix_list[i].at(0)=='V')
            {
                QString temp=postfix_list[i];
                temp.remove(0,1);
                if (IsOperator(temp.at(0)))
                {
                    temp.remove(0,1);
                }

                //set Variables
                int j=Paramnames.indexOf(temp);
                if (Param_number_extra_condition.contains(j))
                {
                    //replace var_name with var equation
                    QString postfix_var=InfixToPostfix(Vars_nan[j]);

                    QStringList postfix_list_var=postfix_var.split(" ", QString::SkipEmptyParts);
                    postfix_list.removeAt(i);
                    for (int k=0;k<postfix_list_var.length();++k)
                    {
                        postfix_list.insert(i,postfix_list_var[k]);
                        ++i;
                    }
                }
                else if(Param_number_extra_condition_not_availible.contains(j))
                {
                    QMessageBox messageBox;
                    messageBox.critical(0,"Optimizations error","some Parameter missing?");
                    messageBox.setFixedSize(500,200);

                    QList<double> none={};
                    return none;
                }
                else if ((!Param_number_used_variables.contains(j))&&(ParamValuesmin[j]!=ParamValuesmax[j]))
                {
                    //add variable if not in list and changable
                    Param_number_used_variables.append(j);
                }
            }
        }

        //use the calculated full postfix
        postfix=postfix_list.join(" ");

        QString calculatedValue=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan);
        if (calculatedValue.at(0)=='V')
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Optimizations error","something is terrible wrong");
            messageBox.setFixedSize(500,200);

            QList<double> none={};
            return none;
        }
    }

    double bestvalue=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).remove(0,1).toDouble();
    //search Optima

    if (isnan(bestvalue))
    {
        bestvalue=std::numeric_limits<double>::max();
    }

    //simple gradient descent Optimization approach
    double oldbestvalue=bestvalue+1;
/*TODO BETTER STOP CONDITION*/
    while(oldbestvalue!=bestvalue)
    {
        oldbestvalue=bestvalue;
        //determine Gradient
        double grad_base_value=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).remove(0,1).toDouble();
        QList<double> gradient={};
        for(int i=0;i<Param_number_used_variables.length();++i)
        {
            double ParamValueold=ParamValues[Param_number_used_variables[i]];
            double epsylon=ParamValues[Param_number_used_variables[i]]*epsylon_divider;
            if (epsylon<0)epsylon=-epsylon;
            if (epsylon<epsylon_min)epsylon=epsylon_min;
            ParamValues[Param_number_used_variables[i]]+=epsylon;
            double grad_new_value=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).remove(0,1).toDouble();
            ParamValues[Param_number_used_variables[i]]=ParamValueold;
            gradient.append((grad_base_value-grad_new_value)/epsylon);
        }

        bool gradient_is_zero=false;
        while(!gradient_is_zero){
            QList<double> oldparam_values=ParamValues;

            //use gradient/ mutate Parameter
            for(int i=0;i<Param_number_used_variables.length();++i)
            {
                ParamValues[Param_number_used_variables[i]]+=gradient[i];
            }

            //limit values by conditions(constasts)
            for(int i=0;i<Param_number_used_variables.length();++i)
            {
                if (ParamValues[Param_number_used_variables[i]]<ParamValuesmin[Param_number_used_variables[i]])
                {
                    //lower than minimum->=minimum
                    ParamValues[Param_number_used_variables[i]]=ParamValuesmin[Param_number_used_variables[i]];
                }

                if (ParamValues[Param_number_used_variables[i]]>ParamValuesmax[Param_number_used_variables[i]])
                {
                    //bigger than maximum->=maximum
                    ParamValues[Param_number_used_variables[i]]=ParamValuesmax[Param_number_used_variables[i]];
                }
            }

            //check if conditions are ok
            //integrated as penalitys
            /*
            bool conditions_are_ok=true;
            for(int i=0;i<Param_number_extra_condition.length();++i)
            {
                double value_to_check=calculate_intern(InfixToPostfix(Paramnames[Param_number_extra_condition[i]]),Paramnames,ParamValues,Vars_nan).remove(0,1).toDouble();
                if ((value_to_check<ParamValuesmin[Param_number_extra_condition[i]])||(value_to_check>ParamValuesmax[Param_number_extra_condition[i]]))
                {
                    //Check Failed
                    conditions_are_ok=false;
                }
            }

            if (conditions_are_ok)
            */
            {
                //calculate new funktion value
                double calculated_value=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).remove(0,1).toDouble();
                if (bestvalue>calculated_value)
                {
                    bestvalue=calculated_value;
                }
                else
                {
                    ParamValues=oldparam_values;
                    for(int i=0;i<gradient.length();++i)gradient[i]/=2;
                    //gradient to big(jump over) -> try with gradient/2
                }
            }
            gradient_is_zero=true;
            for(int i=0;i<gradient.length();++i)
            {
                double epsylon=ParamValues[Param_number_used_variables[i]]*epsylon_divider;
                if (epsylon<0)epsylon=-epsylon;
                if (epsylon<epsylon_min)epsylon=epsylon_min;
                if ((gradient[i]>=epsylon)||(gradient[i]<=-epsylon))gradient_is_zero=false;
                //if gradient<epsylon for all Variables  => (epsylon is steplength) => gradient=0 => optimum
            }
        }
    }
/*TODO RANDOM RESTARTS*/



    //finalize: return best ParameterValues-> Values who Violate most less(sum of all violations)

    //check if conditions are ok
    bool conditions_are_ok=true;
    for(int i=0;i<Param_number_extra_condition.length();++i)
    {
        double value_to_check=calculate_intern(InfixToPostfix(Paramnames[Param_number_extra_condition[i]]),Paramnames,ParamValues,Vars_nan).remove(0,1).toDouble();
        if ((value_to_check<ParamValuesmin[Param_number_extra_condition[i]])||(value_to_check>ParamValuesmax[Param_number_extra_condition[i]]))
        {
            //Check Failed
            conditions_are_ok=false;
        }
    }
    if (conditions_are_ok)
    {
        *parameter_valid=true;
    }
    else
    {
        *parameter_valid=false;
    }
    return ParamValues;
}

QList<double> backend::Optimization_alternativ(QString text,QStringList Paramnames,QList<double> ParamValuesmin,QList<double> ParamValuesmax,QStringList Vars_nan,bool minimization){
    //check if Optimization possible is
    QList<double> ParamValues=ParamValuesmin;
    //make sting calculateable -> infix to postfix
    QString postfix=InfixToPostfix(text);

    postfix.replace(" +"," ");
    QString calculatedValue=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan);
    if (calculatedValue.at(0)=='V')
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Optimizations error","some Parameter missing?\n\rUse minimal values instead");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        //search Optima
        QList<double> ParamValuesdelta=ParamValuesmin;
        for(int i=0;i<Paramnames.length();++i)
        {
            if (!isnan(ParamValuesmin[i]))
            {
                ParamValues[i]=(ParamValuesmin[i]+ParamValuesmax[i])/2;
                //start with gradient =50%
                ParamValuesdelta[i]=(ParamValues[i]+ParamValuesmin[i])/2;
            }
        }
        double bestvalue=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).remove(0,1).toDouble();

        if (isnan(bestvalue))
        {
            if (minimization)bestvalue=std::numeric_limits<double>::max();
            else bestvalue=0;
        }

        //Hill Climb approach
        double oldbestvalue;
        do {
            oldbestvalue=bestvalue;
            //search best direction
            for(int i=0;i<Paramnames.length();++i)
                //nan cant be optimized(is funktion of other variables)
                if (!isnan(ParamValuesmin[i]))
                {
                    //test with minima
                    double oldvalue=ParamValues[i];
                    ParamValues[i]=ParamValuesmax[i];
                    double tempvalue=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).remove(0,1).toDouble();
                    if (((bestvalue>tempvalue)&&minimization)||((bestvalue<tempvalue)&&!minimization))
                    {
                        bestvalue=tempvalue;
                    }
                    else
                    {
                        ParamValues[i]=oldvalue;
                    }

                    //test with maxima
                    oldvalue=ParamValues[i];
                    ParamValues[i]=ParamValuesmin[i];
                    tempvalue=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).remove(0,1).toDouble();
                    if (((bestvalue>tempvalue)&&minimization)||((bestvalue<tempvalue)&&!minimization))
                    {
                        bestvalue=tempvalue;
                    }
                    else
                    {
                        ParamValues[i]=oldvalue;
                    }

                    //test random value between minima and maxima
                    oldvalue=ParamValues[i];
                    ParamValues[i]=randomnumber(ParamValuesmin[i],ParamValuesmax[i]);
                    tempvalue=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).remove(0,1).toDouble();
                    if (((bestvalue>tempvalue)&&minimization)||((bestvalue<tempvalue)&&!minimization))
                    {
                        bestvalue=tempvalue;
                        QMessageBox messageBox;
                        messageBox.critical(0,"Optimizations MSG","Random is better!!");
                        messageBox.setFixedSize(500,200);
                    }
                    else
                    {
                        ParamValues[i]=oldvalue;
                    }
                }
        }
        while(oldbestvalue!=bestvalue);
    }
    return ParamValues;
}

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
    QPair<QString,double> Values=calculate_intern(postfix,VarNames,Vars,Vars_nan);
    return Values.first.remove(0,1);
}

QPair<QString,double>  backend::calculate_intern(QString text,QStringList VarNames,QList<double> Vars,QStringList Vars_nan)
{
    QStack<QString> Stack;
    QStack<double> Stack_numbers;

    int count_numbers=0;
    QPair<QString,double> error;
    error.first="";
    error.second=NAN;

    QStringList postfix_list=text.split(" ", QString::SkipEmptyParts);
    for (int i=postfix_list.length()-1;i>=0;--i)
    {
        if (postfix_list[i].at(0)=='O')
        {
            Stack.push(postfix_list[i]);
            count_numbers=0;
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
                    {
                        Stack.push("N");
                        count_numbers++;
                        Stack_numbers.push(Vars[VarNames.indexOf(temp)]*multipier);
                    }
                    else
                    {
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
                else {
                    Stack.push(postfix_list[i]);
                    count_numbers++;
                }
            }
            else if (postfix_list[i].at(0)=='N')
            {
                Stack.push("N");
                count_numbers++;
                Stack_numbers.push(postfix_list[i].remove(0,1).toDouble());
            }
            else
            {
                QMessageBox messageBox;
                messageBox.critical(0,"Calculate error","unknown Postfix");
                messageBox.setFixedSize(500,200);
                return error;
            }
            if (count_numbers>1)
            {//2 numbers on top
                double Operand1;
                QString Operand_str;
                Operand_str=Stack.pop();
                if (Operand_str.at(0)=='N')
                {
                    Operand1=Stack_numbers.pop();
                }

                while ((!Stack.isEmpty())&&(Stack.top().at(0)!='O'))
                {
                    if (Operand_str.at(0)=='N' && Stack.top().at(0)=='N'){
                        //calculatable
                        Stack.pop();
                        double Operand2=Stack_numbers.pop();
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
                            messageBox.critical(0,"Calculate error","unknown Operator :"+Operator);
                            messageBox.setFixedSize(500,200);
                            return error;
                        }
                    }
                    else
                    {
                        //Not Calculatable Variables
                        if (Operand_str.at(0)=='N')
                        {
                            Operand_str+=QString::number(Operand1);
                        }
                        QString temp=Stack.pop();
                        if (Stack.isEmpty())
                        {
                            QMessageBox messageBox;
                            messageBox.critical(0,"Calculate error","something is missing");
                            messageBox.setFixedSize(500,200);
                            return error;
                        }
                        Operand_str="V"+Operand_str.remove(0,1)+Stack.pop().remove(0,1)+temp.remove(0,1);
                    }
                }
                Stack.push(Operand_str);
                if (Operand_str.at(0)=='N')
                {
                    Stack_numbers.push(Operand1);
                }
            }
        }
    }
    QString temp="E0";
    if (!Stack.empty())
        temp=Stack.pop();
    double Value=NAN;
    if (temp.at(0)=='N')
    {
        Value=Stack_numbers.pop();
        temp+=QString::number(Value);
    }
    if (!Stack.empty())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Calculate error","somthing remained on Stack");
        messageBox.setFixedSize(500,200);
    }
    QPair<QString,double> returnvalue;
    returnvalue.first=temp;
    returnvalue.second=Value;
    return returnvalue;
}

QList<double> backend::Optimization(QString text,QStringList Paramnames,QList<double> ParamValuesmin,QList<double> ParamValuesmax,QStringList Vars_nan,bool *parameter_valid)
{
    QList<double> ParamValues=ParamValuesmin;
    QList<int> Param_number_extra_condition={};
    QList<int> Param_number_extra_condition_not_availible={};
    QList<int> Param_number_used_variables={};
    QString postfix="";
    QString postfix_conditions="";

    //pre optimization
    {
        //check for all Variables with equations if all nessesary variables are availible
        for (int i=0;i<Vars_nan.length();++i)
        {
            if (!Vars_nan[i].isEmpty())
            {
                ParamValues[i]=NAN;
                QPair<QString,double> calculatedValues=calculate_intern(InfixToPostfix(Paramnames[i]),Paramnames,ParamValues,Vars_nan);
                if (calculatedValues.first.at(0)=='V')
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
        QString newtext;
        for (int second_condition_round=0;second_condition_round<2;++second_condition_round){
            newtext="";
            for(int i=0;i<Param_number_extra_condition.length();++i)
            {
                //check if variable has some constrains
                if(!isnan(ParamValuesmin[Param_number_extra_condition[i]])||!isnan(ParamValuesmax[Param_number_extra_condition[i]]))
                {
                    newtext+="[";
                    //new variables needed: MIN_I;MAX_I;Mult(const for all);IS_I=Vars_name[i]
                    if(!isnan(ParamValuesmin[Param_number_extra_condition[i]]))
                    {
                        //MIN:
                        Paramnames.append("MIN_"+QString::number(i));
                        ParamValues.append(ParamValuesmin[Param_number_extra_condition[i]]);
                        ParamValuesmin.append(ParamValuesmin[Param_number_extra_condition[i]]);
                        ParamValuesmax.append(ParamValuesmin[Param_number_extra_condition[i]]);
                        Vars_nan.append("");
                        newtext+="([0<"+Paramnames[Param_number_extra_condition[i]]+"-MIN_"+QString::number(i)+"]/(MIN_"+QString::number(i)+"+"+QString::number(epsylon_min)+"))^2";
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
                        newtext+="([0>"+Paramnames[Param_number_extra_condition[i]]+"-MAX_"+QString::number(i)+"]/(MAX_"+QString::number(i)+"+"+QString::number(epsylon_min)+"))^2";
                    }

                    newtext+="]+";

                    //  Mult*[([0<IS_I/MIN_I-1])^2>([MAX_I>IS_I]/MAX_I-1)^2]
                    //=>Mult*max[(min[MIN_I;IS_I]/MIN_I-1)^2;(max[MAX_I;IS_I]/MAX_I-1)^2]
                }
            }

            if(!newtext.isEmpty())newtext=newtext.remove(newtext.length()-1,1);

            postfix=InfixToPostfix(text);
            postfix_conditions=InfixToPostfix(newtext);

            //create used variables/defiing Poststring
            QStringList postfix_list=postfix.split(" ", QString::SkipEmptyParts);
            for(int postfix_count=0;postfix_count<2;++postfix_count)
            {
                if (postfix_count==1)postfix_list=postfix_conditions.split(" ", QString::SkipEmptyParts);

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
                        if (Param_number_extra_condition.contains(j)&& !Vars_nan[j].isEmpty())
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
                            Param_number_extra_condition.append(j);
                        }
                    }
                }

                //use the calculated full postfix
                if (postfix_count==0)postfix=postfix_list.join(" ");
                if (postfix_count==1)postfix_conditions=postfix_list.join(" ");
            }
        }

        QPair<QString,double> calculatedValues=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan);
        if (calculatedValues.first.at(0)=='V')
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Optimizations error","something is terrible wrong");
            messageBox.setFixedSize(500,200);

            QList<double> none={};
            return none;
        }
        calculatedValues=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan);
        if (calculatedValues.first.at(0)=='V')
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Optimizations error","something is terrible wrong");
            messageBox.setFixedSize(500,200);

            QList<double> none={};
            return none;
        }
    }

    double bestvalue_base=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).second;
    double bestvalue_condition_error=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan).second;
    if (isnan(bestvalue_base))
    {
        bestvalue_base=std::numeric_limits<double>::max();
    }
    if (isnan(bestvalue_condition_error))
    {
        bestvalue_condition_error=std::numeric_limits<double>::max();
    }

    double PenalityMultiplier=PenalityMultiplier_base;

    double bestvalue=bestvalue_base+bestvalue_condition_error*PenalityMultiplier;
    //search Optima

    //simple gradient descent Optimization approach
    double oldbestvalue=-std::numeric_limits<double>::max();
/*TODO BETTER STOP CONDITION*/
    QList<double> variable_change={};
    QList<double> gradient_sum={};
    QList<double> average_gradient_running={};
    QList<double> average_parameter_running={};
    QList<double> average_gradient_momentum={};
    //QList<double> average_gradient_running_error={};
    for(int i=0;i<Param_number_used_variables.length();++i)
    {
        //initialize variable_change
        variable_change.append(ny);
        //initialize average_gradient_running
        average_gradient_running.append(0);
        average_parameter_running.append(0);
        average_gradient_momentum.append(0);

        //average_gradient_running_error.append(0);
        //initialize gradient_sum
        gradient_sum.append(0);
    }

    int round=0;
    while(round<max_rounds)
    {
        ++round;

        oldbestvalue=bestvalue;
        //determine Gradient
        QList<double> gradient={};
        QList<double> gradient_error={};
        for(int i=0;i<Param_number_used_variables.length();++i)
        {
            double ParamValueold=ParamValues[Param_number_used_variables[i]];
            double epsylon=ParamValues[Param_number_used_variables[i]]*epsylon_divider;
            if (epsylon<0)epsylon=-epsylon;
            if (epsylon<epsylon_min)epsylon=epsylon_min;
            ParamValues[Param_number_used_variables[i]]-=epsylon/2;
            double grad_old_value_base=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).second;
            double grad_old_value_condition=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan).second;
            ParamValues[Param_number_used_variables[i]]+=epsylon;
            double grad_new_value_base=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).second;
            double grad_new_value_condition=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan).second;
            ParamValues[Param_number_used_variables[i]]=ParamValueold;
            gradient.append((grad_old_value_base-grad_new_value_base)/epsylon);
            gradient_error.append((grad_old_value_condition-grad_new_value_condition)/epsylon);
        }

        for(int i=0;i<Param_number_used_variables.length();++i)
        {
            //Variant 1 integreated singel strength
            //gradient_sum[i]=gradient[i]+PenalityMultiplier_base*100*gradient_error[i];
            //Variant 2 integreated dynamic
            gradient_sum[i]=(gradient[i]+pow(PenalityMultiplier_time*round,PenalityMultiplier_time_pot)*gradient_error[i]);

            //Variant 1 normal gradient descent
            //variable_change[i]=variable_change[i]+ny*gradient_sum[i];
            //Variant 2 momentum gradient descent
            //variable_change[i]=ny_momentum*variable_change[i]+ny*gradient_sum[i];
            //Variant 3 Adadelta -ny/RMS(grad)*grad
            /*
            average_gradient_running[i]=ny_momentum*average_gradient_running[i]+(1-ny_momentum)*pow(gradient_sum[i],2);
            average_parameter_running[i]=ny_momentum*average_parameter_running[i]+(1-ny_momentum)*pow(variable_change[i],2);

            //average_gradient_running_error[i]=ny_momentum*average_gradient_running_error[i]+(1-ny_momentum)*pow(gradient_error[i],2);

            double RMS_grad=qSqrt(average_gradient_running[i]+epsylon_min);
            double RMS_para=qSqrt(average_parameter_running[i]+epsylon_min);

            //double RMS_grad_error=qSqrt(average_gradient_running_error[i]+epsylon_min);
            variable_change[i]=RMS_para*gradient_sum[i]/RMS_grad;
            */
            //Variant 4 Adam
            average_gradient_running[i]=ny_momentum*average_gradient_running[i]+(1-ny_momentum)*pow(gradient_sum[i],2);
            average_gradient_momentum[i]=ny_momentum*average_gradient_momentum[i]+(1-ny_momentum)*gradient_sum[i];
            average_parameter_running[i]=ny_momentum*average_parameter_running[i]+(1-ny_momentum)*pow(variable_change[i],2);

            //average_gradient_running_error[i]=ny_momentum*average_gradient_running_error[i]+(1-ny_momentum)*pow(gradient_error[i],2);

            double RMS_momentum=average_gradient_momentum[i]/(1-pow(ny_momentum,round));
            double RMS_grad=average_gradient_running[i]/(1-pow(ny_momentum,round));
            RMS_grad=qSqrt(RMS_grad+epsylon_min);
            double RMS_para=average_parameter_running[i]/(1-pow(ny_momentum,round));
            RMS_para=qSqrt(RMS_para+epsylon_min);

            //double RMS_grad_error=qSqrt(average_gradient_running_error[i]+epsylon_min);
            variable_change[i]=RMS_para*RMS_momentum/RMS_grad;
        }

        bool gradient_is_zero=false;
        while(!gradient_is_zero){
            QList<double> oldparam_values=ParamValues;

            //use gradient/ mutate Parameter
            for(int i=0;i<Param_number_used_variables.length();++i)
            {
                double test=ParamValues[Param_number_used_variables[i]];
                test+=variable_change[i];
                ParamValues[Param_number_used_variables[i]]+=variable_change[i];
            }

            {
                //calculate new funktion value
                double calculated_value_base=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).second;
                double calculated_value_condition_error=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan).second;

                double calculated_value=calculated_value_base+calculated_value_condition_error*PenalityMultiplier;
/*
                if (bestvalue>calculated_value)
                {*/
                    bestvalue_condition_error=calculated_value_condition_error;
                    bestvalue_base=calculated_value_base;
                    bestvalue=calculated_value;
                    break;
                /*}
                else if(bestvalue_condition_error>calculated_value_condition_error)
                {
                    bestvalue_condition_error=calculated_value_condition_error;
                    bestvalue_base=calculated_value_base;

                    PenalityMultiplier*=2;

                    bestvalue=calculated_value_base+calculated_value_condition_error;
                    break;
                }
                else
                {
                    ParamValues=oldparam_values;
                    for(int i=0;i<variable_change.length();++i)variable_change[i]/=2;
                    //variable_change to big(jump over) -> try with variable_change/2
                }*/
            }
            gradient_is_zero=true;
            for(int i=0;i<variable_change.length();++i)
            {
                double epsylon=ParamValues[Param_number_used_variables[i]]*epsylon_divider/1000;
                if (epsylon<0)epsylon=-epsylon;
                if (epsylon<epsylon_min)epsylon=epsylon_min;
                if ((variable_change[i]>=epsylon)||(variable_change[i]<=-epsylon))gradient_is_zero=false;
                //if gradient<epsylon for all Variables  => (epsylon is steplength) => gradient=0 => optimum
            }
        }
    }
/*TODO RANDOM RESTARTS*/



    //finalize: return best ParameterValues-> Values who Violate most less(sum of all violations)

    //check if conditions are ok
    bool conditions_are_ok=false;
    if (calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan).second==0)conditions_are_ok=true;

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

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
    infix.replace(QRegExp("([0-9])e([+-])"),"\\1*10^\\2");
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

QList<double> backend::Optimization(QString text,QStringList Paramnames,QList<double> ParamValuesmin,QList<double> ParamValuesmax,QStringList Vars_nan,double *condition_error)
{
    QList<double> ParamValues=ParamValuesmin;
    QList<int> Param_number_extra_condition={};
    QList<int> Param_number_extra_condition_not_availible={};
    QList<int> Param_number_used_variables={};
    QString postfix="";
    QString postfix_conditions="";

    //pre optimization
    //in funktionparameter
    //out postfix-notations,numberlists
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
            //generate function for constrains
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
                        newtext+="([0<"+Paramnames[Param_number_extra_condition[i]]+"-MIN_"+QString::number(i)+"]/(MIN_"+QString::number(i)+"+"+QString::number(epsylon_div_save)+"))^2";
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
                        newtext+="([0>"+Paramnames[Param_number_extra_condition[i]]+"-MAX_"+QString::number(i)+"]/(MAX_"+QString::number(i)+"+"+QString::number(epsylon_div_save)+"))^2";
                    }

                    newtext+="]+";

                    //  [([0<IS_I/MIN_I-1])^2>([MAX_I>IS_I]/MAX_I-1)^2]
                    //=>max[(min[MIN_I;IS_I]/MIN_I-1)^2;(max[MAX_I;IS_I]/MAX_I-1)^2]
                }
            }

            if(!newtext.isEmpty())newtext=newtext.remove(newtext.length()-1,1);

            postfix=InfixToPostfix(text);
            postfix_conditions=InfixToPostfix(newtext);

            //create used variables/make Postfixstring from infixstring
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

        //check if calculations work without problems
        QPair<QString,double> calculatedValues=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan);
        if (calculatedValues.first.at(0)!='N')
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Optimizations error","something is terrible wrong");
            messageBox.setFixedSize(500,200);

            QList<double> none={};
            return none;
        }
        calculatedValues=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan);
        if (calculatedValues.first.at(0)!='N')
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

    bestvalue_base=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).second;
    bestvalue_condition_error=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan).second;
    QList<double> ParamValues_old=ParamValues;

    //search for Optima
    //use gradient descent Optimization approach
    int round=0;
    //do optimizations while Time is left
    while((round<max_rounds))
    {
        bool gradient_is_zero=false;

        //start 1 optimisation => gain a local optima
        while((round<max_rounds)&&!gradient_is_zero)
        {
            ++round;
            //determine Gradient
            QList<double> gradient={};
            QList<double> gradient_error={};
            double grad_old_value_base=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).second;
            double grad_old_value_condition=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan).second;

            //can be parallelized
            for(int i=0;i<Param_number_used_variables.length();++i)
            {
                //calculate epsylon
                double ParamValueold=ParamValues[Param_number_used_variables[i]];
                double epsylon=ParamValues[Param_number_used_variables[i]]*epsylon_divider;
                if (epsylon<0)epsylon=-epsylon;
                if (epsylon<epsylon_min)epsylon=epsylon_min;

                //calculate points x+/-epsylon/2 for every x in variables
                ParamValues[Param_number_used_variables[i]]-=epsylon/2;
                double grad_low_value_base=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).second;
                double grad_low_value_condition=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan).second;
                ParamValues[Param_number_used_variables[i]]+=epsylon;
                double grad_hight_value_base=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).second;
                double grad_hight_value_condition=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan).second;
                ParamValues[Param_number_used_variables[i]]=ParamValueold;

                //set gradients for every x in variables

                if ((grad_hight_value_base>grad_old_value_base)&&(grad_old_value_base<grad_low_value_base))
                    //lowest point in a epysilon range => gradient is 0
                    gradient.append(0);
                else
                   gradient.append((grad_low_value_base-grad_hight_value_base)/epsylon);

                if ((grad_hight_value_condition>grad_old_value_condition)&&(grad_old_value_condition<grad_low_value_condition))
                    //lowest point in a epysilon range => gradient is 0
                    gradient_error.append(0);
                else
                    gradient_error.append((grad_low_value_condition-grad_hight_value_condition)/epsylon);

                if (isnan(gradient[i])||isnan(gradient_error[i]))
                {
                    //error
                }
                if (isinf(gradient[i])||isinf(gradient_error[i]))
                {
                    //error
                }
            }

            //calculate base Steplength/direction from the 2 gradients
            //can be parallelized
            for(int i=0;i<Param_number_used_variables.length();++i)
            {
                //Variant 1 integreated singel strength
                //gradient_sum[i]=gradient[i]+PenalityMultiplier_base*100*gradient_error[i];
                //Variant 2 integreated dynamic
                //gradient_sum[i]=(gradient[i]+pow(PenalityMultiplier_time*round,PenalityMultiplier_time_pot)*gradient_error[i]);
                //Variant 3 error is always more important then optimum
                gradient_sum[i]=gradient_error[i];
                if  ((gradient_sum[i]<epsylon_min)&&(gradient_error[i]>-epsylon_min)) gradient_sum[i]=gradient[i];

                //Variant 1 normal gradient descent
                //variable_change[i]=variable_change[i]+ny*gradient_sum[i];
                //Variant 2 momentum gradient descent
                //variable_change[i]=ny_momentum*variable_change[i]+ny*gradient_sum[i];
                //Variant 3 Adadelta -ny/RMS(grad)*grad
                /*
                average_gradient_running[i]=ny_momentum*average_gradient_running[i]+(1-ny_momentum)*pow(gradient_sum[i],2);
                average_parameter_running[i]=ny_momentum*average_parameter_running[i]+(1-ny_momentum)*pow(variable_change[i],2);

                //average_gradient_running_error[i]=ny_momentum*average_gradient_running_error[i]+(1-ny_momentum)*pow(gradient_error[i],2);

                double RMS_grad=qSqrt(average_gradient_running[i]+epsylon_div_save);
                double RMS_para=qSqrt(average_parameter_running[i]+epsylon_div_save);

                //double RMS_grad_error=qSqrt(average_gradient_running_error[i]+epsylon_div_save);
                variable_change[i]=RMS_para*gradient_sum[i]/RMS_grad;
                */
                //Variant 4 Adam
                /*
                average_gradient_running[i]=ny_momentum*average_gradient_running[i]+(1-ny_momentum)*pow(gradient_sum[i],2);
                average_gradient_momentum[i]=ny_momentum*average_gradient_momentum[i]+(1-ny_momentum)*gradient_sum[i];
                average_parameter_running[i]=ny_momentum*average_parameter_running[i]+(1-ny_momentum)*pow(variable_change[i],2);

                //average_gradient_running_error[i]=ny_momentum*average_gradient_running_error[i]+(1-ny_momentum)*pow(gradient_error[i],2);

                double RMS_momentum=average_gradient_momentum[i]/(1-pow(ny_momentum,round));
                double RMS_grad=average_gradient_running[i]/(1-pow(ny_momentum,round));
                RMS_grad=qSqrt(RMS_grad+epsylon_div_save);
                double RMS_para=average_parameter_running[i]/(1-pow(ny_momentum,round));
                RMS_para=qSqrt(RMS_para+epsylon_div_save);

                //double RMS_grad_error=qSqrt(average_gradient_running_error[i]+epsylon_div_save);
                variable_change[i]=RMS_para*RMS_momentum/RMS_grad;
                //*/
                //Variant 5 hillclimb gradient descent, Armijo-rule like
                //gradient-> direction of descending
                //->go that direction if ascending you go to far
                //low varianz?
                variable_change[i]=gradient_sum[i];
            }

            //actualize parameter by 1 step
            gradient_is_zero=true;
            //can be parallelized
            for(int var_num=0;var_num<Param_number_used_variables.length();++var_num)
            {
                bool gradient_i_is_zero=false;

                //calculate Armijo lines
                double Armijo_base=gradient[var_num];
                if (Armijo_base<0)Armijo_base=-Armijo_base;
                double Armijo_error=gradient_error[var_num];
                if (Armijo_error<0)Armijo_error=-Armijo_error;
                double Armijo_sum=gradient_sum[var_num];
                if (Armijo_sum<0)Armijo_sum=-Armijo_sum;
                double beta=1;

                bool alpha_ascending=false;
                bool alpha_descending=false;

                double lastvalue_base=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).second;
                double lastvalue_condition_error=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan).second;

                bool sucsess=false;

                while(!sucsess)
                {
                    beta=0;
                    if (beta<beta_min){
                        beta=0;
                        sucsess=true;
                    }
                    double alpha=alpha_start;
                    gradient_i_is_zero=false;
                    //set new Value for Parameter var_num
                    while(!gradient_i_is_zero)
                    {
                        //save old value of the Parameter
                        double oldparam_value=ParamValues[Param_number_used_variables[var_num]];
                        //change Value
                        {
                            //check if new steplength is valid or to small
                            gradient_i_is_zero=true;
                            double epsylon=ParamValues[Param_number_used_variables[var_num]]*epsylon_divider/2;
                            if (epsylon<0)epsylon=-epsylon;
                            if (epsylon<epsylon_min)epsylon=epsylon_min;
                            if (((alpha*variable_change[var_num])>=epsylon)||((alpha*variable_change[var_num])<=-epsylon))gradient_i_is_zero=false;
                            //if gradient<epsylon for Variable  => (epsylon is steplength) => gradient=0 => optimum

                            double change=alpha*variable_change[var_num];
                            //set maximum change for this round
                            if (change>max_variable_change)change=max_variable_change;
                            if (change<-max_variable_change)change=-max_variable_change;
                            ParamValues[Param_number_used_variables[var_num]]+=change;

                            //cut of extrem violations of variables
                            if (ParamValues[Param_number_used_variables[var_num]]<ParamValuesmin[Param_number_used_variables[var_num]]/2)
                            {
                                variable_change[var_num]=-max_variable_change;
                                ParamValues[Param_number_used_variables[var_num]]=ParamValuesmin[Param_number_used_variables[var_num]]/2;
                            }
                            if (ParamValues[Param_number_used_variables[var_num]]>ParamValuesmax[Param_number_used_variables[var_num]]*2)
                            {
                                variable_change[var_num]=+max_variable_change;
                                ParamValues[Param_number_used_variables[var_num]]=ParamValuesmax[Param_number_used_variables[var_num]]*2;
                            }
                        }

                        //calculate new funktion value
                        double calculated_value_base=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).second;
                        double calculated_value_condition_error=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan).second;

                        //Variant 2
                        //double calculated_value=calculated_value_base+calculated_value_condition_error*pow(PenalityMultiplier_time*round,PenalityMultiplier_time_pot);
                        //double lastvalue=lastvalue_base+lastvalue_condition_error*pow(PenalityMultiplier_time*round,PenalityMultiplier_time_pot);
                        //Variant 3
                        double calculated_value=calculated_value_condition_error;
                        double lastvalue=lastvalue_base+lastvalue_condition_error;

                        //Armijo-rule
                        //f(x-t*grad)-f(x)<=-1/2*t*|grad|^2
                        //|grad|^2==abs(grad)
                        //=>f(x+t*x1)<=falt(x)-1/2*t*x1^2
                        //t=1/2^m,m=0,1,2,3,4,... => t1->t2 == x1->x1/2,...

                        //Variant 1/2
        //                if(calculated_value<(lastvalue-0.5*alpha*Armijo_sum))
                        //Variante 3
                        //use better value only if condition error is not worse then bevor
                        if((calculated_value_condition_error<lastvalue_condition_error-beta*alpha*Armijo_error)
                                ||((calculated_value_condition_error==lastvalue_condition_error)&&(calculated_value_base<lastvalue_base-beta*alpha*Armijo_base))
                                //||(gradient_i_is_zero)&&((calculated_value_condition_error<lastvalue_condition_error)
                                //                        ||((calculated_value_condition_error==lastvalue_condition_error)&&(calculated_value_base<lastvalue_base)))
                                )
                        {

                            lastvalue_condition_error=calculated_value_condition_error;
                            lastvalue_base=calculated_value_base;

                            //set ascending/descending of alpha
                            //=>search the biggest possible value for alpha=1/2^m, m in integer
                            if (alpha_descending)
                            {
                                break;
                            }
                            //if change of variable will be bigger than maximum break
                            if (alpha*2*variable_change[var_num]>max_variable_change)
                                break;
                            if (alpha_ascending)
                                //variable change can maybe be bigger, try the double length
                                //at first time dont double alpha, 2nd addition dos this instead
                                alpha*=2;
                            else
                                alpha_ascending=true;
                            gradient_i_is_zero=false;
                        }
                        else
                        {
                            //reset values to latest working version
                            ParamValues[Param_number_used_variables[var_num]]=oldparam_value;

                            //set ascending/descending of alpha
                            //=>search the biggest possible value for alpha=1/2^m, m in integer
                            if (alpha_ascending)
                            {
                                break;
                            }
                            alpha_descending=true;

                            alpha/=2;
                            //variable_change to big(jump over) -> try with the half length
                        }
                    }
                }
                //check if the overallgradient=0
                if (!gradient_i_is_zero)gradient_is_zero=false;
            }
            //for parallelization check if Gradient of all komponents=0
        }

        double lastvalue_base=calculate_intern(postfix,Paramnames,ParamValues,Vars_nan).second;
        double lastvalue_condition_error=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan).second;

        //check if new solution is better than bevor
        if((lastvalue_condition_error<bestvalue_condition_error)
                ||((lastvalue_condition_error==bestvalue_condition_error)&&(lastvalue_base<bestvalue_base)))
        {
            //new Parameter are better
            bestvalue_base=lastvalue_base;
            bestvalue_condition_error=lastvalue_condition_error;
            ParamValues_old=ParamValues;
        }

        //check if time is left
        if (round>=max_rounds)
        {
            //end
            ParamValues=ParamValues_old;
        }
        else
        {
            //next try
            for(int var_num=0;var_num<Param_number_used_variables.length();++var_num)
            {
                //randomize
                ParamValues[Param_number_used_variables[var_num]]=randomnumber(ParamValuesmin[Param_number_used_variables[var_num]],ParamValuesmax[Param_number_used_variables[var_num]]);
            }
        }
    }


    //finalize: return best ParameterValues-> Values who Violate most less(sum of all violations)

    //check if conditions are ok
    *condition_error=calculate_intern(postfix_conditions,Paramnames,ParamValues,Vars_nan).second;

    return ParamValues;
}

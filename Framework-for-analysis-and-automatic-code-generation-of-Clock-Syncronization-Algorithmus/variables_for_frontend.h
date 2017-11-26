#ifndef VARIABLES_FOR_FRONTEND_H
#define VARIABLES_FOR_FRONTEND_H

#include<qstringlist.h>

using namespace std;

//dont change the order new stuff at back
const QStringList Systemparameter_default   ={"Red","Pre","Acc","Msg"};
const QStringList Systemparameter_desc      ={"Redundancy","Precision","Accuracy","messages over Network"};

//dont change the order new stuff in front
const QStringList Algorithms_colum_lables_special={"Optimisations equilation","Parameter"};

//dont change the order new stuff at back
const QStringList Algorithms_colum_lables_db_calculation_needed_default   ={"Redundancy","Precision","Accuracy","Messages"};
const QStringList Algorithms_colum_lables_db_calculation_needed_display   ={"Redundancy","Precision in us","Accuracy in us","Messages"};

//dont change the order insert new stuff at back-1
const QStringList Taxonomie_colum_lables    ={"Items"                       ,"Notifications","Systemparameter"  ,"Type"};
const QStringList Taxonomie_colum_types     ={"TEXT PRIMARY KEY NOT NULL"   ,"TEXT"         ,"TEXT"             ,"TEXT"};

//dont change the order new stuff at back
const QStringList Parameter_colum_lables    ={"SystemParameter"             ,"Description"  ,"Std_min"  ,"Std_max"  ,"Std_equalation"};
const QStringList Parameter_colum_types     ={"TEXT PRIMARY KEY NOT NULL"   ,"TEXT"         ,"TEXT"     ,"TEXT"     ,"TEXT"};

//dont change the order new stuff at back
const QStringList Algorithms_colum_lables_db={"Reference"                   ,"AlgoType" ,"FailuresC" ,"FailuresL" ,"FailuresP" ,"Structure","SyncEventDet"                     ,"RemClockEsti"             ,"ClockCorrect"     ,"SyncType" ,"Redundancy","Precision","Accuracy","Messages"};
const QStringList Algorithms_colum_types    ={"TEXT PRIMARY KEY NOT NULL"   ,"TEXT"     ,"TEXT"      ,"TEXT"      ,"TEXT"      ,"TEXT"     ,"TEXT"                             ,"TEXT"                     ,"TEXT"             ,"TEXT"     ,"TEXT"      ,"TEXT"     ,"TEXT"    ,"TEXT"};

//dont change the order new stuff at back
const QStringList Quarz_colum_lables    ={"Name"                        ,"Frequency","FrequencyStabilityinPPM"  ,"Price"};
const QStringList Quarz_colum_types     ={"TEXT PRIMARY KEY NOT NULL"   ,"TEXT"     ,"TEXT"                     ,"TEXT"};


#endif // VARIABLES_FOR_FRONTEND_H

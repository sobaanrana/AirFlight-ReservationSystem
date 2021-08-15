#include <iostream>
//FA18-BCS-038-B
//Flight Management System
using namespace std;


struct Date{
    int day;
    int month;
    int year;
};

struct Time{
    int hour;
    int min;
};

struct Que_Arrival{
    int flightID;
    int fuel;
    string destination;
    struct Date arrival_date;
    struct Time arrival_time;
    struct Time landing_time;
    struct Time waiting_time;
    int runwayID;
}arr_que[5];

struct Que_Departure{
    int flightID;
    string destination;
    struct Date scheduled_date;
    struct Time scheduled_time;
    struct Date actual_date;
    struct Time actual_time;
    struct Time waiting_time;
    string flight_status;
    int runwayID;
}dep_que[5];

int arr_counter=0, dep_counter=0,size=5;

class Airport{

private :
    int arr_tailF=-1,arr_frontF=-1,arr_runwayF[5],arr_counterF=0,arr_tailS=-1,arr_frontS=-1,arr_runwayS[5],arr_counterS=0,
    dep_tailF=-1,dep_frontF=-1,dep_runwayF[5],dep_counterF=0,dep_tailS=-1,dep_frontS=-1,dep_runwayS[5],dep_counterS=0,
    emergency_flights[5],emergency_counter=0, emergency_tail=-1,emergency_front=-1,
    cancel[5],cancel_counter=0, cancel_tail=-1,cancel_front=-1;

public:

    void  Enqueue_arrivalRunway(int runwayID)
    {
        if(IsFull()==true)
        {
            cout<<"Arrival Runways are Full!"<<endl;
        }
        else
        {
            if(arr_counterF<=arr_counterS)
            {
                arr_runwayF[++arr_tailF]= runwayID;
                arr_counterF++;
            }
            else if(arr_counterF>arr_counterS)
            {
                arr_runwayS[++arr_tailS]=runwayID;
                arr_counterS++;
            }
        }
    }

    void  Enqueue_departureRunway(int runwayID)
    {
        if(IsFull()==true)
        {
            cout<<"Departure Runways are Full!"<<endl;

        }
        else
        {
            if(dep_counterF<=dep_counterS)
            {
                dep_runwayF[++dep_tailF]= runwayID;
                dep_counterF++;

            }
            else if(dep_counterF>dep_counterS)
            {
                dep_runwayS[++dep_tailS]=runwayID;
                dep_counterS++;
            }

        }

    }


   void Priority_emergencyLanding(int id)
   {
       int stack[5],top=-1,rep=0;

       for(int i=0;i<5;i++)
       {
           if(id==arr_que[i].flightID)
           {
               cout<<"Diverting airplane to emergency runway"<<endl;
               while (emergency_tail>=0 && id>emergency_flights[emergency_tail])
               {
                   stack[top++]=emergency_flights[emergency_tail--];
                   emergency_counter--;
               }
               emergency_flights[++emergency_tail]=id;

               emergency_counter++;

               while(top>=0)
               {
                   emergency_flights[emergency_tail++]=stack[top--];
                   emergency_counter++;
               }


           }

           else if(id!=arr_que[i].flightID || id<0)
            {
               rep++;

            }
       }

       if(rep==5)
       {
           cout<<"Flight ID is not valid"<<endl;
       }
   }

   void cancel_flight(int id)
   {
       //is flight id is matched with departure flights ids then that id moves to the canceled flight list and removes from departure list
       int rep=0;
       for(int i=0;i<5;i++)
       {
           if(id==dep_que[i].flightID)
           {
            cancel[cancel_counter++]= dep_que[i].flightID;
            for(int j=i;j<dep_counter;j++) //canceled flight record is removed
            {
                dep_que[j]=dep_que[j+1];
                 dep_counter--;
            }

           }

           else if(id != dep_que[i].flightID || id<0)
            {
                rep++;
            }

       }

       if(rep==5)
       {
           cout<<"Flight ID is not valid"<<endl;
       }


}


   void FuelandTime(Time t,int fuel,int id)
   {
       //fuel per gallons will decrease with respect to time as with more waiting time for a plane, more gallons will decrease
           if(t.hour>=1 && t.hour<=4 && fuel>=30)
            {
                fuel=fuel-10;
                cout<<"Fuel has decreased to "<<fuel<<" gallons"<<" with time"<<endl;
            }
            else if(t.hour>=4 && t.hour<=8 && fuel>=60)
            {
                fuel=fuel-30;
                cout<<"Fuel has decreased to "<<fuel<<" gallons"<<" with time"<<endl;
            }
            else if (fuel<30)
            {
                cout<<"Fuel is not suffient!"<<endl;
                cout<<"Need to land emergency!"<<endl;
                Priority_emergencyLanding(id); //flight ID is sent for emergency landing
            }
    }



    void displayArrRunwayF()
    {
        cout<<"\nRunway ID(s)"<<endl;
        for(int i=0;i<arr_counterF;i++)
        {
            cout<<arr_runwayF[i]<<endl;
        }
    }

    void displayArrRunwayS()
    {
        cout<<"\nRunway ID(s)"<<endl;
        for(int i=0;i<arr_counterS;i++)
        {
            cout<<arr_runwayS[i]<<endl;
        }
    }

      void displayDepRunwayF()
    {
        cout<<"\nRunway ID(s)"<<endl;
        for(int i=0;i<dep_counterF;i++)
        {
            cout<<dep_runwayF[i]<<endl;
        }
    }

    void displayDepRunwayS()
    {
        cout<<"\nRunway ID(s)"<<endl;
        for(int i=0;i<dep_counterS;i++)
        {
            cout<<dep_runwayS[i]<<endl;
        }
    }

    void displayEmergency()
    {

        for(int i=0;i<emergency_counter;i++)
        {
            cout<<"Flight ID :"<<emergency_flights[i]<<endl;
        }
    }


    void displayCancel()
    {

        for(int i=0;i<cancel_counter;i++)
        {
            cout<<"Flight ID :"<<cancel[i]<<endl;
        }
    }


    bool IsFull()
    {
        if(arr_counterF>=size || arr_counterS>=size || dep_counterF>=size || dep_counterS>=size || emergency_counter>=size)
        {
            return true;
        }
        else
        {
            return false;
        }
    }



};

int main()
{

    Airport airplane;


    again:
    cout<<"\nEnter \n 1. Arrival \n 2. Departure \n 3. Emergency Landing \n 4. Cancel Flight \n 5. Reports \n 6. Exit "<<endl;
    int option;
    cin>>option;
   //all checks for ids , date and time are applied
    switch(option)
    {
    case 1:
        {
            if(arr_counter>=size)
            {
                cout<<"Arrival Queue is Full"<<endl;
                break;
            }
            else
            {
                cout<<"Enter details for arrival"<<endl;
                again_flight_id:
                cout<<"Flight ID : "<< endl;
                cin>>arr_que[arr_counter].flightID;
                if(arr_que[arr_counter].flightID<0)
                {
                    cout<<"Wrong! Enter Flight ID again"<<endl;
                    goto again_flight_id;
                }
                cout<<"Fuel(gallons (greater than 30)): "<<endl;
                cin>>arr_que[arr_counter].fuel;
                cout<<"Destination : "<<endl;
                cin>>arr_que[arr_counter].destination;
                again_arrival__date:
                cout<<"Arrival Date (ddmmyy) : "<<endl;
                cin>>arr_que[arr_counter].arrival_date.day;
                cin>>arr_que[arr_counter].arrival_date.month;
                cin>>arr_que[arr_counter].arrival_date.year;
                if(arr_que[arr_counter].arrival_date.day>=32 || arr_que[arr_counter].arrival_date.day<=0 || arr_que[arr_counter].arrival_date.month>=13 || arr_que[arr_counter].arrival_date.month<=0 || arr_que[arr_counter].arrival_date.year<=0)
                {
                    cout<<"Wrong! Please Enter Date again"<<endl;
                    goto again_arrival__date;
                }

                again_arrival_time:
                cout<<"Arrival Time (00:00) : "<<endl;
                cin>>arr_que[arr_counter].arrival_time.hour;
                cin>>arr_que[arr_counter].arrival_time.min;
                if(arr_que[arr_counter].arrival_time.min<0 || arr_que[arr_counter].arrival_time.min>60 || arr_que[arr_counter].arrival_time.hour>24 || arr_que[arr_counter].arrival_time.hour<0)
                {
                    cout<<"Wrong! Please Enter Time again"<<endl;
                    goto again_arrival_time;
                }

                again_landing_time:
                cout<<"Landing Time (00:00): "<<endl;
                cin>>arr_que[arr_counter].landing_time.hour;
                cin>>arr_que[arr_counter].landing_time.min;
                if(arr_que[arr_counter].landing_time.min<0 || arr_que[arr_counter].landing_time.min>60 || arr_que[arr_counter].landing_time.hour>24 || arr_que[arr_counter].landing_time.hour<0)
                {
                    cout<<"Wrong! Please Enter Time again"<<endl;
                    goto again_landing_time;
                }

                again_waiting_time:
                cout<<"Waiting Time (00:00): "<<endl;
                cin>>arr_que[arr_counter].waiting_time.hour;
                cin>>arr_que[arr_counter].waiting_time.min;
                if(arr_que[arr_counter].waiting_time.min<0 || arr_que[arr_counter].waiting_time.min>60 || arr_que[arr_counter].waiting_time.hour>24 || arr_que[arr_counter].waiting_time.hour<0)
                {
                    cout<<"Wrong! Please Enter Time again"<<endl;
                    goto again_waiting_time;
                }

                again_runway_id:
                cout<<"Runway ID : "<<endl;
                cin>>arr_que[arr_counter].runwayID;
                if(arr_que[arr_counter].runwayID<0)
                {
                    cout<<"Wrong! Enter Runway ID again"<<endl;
                    goto again_runway_id;
                }
                //cout<<"Plane with runway ID "<<arr_que[arr_counter].runwayID<<" arriving at runway "<<airplane.Enqueue_arrivalRunway(arr_que[arr_counter].runwayID)<<endl;

                airplane.Enqueue_arrivalRunway(arr_que[arr_counter].runwayID);
                airplane.FuelandTime(arr_que[arr_counter].waiting_time,arr_que[arr_counter].fuel,arr_que[arr_counter].flightID);
                arr_counter++;

                goto again;

                break;

            }

        }

    case 2:
        {
            if(dep_counter>=size)
            {
                cout<<"Departure Queue is Full"<<endl;
                break;

            }
            else
            {
                cout<<"Enter details for departure"<<endl;
                dep_flight_id:
                cout<<"Flight ID : "<<endl;
                cin>>dep_que[dep_counter].flightID;
                if(dep_que[dep_counter].flightID<0)
                {
                    cout<<"Wrong! Enter Flight ID again"<<endl;
                    goto dep_flight_id;
                }
                cout<<"Destination : "<<endl;
                cin>>dep_que[dep_counter].destination;
                dep_sch__date:
                cout<<"Scheduled Date (ddmmyy): "<<endl;
                cin>>dep_que[dep_counter].scheduled_date.day;
                cin>>dep_que[dep_counter].scheduled_date.month;
                cin>>dep_que[dep_counter].scheduled_date.year;
                if(dep_que[dep_counter].scheduled_date.day>=32 || dep_que[dep_counter].scheduled_date.day<=0 || dep_que[dep_counter].scheduled_date.month>=13 || dep_que[dep_counter].scheduled_date.month<=0 || dep_que[dep_counter].scheduled_date.year<=0)
                {
                    cout<<"Wrong! Please Enter Date again"<<endl;
                    goto dep_sch__date;
                }
                dep_sch_time:
                cout<<"Scheduled Time (00:00) "<<endl;
                cin>>dep_que[dep_counter].scheduled_time.hour;
                cin>>dep_que[dep_counter].scheduled_time.min;
                if(dep_que[dep_counter].scheduled_time.min<0 || dep_que[dep_counter].scheduled_time.min>60 || dep_que[dep_counter].scheduled_time.hour>24 || dep_que[dep_counter].scheduled_time.hour<0)
                {
                    cout<<"Wrong! Please Enter Time again"<<endl;
                    goto dep_sch_time;
                }
                dep_actual__date:
                cout<<"Actual Date (ddmmyy): "<<endl;
                cin>>dep_que[dep_counter].actual_date.day;
                cin>>dep_que[dep_counter].actual_date.month;
                cin>>dep_que[dep_counter].actual_date.year;
                if(dep_que[dep_counter].actual_date.day>=32 || dep_que[dep_counter].actual_date.day<=0 || dep_que[dep_counter].actual_date.month>=13 || dep_que[dep_counter].actual_date.month<=0 || dep_que[dep_counter].actual_date.year<=0)
                {
                    cout<<"Wrong! Please Enter Date again"<<endl;
                    goto dep_actual__date;
                }
                dep_actual_time:
                cout<<"Actual Time (00:00): "<<endl;
                cin>>dep_que[dep_counter].actual_time.hour;
                cin>>dep_que[dep_counter].actual_time.min;
                if(dep_que[dep_counter].actual_time.min<0 || dep_que[dep_counter].actual_time.min>60 || dep_que[dep_counter].actual_time.hour>24 || dep_que[dep_counter].actual_time.hour<0)
                {
                    cout<<"Wrong! Please Enter Time again"<<endl;
                    goto dep_actual_time;
                }
                dep_waiting_time:
                cout<<"Waiting Time (00:00): "<<endl;
                cin>>dep_que[dep_counter].waiting_time.hour;
                cin>>dep_que[dep_counter].waiting_time.min;
                if(dep_que[dep_counter].waiting_time.min<0 || dep_que[dep_counter].waiting_time.min>60 || dep_que[dep_counter].waiting_time.hour>24 || dep_que[dep_counter].waiting_time.hour<0)
                {
                    cout<<"Wrong! Please Enter Time again"<<endl;
                    goto dep_waiting_time;
                }
                cout<<"Flight Status : "<<endl;
                cin>>dep_que[dep_counter].flight_status;
                dep_runway_id:
                cout<<"Runway ID : "<<endl;
                cin>>dep_que[dep_counter].runwayID;
                if(dep_que[dep_counter].runwayID<0)
                {
                    cout<<"Wrong! Enter Runway ID again"<<endl;
                    goto dep_runway_id;
                }

                //cout<<"plane with runway ID "<<dep_que[dep_counter].runwayID<<" departing from runway "<<airplane.departureRunway(dep_que[dep_counter].runwayID);
                airplane.Enqueue_departureRunway(dep_que[dep_counter].runwayID);
                dep_counter++;

                goto again;
                break;


            }

        }
    case 3:
        {
            int id; //to get id from user
            cout<<"Enter Flight ID for emergency landing"<<endl;
            cin>>id;
            airplane.Priority_emergencyLanding(id);
            goto again;
            break;

        }

    case 4:
        {
            int id; //to get id from user
            cout<<"Enter Flight ID to cancel Flight"<<endl;
            cin>>id;
            airplane.cancel_flight(id);
            goto again;
            break;
        }
    case 5:
        {
            int o;

            again_reports:

            cout<<"\nPress \n 1. Arrival Report \n 2. Departure Report \n 3. Emergency Landing Report \n 4. Canceled Flight Report \n 5. Exit"<<endl;
            cin>>o;
            if(o==1)
            {
                cout<<"<-----Arrival Report----->"<<endl;
                for(int i=0;i<arr_counter;i++)
                {
                cout<<" \n \t Plane "<<i<<endl;
                cout<<"Flight ID : "<< arr_que[i].flightID<<endl;
                cout<<"Fuel(unit) : "<<arr_que[i].fuel<<endl;
                cout<<"Destination : "<<arr_que[i].destination<<endl;
                cout<<"Arrival Date (ddmmyy): "<<arr_que[i].arrival_date.day<<"/"<<arr_que[i].arrival_date.month<<"/"<<arr_que[i].arrival_date.year<<endl;
                cout<<"Arrival Time (00:00): "<<arr_que[i].arrival_time.hour<<":"<<arr_que[i].arrival_time.min<<endl;
                cout<<"Landing Time (00:00): "<<arr_que[i].landing_time.hour<<":"<<arr_que[i].landing_time.min<<endl;
                cout<<"Waiting Time (00:00): "<<arr_que[i].waiting_time.hour<<":"<<arr_que[i].waiting_time.min<<endl;
                 cout<<"Runway ID : "<<arr_que[i].runwayID<<endl;
                cout<<"\n"<<endl;
                }

                cout<<"-----Plane on First runway-----"<<endl;

                airplane.displayArrRunwayF();

                cout<<"\n-----Plane on Second runway-----"<<endl;

                airplane.displayArrRunwayS();
                goto again_reports;

            }
           else if(o==2)
           {
               cout<<"<-----Departure Report----->"<<endl;

               for(int i=0;i<dep_counter;i++)
               {
                cout<<"\n \t Plane "<<i<<endl;
                cout<<"Flight ID : "<<dep_que[i].flightID<<endl;
                cout<<"Destination : "<<dep_que[i].destination<<endl;
                cout<<"Scheduled Date (ddmmyy): "<<dep_que[i].scheduled_date.day<<"/"<<dep_que[i].scheduled_date.month<<"/"<<dep_que[i].scheduled_date.year<<endl;
                cout<<"Scheduled Time (00:00): "<<dep_que[i].scheduled_time.hour<<":"<<dep_que[i].scheduled_time.min<<endl;
                cout<<"Actual Date(ddmmyy): "<<dep_que[i].actual_date.day<<"/"<<dep_que[i].actual_date.month<<"/"<<dep_que[i].actual_date.year<<endl;
                cout<<"Actual Time (00:00): "<<dep_que[i].actual_time.hour<<":"<<dep_que[i].actual_time.min<<endl;
                cout<<"Waiting Time (00:00): "<<dep_que[i].waiting_time.hour<<":"<<dep_que[i].waiting_time.min<<endl;
                cout<<"Flight Status : "<<dep_que[i].flight_status<<endl;
                cout<<"Runway ID : "<<dep_que[i].runwayID<<endl;

                }
                cout<<"-----Plane on First runway-----"<<endl;

                airplane.displayDepRunwayF();

                cout<<"\n-----Plane on Second runway-----"<<endl;

                airplane.displayDepRunwayS();

                goto again_reports;


           }
           else if(o==3)
           {
               cout<<"<-----Emergency Landing Report----->"<<endl;
               cout<<"List of airplane(s) for emergency landing"<<endl;
               airplane.displayEmergency();
               goto again_reports;
           }

           else if(o==4)
           {
               cout<<"<-----Cancel Flight Report----->"<<endl;
               cout<<"List of Canceled Flights(s)"<<endl;
               airplane.displayCancel();
               goto again_reports;
           }
           else if(o==5)
           {
               exit(0);
           }

           else
           {
               cout<<"Invalid option selected"<<endl;
               goto again_reports;
           }

        }
    case 6:
        {
            exit(0);
        }
    default:
        {
            cout<<"Invalid Option selected"<<endl;
            break;
        }

    }
}

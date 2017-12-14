
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

int monthset[20]={0,31,28,31,30,31,30,31,31,30,31,30,31};

class cal
{
    public:
    void input();
    void outyear();
    void outmonth();
    void outday();
    bool isleap(int year);//判断是否是闰年
    int getday(int year,int month,int day);//获取到目前为止的所有天数
    void print(int year,int month);//输出某一年某一月的月历
};


void cal::input()
{
    int choice;
    bool flag=true;
    while(flag)
    {
        cout<<"请输入查询参数"<<endl;
        cout<<"1:输入年"<<endl;
        cout<<"2:输入年，月"<<endl;
        cout<<"3:输入年，月，日"<<endl;
        cout<<"0:退出"<<endl;
        cin>>choice;
        switch(choice)
        {
            case(1):outyear();
            break;
            case(2):outmonth();
            break;
            case(3):outday();
            break;
            case(0):flag=false;break;
            default:cout<<"输入错误！请重新输入"<<endl;
        }
    }
}

void cal::outyear()
{
    int year;
    int i;
    cout<<"请输入年："<<endl;
    cin>>year;
    if(isleap(year))//如果是闰年的二月
    {
        monthset[2]=29;
    }
    else
    {
        monthset[2]=28;
    }
    cout<<"The calendar of the year "<<year<<endl<<endl;
    for(i=1;i<=12;i++)
    {
        print(year,i);
    }
}

void cal::outmonth()
{
    int year,month;
    cout<<"请输入年："<<endl;
    cin>>year;
    if(isleap(year))//如果是闰年的二月
    {
        monthset[2]=29;
    }
    else
    {
        monthset[2]=28;
    }
    cout<<"请输入月："<<endl;
    cin>>month;
    print(year,month);
}

void cal::outday()
{
    int year,month,day;
    int sumday,weekday;
    cout<<"请输入年："<<endl;
    cin>>year;
    if(isleap(year))//如果是闰年的二月
    {
        monthset[2]=29;
    }
    else
    {
        monthset[2]=28;
    }
    cout<<"请输入月："<<endl;
    cin>>month;
    cout<<"请输入日："<<endl;
    cin>>day;
    cout<<year<<"年"<<month<<"月"<<"日 ";
    sumday=getday(year,month,day);
    weekday=sumday%7;
    switch(weekday)
    {
        case(0):cout<<"星期日";
        break;
        case(1):cout<<"星期一";
        break;
        case(2):cout<<"星期二";
        break;
        case(3):cout<<"星期三";
        break;
        case(4):cout<<"星期四";
        break;
        case(5):cout<<"星期五";
        break;
        case(6):cout<<"星期六";
        break;
    }
    cout<<endl;
}

bool cal::isleap(int year)
{
    if(year%4==0 && year%100!=0 ||(year%400==0))
        return true;
    else return false;
}

int cal::getday(int year,int month,int day)
{
    int i;
    int x=0;
    int yearday=0;
    int monthday=0;
    int sumday=0; //从公元1年1月1日到当前日期的所有天数
    for(i=1;i<year;i++)
    {
        if(isleap(i))//如果有闰年，则该年的天数加一
            x++;
    }
    yearday=x+(year-1)*365;
    for(i=1;i<month;i++)
    {
      monthday+=monthset[i];
    }
    sumday=yearday+monthday+day;
    return sumday;
}

void cal::print(int year,int month)
{
    int sumday=getday(year,month,1);
    int i;
    int weekday=sumday%7;//得到该月一号的星期值

    switch(month)
    {
        case (1):cout<<"Januray 1"<<endl;break;
        case (2):cout<<"February 2"<<endl;break;
        case (3):cout<<"Match 3"<<endl;break;
        case (4):cout<<"April 4"<<endl;break;
        case (5):cout<<"May 5"<<endl;break;
        case (6):cout<<"Juno 6"<<endl;break;
        case (7):cout<<"July 7"<<endl;break;
        case (8):cout<<"August 8"<<endl;break;
        case (9):cout<<"September 9"<<endl;break;
        case (10):cout<<"October 10"<<endl;break;
        case (11):cout<<"November 11"<<endl;break;
        case (12):cout<<"December 12"<<endl;break;
    }

    cout<<"========================================"<<endl;
    cout<<"Sun   Mon   Tue   Wed   Thu   Fri   Sat"<<endl<<endl;
    switch(weekday)
    {
        case(0):cout<<" "<<setw(6)<<setiosflags(ios::left)<<"1";
        break;
        case(1):cout<<"       "<<setw(6)<<setiosflags(ios::left)<<"1";
        break;
        case(2):cout<<"             "<<setw(6)<<setiosflags(ios::left)<<"1";
        break;
        case(3):cout<<"                   "<<setw(6)<<setiosflags(ios::left)<<"1";
        break;
        case(4):cout<<"                         "<<setw(6)<<setiosflags(ios::left)<<"1";
        break;
        case(5):cout<<"                               "<<setw(6)<<setiosflags(ios::left)<<"1";
        break;
        case(6):cout<<"                                     "<<setw(6)<<setiosflags(ios::left)<<"1"<<endl;
        break;
    }
    for(i=2;i<=monthset[month];i++)
    {
        weekday=(weekday++)%7;
        if(weekday==6)
        {
            //cout<<endl;
            cout<<setw(6)<<setiosflags(ios::left)<<i;
            cout<<endl;
        }
        else
            cout<<setw(6)<<setiosflags(ios::left)<<i;
    }
    cout<<endl<<endl;
}

int main()
{
    cal c1;
    c1.input();
    return 0;
}

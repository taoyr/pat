//1、把通话记录逐条保存到容器中，一条通话记录就是一个结构体。考虑到后面要进行删除操作，使用list容器比较好。
//2、把通话时间换成以分为单位的绝对值，把通话记录按时间先后进行排序
//3、把on-line和off-line无法配对的记录删除。如果当前通话是on-line，向后一直寻找同一个人的off-line，如果先找到同一个人的on-line或者一直没找到off-line，则删除当前的on-line；如果当前通话是off-line，直接删除当前的通话记录。
//4、把list容器按姓名的先后顺序进行排序
#pragma warning(disable:4996) //全部关掉
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>

using namespace std;
#define INFINITY 1000000000;
#define LEAST -1000000000;

struct CallRecord{
  string name;
  int month;
  int day;
  int hour;
  int min;
  string call_state;
};

struct CallRecordAbs{
  string name;
  int calltime;
  string call_state;
};

struct node{
  bool operator()(const CallRecordAbs& t1,const CallRecordAbs& t2){
    return t1.calltime<t2.calltime;
  }
};

struct node2{
  bool operator()(const CallRecordAbs& t1,const CallRecordAbs& t2){
    return t1.name<t2.name;
  }
};



class PhoneBill{
public:
  PhoneBill();
  ~PhoneBill();
  const int input();  //返回0表示正确，返回其他表示错误。
  const int timechange();
 // const bool lesstime(const CallRecordAbs& m1,const CallRecordAbs& m2);
  const int output();
  const int deleteuselessrecord();
  const int sortbytime();
 // const bool lessname(const CallRecordAbs& m1,const CallRecordAbs& m2);
  const int sortbyname();
  const double cost(const int,const int) const;  //计算on-line和off-line之间的通话费用
private:
  list<CallRecord> AllCallRecord; //保存所有通话记录
  list<CallRecordAbs> AllCallRecordAbs; //保存把时间改变成绝对值的所有通话记录
  vector<int> Cost; //保存每个时段的通话费用
  int CallNum;  //通话记录的条数
  int month;  //月份
};

PhoneBill::PhoneBill():Cost(24),CallNum(0){
}

PhoneBill::~PhoneBill(){}

const int PhoneBill::input(){
  for(int i=0;i<24;++i){
    scanf("%d",&Cost[i]);
  }
  scanf("%d",&CallNum);
  for(int i=0;i<CallNum;++i){
    //struct CallRecord temp={"",0,0,0,0,""};
    struct CallRecord temp;
    cin>>temp.name;
    scanf("%d",&temp.month);
    month=temp.month;
    char temp_1;
    scanf("%c",&temp_1);
    scanf("%d",&temp.day);
    scanf("%c",&temp_1);
    scanf("%d",&temp.hour);
    scanf("%c",&temp_1);
    scanf("%d",&temp.min);
    cin>>temp.call_state;
    AllCallRecord.push_back(temp);
  }
  return 0;
}

const int PhoneBill::timechange(){
  list<CallRecord>::iterator it=AllCallRecord.begin();
  for(;it!=AllCallRecord.end();++it){
    struct CallRecordAbs temp;
    temp.name=it->name;
    temp.call_state=it->call_state;
    temp.calltime=(it->min)+(it->hour)*60+(it->day)*60*24;
    AllCallRecordAbs.push_back(temp);
  }
  return 0;
}

const int PhoneBill::sortbytime(){
  AllCallRecordAbs.sort(node());
  //sort(AllCallRecordAbs.begin(),AllCallRecordAbs.end(),&PhoneBill::lesstime);
  return 0;
}

const int PhoneBill::deleteuselessrecord(){
  list<CallRecordAbs>::iterator it=AllCallRecordAbs.begin();
  for(;it!=AllCallRecordAbs.end();){
    if(it->call_state=="off-line"){ //当前通话记录是off-line，直接删除当前通话记录
      AllCallRecordAbs.erase(it++);
      continue;
    }
    else{ //当前通话记录是on-line
      list<CallRecordAbs>::iterator it_temp=it;
      ++it_temp;
      if(it_temp==AllCallRecordAbs.end()){  //如果当前通话记录是最后一条，直接删除当前通话记录,并且结束删除无效通话记录的工作
        AllCallRecordAbs.erase(it++);
        break;  
      }
      else{ //如果当前通话记录不是最后一条，往后寻找与当前通话记录匹配的通话记录
        while(1){
          if(it_temp==AllCallRecordAbs.end()){  //如果找到最后，一直没有找到与当前通话记录匹配的记录，则删除当前通话记录
            AllCallRecordAbs.erase(it++);
            break;
          }
          if((it_temp->name==it->name)&&(it_temp->call_state==it->call_state)){ //找到名字相同的，但是也是on-line的，删除当前通话记录
            AllCallRecordAbs.erase(it++);
            break;
          }
          else if((it_temp->name==it->name)&&(it_temp->call_state!=it->call_state)){  //找到名字相同的，而且状态是off-line的
            ++it;
            AllCallRecordAbs.insert(it,*it_temp); //在it指向的元素前插入元素
            if(it_temp==it){  //如果两条匹配的通话记录刚好是相邻的
              AllCallRecordAbs.erase(it++);
              break;
            }
            else{ //匹配的两条通话记录不相邻
              AllCallRecordAbs.erase(it_temp++);  //删除多出来的同一条通话记录
              break;
            }
          }
          else{ //名字不相同的情况下
  //          else{ //如果不是最后一条通话记录，接着往后找匹配的通话记录
              ++it_temp;
              continue;
          }
        }
      }
    }
  }
  return 0;
}

const int PhoneBill::sortbyname(){
  AllCallRecordAbs.sort(node2());
  return 0;
}

const int PhoneBill::output(){
  string name_temp="";
  list<CallRecordAbs>::iterator it=AllCallRecordAbs.begin();
  for(;it!=AllCallRecordAbs.end();){
    if(it->name!=name_temp){  //新的一个用户开始了
      cout<<it->name<<" ";
      printf("%02d\n",month);
      int day,hour,min; //先输出该用户的一条记录
      int day_r;
      int calltime_1,calltime_2;
      int begin_min,end_min,distance_min;
      calltime_1=it->calltime;
      day=it->calltime/1440;
      day_r=it->calltime%1440;
      hour=day_r/60;
      min=day_r%60;
      printf("%02d%c%02d%c%02d%c",day,':',hour,':',min,' ');
      begin_min=it->calltime;
      ++it;
      end_min=it->calltime;
      distance_min=end_min-begin_min;
      calltime_2=it->calltime;
      day=it->calltime/1440;
      day_r=it->calltime%1440;
      hour=day_r/60;
      min=day_r%60;
      printf("%02d%c%02d%c%02d%c",day,':',hour,':',min,' ');
      printf("%d ",distance_min);
      double Cost_temp=cost(calltime_1,calltime_2);
      double Cost_total=0;
      Cost_total=Cost_temp;
      printf("%c%0.2lf\n",'$',Cost_total/100);
      name_temp=it->name;
      ++it;
      if(it==AllCallRecordAbs.end()){ //如果最后一条记录已经输出，结束输出
        printf("%s","Total amount: ");
        printf("%c%0.2lf\n",'$',Cost_total/100);
        break;
      }
      while(name_temp==it->name){ //如果该用户有多条记录，输出该用户的其他记录
        calltime_1=it->calltime;
        day=it->calltime/1440;
        day_r=it->calltime%1440;
        hour=day_r/60;
        min=day_r%60;
        begin_min=it->calltime;
        printf("%02d%c%02d%c%02d%c",day,':',hour,':',min,' ');
        ++it;
        end_min=it->calltime;
        distance_min=end_min-begin_min;
        calltime_2=it->calltime;
        day=it->calltime/1440;
        day_r=it->calltime%1440;
        hour=day_r/60;
        min=day_r%60;
        printf("%02d%c%02d%c%02d%c",day,':',hour,':',min,' ');
        printf("%d ",distance_min);
        Cost_temp=cost(calltime_1,calltime_2);
        Cost_total=(Cost_total+Cost_temp);
        printf("%c%0.2lf\n",'$',Cost_temp/100); 
        ++it;
      }
      printf("%s","Total amount: ");
      printf("%c%0.2lf\n",'$',Cost_total/100);
    }
  }
  return 0;
}

const double PhoneBill::cost(const int time_1,const int time_2) const{
  //先算出两个时间是否是在同一天的，同一个小时内
  int day_1,hour_1,min_1; 
  int day_r_1;
  day_1=time_1/1440;
  day_r_1=time_1%1440;
  hour_1=day_r_1/60;
  min_1=day_r_1%60;
  int day_2,hour_2,min_2;
  int day_r_2;
  day_2=time_2/1440;
  day_r_2=time_2%1440;
  hour_2=day_r_2/60;
  min_2=day_r_2%60;
  double sum=0;
  if((day_1==day_2)&&(hour_1==hour_2)){ //如果是同一天的同一个小时内
    int calltime=time_2-time_1;
    return calltime*Cost[hour_1];
  }
  else if(day_1==day_2){  //如果是同一天的不同小时
    sum=(60-min_1)*Cost[hour_1]+min_2*Cost[hour_2];
    for(int i=hour_1+1;i<hour_2;++i){
      sum=sum+60*Cost[i];
    }
    return sum;
  }
  else{ //如果不是同一天
    sum=(60-min_1)*Cost[hour_1]+min_2*Cost[hour_2];
    for(int i=hour_1+1;i<24;++i){
      sum=sum+60*Cost[i];
    }
    for(int i=0;i<hour_2;++i){
      sum=sum+60*Cost[i];
    }
    double Cost_temp=0;
    for(int j=0;j<24;++j){
      Cost_temp=Cost_temp+Cost[j];
    }
    for(int i=day_1+1;i<day_2;++i){
      sum=sum+Cost_temp*60;
    }
    return sum;
  }
}

int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  PhoneBill a;
  a.input();
  a.timechange();
  a.sortbytime();
  a.deleteuselessrecord();
  a.sortbyname();
  a.output();
  return 0;
}





  


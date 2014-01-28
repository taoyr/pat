//1����ͨ����¼�������浽�����У�һ��ͨ����¼����һ���ṹ�塣���ǵ�����Ҫ����ɾ��������ʹ��list�����ȽϺá�
//2����ͨ��ʱ�任���Է�Ϊ��λ�ľ���ֵ����ͨ����¼��ʱ���Ⱥ��������
//3����on-line��off-line�޷���Եļ�¼ɾ���������ǰͨ����on-line�����һֱѰ��ͬһ���˵�off-line��������ҵ�ͬһ���˵�on-line����һֱû�ҵ�off-line����ɾ����ǰ��on-line�������ǰͨ����off-line��ֱ��ɾ����ǰ��ͨ����¼��
//4����list�������������Ⱥ�˳���������
#pragma warning(disable:4996) //ȫ���ص�
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
  const int input();  //����0��ʾ��ȷ������������ʾ����
  const int timechange();
 // const bool lesstime(const CallRecordAbs& m1,const CallRecordAbs& m2);
  const int output();
  const int deleteuselessrecord();
  const int sortbytime();
 // const bool lessname(const CallRecordAbs& m1,const CallRecordAbs& m2);
  const int sortbyname();
  const double cost(const int,const int) const;  //����on-line��off-line֮���ͨ������
private:
  list<CallRecord> AllCallRecord; //��������ͨ����¼
  list<CallRecordAbs> AllCallRecordAbs; //�����ʱ��ı�ɾ���ֵ������ͨ����¼
  vector<int> Cost; //����ÿ��ʱ�ε�ͨ������
  int CallNum;  //ͨ����¼������
  int month;  //�·�
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
    if(it->call_state=="off-line"){ //��ǰͨ����¼��off-line��ֱ��ɾ����ǰͨ����¼
      AllCallRecordAbs.erase(it++);
      continue;
    }
    else{ //��ǰͨ����¼��on-line
      list<CallRecordAbs>::iterator it_temp=it;
      ++it_temp;
      if(it_temp==AllCallRecordAbs.end()){  //�����ǰͨ����¼�����һ����ֱ��ɾ����ǰͨ����¼,���ҽ���ɾ����Чͨ����¼�Ĺ���
        AllCallRecordAbs.erase(it++);
        break;  
      }
      else{ //�����ǰͨ����¼�������һ��������Ѱ���뵱ǰͨ����¼ƥ���ͨ����¼
        while(1){
          if(it_temp==AllCallRecordAbs.end()){  //����ҵ����һֱû���ҵ��뵱ǰͨ����¼ƥ��ļ�¼����ɾ����ǰͨ����¼
            AllCallRecordAbs.erase(it++);
            break;
          }
          if((it_temp->name==it->name)&&(it_temp->call_state==it->call_state)){ //�ҵ�������ͬ�ģ�����Ҳ��on-line�ģ�ɾ����ǰͨ����¼
            AllCallRecordAbs.erase(it++);
            break;
          }
          else if((it_temp->name==it->name)&&(it_temp->call_state!=it->call_state)){  //�ҵ�������ͬ�ģ�����״̬��off-line��
            ++it;
            AllCallRecordAbs.insert(it,*it_temp); //��itָ���Ԫ��ǰ����Ԫ��
            if(it_temp==it){  //�������ƥ���ͨ����¼�պ������ڵ�
              AllCallRecordAbs.erase(it++);
              break;
            }
            else{ //ƥ�������ͨ����¼������
              AllCallRecordAbs.erase(it_temp++);  //ɾ���������ͬһ��ͨ����¼
              break;
            }
          }
          else{ //���ֲ���ͬ�������
  //          else{ //����������һ��ͨ����¼������������ƥ���ͨ����¼
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
    if(it->name!=name_temp){  //�µ�һ���û���ʼ��
      cout<<it->name<<" ";
      printf("%02d\n",month);
      int day,hour,min; //��������û���һ����¼
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
      if(it==AllCallRecordAbs.end()){ //������һ����¼�Ѿ�������������
        printf("%s","Total amount: ");
        printf("%c%0.2lf\n",'$',Cost_total/100);
        break;
      }
      while(name_temp==it->name){ //������û��ж�����¼��������û���������¼
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
  //���������ʱ���Ƿ�����ͬһ��ģ�ͬһ��Сʱ��
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
  if((day_1==day_2)&&(hour_1==hour_2)){ //�����ͬһ���ͬһ��Сʱ��
    int calltime=time_2-time_1;
    return calltime*Cost[hour_1];
  }
  else if(day_1==day_2){  //�����ͬһ��Ĳ�ͬСʱ
    sum=(60-min_1)*Cost[hour_1]+min_2*Cost[hour_2];
    for(int i=hour_1+1;i<hour_2;++i){
      sum=sum+60*Cost[i];
    }
    return sum;
  }
  else{ //�������ͬһ��
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





  


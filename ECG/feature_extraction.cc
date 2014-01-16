#include "feature_extraction.h"

namespace ECG{

feature_extraction::feature_extraction(){
  collect_num=0;
}

feature_extraction::~feature_extraction(){
}

void feature_extraction::StoreOneBeat(){
  //跳过1万个点，在心跳稳定的部分采点
  //找出幅值最大的点，将其一半的值作为阈值
  //fantasia每个样本点的时间间隔为0.004s，如果心跳1s跳一次，则R-R之间的点数大约为250个
  //mghdb每个样本点的时间间隔为0.003s，R-R之间的点数大约为333个
  //在一个人的心电图上采集到5个心跳
  FILE *fp;
  fp=freopen("input.txt","r",stdin);
  float voltage=0;  //心电幅值
  std::list<float> feature_vector_temp; //暂时存储特征向量，若采样点数符合要求，则保存到feature_vector中
  for(int i=0;i<10000;++i){ //跳过一万个点
    scanf("%f",&voltage);
  }
  float voltage_biggest=-1000;  //最大的电压值
  for(int i=0;i<10000;++i){ //在10001个点和20000个点之间找出最大电压值
    scanf("%f",&voltage);
    if(voltage>voltage_biggest){
      voltage_biggest=voltage;
    }
  }
  fclose(fp);
  fp=freopen("input.txt","r",stdin);
  for(int i=0;i<10000;++i){ //跳过一万个点
    scanf("%f",&voltage);
  }
  float threshold;  //判断R波的阈值，为最大电压值的一半
  threshold=voltage_biggest/2;
  while(scanf("%f",&voltage)!=0){ //找出5个特征向量
    if(collect_num>=5){
      break;
    }
    if(voltage>threshold){  //找到第一个R波
      for(int i=0;i<100;++i){ //找到R波以后，先保存100个采样点，再找第二个R波
        scanf("%f",&voltage);
        feature_vector_temp.push_back(voltage);
      }
      while(scanf("%f",&voltage)!=0){ //找第二个R波
        feature_vector_temp.push_back(voltage);
        if(voltage>threshold){  //找到了第二个R波
          if((feature_vector_temp.size()>200)&&(feature_vector_temp.size()<300)){ //如果点数符合要求,拷贝到另一个容器中
            std::list<float>::iterator it=feature_vector_temp.begin();
            for(;it!=feature_vector_temp.end();++it){
              feature_vector.push_back(*it);
            }
            feature_vector.push_back(-1000);
            collect_num=collect_num+1;
            break;
          }
          else{ //如果点数不符合要求，从当前点开始重新找第一个R波
            feature_vector_temp.clear();
            break;
          }
        }
        else{ //没找到第二个R波
          continue;
        }
      }
    }
  }
  fclose(fp);
}

void feature_extraction::FormVector(){
  freopen("output.txt","w",stdout);
  std::vector<float> feature_vector_temp; //用于存储一个心跳的心电图的样本点
  std::list<float>::iterator it=feature_vector.begin();
  for(;it!=feature_vector.end();++it){
    std::list<float>::iterator it_temp=it;
    for(;*it_temp!=-1000;++it_temp){  
      feature_vector_temp.push_back(*it_temp);
    }
    it=it_temp; //让迭代器跳过-1000，找下一个向量
    //取出一个向量后，对向量重新采点，形成长度为50的向量，保存到文件中
    float interval; //间隔，为原始样本点个数除以50
    float length_temp=0;
    int length=0; //所要采的点离容器起始处的距离
    interval=feature_vector_temp.size()/50;
    std::list<float> feature_vector_final;  //用于存储长度为50的特征向量
    std::vector<float>::iterator it_vector=feature_vector_temp.begin();
    for(;it_vector!=feature_vector_temp.end();){
      if(feature_vector_final.size()>=50){
        break;
      }
      length_temp=length_temp+interval;
      length=(length_temp*10)/10;  //取整
      it_vector=feature_vector_temp.begin()+length;
      feature_vector_final.push_back(*it_vector);
    }
    //存满50个点后，把特征向量保存到output.txt中
    for(it_temp=feature_vector_final.begin();it_temp!=feature_vector_final.end();++it_temp){
      std::cout<<*it_temp<<" ";
    }
    std::cout<<"\n";
  }
}

}
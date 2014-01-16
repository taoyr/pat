#ifndef FEATURE_EXTRACTION_H
#define FEATURE_EXTRACTION_H
#include<string>
#include<vector>
#include<list>
#include <algorithm>
#include <iostream>
#include <cstdio>

namespace ECG{

class feature_extraction{
//using std::vector;
//using std::string;
//using std::list;
public:
  feature_extraction();
  ~feature_extraction();
	void StoreOneBeat();  //存储5个完整心跳
	void FormVector();  //把5个特征向量保存到一个文件中
private:
  std::list<float> feature_vector;  //特征向量,这个list保存5个特征向量，每个特征向量之间用-1000标志位隔开
  int collect_num;  //采集到特征向量的个数
};

}	//namespace ECG
#endif

//��ͨ����¼�������浽�����У�һ��ͨ����¼����һ���ṹ�塣
//��ͨ����¼��ʱ���Ⱥ�������򣬰�on-line��off-line�޷���Եļ�¼ɾ����
//����ͨ����¼��ʹ�ýṹ�壬���ݽṹ�б����û��������û��������е�ͨ����¼��ʹ��vector����ָ���һ���ṹ���ָ�롣
//���Կ���ʹ�ù�ϣ���γɽṹ�����飬Ȼ���û���ӳ�䵽�����±ꡣ

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
#define INFINIT 1000000000;
#define LEAST -1000000000;

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

}

class PhoneBill{
public:
	PhoneBill();
	~PhoneBill();
	int SortByTime();
private:
	struct CallRecord{
		string name;
		vector<int> call_time;
		string call_state;
	};


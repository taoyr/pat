//把通话记录逐条保存到容器中，一条通话记录就是一个结构体。
//把通话记录按时间先后进行排序，把on-line和off-line无法配对的记录删除。
//遍历通话记录，使用结构体，数据结构中保存用户名，该用户名的所有的通话记录（使用vector），指向后一个结构体的指针。
//可以考虑使用哈希，形成结构体数组，然后用户名映射到数组下标。

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


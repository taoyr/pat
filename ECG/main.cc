#include "feature_extraction.h"

using namespace ECG;

int main(){
  feature_extraction a;
  a.StoreOneBeat();
  a.FormVector();
  return 0;
}


#include <iostream>
#include <cstdint>
#include <algorithm>

struct restrict {
  int32_t lb;
  int32_t rb;
  int32_t minTreeCount;
  int32_t count;
  
};
bool rcomp(restrict a, restrict b) {
  if(a.lb<b.lb) return true;
  else if(a.lb==b.lb) {
    if(a.rb<b.rb) return true;
    else return false;
  }
  else return false;
}
bool comp(int32_t a, int32_t b) {
  return a<b;
}

int32_t findIndex(int32_t tree, int32_t *trees, int32_t l) {
  int32_t lp = 0, rp = l-1;
  while(rp>lp) {
    if(tree>trees[(lp+rp)/2]) {lp=((lp+rp)/2)+1; if(lp>l-1) lp = l-1;}
    else if(tree<trees[(lp+rp)/2]) {rp=((lp+rp)/2)-1; if(rp<0) rp = 0;}
    else return (lp+rp)/2;
  }
  return lp;
}

int main() {
  uint8_t T;
  std::cin>>T;
  uint32_t r[T];
  for(uint8_t z=0;z<T;++z) {
    int32_t n, k, c=0;
    std::cin>>n>>k;
    int32_t trees[n];
    restrict rests[k];
    for(int32_t i = 0; i<n; ++i) std::cin>>trees[i];
    for(int32_t i = 0; i<k; ++i) std::cin>>rests[i].lb>>rests[i].rb>>rests[i].minTreeCount;
    std::sort(rests,rests+k, rcomp);
    std::sort(trees, trees+n, comp);
    for(uint32_t i = 0; i<n; ++i) std::cout << trees[i] << std::endl;
    for(int32_t i = 0; i<k; ++i) {
      int32_t s=findIndex(rests[i].lb, trees, n), e=findIndex(rests[i].rb, trees, n);
      rests[i].count = (trees[e]==rests[i].rb?e+1:e)-(trees[s]<rests[i].lb?s-1:s);
    }
    for(uint32_t i = 0; i<k; ++i) std::cout << rests[i].lb << " " << rests[i].rb << " " << rests[i].minTreeCount << " " << rests[i].count << std::endl;
    for(int32_t i = 0; i<n; ++i) {
      

    }
  }
  return 0;
}

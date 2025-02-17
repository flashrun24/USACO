#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <bitset>

struct point {
  int64_t x;
  int64_t y;
  point() {
    this->x = 0;
    this->y = 0;
  }
  point(int64_t x, int64_t y) {
    this->x = x;
    this->y = y;
  }
  bool operator==(const point& o) const {
    return x == o.x && y == o.y;
  }
};

std::hash<std::bitset<64>> h;

template<>
struct std::hash<point> {
  std::size_t operator()(const point &p) const {
    std::size_t a = hash<std::bitset<64>>()(std::bitset<64>(p.x*13+p.y));
    return ((int32_t)(a>>32))^((int32_t)a);
    //return std::hash<std::bitset<64>>()(std::bitset<64>(p.x*13+p.y));
    //return std::hash<std::bitset<128>>()((std::bitset<128>(p.x)<<64)|std::bitset<128>(p.y));
  }
};

int32_t s, e, n, k, xe, ye;
std::pair<int32_t, int32_t> sMoves[20], eMoves[20];
std::unordered_map<point, uint64_t> sPointMap[21];
std::unordered_map<point, uint64_t> ePointMap[21];
int main() {
  for(auto &m : ePointMap) m.reserve(100003);
  for(auto &m : sPointMap) m.reserve(100003);
  std::cin>>n>>xe>>ye;
  uint64_t result[n+1];
  for(uint64_t& i : result) i=0;
  s=(n>>1)+(n&1);
  e=n>>1;
  for(int32_t i = 0; i<s; ++i) std::cin>>sMoves[i].first>>sMoves[i].second;
  for(int32_t i = 0; i<e; ++i) std::cin>>eMoves[i].first>>eMoves[i].second;
  sPointMap[0][{0,0}]=1;
  ePointMap[0][{xe,ye}]=1;
  for(int32_t i = 1; i<1<<s; ++i) {
    int64_t x=0, y=0;
    for(int32_t j = 0; j<s; ++j) if((1<<j)&i) {
      x+=sMoves[j].first;
      y+=sMoves[j].second;
    }
    sPointMap[__builtin_popcount(i)][{x,y}]++;
  }
  for(int32_t i = 1; i<1<<e; ++i) {
    int64_t x=xe, y=ye;
    for(int32_t j = 0; j<e; ++j) if((1<<j)&i) {
      x-=eMoves[j].first;
      y-=eMoves[j].second;
    }
    ePointMap[__builtin_popcount(i)][{x,y}]++;
  }
  for(int32_t i = 0; i<=s;++i)
    for(int32_t j = 0; j<=e; ++j) for(const auto&[p,c] : sPointMap[i]) if(ePointMap[j].find(p)!=ePointMap[j].end()) result[i+j]+=c*ePointMap[j][p];
  for(int32_t i = 1; i<n+1; ++i) std::cout << result[i] << std::endl;
  return 0;
}

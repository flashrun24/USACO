#include <iostream>
#include <cstdint>
#include <vector>

int main() {
  uint32_t c, n;
  std::cin>>c>>n;
  uint32_t a[n], dist[1<<c];
  for(uint32_t i = 0; i<(1<<c); ++i) dist[i]=19;
  for(uint32_t i = 0; i<n; ++i) {
    std::string s;
    std::cin>>s;
    a[i]=0;
    for(uint8_t j = 0; j<c; ++j) if(s[j]=='G') a[i]|=1<<(c-(j+1));
    dist[a[i]]=0;
  }
  for(uint32_t i = 0; i<c; ++i) {
    for(uint32_t j = 0; j<(1<<c); ++j) dist[j]=dist[j]<1+(dist[j^(1<<i)])?dist[j]:1+(dist[j^(1<<i)]);
  }
  for(uint32_t i = 0; i<n; ++i) std::cout << c-dist[(~a[i])&((1<<(c))-1)] << std::endl;
  return 0;
}
// bfs way
#include <iostream>
#include <bitset>
#include <cstdint>
#include <queue>
#include <unordered_map>
#include <vector>

#define N 18

std::unordered_map<std::bitset<N>, uint32_t> nodes;
std::queue<std::bitset<N>> nQueue;

void bfs(uint32_t c) {
  for(uint32_t i = 0; i<(1<<c); ++i) {
    if(nodes[i] == 0)
    nQueue.push(i);
  }
  while(!nQueue.empty()) {
    std::bitset<N> cNode = nQueue.front();
    uint32_t cNodeDist = nodes[cNode];
    for(uint32_t i = 0; i<N; ++i) {
      cNode.flip(i);
      if(nodes[cNode]==N) {
	nQueue.push(cNode);
        nodes[cNode] = cNodeDist+1;
      }
     cNode.flip(i);
    }
    nQueue.pop();
  }
}

int mainn() {
  uint32_t c, n;
  std::cin>>c>>n;
  std::vector<std::bitset<N>> src;
  for(uint32_t i = 0; i<(1<<c); ++i) nodes[i]=N;
  for(uint32_t i = 0; i<n; ++i) {
    std::string s;
    std::cin>>s;
    std::bitset<N> sb;
    for(uint8_t j = 0; j<c; ++j) if(s[j]=='G') sb.set(j);
    nodes[sb]=0;
    src.emplace_back(sb);
  }
  bfs(c);
  for(auto k : src) {
    std::cout << (c-nodes[(~k).to_ulong()&((1<<c)-1)]) << std::endl;
  }
  return 0;
}

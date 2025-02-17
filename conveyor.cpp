#include <iostream>
#include <cstdint>

struct node {
  bool usable{false};
  char d{'?'};
};

struct query {
  int16_t i;
  int16_t j;
};

uint16_t n;
uint32_t q;
int32_t usableCount = 0;
node matrix[1000][1000];

bool isUsable(int16_t i, int16_t j) {
  switch(matrix[i][j].d) {
    case 'L':
      return j==0 || matrix[i][j-1].usable;
    case 'R':
      return j==n-1 || matrix[i][j+1].usable;
    case 'U':
      return i==0 || matrix[i-1][j].usable;
    case 'D':
      return i==n-1 || matrix[i+1][j].usable;
    case '?':
      return i==n-1 || matrix[i+1][j].usable || i==0 || matrix[i-1][j].usable || j==n-1 || matrix[i][j+1].usable || j==0 || matrix[i][j-1].usable;
  }
}

void bfs(int16_t i, int16_t j) {
  if(!matrix[i][j].usable&&i<n&&j<n&&j>=0&&i>=0) if(isUsable(i,j)) {
    matrix[i][j].usable=true; ++usableCount;
    bfs(i+1,j);
    bfs(i-1,j);
    bfs(i,j+1);
    bfs(i,j-1);
  }
}

// i row j col
int main() {
  std::cin >> n >> q;
  query queries[q];
  uint32_t answers[q];
  // Take input
  for(uint32_t k = 0; k<q; ++k) {
    char dir;
    std::cin >> queries[k].i >> queries[k].j >> dir;
    queries[k].i=queries[k].i-1;
    queries[k].j=queries[k].j-1;
    matrix[queries[k].i][queries[k].j].d=dir;
  }
  // Do the N squared computation of the final state
  for(int16_t i = 0; i<n; ++i) {
    for(int16_t j = 0; j<n; ++j) {
      bfs(i,j);
    }
  }
  // Get answers one by one
  for(int32_t k = q-1; k>=0; --k) {
    answers[k]=(n*n)-usableCount;
    matrix[queries[k].i][queries[k].j].d='?';
    bfs(queries[k].i,queries[k].j);
  }
  for(uint32_t i : answers) std::cout << i << "\n";
  return 0;
}

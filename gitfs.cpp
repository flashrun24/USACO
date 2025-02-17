#include <iostream>
#include <cstdint>

#define GINF 300000

typedef uint32_t T;

T n, preferenceDist[500][500], cowPref[500][500], assignments[500];//, prev[500][500];

//void pathSwp(T u, T v) {
//  while() {
//
//    v=prev[u][v];
//  }
//}

void warshall() {
  for(T k = 0; k<n; ++k) for(T i = 0; i<n; ++i) {
    for(T j = 0; j<n; ++j) if(preferenceDist[i][j]>preferenceDist[i][k]+preferenceDist[k][j]) {
      preferenceDist[i][j]=preferenceDist[i][k]+preferenceDist[k][j];
    }
  }
}

int main() {
  // Number of cows to be stored on n
  std::cin>>n;
  // Read the cow preference ;ist and null out all preferences that are lower than cow number (becasue cow i is assigned gift i initially)
  for(T i=0;i<n;++i) {
    bool f = true;
    assignments[i]=i;
    for(T j=0;j<n;++j) {
      T tmp;
      std::cin>>tmp;
      cowPref[i][j]=tmp;
      if(f)// {
	preferenceDist[i][tmp-1] = 1;
	//prev[i][tmp-1] = i;
      //}
      else preferenceDist[i][tmp-1] = GINF;
      if(tmp-1==assignments[i]) f = false;
    }
  }
  // According to Wikipedia 
  for(T i = 0; i < n; ++i) {
    preferenceDist[i][i]=GINF;
    //prev[i][i] = i;
  }
  //for(T i = 0; i<n; ++i) for(T j = 0; j<n; ++j) prev[i][j]=preferenceDist[i][j]!=GINF?i:n; 
  // Run Warshall and also figure out the prev matrix
  warshall();

  // after running Warshall, the preferenceDist[j][i] means if cow j has a path to gift i and the value is sum of preferences
  // The amazing loop below converts all large numbers to 0 when 0 means no cycles between i<->j
  for(T i = 0; i<n; ++i) for(T j = 0; j<n; ++j) if(preferenceDist[j][i]==0||preferenceDist[j][i]==GINF||preferenceDist[i][j]==GINF)
     preferenceDist[i][j]=0;

  // Print the cycle matrix
  for(T i = 0; i<n; ++i) {
    for(T j = 0; j<n; ++j) {
      if(preferenceDist[i][cowPref[i][j]-1]!=0||cowPref[i][j]==i+1) {
	std::cout << cowPref[i][j];
	break;
      }
    }
    std::cout << std::endl;
  }
  // the f'ing algorithm is trying to reuse the assignments array in-place. So we need to make sure we are not assigning a gift to a cow twice since we will visit each loop k times with k identified as the number of members in that loop. assignments[i]==i meant to identify the first time we are preocessing this loop
  //for(T i = 0; i<n; ++i) if(assignments[i]==i&&preferenceDist[i][i]!=GINF) {
  //  std::cout << "swapped\n";
  //  pathSwp(i,i);
  //}
  
  //for(T i = 0; i<n; ++i) std::cout << 1+assignments[i] << std::endl;
  return 0;
}
// 4 7 3 6 5 8 2 1



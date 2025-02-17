#include <iostream>
#include <cstdint>
#include <algorithm>


int main() {
  int32_t t;
  std::cin >> t;
  for(int32_t z = 0; z<t; ++z) {
    int32_t n,m;
    std::cin >> n >> m;
    int32_t a[n];
    for(int32_t i = 0; i<n; ++i) {
      std::cin >> a[i];
      a[i]=(a[i]%m)>m>>1?(a[i]%m)-m:a[i]%m;
    }
    std::sort(a, a+n);
    int32_t x = a[(n>>1)];
    int32_t s = 0;
    for(int32_t i = 0; i<n; ++i) {
      a[i]=a[i]-x;
      a[i]=(std::abs(a[i])%m)>m>>1?(a[i]%m)-m:a[i]%m;
      s+=std::abs(a[i]);
    }
    std::cout << s << std::endl;
  }
  return 0;
}

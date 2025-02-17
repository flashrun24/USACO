#include <iostream>
#include <cstdint>
#include <algorithm>

int64_t cowsChecked = 0;
int64_t preCompCheck = 0;

int main() {
  int32_t n;
  std::cin >> n;
  int32_t a[n], b[n];
  int8_t c[n];
  for(int32_t i = 0; i<n; ++i) std::cin >> a[i];
  for(int32_t i = 0; i<n; ++i) std::cin >> b[i];
  for(int32_t i = 0; i<n; ++i) { // pre comp
    c[i]=(a[i]==b[i]);
    preCompCheck+=c[i];
  }
  for(int32_t i = 0; i<n; ++i) { // left side
    for(int32_t j = 0; j<=i>>1; ++j) {
      int8_t o = (c[j])+(c[i-j]); // original diff
      int8_t n = (a[j]==b[i-j])+(a[i-j]==b[j]); // swap diff
      int8_t delta = n-o; // change in checked
      cowsChecked+=preCompCheck + (delta * (j+1)); // number of checked + this time and all the sets its used in
    }
  }
  std::reverse(a, a+n);
  std::reverse(b, b+n);
  std::reverse(c, c+n);
  for(int32_t i = 0; i<n-1; ++i) { // left side
    for(int32_t j = 0; j<=i>>1; ++j) {
      int8_t o = (c[j])+(c[i-j]); // original diff
      int8_t n = (a[j]==b[i-j])+(a[i-j]==b[j]); // swap diff
      int8_t delta = n-o; // change in checked
      cowsChecked+=preCompCheck + (delta * (j+1)); // number of checked + this time and all the sets its used in
    }
  }
//  for(int32_t i = n-1; i>=0; --i) { // right side
//    for(int32_t j = i; j<=(n-1)>>1; ++j) {
//      int8_t o = (a[n-1-j]==b[n-1-j])+(a[i-(n-1-j)]==b[i-(n-1-j)]); // original diff
//      int8_t n = (a[n-1-j]==b[i-(n-1-j)])+(a[i-(n-1-j)]==b[n-1-j]); // swap diff
//      int8_t delta = n-o; // change in checked
//      cowsChecked+=preCompCheck + (delta * (j+1)); // number of checked + this time and all the sets its used in
//    }
//  }
  std::cout << cowsChecked;
  return 0;
}

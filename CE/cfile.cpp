#include <iostream>
int gcd(int x, int y){ 
int res;
if((x) < (y)){
return gcd(y, x);
};
if((y) == (0)){
return x;
};
res = (y) - ((x) / (y));
return gcd(y, res);
};
int main(){ 
int x;
int y;
std::cin >> x;
std::cin >> y;
std::cout << gcd(x, y) << std::endl;
return 0;
};


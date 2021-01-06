#include <iostream>
#include<vector>
#include <algorithm>
#include<cmath>
#include<numeric>
#include<boost/range/adaptor/indexed.hpp>
#include <boost/range/irange.hpp>

template<typename T, typename U>
auto map(T&& container, U&& lambda){
      std::vector<decltype(lambda(*container.begin()))> w;
      std::transform(container.begin(),container.end(),std::back_inserter(w), lambda);
      return w;
}

template<typename T, typename U>
auto zip(T&& container1, T&& container2, U&& lambda){
      std::vector<decltype(lambda(*container1.begin(), *container2.begin()))> w;
      std::transform(container1.begin(),container1.end(),container2.begin(), std::back_inserter(w), lambda);
      return w;
}

template<typename T>
auto sum(T&& t) {
  return std::accumulate(t.begin(), t.end(), 0.0);
}
int main() {
  std::vector<double> a = {-79.0, 
                    409.0, 
                    -21697.0, 
                    -67877.0, 
                    88163.0, 
                    -1029115.0, 
                    4562068069.0, 
                    -2884823503.0, 
                    1191723787.0, 
                    -1580287133.0, 
                    1391865319.0, 
                    -170471681.0, 
                    10908.0      } ;
  std::vector<double> b = {31933440.0, 
                    3193344.0, 
                    14515200.0, 
                    1451520.0, 
                    46080.0, 
                    32256.0, 
                    14515200.0, 
                    1451520.0, 
                    145152.0, 
                    72576.0, 
                    39600.0, 
                    5544.0, 
                    1.0  };

  auto f = [&a, &b](int i) {
    return std::round(sum(map(zip(a, b, [](const auto& aa, const auto& bb){
                    return std::make_pair(aa, bb);
    }) | boost::adaptors::indexed(0), [i](auto j) {
      return (j.value().first * std::pow(i, 12.0 - j.index())) / j.value().second;
    })));
  };
  
  for(auto i: boost::irange(1, 14)) {
    std::cout << char(f(i) + 32);
  }

  return 0;
}
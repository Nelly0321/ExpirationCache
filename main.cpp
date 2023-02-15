#include <iostream>
#include "Cache.hpp"
using namespace std;

int main(){
    Cache<int, int> cache;
    int x = 5;
    int y = 2;
    cache.insert(x, 25);
    cache.insert(y, 20);
    if(cache.find(x).has_value()){
        cout << cache.find(x).value() << endl;
    }
    if(cache.find(y).has_value()){
        cout << cache.find(y).value() << endl;
    }
    for(int i =0; i<1000; i++){
        cache.insert(i, i*i);
    }

    for(int i =1000; i<100000; i++){
        cache.insert(i, i*i);
    }
    if(cache.find(y).has_value()){
        cout << cache.find(y).value() << endl;
    }else{
        cout << "Not found!" << endl;
    }
    if(cache.find(100000).has_value()){
        cout << cache.find(y).value() << endl;
    }else{
        cout << "Not found!" << endl;
    }

    return 0;
}

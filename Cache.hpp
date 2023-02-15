#pragma once
#include <iostream>
#include <shared_mutex>
#include <unordered_map>
#include <thread>
#include <optional>
#include <chrono>
using namespace std;



template <typename T1, typename T2>
class Cache{
public:
 Cache():
 _alive(true),
 _workerThread([this](){
      while(_alive){
         arrange();
         this_thread::sleep_for(1ms);
      }
   })
 {}

 ~Cache(){
    _data1.clear();
    _data2.clear();
    _alive = false;
    _workerThread.join();
 }
 void insert(T1 key, T2 value){
    if(!_data1.contains(key) && !_data2.contains(key)){
         unique_lock l(_lock);
         _data1[key] = value;
    }
 }
 optional<T2> find(T1 key){
   shared_lock l(_lock);
   if(_data1.contains(key)){
      return _data1[key];
   }
   if(_data2.contains(key)){
      return _data2[key];
   }
   return optional<T2>();
 }
private:
 void arrange(){
   unique_lock l(_lock);
   if(_data1.size() >= 100){
      cerr << "Here!" << endl;
      _data2.clear();
      _data2 = _data1;
      _data1.clear();
   }
   
 }
private:
 unordered_map<T1, T2> _data1;
 unordered_map<T1, T2> _data2;
 thread _workerThread;
 bool _alive;
 shared_mutex _lock;
};



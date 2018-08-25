# shine serial 媲美protobuf的强大序列化/反序列化工具
![](https://i.imgur.com/A78rQ4O.png)

[![Open Source Love](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://github.com/ellerbrock/open-source-badge/)
[![stable](http://badges.github.io/stability-badges/dist/stable.svg)](http://github.com/badges/stability-badges)[![Build Status](https://travis-ci.com/shineframe/shine_serial.svg?branch=master)](https://travis-ci.com/shineframe/shineframe)

## 一、简述 ## 
shine serial 媲美protobuf的强大序列化/反序列化工具

支持c++原生对象的序列化与反序列化，是网络自定义协议格式应用的开发利器。

shine serial编解效率均高于google protobuf,提供与protobuf相似的序列化特性，如：数值压缩编码，类似于varint,序列化后体积极小(小于protobuf)。serial支持协议向前向后兼容（新版本的model能够解码旧版本的字节流，旧版本的model也能够解码新版本的字节流），同时serial支持比protobuf更丰富强大的数据类型，基本的数据类型及主要STL标准容器类型字段均可进行序列化(vector, deque, list, forward_list, map, unordered_map, set, unordered_set)，支持结构嵌套（注:嵌套的结构体一定也要以SHINE_SERIAL_MODEL宏修饰，否则不支持，编译不通过）

github：[https://github.com/shineframe/shine_serial](https://github.com/shineframe/shine_serial)

技术交流群：805424758

![](https://i.imgur.com/dHd7VJZ.png)




### shine_serial使用示例（一行代码实现c++原生对象的序列化与反序列化）： ###

	#include <iostream>
	#include "shine_serial.hpp"

	struct B
	{
	    int a;
	    double b;
	    std::string c;
	    //将类型名称及需要序列化的字段用SHINE_SERIAL包裹
	    SHINE_SERIAL(B, a, b, c);
	};
	
	struct A{
	    int a;
	    double b;
	    std::string c;
	
	    //此处嵌套上方的结构体B
	    std::map<int, B> d;
	
	    std::list<int> e;
	    std::vector<float> f;
	    std::deque<double> g;
	    std::forward_list<long> h;
	    std::set<std::string> i;
	
	    SHINE_SERIAL(A, a, b, c, d, e, f, g, h, i);
	};
	
	int main(){
	
	    A a;
	    a.a = 123;
	    a.b = 345.567;
	    a.c = "hello world!";
	
	    B b;
	
	    b.a = 666;
	    b.b = 777.7777;
	    b.c = "999999!";
	
	    a.d.emplace(999, b);
	
	    a.e.emplace_back(123);
	    a.e.emplace_back(345);
	
	    a.f.emplace_back((float)12.34);
	    a.f.emplace_back((float)45.67);
	
	    a.g.emplace_back((double)456.789);
	    a.g.emplace_back((double)78.9);
	
	    a.h.emplace_front(666);
	    a.h.emplace_front(555);
	
	    a.i.emplace("A");
	    a.i.emplace("B");
	    a.i.emplace("C");
	
	    //将对象a序列化成字节流
	    auto data = a.shine_serial_encode();
	
	    //将字节流反序列化成对象，反序列化后a2与a中数据相同
	    A a2;
	    a2.shine_serial_decode(data);
	
        //确定结果
	    std::cout << ((a == a2) ? "success" : "failed") << std::endl;
	
	    return 0;
	}


执行后输出:success


## shine_serial与google protocol buffer性能对比 ##

**场景如下：**

**模型定义：**一个公司下有10个部门，每个部门又有10个员工，员工有名称，年龄，性别三个字段，将公司对应的model序列化/反序列化各100万次，观察耗时及包体字节体积

**测试结果：**

| 循环1000次 | google protobuf | shine serial | 胜出|
| ------ | ------ | ------ | ----- |
| 序列化总耗时 | 43 ms | 24 ms |shine serial |
| 反序列化总耗时 | 41 ms | 15 ms | shine serial|
| 序列化后字节总体积 |1286000 byte| 878000 byte | shine serial|
|反序列化错误数|0|0|持平|

| 循环10,000次 | google protobuf | shine serial | 胜出|
| ------ | ------ | ------ | ----- |
| 序列化总耗时 | 466 ms | 226 ms |shine serial |
| 反序列化总耗时 | 432 ms | 154 ms | shine serial|
| 序列化后字节总体积 |12860000 byte| 8780000 byte | shine serial|
|反序列化错误数|0|0|持平|

| 循环1,000,000次 | google protobuf | shine serial | 胜出|
| ------ | ------ | ------ | ----- |
| 序列化总耗时 | 42649 ms | 21178 ms |shine serial |
| 反序列化总耗时 | 39029 ms | 14513 ms | shine serial|
| 序列化后字节总体积 |1286000000 byte| 878000000 byte | shine serial|
|反序列化错误数|0|0|持平|

### protobuf idl及测试代码 ###

model.proto

	message employee{
		optional string name = 1;//员工名称
		optional int32 age = 2;//年龄
		optional bool sex = 3;//性别
	}
	
	message department{
		optional string name = 1;//部门名称
		repeated employee employees = 2;//部门员工列表
	}
	
	message company{
		optional string name = 1;//公司名
		repeated department departments = 2;//公司部门列表
	}

测试代码:

	#include <iostream>
	#include <chrono>
	#include "pb/model.pb.h"
	
	unsigned long long get_timestamp()
	{
	    auto now = std::chrono::high_resolution_clock::now();
	    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	}
	
	void build_model(::company &L1){
	    const std::string name = "name";
	    const int age = 20;
	    const bool sex = true;
	
	    L1.set_name(name);
	    for (int m = 0; m < 10; m++)
	    {
	        ::department *L2 = L1.add_departments();
	        L2->set_name(name);
	
	        for (int n = 0; n < 10; n++)
	        {
	            ::employee *L3 = L2->add_employees();
	            L3->set_name(name);
	            L3->set_age(age);
	            L3->set_sex(sex);
	        }
	    }
	}
	
	int main(){
	    ::company L1;
	    ::company clone;
	    build_model(L1);
	
	    std::string data;
	
	    for (;;)
	    {
	       unsigned int count = 0;
	        std::cout << "input loop count : ";
	        std::cin >> count;
	       unsigned int error = 0;
	       unsigned long long total_data_size = 0;
	
	       unsigned long long encode_begin = get_timestamp();
	       for (unsigned int i = 0; i < count; i++)
	        {
	            data = L1.SerializeAsString();
	            total_data_size += data.size();
	        }
	       unsigned long long encode_end = get_timestamp();
	
	
	       unsigned long long decode_begin = get_timestamp();
	       for (unsigned int i = 0; i < count; i++)
	        {
	            if (!clone.ParseFromString(data))
	            {
	                error++;
	            }
	        }
	       unsigned long long decode_end = get_timestamp();
	
	       std::cout << "google protobuf result : " << (L1.SerializeAsString() == clone.SerializeAsString()) << std::endl;
	       std::cout << "google protobuf encode total data size : " << total_data_size << std::endl;
	       std::cout << "google protobuf encode cost : " << encode_end - encode_begin << " ms" << std::endl;
	       std::cout << "google protobuf decode cost : " << decode_end - decode_begin << " ms, error : " << error << std::endl << std::endl;
	    }
	
	    return 0;
	}
	

### shine serial测试代码 ###

idl文件:不需要

测试代码:

	#include <iostream>
	#include "shine_serial.hpp"
		
	struct employee{
	    std::string name;//员工名称
	    int32 age;//年龄
	    bool sex;//性别
	    SHINE_SERIAL(employee, name, age, sex);
	}
	
	struct department{
	    std::string name;//部门名称
	    std::vector<employee> employees;//部门员工列表
	    SHINE_SERIAL(department, name, employees);
	}
	
	struct company{
	    std::string name;//公司名
	    std::vector<department> departments;//公司部门列表
	    SHINE_SERIAL(company, name, departments);
	}
	
	unsigned long long get_timestamp()
	{
	    auto now = std::chrono::high_resolution_clock::now();
	    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	}
	
	void build_model(::company &L1){
	    const std::string name = "name";
	    const int age = 20;
	    const bool sex = true;
	
	    L1.name = name;
	    L1.departments.resize(10);
	    for (int m = 0; m < 10; m++)
	    {
	        ::department &L2 = L1.departments[m];
	        L2.name = name;
	        L2.employees.resize(10);
	
	        for (int n = 0; n < 10; n++)
	        {
	            ::employee &L3 = L2.employees[n];
	            L3.name = name;
	            L3.age = age;
	            L3.sex = sex;
	        }
	    }
	}
		
	int main(){
	    ::company L1;
	    ::company clone;
	    build_model(L1);
	
	    std::string data;
	
	    for (;;)
	    {
	        unsigned int count = 0;
	        std::cout << "input loop count : ";
	        std::cin >> count;
	        unsigned int error = 0;
	        unsigned long long total_data_size = 0;
	
	        unsigned long long encode_begin = get_timestamp();
	        for (unsigned int i = 0; i < count; i++)
	        {
	            data = L1.shine_serial_encode();
	            total_data_size += data.size();
	        }
	        unsigned long long encode_end = get_timestamp();
	
	        unsigned long long decode_begin = get_timestamp();
	        for (unsigned int i = 0; i < count; i++)
	        {
	            if (!clone.shine_serial_decode(data))
	            {
	                error++;
	            }
	        }
	        unsigned long long decode_end = get_timestamp();
	
	
	        std::cout << "shine serial result : " << (L1.serial_encode() == clone.serial_encode()) << std::endl;
	        std::cout << "shine serial encode total data size : " << total_data_size << std::endl;
	        std::cout << "shine serial encode cost : " << encode_end - encode_begin << " ms" << std::endl;
	        std::cout << "shine serial decode cost : " << decode_end - decode_begin << " ms, error : " << error << std::endl << std::endl;
	    }
	
	    return 0;
	}


	

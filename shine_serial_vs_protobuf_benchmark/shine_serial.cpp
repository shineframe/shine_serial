#include <iostream>
#include <chrono>
#include "shine_serial.hpp"

using namespace shine;

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


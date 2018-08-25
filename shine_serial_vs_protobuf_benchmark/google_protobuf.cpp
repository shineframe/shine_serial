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

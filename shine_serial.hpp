 /**
 *****************************************************************************
 *
 *@note shine serial序列化库 https://github.com/shineframe/shine_serial
 *
 *@file shine_serial.hpp
 *
 *@brief 序列化库 -- shine serial
 *
 *使用SHINE_SERIAL宏，只需要一行代码即可完成C++对象序列化/反序列化操作
 *
 *@todo 
 *
 *@author sunjian 39215174@qq.com
 *
 *@version 1.0
 *
 *@date 2018/6/14 
 *****************************************************************************
 */

#pragma once
#include <string>
#include <cassert>
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <vector>
#include <memory>
#include <functional>
#include <type_traits>
#include <ctype.h>
#include <stdlib.h>
#include <initializer_list>

#if (defined WIN32)
#pragma warning(disable:4146)
#endif

#define SHINE_SERIAL_MARCO_EXPAND(...) __VA_ARGS__
#define SHINE_SERIAL_MAKE_ARG_LIST_1(op, arg, ...)   op(arg)
#define SHINE_SERIAL_MAKE_ARG_LIST_2(op, arg, ...)   op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_1(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_3(op, arg, ...)   op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_2(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_4(op, arg, ...)   op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_3(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_5(op, arg, ...)   op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_4(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_6(op, arg, ...)   op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_5(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_7(op, arg, ...)   op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_6(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_8(op, arg, ...)   op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_7(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_9(op, arg, ...)   op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_8(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_10(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_9(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_11(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_10(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_12(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_11(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_13(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_12(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_14(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_13(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_15(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_14(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_16(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_15(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_17(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_16(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_18(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_17(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_19(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_18(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_20(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_19(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_21(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_20(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_22(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_21(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_23(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_22(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_24(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_23(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_25(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_24(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_26(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_25(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_27(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_26(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_28(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_27(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_29(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_28(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_30(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_29(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_31(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_30(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_32(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_31(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_33(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_32(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_34(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_33(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_35(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_34(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_36(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_35(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_37(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_36(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_38(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_37(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_39(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_38(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_40(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_39(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_41(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_40(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_42(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_41(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_43(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_42(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_44(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_43(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_45(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_44(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_46(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_45(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_47(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_46(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_48(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_47(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_49(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_48(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_50(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_49(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_51(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_50(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_52(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_51(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_53(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_52(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_54(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_53(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_55(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_54(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_56(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_55(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_57(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_56(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_58(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_57(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_59(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_58(op, __VA_ARGS__))
#define SHINE_SERIAL_MAKE_ARG_LIST_60(op, arg, ...)  op(arg) SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_MAKE_ARG_LIST_59(op, __VA_ARGS__))

#define SHINE_SERIAL_MARCO_EXPAND_WARP(...) SHINE_SERIAL_MARCO_EXPAND(__VA_ARGS__)

#define SHINE_SERIAL_MACRO_CONCAT(A, B)  A##_##B

#define SHINE_SERIAL_MAKE_ARG_LIST(N, op, arg, ...) \
    SHINE_SERIAL_MACRO_CONCAT(SHINE_SERIAL_MAKE_ARG_LIST, N)(op, arg, __VA_ARGS__)

#define SHINE_SERIAL_RSEQ_N() \
    119, 118, 117, 116, 115, 114, 113, 112, 111, 110, \
    109, 108, 107, 106, 105, 104, 103, 102, 101, 100, \
    99, 98, 97, 96, 95, 94, 93, 92, 91, 90, \
    89, 88, 87, 86, 85, 84, 83, 82, 81, 80, \
    79, 78, 77, 76, 75, 74, 73, 72, 71, 70, \
    69, 68, 67, 66, 65, 64, 63, 62, 61, 60, \
    59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
    49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
    39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
    29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
    19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
    9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define SHINE_SERIAL_ARG_N( \
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
    _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
    _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
    _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
    _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, \
    _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, \
    _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, \
    _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, \
    _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, \
    _111, _112, _113, _114, _115, _116, _117, _118, _119, N, ...) N

#define SHINE_SERIAL_GET_ARG_COUNT_INNER(...)    SHINE_SERIAL_MARCO_EXPAND(SHINE_SERIAL_ARG_N(__VA_ARGS__))
#define SHINE_SERIAL_GET_ARG_COUNT(...)          SHINE_SERIAL_GET_ARG_COUNT_INNER(__VA_ARGS__, SHINE_SERIAL_RSEQ_N())


#define SHINE_SERIAL_GEN_ENCODE_FUNC(N, ...) \
    SHINE_SERIAL_MARCO_EXPAND_WARP(SHINE_SERIAL_MAKE_ARG_LIST(N, SHINE_SERIAL_ENCODE_FIELD, __VA_ARGS__))

#define SHINE_SERIAL_GEN_DECODE_FUNC(N, ...) \
    SHINE_SERIAL_MARCO_EXPAND_WARP(SHINE_SERIAL_MAKE_ARG_LIST(N, SHINE_SERIAL_DECODE_FIELD, __VA_ARGS__))

#define SHINE_SERIAL_GEN_COMPARE_FUNC(N, ...) \
    SHINE_SERIAL_MARCO_EXPAND_WARP(SHINE_SERIAL_MAKE_ARG_LIST(N, SHINE_SERIAL_COMPARE_FIELD, __VA_ARGS__))

#define SHINE_SERIAL_ENCODE(...) SHINE_SERIAL_GEN_ENCODE_FUNC(SHINE_SERIAL_GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define SHINE_SERIAL_DECODE(...) SHINE_SERIAL_GEN_DECODE_FUNC(SHINE_SERIAL_GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define SHINE_SERIAL_COMPARE(...) SHINE_SERIAL_GEN_COMPARE_FUNC(SHINE_SERIAL_GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)


#define SHINE_SERIAL_ENCODE_FIELD(field)\
{\
    shine_serial_encode_field(this->field, ret);\
}

#define SHINE_SERIAL_DECODE_FIELD(field) \
{\
        if (!shine_serial_decode_field(this->field, data, len, cost_len)) return false;\
        if (cost_len - flag >= size) return true; \
}

#define SHINE_SERIAL_COMPARE_FIELD(field) \
{\
    if (!(a.field == b.field)) return false;\
}

#define SHINE_SERIAL(TYPE, ...) \
    public:\
TYPE(){}\
~TYPE(){}\
inline std::string shine_serial_encode() const{\
    std::string ret;\
    ret.reserve(1024);\
    shine_serial_encode(ret);\
    return std::move(ret);\
}\
inline void shine_serial_encode(std::string &ret) const{\
    std::size_t old_size_flag = ret.size();\
    SHINE_SERIAL_ENCODE(__VA_ARGS__); \
    shine_serial_encode_size(ret.size() - old_size_flag, ret, false, old_size_flag); \
    }\
    \
    inline bool shine_serial_decode(const std::string &data){\
        std::size_t cost_len = 0;\
        return shine_serial_decode(data.data(), data.size(), cost_len);\
    } \
    inline bool shine_serial_decode(const char *data, const std::size_t len){\
        std::size_t cost_len = 0;\
        return shine_serial_decode(data, len, cost_len);\
    } \
    \
    inline bool shine_serial_decode(const char *data, const std::size_t len, std::size_t &cost_len){\
        if (len - cost_len == 0) return true;\
        std::size_t size = 0; \
        if (!shine_serial_decode_size(size, data, len, cost_len)) return false; \
        if (size == 0) return true;\
        std::size_t flag = cost_len;\
        if (len - cost_len < size) return false; \
        SHINE_SERIAL_DECODE(__VA_ARGS__); \
        cost_len = flag + size;\
        return true; \
    } \
    }; \
    inline bool operator==(const TYPE &a, const TYPE &b){\
    SHINE_SERIAL_COMPARE(__VA_ARGS__); \
        return true;\
    }\
    inline bool operator!=(const TYPE &a, const TYPE &b){\
        return !(a == b);\
    }\
    inline void shine_serial_encode_field(const TYPE &val, std::string &ret){ return val.shine_serial_encode(ret); }\
    inline bool shine_serial_decode_field(TYPE &val, const char *data, const std::size_t len, std::size_t &cost_len){\
    return val.shine_serial_decode(data, len, cost_len);

#define SHINE_SERIAL_DECODE_BASE_CHECK(type) if (len < cost_len + 1) return false;

inline void shine_serial_encode_size(std::size_t len, std::string &ret, bool back = true, std::size_t pos = 0){
    do {
        char ch = len & ((1 << 7) - 1);
        if (len >>= 7)
            ch |= 0x80;

        if (back) 
            ret += ch;
        else
            ret.insert(pos++, 1, ch);
    } while (len);
}

inline std::string shine_serial_encode_size(std::size_t len){
    std::string ret;
    shine_serial_encode_size(len, ret);
    return std::move(ret);
}

inline bool shine_serial_decode_size(std::size_t &val, const char *data, const std::size_t len, std::size_t &cost_len){
    if (len < cost_len + 1) 
        return false;

    val = 0;
    const unsigned char *p = (const unsigned char *)data + cost_len;
    std::size_t i = 0;

    for (;;)
    {
        if (p[i] & 0x80)
        {
            if (i < len - cost_len - 1)
            {
                val |= (size_t)(p[i] & 0x7F) << (7 *  i);
                i++;
            }
            else
                return false;
        }
        else
        {
            val |= (size_t)(p[i] & 0x7F) << (7 * i);
            cost_len += i + 1;
            return true;
        }
    }
}

template<class T>
void shine_serial_encode_integer(T val, std::string &ret){
    bool flag = val < 0;
    std::size_t size = ret.size();
    std::size_t value = flag ? -val : val;
    do {
        unsigned char ch = value & 0x3F;
        if (value >>= 6)
            ch |= 0x80;

        ret += ch;
    } while (value);

    if (flag)
        ret[size] |= 0x40;
}


template<class T>
bool shine_serial_decode_integer(T &val, const char *data, const std::size_t len, std::size_t &cost_len){
    val = 0;
    const unsigned char *p = (const unsigned char *)data + cost_len;
    bool flag = (p[0] & 0x40) > 0;
    std::size_t i = 0;

    for (;;)
    {
        if (p[i] & 0x80)
        {
            if (i < len - cost_len - 1)
            {
                val |= (size_t)(p[i] & 0x3F) << (6 * i);
                i++;
            }
            else
                return false;
        }
        else
        {
            val |= (size_t)(p[i] & 0x3F) << (6 * i);
            break;
        }
    }

    if (flag)
        val = -val;

    cost_len += i + 1;
    return true;
}

inline void shine_serial_encode_field(bool val, std::string &ret){
    ret += (char)(val ? '\1' : '\0');
}

inline bool shine_serial_decode_field(bool &val, const char *data, const std::size_t len, std::size_t &cost_len){
    SHINE_SERIAL_DECODE_BASE_CHECK(std::serial::e_bool);

    val = data[cost_len++] == '\1';
    return true;
}

inline void shine_serial_encode_field(char val, std::string &ret){
    ret += val;
}

inline bool shine_serial_decode_field(char &val, const char *data, const std::size_t len, std::size_t &cost_len){
    SHINE_SERIAL_DECODE_BASE_CHECK(std::serial::e_byte);

    val = data[cost_len++];
    return true;
}

inline void shine_serial_encode_field(unsigned char val, std::string &ret){
    ret += val;
}

inline bool shine_serial_decode_field(unsigned char &val, const char *data, const std::size_t len, std::size_t &cost_len){
    SHINE_SERIAL_DECODE_BASE_CHECK(std::serial::e_byte);

    val = data[cost_len++];
    return true;
}

#define SHINE_SERIAL_ENCODE_BYTES_FIELD(TYPE) \
    inline void shine_serial_encode_field(const TYPE &val, std::string &ret){\
        shine_serial_encode_size(val.size(), ret); \
        ret.append(val);\
    }

SHINE_SERIAL_ENCODE_BYTES_FIELD(std::string);

#define SHINE_SERIAL_DECODE_BYTES_FIELD(TYPE) \
    inline bool shine_serial_decode_field(TYPE &val, const char *data, const std::size_t len, std::size_t &cost_len){\
        std::size_t size = 0; \
        if (!shine_serial_decode_size(size, data, len, cost_len)) return false;\
        if (size + cost_len > len) return false;\
        val.assign(data + cost_len, size); \
        cost_len += size; \
        return true; \
    }

SHINE_SERIAL_DECODE_BYTES_FIELD(std::string);

#define SHINE_SERIAL_ENCODE_INTEGER_FIELD(TYPE) \
    inline void shine_serial_encode_field(const TYPE &val, std::string &ret){\
        return shine_serial_encode_integer(val, ret); \
    }

#define SHINE_SERIAL_DECODE_INTEGER_FIELD(TYPE) \
    inline bool shine_serial_decode_field(TYPE &val, const char *data, const std::size_t len, std::size_t &cost_len){\
        return shine_serial_decode_integer(val, data, len, cost_len); \
    }

SHINE_SERIAL_ENCODE_INTEGER_FIELD(short);
SHINE_SERIAL_DECODE_INTEGER_FIELD(short);

SHINE_SERIAL_ENCODE_INTEGER_FIELD(unsigned short);
SHINE_SERIAL_DECODE_INTEGER_FIELD(unsigned short);

SHINE_SERIAL_ENCODE_INTEGER_FIELD(int);
SHINE_SERIAL_DECODE_INTEGER_FIELD(int);

SHINE_SERIAL_ENCODE_INTEGER_FIELD(long);
SHINE_SERIAL_DECODE_INTEGER_FIELD(long);

SHINE_SERIAL_ENCODE_INTEGER_FIELD(unsigned long);
SHINE_SERIAL_DECODE_INTEGER_FIELD(unsigned long);

SHINE_SERIAL_ENCODE_INTEGER_FIELD(unsigned int);
SHINE_SERIAL_DECODE_INTEGER_FIELD(unsigned int);

SHINE_SERIAL_ENCODE_INTEGER_FIELD(long long);
SHINE_SERIAL_DECODE_INTEGER_FIELD(long long);

SHINE_SERIAL_ENCODE_INTEGER_FIELD(unsigned long long);
SHINE_SERIAL_DECODE_INTEGER_FIELD(unsigned long long);

#define SHINE_SERIAL_ENCODE_FLOAT_FIELD(TYPE)\
inline void shine_serial_encode_field(const TYPE &val, std::string &ret){\
    ret.append((const char*)&val, sizeof(val));\
}

#define SHINE_SERIAL_DECODE_FLOAT_FIELD(TYPE)\
inline bool shine_serial_decode_field(TYPE &val, const char *data, const std::size_t len, std::size_t &cost_len){\
    if (len < cost_len + sizeof(val))\
        return false;\
        \
    val = *((TYPE*)(data + cost_len));\
    cost_len += sizeof(val);\
    return true;\
}

SHINE_SERIAL_ENCODE_FLOAT_FIELD(float);
SHINE_SERIAL_DECODE_FLOAT_FIELD(float);

SHINE_SERIAL_ENCODE_FLOAT_FIELD(double);
SHINE_SERIAL_DECODE_FLOAT_FIELD(double);

SHINE_SERIAL_ENCODE_FLOAT_FIELD(long double);
SHINE_SERIAL_DECODE_FLOAT_FIELD(long double);

#define SHINE_SERIAL_ENCODE_MAP_FIELD(TYPE) \
    template<typename T1, typename T2>\
    inline void shine_serial_encode_field(const TYPE<T1, T2> &val, std::string &ret){\
        shine_serial_encode_size(val.size(), ret); \
        for (auto &iter : val)\
        {\
            shine_serial_encode_field(iter.first, ret); \
            shine_serial_encode_field(iter.second, ret); \
        }\
    }

#define SHINE_SERIAL_DECODE_MAP_FIELD(TYPE) \
    template<typename T1, typename T2>\
    inline bool shine_serial_decode_field(TYPE<T1, T2> &val, const char *data, const std::size_t len, std::size_t &cost_len){\
        std::size_t size = 0; \
        if (!shine_serial_decode_size(size, data, len, cost_len)) return false; \
        for (std::size_t i = 0; i < size; i++)\
        {\
            T1 k;\
            if (!shine_serial_decode_field(k, data, len, cost_len)) return false;\
            T2 v;\
            if (!shine_serial_decode_field(v, data, len, cost_len)) return false;\
            val.emplace(std::move(k), std::move(v));\
        }\
        return true; \
    }


SHINE_SERIAL_ENCODE_MAP_FIELD(std::map);
SHINE_SERIAL_ENCODE_MAP_FIELD(std::unordered_map);

SHINE_SERIAL_DECODE_MAP_FIELD(std::map);
SHINE_SERIAL_DECODE_MAP_FIELD(std::unordered_map);


#define SHINE_SERIAL_ENCODE_ARRAY_FIELD(TYPE) \
    template<typename T>\
    inline void shine_serial_encode_field(const TYPE<T> &val, std::string &ret){\
        shine_serial_encode_size(val.size(), ret); \
        for (auto &iter : val) shine_serial_encode_field(iter, ret); \
    }

#define SHINE_SERIAL_DECODE_ARRAY_FIELD(TYPE) \
    template<typename T>\
    inline bool shine_serial_decode_field(TYPE<T> &val, const char *data, const std::size_t len, std::size_t &cost_len){\
        std::size_t size = 0; \
        if (!shine_serial_decode_size(size, data, len, cost_len)) return false; \
        val.resize(size);\
        for (std::size_t i = 0; i < size; i++)\
        {\
            if (!shine_serial_decode_field(val[i], data, len, cost_len)) return false; \
        }\
        return true; \
    }

SHINE_SERIAL_ENCODE_ARRAY_FIELD(std::vector);
SHINE_SERIAL_DECODE_ARRAY_FIELD(std::vector);

SHINE_SERIAL_ENCODE_ARRAY_FIELD(std::deque);
SHINE_SERIAL_DECODE_ARRAY_FIELD(std::deque);

template<typename T>
inline void shine_serial_encode_field(const std::list<T> &val, std::string &ret){
    shine_serial_encode_size(val.size(), ret); 
    for (auto &iter : val) {
        shine_serial_encode_field(iter, ret);
    }
}

template<typename T>
inline bool shine_serial_decode_field(std::list<T> &val, const char *data, const std::size_t len, std::size_t &cost_len){
    std::size_t size = 0;
    if (!shine_serial_decode_size(size, data, len, cost_len)) return false;
    val.resize(size);
    auto iter = val.begin();
    for (std::size_t i = 0; i < size; i++)
    {
        if (!shine_serial_decode_field(*iter++, data, len, cost_len)) return false;
    }
    return true;
}


template<typename T>
inline void shine_serial_encode_field(const std::forward_list<T> &val, std::string &ret){
        std::size_t begin = ret.size();
        std::size_t size = 0;
        for (auto &iter : val) {
            std::string tmp;
            shine_serial_encode_field(iter, tmp);
            ret.insert(begin, std::move(tmp));
            size++;
        }

        shine_serial_encode_size(size, ret, false, begin);
}

template<typename T>
inline bool shine_serial_decode_field(std::forward_list<T> &val, const char *data, const std::size_t len, std::size_t &cost_len){
        std::size_t size = 0;
        if (!shine_serial_decode_size(size, data, len, cost_len)) return false;
        for (std::size_t i = 0; i < size; i++)
        {
            T v;
            if (!shine_serial_decode_field(v, data, len, cost_len)) return false;
            val.emplace_front(std::move(v)); 
        }
        return true; 
    }

#define SHINE_SERIAL_ENCODE_SET_FIELD(TYPE) \
    template<typename T>\
    inline void shine_serial_encode_field(const TYPE<T> &val, std::string &ret){\
        ret += std::move(shine_serial_encode_size(val.size())); \
        for (auto &iter : val) shine_serial_encode_field(iter, ret); \
    }

#define SHINE_SERIAL_DECODE_SET_FIELD(TYPE) \
    template<typename T>\
    inline bool shine_serial_decode_field(TYPE<T> &val, const char *data, const std::size_t len, std::size_t &cost_len){\
        std::size_t size = 0; \
        if (!shine_serial_decode_size(size, data, len, cost_len)) return false; \
        for (std::size_t i = 0; i < size; i++)\
        {\
            T v;\
            if (!shine_serial_decode_field(v, data, len, cost_len)) return false;\
            val.emplace(std::move(v)); \
        }\
        return true; \
    }

SHINE_SERIAL_ENCODE_SET_FIELD(std::set);
SHINE_SERIAL_DECODE_SET_FIELD(std::set);

SHINE_SERIAL_ENCODE_SET_FIELD(std::unordered_set);
SHINE_SERIAL_DECODE_SET_FIELD(std::unordered_set);


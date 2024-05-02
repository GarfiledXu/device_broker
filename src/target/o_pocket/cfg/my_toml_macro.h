#pragma once
#include "toml.hpp"
#define NAMESPACE_BEGIN(name) namespace name{
#define NAMESPACE_END(name) }
/**
 *@brief to fast generate the function of convert struct to toml.
 */
#define DEFINE_FROM_TOML(OUT_STRUCT_TYPE, IN_TOML_VALUE_NAME) \
namespace toml{ \
template<> \
struct from<OUT_STRUCT_TYPE> { \
    static OUT_STRUCT_TYPE from_toml(const value& IN_TOML_VALUE_NAME);};} \
inline OUT_STRUCT_TYPE toml::from<OUT_STRUCT_TYPE>::from_toml(const value& IN_TOML_VALUE_NAME) 


 /**
  *@brief to fast generate the function fo convert toml value to struct obj.
  */
#define DEFINE_INTO_TOML(STRUCT_TYPE, IN_STRUCT_NAME) \
namespace toml \
{ \
template<> \
struct into<STRUCT_TYPE> \
{ \
    static value into_toml(const STRUCT_TYPE& IN_STRUCT_NAME); \
}; \
} \
inline toml::value toml::into<STRUCT_TYPE>::into_toml(const STRUCT_TYPE& IN_STRUCT_NAME)

/**
 *@brief to complete one toml value by another toml value
    strategy:
    1. if dst toml not contain the key and value, will assigned by the template toml directly.
    2. if dst toml has conttained the target key and value(table), will do noting next.
 */
namespace toml {
     static int patch_toml_value(const toml::value& cmp_v, toml::value& out_v) {
         //check if a table, that illustrate have multi pair
        if (cmp_v.is_table() && out_v.is_table()) {
            for (const auto& src_kv : cmp_v.as_table()) {
                if (out_v.contains(src_kv.first)) {
                    patch_toml_value(src_kv.second, out_v.at(src_kv.first));
                }
                else {
                    out_v.as_table().insert(src_kv);
                }
            }
        }
        else if (cmp_v.is_array() && out_v.is_array()) {
            if (out_v.as_array().empty()) {
                out_v = cmp_v;
            }
        }
        else {
            // out_v = cmp_v;
            //do noting, don't to override
        }
        return 0;
    }
};

// #define DEFINE_FROM_TOML2(stru, ...) \

// template<typename T, typename ... Args>
// T get_struct(T& out_s, toml::value& in_v, Args&... args) {
// }

#define GET_SUB_VALUE(out_prefix, in_value, key) \
auto out_prefix##key=toml::get<toml::table>(in_value).at(#key);

#define FIND_VALUE_TO_ASSIGN(out_var, in_value, key, type) \
out_var.key=find<type>(in_value, #key);

// #define FIND_VALUE_OR_TO_ASSIGN(be_assign_out, in_toml_value, key, default_value) \
//                 be_assign_out.key = toml::find_or(in_toml_value, #key, default_value);

#define INSERT_KEY_VALUE_BY_STRU(in_var, key) \
{#key, in_var.key}
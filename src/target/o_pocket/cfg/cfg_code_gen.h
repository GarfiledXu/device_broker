//xjf add
#pragma once

#define CFG_INS CfgFocus::get_ins()
//all for laziness generate correspond mutex instread of template function
#define DECLARE_GET_SET(TYPE) \
private: \
    bool TYPE##_is_load = false; \
    TYPE TYPE##_ = TYPE(); \
    mutable std::mutex mutex_##TYPE##_; \
public: \
    void set_##TYPE(const TYPE& value) { \
        std::lock_guard<std::mutex> lg(mutex_##TYPE##_); \
        TYPE##_ = value; \
        TYPE##_is_load = true; \
    }; \
    TYPE get_##TYPE() const { \
        std::lock_guard<std::mutex> lg(mutex_##TYPE##_); \
        if(!TYPE##_is_load) throw std::logic_error("current cfg not loaded!"); \
        return TYPE##_; \
    } ;\
    const TYPE& get_##TYPE##ref() const{ \
        std::lock_guard<std::mutex> lg(mutex_##TYPE##_); \
        if(!TYPE##_is_load) throw std::logic_error("current cfg not loaded!"); \
        return TYPE##_; \
    };  
// \
//     const TYPE set_##TYPE(const std::string& in_path, const std::string& in_protocol) { \
//         std::lock_guard<std::mutex> lg(mutex_##TYPE##_); \
//         TYPE##_ = load_cfg_by_path<TYPE>(in_path, in_protocol); \
//         TYPE##_is_load = true; \
//     }


//privade the declare macro, hope to implemente private struct convert by non invasive.
//just to include header to determine which cfg cvt to be choice
//template function for adapt protocol to struct, hide protocol
#define CFG_FOCUS_BEGIN() \
class CfgFocus { \
public: 

#define CFG_FOCUS_END() \
static CfgFocus& get_ins() { \
        static CfgFocus cfg_focus{}; \
        return cfg_focus; \
    }; \
    template <typename T> \
    static T load_cfg_by_path(const std::string& in_path, const std::string& in_protocol); \
    template <typename T> \
    static T load_cfg_by_iostream(std::ifstream& instream, const std::string& in_protocol); \
    template <typename T> \
    static T load_cfg_by_content(const std::string& in_content, const std::string& in_protocol); \
private: \
    CfgFocus() = default; \
    virtual ~CfgFocus() = default; \
};

//complete define
// class CfgFocus {
// public:
//     DECLARE_GET_SET(cfg_init_to_server);

//     static CfgFocus& get_ins() {
//         static CfgFocus cfg_focus{};
//         return cfg_focus;
//     };
//     //adapt protocol to struct, hide protocol
//     template <typename T>
//     static T load_cfg_by_path(const std::string& in_path, const std::string& in_protocol);

//     template <typename T>
//     static T load_cfg_by_iostream(std::ifstream& instream, const std::string& in_protocol);

//     template <typename T>
//     static T load_cfg_by_content(const std::string& in_content, const std::string& in_protocol);

// private:
//     CfgFocus() = default;
//     virtual ~CfgFocus() = default;
// };



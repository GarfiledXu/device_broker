#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <typeindex>

struct Any
{
    Any(void)
        : type_index_(std::type_index(typeid(void))) {}
    Any(const Any& that)
        : ptr_(that.clone()), type_index_(that.type_index_) {}
    Any(Any&& that)
        : ptr_(std::move(that.ptr_)), type_index_(that.type_index_) {}
    ~Any() = default;

    //使用std::type_index 代替 std::type_info, 拥有更好的封装性，内涵type比较操作
    //std::decay 去除input 类型的引用符和cv符, 获取原始类型
    //std::is_same对比两个类型
    //typename 声明跟随符号为类型而非对象符号，除非是模板定义中输入的明确类型，否则编译器都视之为非类型符号，进行解释
    //class = XXX_T 使用等号是默认模板参数用法，而没有使用类型形参，是允许的，等同于只是执行了类型表达式而已
    //std::enable_if 模板定义中常用的类型小工具，第一个模板参数为条件表达式，第二个模板参数为类型参数
    template <
        typename T
        , class = typename std::enable_if<
            !std::is_same<typename std::decay<T>::type, Any>::value, T
        >::type
    >
    Any(T&& value)
        : ptr_(new Derived <typename std::decay<T>::type>(std::forward<T>(value)))
        , type_index_(std::type_index(typeid(typename std::decay<T>::type)))
    {}

    bool is_null() const {
        return !bool(ptr_);
    }

    template<class T>
    bool is_type() const {
        return type_index_ == std::type_index(typeid(T));
    }

    template<class T>
    T& any_cast() {
        if (!is_type<T>()) {
            printf("can't cast type:%s to type:%s\n", typeid(T).name(), type_index_.name());
            std::cout << "can not cast " << typeid(T).name() << " to " << type_index_.name() << std::endl;
            throw std::bad_cast();
        }
        auto derived = dynamic_cast<Derived<T>*> (ptr_.get());
        return derived->m_value;
    }

    Any& operator=(const Any& a) {
        if (ptr_ == a.ptr_)
            return *this;

        ptr_ = a.clone();
        type_index_ = a.type_index_;
        return *this;
    }

private:
    //为什么需要定义Base数据结构？
    //clone只是继承的附属品，是实现=操作符的处理方式
    //Any 需要一个类型明确的数据结构作为基类，在any空初始化时实例化，并在后续接受继承类derived实例化后的对象
    struct Base;
    using BasePtr = std::unique_ptr<Base>;
    struct Base {
        virtual ~Base() {}
        virtual BasePtr clone() const = 0;
    };

    template<typename T>
    struct Derived : Base {
        template<typename U>
        Derived(U&& value)
            : m_value(std::forward<U>(value)) {};

        BasePtr clone() const {
            return BasePtr(new Derived<T>(m_value));
        }
        T m_value;
    };

    BasePtr clone() const {
        if (ptr_ != nullptr)
            return ptr_->clone();
        return nullptr;
    }

    BasePtr ptr_;
    std::type_index type_index_;
};

#if 0
struct bbb{
  std::string ddd;
  int ccc;
};
template<typename T>
struct aaa{
  int a ;
  std::string b;
  T custom;
};
int main(){
    printf("hello world\n");
    Any n;    
    auto r = n.is_null();//true
    std::string s1 = "hello";
    n = s1;
    n = "world";
    //n.any_cast<int>(); //can not cast int to string
    Any n1 = 1;
    n1.is_type<int>(); //true
    printf("is_type int :%d\n", n1.is_type<int>());
    printf("is_type int :%d\n", n1.is_type<bool>());
    aaa<int> aaa_int;
    aaa<bool> aaa_bool;
    aaa<bbb> aaa_bbb;
    Any a_int = aaa_int;
    Any a_bool = aaa_bool;
    Any a_bbb = aaa_bbb;
    
    printf("is_type a_int :%d\n", a_int.is_type<aaa<int>>());
    printf("is_type a_bool :%d\n", a_bool.is_type<aaa<bool>>());
    printf("is_type a_bbb :%d\n", a_bbb.is_type<aaa<bbb>>());
    
    printf("is_type a_int is_type bool:%d\n", a_int.is_type<bool>());
    printf("is_type a_bool is_type bool:%d\n", a_bool.is_type<bool>());
    printf("is_type a_bbb is_type bool:%d\n", a_bbb.is_type<bool>());
    return 0;
}
#endif
#include "log.h"
#include "errorcode.h"
#include "gtest.h"
//defect
//自动抛出异常是抛出自身引用，如果自身是一个临时变量呢？
//eg: 直接在try中执行erc(10);最后无法捕获，并且crash
//eg: 直接 throw erc(10); 能够捕获

//significance
//1. auto check return processing, if method use erc as errorcode to return, it will help you to check the status of one method returned that if be performed, if not, will thow exception
//2. unified processing for convenient

//usage specification
//1. use std::exception to catch combine exception and error
//2. to handle the sequential calls that mixed with various error codes and end once there is an error in call by using logic or operator or try-catch code block 
//3. to packge the normal error return of type int for uniform handle
//4. to handle the sequential calls that not end once there is an error in call 
//5. to handle the erc obj from generate from function inside and return to int type
//6. to handle the erc obj from generate from function inside and return to int erc
TEST(error_code, signal_destruct_exception) {

    EXPECT_THROW({ erc cur_erc(1); }, erc);

    try {
        erc cur_erc(1);
    }
    catch (erc& e) {
        SLOGD("enter catch, what:{}", e.what());
        SUCCEED();
    }

}
//这条case已经可以充分说明了，erc的设计不能使用c++标准的异常机制进行处理，
//由于析构抛出异常是违反了 异常机制的默认规则，尤其是erc对象数量未知
//意味着 erc 对象是无法通过catch被预期捕获的
//erc与异常唯一的关联点，就是利用 异常terminate来显式报错, erc没有被处理就直接terminate 显式报错
TEST(error_code, multi_destruct_exception) {

    try {
        erc cur_erc(1);
        //erc cur_erc(2);
        // throw std::logic_error();//打开后将会出现多个异常，程序必定会被终止
    }
    catch (erc& e) {
        SLOGD("enter catch, what:{}", e.what());
        SUCCEED();
    }
    catch (erc& e) {
        SLOGD("enter catch, what:{}", e.what());
        SUCCEED();
    }
    catch (std::exception& e) {
        SLOGD("enter catch, what:{}", e.what());
    }

}
auto funcint0 = []() ->int {return 0;};
auto funcint1 = []() ->int {return 1;};
auto funcint2 = []() ->int {return 2;};
auto funcint3 = []() ->int {return 3;};

auto func0 = []() -> erc {SLOGD("enter func0");return erc(0);};
auto func1 = []() -> erc {SLOGD("enter func1");return erc(1);};
auto func2 = []() -> erc{SLOGD("enter func2");return erc(2);};
auto func3 = []() -> erc{SLOGD("enter func3");return erc(3);};
TEST(error_code, sequential_call_erc_to_tmpint) {
    while (func0()) {
        FAIL();
    }

    if (func0() || func1() || func2() || func3()) {
        SUCCEED();
        //fail process
    }
    else {
        FAIL();
        //success process
    }
}

#if 1
TEST(error_code, sequential_call_erc_to_left_erc) {
    //save ret to pass and process
    auto run0 = [&]()->erc {
        erc ret_erc{};
        //这里如果是存在数值的即使是0也是会被，那么直接在下面的第一步骤就会触发move=，
        //move = 触发的异常与析构触发的不同，是不判断值是否为0的，所以必须默认构造


        //这里发生了移动赋值，会将临时变量的状态覆盖到接收的对象，但是接收对象原来状态呢？
        //所有erc对象异常的抛出都是基于析构的，即不是在对象所处代码处，都是延后异常
        //决定erc 对象是否抛出异常的, 三点:1. 返回值是否非0 2. 是否active 3.等级
        //active 通常是显式调用处理的，所以基本上等同于 非0 就会抛出异常，0就不会
        //触发了
        (ret_erc = func0())
            || (ret_erc = func1())
            || (ret_erc = func2())
            || (ret_erc = func3());
        SLOGD("will out run2");

        //must clean process
        //return
        return ret_erc;
        };
    //return non
    run0().deactivate();
    if (!run0()) {
        FAIL();
    }
}
#endif

TEST(error_code, sequential_call_erc_to_left_int) {

    //mix usage
    auto run1 = [&]()->erc {
        if (func0()) {
            SLOGD("func0 return non 0");
        }
        if (func1()) {
            SLOGD("func1 return non 1");
        }
        if (func2() || func3()) {
            SLOGD("func2 or func 3 return non 1");
        }
        return func3();
        };
    //expect run1 return 3, if enter if state means current code error
    if (run1()) {
        SUCCEED();
    }
    else {
        FAIL();
    }

    //using int accpet to as return value
    auto run2 = [&]()->int {
        int ret_erc{0};
       
        (ret_erc = func0())
            || (ret_erc = func1())
            || (ret_erc = func2())
            || (ret_erc = func3());

        //must clean process
        //return
        return ret_erc;
        };
    //return non
    erc ret = run2();
    EXPECT_EQ(ret, 1);
}

//使用不当就会触发terminate，尤其是在erc对象赋值操作的时候
//准则: 已经存在的erc对象，如果是非默认构造的的erc，那么一旦触发move=就会抛出异常，并且触发move=是非常频繁的
//只要使用erc去接收对象，就会存在处理复杂性, 此时我对该机制的实用性存疑
//当使用默认erc对象时:
//1. 当int用，默认构造的erc+ || 连接的逻辑表达式使用，最后透传一个erc给下一层
//2. 直接使用 int 进行接收
//3. 当异常用需要throw的时候还是可以直接throw的，但不是通过return的对象析构来throw，是直接throw
//总而言之，使用 已存在的erc对象进行接收要特别注意
//当使用设置erc 等级的对象时
//warnning 以上触发 log 报错，但不会抛出异常
//error 触发log+ 异常
TEST(error_code, sequential_call_trigger_move_copy_assign) {
    //mixed using erc to wrap int type return value 
    //mixed construct assign and move assign and hide convert
    //资源转移时，会进行raise,所有只有move=会触发raise，而移动构造时，没有原有资源所以不会raise
    //关键在于 理解什么时候会触发 raise: 1. 析构 (在代码块执行完以后)2. move= (在当前代码块)

    //触发 析构 throw, 会raise
    EXPECT_THROW({erc cur_erc{1};}, erc);
    //触发 隐式构造，move =, 会raise
    EXPECT_THROW({ erc cur_erc{1}; cur_erc = 1; }, erc);
    EXPECT_THROW({ erc cur_erc{1}; cur_erc = funcint1(); }, erc);
    EXPECT_THROW({ erc cur_erc{1}; cur_erc = erc(funcint1()); }, erc);
    EXPECT_THROW({ erc cur_erc{0}; cur_erc = 1; }, erc);
    //触发 copy =，不会raise
    EXPECT_NO_THROW({ erc cur_erc{1}; erc cur_erc2{0};cur_erc = cur_erc2; });
    EXPECT_NO_THROW({ erc cur_erc{}; cur_erc = 1; cur_erc.deactivate(); });
    EXPECT_NO_THROW({ erc cur_erc{1}; cur_erc.deactivate(); cur_erc = 1; cur_erc.deactivate(); });
    //触发 int(), 不会rasie
    EXPECT_NO_THROW({ int out_ret = 0; erc cur_erc{1}; out_ret = cur_erc; });
}



//不同priority
TEST(error_code, pass_msg_to_top_call) {
    //应该设计一个数据结构，封装宏定义，使用name作为key
    //注册宏和引用宏

    //no log
    EXPECT_NO_THROW({ erc cur_erc(-1, ERROR_PRI_NOTICE, ERRFAC_DEFAULT()); });
    //no throw
    EXPECT_NO_THROW({ erc cur_erc(-1, ERROR_PRI_WARNING, ERRFAC_DEFAULT()); });
    //have throw
    EXPECT_THROW({ erc cur_erc(-2, ERROR_PRI_ERROR, ERRFAC_DEFAULT()); }, erc);
    //have log, no throw
    EXPECT_NO_THROW({ erc cur_erc(-3, ERROR_PRI_WARNING, ERRFAC_REGI("priority_test1", ERROR_PRI_WARNING, ERROR_PRI_CRITICAL)); });
    //reigster and use
    ERRFAC_REGI("priority_test2", ERROR_PRI_WARNING, ERROR_PRI_CRITICAL);
    EXPECT_THROW({ erc cur_erc(-4, ERROR_PRI_CRITICAL, ERRFAC_REF("priority_test2")); }, erc);


    //common use
    //default construct erc is not log and throw, but will override by move=
    EXPECT_THROW({ erc cur_erc{}; cur_erc = -5; }, erc);
    EXPECT_NO_THROW({ erc cur_erc(-1, ERROR_PRI_WARNING, ERRFAC_REGI_NAME("priority_test3")); });

    //所以这个机制的意义到底何在?
    //在传统错误码的基础上 新增了判断行为检查，没有则抛出异常
    //是否有必要加入log level
    //是否应该直接修改 throw level 为throw switch
    //如何利用错误对象机制来传递更多东西
    // erc(<code>, <msg>,  focus check, void*)
    //exist_erc.push_msg();
    //when throw: sloge(msg)
    //or active: sloge(exist_erc.get_msg())
    //other: exist_erc.get_other()

///var/i30_objective/device_ping/run_dv_ping.sh
}

TEST(error_code, pass_msg_chain_to_top_call) {
    
}
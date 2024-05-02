#ifndef GF_MESSAGE_BUS_TEST_HPP
#define GF_MESSAGE_BUS_TEST_HPP

#include "message_bus.hpp"
#define TEST_MESSAGE_BUS_ 0

#if TEST_MESSAGE_BUS_
    #include "gtest/gtest.h"
    int func1(){
       return 1; 
    }
    int func2(){
       return 2; 
    }
    TEST(MessageBusTest, SingleThreadTest) {
        MessageBus<std::string, std::function<int()>> bus;
        std::string channel1 = "download"; 
        ASSERT_EQ(0, bus.register_channel(&channel1));
        std::string channel2 = "run";
        ASSERT_EQ(0, bus.register_channel(&channel2));
        ASSERT_EQ(0, bus.post_to_mq([]() -> int { return func1(); }, nullptr));
        ASSERT_EQ(2, bus.get_channel_set().size());
        std::function<int()> f;
        bus.fetch_mq_msg_sync(&channel1, f);
        ASSERT_EQ(1, f());
        bus.fetch_mq_msg_sync(&channel2, f);
        ASSERT_EQ(1, f());
        ASSERT_EQ(0, bus.post_to_mq([]() -> int { return func2(); }, nullptr));
        bus.fetch_mq_msg_sync(&channel2, f);
        ASSERT_EQ(2, f());
    }

    TEST(MessageBusTest,  MultiThreadTest) {
        MessageBus<std::string, int(*)(void)> bus;
        std::string channel1 = "download"; 
        ASSERT_EQ(0, bus.register_channel(&channel1));
        std::string channel2 = "run";
        ASSERT_EQ(0, bus.register_channel(&channel2));
        std::vector<std::thread> threads;
        for (int i = 0; i < 2; i++) {
            threads.emplace_back([&](){
                for(int j = 0; j<2; j++){
                    bus.post_to_mq([]() -> int { return func1(); }, &channel1);
                    bus.post_to_mq([]() -> int { return func2(); }, &channel2);
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            });
        }
        for(int i=0; i<2; i++){
            threads.emplace_back([&bus](){
                typedef int(*func)(void);
                func f;
                for(int i=0; i<2; i++){
                    std::string channel = "download"; 
                    bus.fetch_mq_msg_sync(&channel, f);
                    ASSERT_EQ(1, f());
                }
            });
        }
        for(int i=0; i<2; i++){
            threads.emplace_back([&bus](){
                typedef int(*func)(void);
                func f;
                for(int i=0; i<2; i++){
                    std::string channel = "run"; 
                    bus.fetch_mq_msg_sync(&channel, f);
                    ASSERT_EQ(2, f());
                }
            });
        }
        for (auto& thread : threads) {
            thread.join();
        }
    }

#endif

#endif
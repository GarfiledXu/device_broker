#ifndef GF_SAFE_QUEUE_TEST_HPP
#define GF_SAFE_QUEUE_TEST_HPP

#define TEST_SAFTQUEUE_ 1
#include "safe_queue.hpp"
#if TEST_SAFTQUEUE_
    #include "gtest/gtest.h"

    TEST(SafeQueueTest, MultiAsyncPushPopTest) {
        SafeQueue<int> que(10);
        std::vector<std::thread> threads;
        // 创建15个线程  每个插入队列一次
        for (int i = 0; i < 15; i++) {
            threads.emplace_back([&que, i]() {
                if(i<10) ASSERT_EQ(0, que.push_async(1));
                else ASSERT_GT(0, que.push_async(1));
            });
        }
        // 创建3个线程  每个拿取队列
        for (int i = 0; i < 3; i++) {
            threads.emplace_back([&que, i]() {
                if(i==0){
                    int a;
                    ASSERT_EQ(0, que.pop_async(a));
                }else if(i==1){
                    std::list<int> a;
                    ASSERT_EQ(0, que.pop_async_list(a));
                    ASSERT_EQ(a.size(), 9);
                    for(auto c: a){
                        ASSERT_EQ(c, 1);
                    }
                }
                else{
                    std::list<int> a;
                    int b;
                    ASSERT_GT(0, que.pop_async_list(a));
                    ASSERT_GT(0, que.pop_async(b));
                }
            });
        }
        for (auto& thread : threads) {
            thread.join();
        }
        ASSERT_EQ(0, que.get_size());
    }

    TEST(SafeQueueTest, MultiSyncPushPopTest) {
        SafeQueue<int> que(10);
        std::vector<std::thread> threads;
        for (int i = 0; i < 15; i++) {
            threads.emplace_back([&que, i]() {
                que.push_sync(1);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                if(i<10){
                    int a;
                    que.pop_sync(a);
                    ASSERT_EQ(a, 1);
                }
            });
        }
        for (auto& thread : threads) {
            thread.join();
        }
        ASSERT_EQ(5, que.get_size());
        std::list<int> a;
        que.pop_sync_list(a);
        ASSERT_EQ(a.size(), 5);
        for(auto c: a){
            ASSERT_EQ(c, 1);
        }
        ASSERT_EQ(0, que.get_size());
    }   

    TEST(SafeQueueTest, MultiTryPushPopTest) {
        SafeQueue<int> que(10);
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; i++) {
            threads.emplace_back([&que, i]() {
                ASSERT_EQ(0, que.try_push(1, 100));
            });
        }
        ASSERT_EQ(10, que.get_size());
        for (int i = 0; i < 5; i++) {
            threads.emplace_back([&que, i]() {
                ASSERT_GT(0, que.try_push(1, 100));
            });
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        for (int i = 0; i < 3; i++) {
            threads.emplace_back([&que, i]() {
                if(i==0){
                    int a;
                    ASSERT_EQ(0, que.try_pop(a, 100));
                }else if(i==1){
                    std::list<int> a;
                    ASSERT_EQ(0, que.try_pop_list(a, 100));
                    ASSERT_EQ(a.size(), 9);
                    for(auto c: a){
                        ASSERT_EQ(c, 1);
                    }
                }
                else{
                    int a;
                    ASSERT_GT(0, que.try_pop(a, 100));
                }
            });
        }
        for (auto& thread : threads) {
            thread.join();
        }
        ASSERT_EQ(0, que.get_size());

        SafeQueue<int> que2(2);
        ASSERT_EQ(0, que2.try_push(1, 100));
        ASSERT_EQ(0, que2.try_push(1, 100));
        int a = 1;
        ASSERT_EQ(2, que2.count(a));
        std::thread t([&que2]() {
                ASSERT_EQ(-1, que2.try_push(1, 1000));
        });
        t.detach();
        que.stop();
        ASSERT_EQ(2, que2.get_size());
        ASSERT_EQ(0, que2.reset());
        ASSERT_TRUE(que2.empty());
    }

#endif
#endif
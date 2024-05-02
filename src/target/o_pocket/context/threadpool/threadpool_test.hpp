#ifndef GF_THREADPOOL_TEST_HPP
#define GF_THREADPOOL_TEST_HPP
#include "threadpool.hpp"
GF_NAMESPACE_START(main_service)
/**
 *@brief sample test code
 */
inline void test_monitor() {
    //test reference collapse
    //start monitor
    #if 1
    LOG_EXTR("enter test_monitor\n");
        auto monitor = [](ShareTaskInfo<int> taskinfo)->bool {
        auto timer = taskinfo->get_timer();
        auto future = taskinfo->get_future();

        LOG_EXTR(
            "\nget elapsed ms:%lld\n"
            "get elapsed end ms:%lld\n"
            "get obj serial:%lu\n"
            "get obj count:%lu\n",
            timer->get_elapsed_ms(),
            timer->get_end_elapsed_ms(),
            taskinfo->get_obj_serial(),
            taskinfo->get_obj_count());
        if (timer->is_end()) {
            //fetach task return value
            unsigned long task_obj_serial = taskinfo->get_obj_serial();
            try {
                int ret = future.get();
                LOG_INFO("task is end! get return value:%d\n, task obj serial:%lu\n", ret, task_obj_serial);
            }
            catch (std::exception& e) {
                LOG_ERROR("task catch: %s\n, task obj serial: %lu\n", e.what(), task_obj_serial);
                LOG_INFO("hello!\n");
            }
        }
        return timer->is_end();
    };

    LoopMonitor<int> loop_monitor(monitor, 1000, 10000);
    auto loop_list = loop_monitor.start();
    //generate threadpool
    Threadpool<int> threadpool1(4, 10, nullptr, "threadpool one", nullptr), threadpool2(3, 20, nullptr, "threadpool second", nullptr);
    threadpool1.bind_monitor_list(loop_list);
    threadpool2.bind_monitor_list(loop_list);
    threadpool1.start_workers();
    threadpool2.start_workers();
    //task generator
    std::thread thread2([&]() {
        for (int i = 0;i < 1000;i++) {
            threadpool1.enqueue_task_sync([=]()->int {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                LOG_INFO("threadpool1, run task,from thread2, i:%d\n", i);
                return i;
                });
        }
        LOG_INFO("thread2, task generator end! 1000 task!\n");
    });
    std::thread thread3([&]() {
        for (int i = 0;i < 2;i++) {
            threadpool2.enqueue_task_sync([=]()->int {
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                throw std::runtime_error("threadpool2 runtime error!\n");
                LOG_INFO("threadpool2, run task,from thread3, i:%d\n", i);
                return i;
                });
        }
        LOG_INFO("thread3, task generator end! 2000 task!\n");
    });
    if (thread2.joinable())
        thread2.join();
    if (thread3.joinable())
        thread3.join();

    //thread2.detach();
    //thread3.detach();
    //sleep(30);
    LOG_EXTR("enter sleep\n");
    sleep(20);
    threadpool1.stop_workers_sync();
    threadpool2.stop_workers_sync();
    LOG_EXTR("sleep out\n");

#endif


}
#if 0
inline void test_monitor_priority() {
    //test reference collapse
    //start monitor
    using T_task = std::function<TaskReturn()>;
    using T_task_pair = std::pair<T_task, int>;
    using TaskQueue = std::shared_ptr<SafeQueue<T_task_pair>>; 
        
main_service::Threadpool<main_service::TaskReturn> threadpool_down_update(3, 10000, nullptr, "thread down update", nullptr);
std::mutex mutex;
    #if 1
    LoopMonitor<TaskReturn> loop_monitor([](ShareTaskInfo<TaskReturn> taskinfo) {
        auto timer = taskinfo->get_timer();
        auto future = taskinfo->get_future();
    LOG_EXTR(
        "\nget elapsed ms:%lld\n"
        "get elapsed end ms:%lld\n"
        "get obj serial:%lu\n"
        "get obj count:%lu\n",
        timer->get_elapsed_ms(),
        timer->get_end_elapsed_ms(),
        taskinfo->get_obj_serial(),
        taskinfo->get_obj_count());
    if (timer->is_end()) {
        //fetach task return value
        unsigned long task_obj_serial = taskinfo->get_obj_serial();
        try{
            TaskReturn ret = future.get();
            LOG_INFO("task is end! get return value:%d, type: % d, task obj serial : % lu\n", ret.code, ret.task_type, task_obj_serial);
                //actual process
        }
        catch (std::exception& e) {
            LOG_ERROR("task catch: %s\n, task obj serial: %lu\n", e.what(), task_obj_serial);
            LOG_INFO("end exception!\n");
        }
    }
    return timer->is_end();
        }, 1000, 10000);
    // LoopMonitor<TaskReturn> loop_monitor(monitor_1, 1000, 10000);
    auto loop_list = loop_monitor.start();
    threadpool_down_update.bind_monitor_list(loop_list);
    // threadpool_run_testbed.bind_monitor_list(loop_list);
    //threadpool
    threadpool_down_update.start_workers();
    // threadpool_run_testbed.start_workers();

   //task generator
    std::thread thread_task_generator_1([&]() {
        for (int i = 0;i < 100;i++) {
            threadpool_down_update.enqueue_task_sync([=]()->TaskReturn{
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                LOG_INFO("threadpool update and download, run task,from thread2, i:%d\n", i);
                TaskReturn taskreturn;
                taskreturn.code = i;
                taskreturn.task_type = TASK_TYPE_RUNING;
                return taskreturn;
                }, 2);
            std::lock_guard<std::mutex> lg(mutex);
            LOG_DEBUG("enqueu one task, priority:2\n");
            TaskQueue taskqueue = threadpool_down_update.get_task_queue();
            auto queue = taskqueue->get_inner_queue();
            LOG_DEBUG(">>> test >> printf task after enqueue:%d\n", queue.size());
            for (const auto& task : queue) {
                printf("%d\n", task.second);
            }
        }
        LOG_INFO("generator 1, task generator end! 1000 task!\n");
    });
    std::thread thread_task_generator_2([&]() {
        for (int i = 0;i < 100;i++) {
            threadpool_down_update.enqueue_task_sync([=]()->TaskReturn{
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                LOG_INFO("threadpool update and download, run task,from thread2, i:%d\n", i);
                TaskReturn taskreturn;
                taskreturn.code = i;
                taskreturn.task_type = TASK_TYPE_RUNING;
                return taskreturn;
                }, 4);
            std::lock_guard<std::mutex> lg(mutex);
            LOG_DEBUG("enqueu one task, priority:4\n");
            TaskQueue taskqueue = threadpool_down_update.get_task_queue();
            auto queue = taskqueue->get_inner_queue();
            LOG_DEBUG(">>> test >> printf task after enqueue:%d\n", queue.size());
            for (const auto& task : queue) {
                printf("%d\n", task.second);
            }
        }
        LOG_INFO("generator 2, task generator end! 1000 task!\n");
        });
    std::thread thread_task_generator_3([&]() {
        for (int i = 0;i < 100;i++) {
            threadpool_down_update.enqueue_task_sync([=]()->TaskReturn{
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                LOG_INFO("threadpool update and download, run task,from thread2, i:%d\n", i);
                TaskReturn taskreturn;
                taskreturn.code = i;
                taskreturn.task_type = TASK_TYPE_RUNING;
                return taskreturn;
                }, -1);
            std::lock_guard<std::mutex> lg(mutex);
            LOG_DEBUG("enqueu one task, priority:-1\n");
            TaskQueue taskqueue = threadpool_down_update.get_task_queue();
            auto queue = taskqueue->get_inner_queue();
            LOG_DEBUG(">>> test >> printf task after enqueue:%d\n", queue.size());
            for (const auto& task : queue) {
                printf("%d\n", task.second);
            }
        }
        LOG_INFO("generator 3, task generator end! 1000 task!\n");
    });
    if (thread_task_generator_1.joinable())
        thread_task_generator_1.join();
    if (thread_task_generator_2.joinable())
        thread_task_generator_2.join();
    if (thread_task_generator_3.joinable())
        thread_task_generator_3.join();

    LOG_EXTR("enter sleep\n");
    sleep(20);
    threadpool_down_update.stop_workers_sync();
    // threadpool_run_testbed.stop_workers_sync();

    LOG_EXTR("sleep out\n");

#endif


}
#endif
inline void test_monitor_1() {
    //test reference collapse
    //start monitor
    #if 0
    LoopMonitor<TaskReturn> loop_monitor([](ShareTaskInfo<TaskReturn> taskinfo) {
        auto timer = taskinfo->get_timer();
        auto future = taskinfo->get_future();
    LOG_EXTR(
        "\nget elapsed ms:%lld\n"
        "get elapsed end ms:%lld\n"
        "get obj serial:%lu\n"
        "get obj count:%lu\n",
        timer->get_elapsed_ms(),
        timer->get_end_elapsed_ms(),
        taskinfo->get_obj_serial(),
        taskinfo->get_obj_count());
    if (timer->is_end()) {
        //fetach task return value
        unsigned long task_obj_serial = taskinfo->get_obj_serial();
        try{
            TaskReturn ret = future.get();
            LOG_INFO("task is end! get return value:%d, type: % d, task obj serial : % lu\n", ret.code, ret.task_type, task_obj_serial);
                //actual process

        }
        catch (std::exception& e) {
            LOG_ERROR("task catch: %s\n, task obj serial: %lu\n", e.what(), task_obj_serial);
            LOG_INFO("end exception!\n");
        }
    }
    return timer->is_end();
        }, 1000, 10000);
    // LoopMonitor<TaskReturn> loop_monitor(monitor_1, 1000, 10000);
    auto loop_list = loop_monitor.start();
    threadpool_down_update.bind_monitor_list(loop_list);
    threadpool_run_testbed.bind_monitor_list(loop_list);
    //threadpool
    threadpool_down_update.start_workers();
    threadpool_run_testbed.start_workers();

   //task generator
    std::thread thread2([&]() {
        for (int i = 0;i < 1000;i++) {
            threadpool_down_update.enqueue_task_sync([=]()->TaskReturn{
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                LOG_INFO("threadpool update and download, run task,from thread2, i:%d\n", i);
                TaskReturn taskreturn;
                taskreturn.code = i;
                taskreturn.task_type = TASK_TYPE_RUNING;
                return taskreturn;
                });
        }
        LOG_INFO("thread2, task generator end! 1000 task!\n");
    });
    std::thread thread3([&]() {
        for (int i = 0;i < 1000;i++) {
            threadpool_run_testbed.enqueue_task_sync([=]()->TaskReturn {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                LOG_INFO("threadpool run testbed, run task,from thread3, i:%d\n", i);
                TaskReturn taskreturn;
                taskreturn.code = i;
                taskreturn.task_type = TASK_TYPE_UPLOAD ;
                return taskreturn;
                });
        };
        LOG_INFO("thread3, task generator end! 2000 task!\n");
    });
    if (thread2.joinable())
        thread2.join();
    if (thread3.joinable())
        thread3.join();

    //thread2.detach();
    //thread3.detach();
    //sleep(30);
    LOG_EXTR("enter sleep\n");
    sleep(20);
    threadpool_down_update.stop_workers_sync();
    threadpool_run_testbed.stop_workers_sync();

    LOG_EXTR("sleep out\n");

#endif


}
GF_NAMESPACE_END(main_service)

#endif
#pragma once
#include <vector>
#include <cassert>
    //remainder: 获得一个数在一个范围内的相对位置
    //周期性处理数据，将数据映射到一个范围内，判断值范围，奇偶
    //范围4时，1->1, 2->2, 5 -> 1, 7->3

    //环形队列的使用场景:
    //1. 本质上就是存储，存储特色: 固定长度，允许覆盖push，保留定长范围内的最新数据
    //2. 缓冲区管理, 音视频数据

    //模型
    //原地自转贪吃蛇: 长度固定，拥有头部和尾部，吃一个元素在尾部增加
    //圆形场地的周长作为蛇的最大长度
    //吞食:
    //在未达到最大长度前(蛇尾未到达蛇头前)，蛇的头部不动，尾部依次增长
    //当蛇尾即将增长到达蛇头位置，蛇头吐出一个单位/后缩一个单位(即将原蛇头位置存放新添加的尾部，原蛇头后方单位作为新蛇头)
    //吐食:
    //1. 被动吐食， 蛇尾到达蛇头时，必须吐出，让位给新增的尾部，头部主动后缩一个单位
    //2. 主动吐食，主动吐食，则提前预留位置给尾部
    //3. 二者区别，被动吐食是等同于直接覆盖了，被覆盖数据是没有被使用到的，主动吐食是将数据抛出给外部，留下的是空位
    //4. 最糟糕的情况就是整条蛇一直处于被动吐食(数据覆盖)，即进食后 蛇头和蛇尾是相邻的
    //5. 只有在不容纳任何数据的情况下，蛇头和蛇尾才会在同一个位置，最远之间相隔 max-1(idx_tail-idx_head)， 最近相隔1
    //6. 通过在进食这个单位操作过程中，计算进食后尾部位置与头部是否相同，可以得知是否数据被覆盖，所以overrun的统计是在这个单位操作里实现的
    //7. 吐食越快(消费越快) -> 进食越能有保障，数据都不会被覆盖, 所以循环队列可以用于保证 以稳定的负载能力（限定的负载能力）去消费最新的数据
    //8. 对外提供的功能: 直接 覆盖push，pop front， 以及一个覆盖统计数据的获取，以及常规的容器数据访问
    //9. 如何判断队列为空或者全满?  
    //通过判断头尾索引可以或者是否为空
    //如果头尾相近时，既有可能是只有两个元素，也有可能是满元素
    //当头在前，尾在后，即判断头尾节点在真实数组中的相对位置，只要头节点的索引大于尾节点并且相邻则说明此时头尾相接，是full状态
    //通过取余操作，获得在数组中的相对位置，(cur_tail+i ）%max==cur_head
    //为什么要浪费一个空间？为了方便判断，用空间换取时间?解决一些判定条件的冲突?

    //size = 5
    //0 1 2 3 4
    //0 0 0 0 0
    //1 0 0 0 0 head = 0, tail = 0
    //1 2 0 0 0 head = 0, tail = 
    //1 2 3 4 5  
    //6 2 3 4 5 
    //6 7 3 4 5
    //6 7 8 4 5
    //6 7 8 9 5
    //6 7 8 9 10
    //11 7 8 9 10
template<typename T>
class circular_queue {
public:
    circular_queue() = default;
    explicit circular_queue(size_t in_max_num);
    //copy
    circular_queue(const circular_queue&) = default;
    circular_queue& operator=(const circular_queue&) = default;
    //move
    circular_queue(circular_queue&& in_obj);
    circular_queue& operator=(circular_queue&& in_obj);
    //destruct
    ~circular_queue() = default;

    //outside behavior : 1. pushback ->  if is reach max num -> strip front item and pushback(override the oldest data) 2. pop front -> to get oldest and leave space for it
    //inner implementation: if not reach max num : to pushback -> if reach, to replace old item
    //key how to mark the oldest item? by acculate idx of item, and the front pointer to oldest item, and the end pointer to the
    void push_back(T&& in_item);
    //data access
    const T& front() const;
    T& front();
    void pop_front();
    //just const reference access
    const T& at(size_t in_idx) const;

    //front and pop combination
    void get_and_pop_front(const T& out_item) const;
    void get_and_pop_front(T& out_item);
    //size check
    bool empty() const;
    size_t size() const;
    bool full() const;
    size_t override_count() const;
    void reset_override_count();

private:
    void copy_moveable_(circular_queue&& in_moved_target);

    //max size
    size_t max_num_;
    //over count
    size_t over_counter_;
    //inner container
    std::vector<T> inner_c_;
    //queue pointer
    typename std::vector<T>::size_type head_;
    typename std::vector<T>::size_type tail_;
};

template<typename T>
inline circular_queue<T>::circular_queue(size_t in_max_num)
    : max_num_(in_max_num), head_(0), tail_(0), over_counter_(0) {
}

template<typename T>
inline circular_queue<T>::circular_queue(circular_queue&& in_obj)
{
}

template<typename T>
inline circular_queue<T>& circular_queue<T>::operator=(circular_queue&& in_obj)
{
    // TODO: insert return statement here
}

template<typename T>
inline void circular_queue<T>::push_back(T&& in_item)
{
}

template<typename T>
inline const T& circular_queue<T>::front() const
{
    // TODO: insert return statement here
}

template<typename T>
inline T& circular_queue<T>::front()
{
    // TODO: insert return statement here
}

template<typename T>
inline void circular_queue<T>::pop_front()
{
}

template<typename T>
inline const T& circular_queue<T>::at(size_t in_idx) const
{
    // TODO: insert return statement here
}

template<typename T>
inline void circular_queue<T>::get_and_pop_front(const T& out_item) const
{
}

template<typename T>
inline void circular_queue<T>::get_and_pop_front(T& out_item)
{
}

template<typename T>
inline bool circular_queue<T>::empty() const
{
    return false;
}

template<typename T>
inline size_t circular_queue<T>::size() const
{
    return size_t();
}

template<typename T>
inline bool circular_queue<T>::full() const
{
    return false;
}

template<typename T>
inline size_t circular_queue<T>::override_count() const
{
    return size_t();
}

template<typename T>
inline void circular_queue<T>::reset_override_count()
{
}

template<typename T>
inline void circular_queue<T>::copy_moveable_(circular_queue&& in_moved_target)
{
}

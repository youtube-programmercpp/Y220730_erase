#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <numeric>

template<class T>void erase_odd_elements(T& a)
{
    //奇数だったら削除…奇数の要素群を削除する
    for (auto it = a.begin(); ; ) {//iterator
        if (it == a.end())
            break;
        else if (*it & 1) //奇数のとき
            it = a.erase(it);
        else //偶数のとき
            ++it;            
    }
}
template<class T>void erase_odd_elements_2(T& a)
{
    auto last = a.end();
    auto first = std::remove_if(a.begin(), last, [](int value)->bool { return value & 1; });
    a.erase(first, last);
}




template
< class  T //std::list<int> か std::vector<int> など
, size_t N //要素数
, class generator_type//ラムダ式
>T make_random_array(const generator_type& gen)
{
    T a(N);
    for (auto it = a.begin(); ; ) {//iterator
        if (it == a.end())
            break;
        else
            *it++ = gen();
    }
    return a;
}


int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    using T =
#if 1
        std::vector<int>
#else
        std::list<int>
#endif
        ;
    static constexpr size_t N = 1024 * 1024;
    auto a = make_random_array<T, N>
        ([&distrib, &gen]() { return distrib(gen); }
        );
#if 0
    erase_odd_elements(a);
#else
    erase_odd_elements_2(a);
#endif
}

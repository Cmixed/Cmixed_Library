#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <memory>
#include <format>
#include <thread>

#include "zzj.hpp"

using namespace std;

template <typename IteratorType>
void iteratorTraitsTest(IteratorType it)
{
    typename iterator_traits<IteratorType>::value_type temp;   
    temp = *it;
    cout << temp << endl;
}

template <typename InputIter, typename OutputIter>
void myCopy(InputIter begin, InputIter end, OutputIter target)
{
    for ( auto iter { begin }; iter != end; ++iter, ++target) {
        *target = *iter;
    }
}

template <typename InputIter >
auto sum(InputIter begin, InputIter end)
{
    auto sum { *begin };
    for (auto iter { ++begin }; iter != end; ++iter) {
        sum += *iter;
    }
    return sum;
}

int main()
{
    zzj::LogCtrl.is_Log = true;
    zzj::LogCtrl.LogTerminalCtrl.is_logFileName = true;

    std::vector<int> vec { 8, 2, 3, 4, 5, 6, 7};

    std::ranges::sort(vec);

    for (auto i : vec) {
        cout << i << " ";
    } 

    auto elementVector { make_unique<vector<int>>(10) };

    elementVector->push_back(1);
    std::jthread t1 { [](int x) { std::cout << x << std::endl; }, 1 };

    std::cout << std::format("\nsize: {}\n", elementVector->size());

    auto basic_lambda = [](int x) -> auto { zzj::Log give_me_a_name("Hello World", zzj::ColorName::BLUE); 
                                            return true; };
    basic_lambda(10);

    // using namespace zzj::log;
    auto x { " "sv};
    auto xl { "form"_log};

    auto b { " "sv};
}
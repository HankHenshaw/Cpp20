#include <iostream>
#include <set>
#include <ranges>
#include <algorithm>
#include <span>

void rangesExamples()
{
    std::vector vec{1,2,3};
    //Ranges небольшие примеры
    std::vector vec_range{1,2,3,4,5,6,7,8,9,10};
    auto res { vec_range | std::views::filter([](const auto& val){return val&1;}) // 1 | 3 | 5 | 7 | 9 |
                         | std::views::transform([](const auto& val){return val*val;})  // 1 | 9 | 25 | 49 | 81 |
                         | std::views::drop(2)  // 25 | 49 | 81 |
                         | std::views::reverse  // 81 | 49 | 25 |
                         | std::views::transform([](int val){return std::to_string(val);})}; // "81" | "49" | "25" |
    std::ranges::copy(res, std::ostream_iterator<std::string>(std::cout, " | "));
    std::cout << '\n';

    auto iter = std::ranges::min_element(vec);
    std::cout << *iter << '\n';

    //1 - subrange комбинирует пару итераторов во view
    std::multiset<int> msetOfInts{1,2,3,5,7,2,2,4,3};
    auto pair = std::ranges::equal_range(msetOfInts, 3);
    auto subrange = std::ranges::subrange(pair);
    std::ranges::copy(subrange, std::ostream_iterator<int>(std::cout, " | "));
    std::cout << '\n';
}
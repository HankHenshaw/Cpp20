//Остальные нововведения С++20

#include <cmath>
#include <span>
#include <array>
#include <ranges>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <bit>
#include <bitset>
#include <vector>
#include <numbers>
#include <compare>
#include <type_traits>
#include <map>
#include <thread>
#include <stop_token>
#include <concepts>
/* Gcc 10.2 не поддерживает
 * #include <source_location> 
 * #include <semaphore>
 * #include <barrier>
 * #include <latch> */

using namespace std::literals::chrono_literals;

struct two_t{};
template<typename T>
constexpr auto operator^(T base, two_t) {return base*base;}

template<typename T>
void ordering()
{
    if constexpr (std::is_same_v<T, std::strong_ordering>)
        std::cout << "strong ordering\n";
    else if constexpr (std::is_same_v<T, std::weak_ordering>)
        std::cout << "weak ordering\n";
    else if constexpr (std::is_same_v<T, std::partial_ordering>)
        std::cout << "partial ordering\n";
    else
        std::cout << "illegal comparison result type\n";
}

struct weakOrdering
{
    int m_val;
    weakOrdering(int val) : m_val(val) {}
};

constexpr std::weak_ordering operator<=>(const weakOrdering& lhs, const weakOrdering& rhs)
{
    return lhs.m_val <=> rhs.m_val;
}



void span()
{
    //span - вью над последовательно расположенними объектами, который не владее ими
    std::cout << "\n\nSpan:\n";
    std::array<int, 5> arr{1,2,3,4,5};
    std::span span{arr};
    
    std::ranges::copy(span, std::ostream_iterator<int>(std::cout, "|"));
    std::cout << '\n';

    for(auto &val: arr) val *= val;

    std::ranges::copy(span, std::ostream_iterator<int>(std::cout, "|"));
    std::cout << '\n';
}

void bit()
{
    std::cout << "\n\nBit:\n";

    std::endian::native == std::endian::little ? std::cout << "Little Endian\n" : std::cout << "Big Endian\n";

    // gcc 10.2 не поддерживает bit_cast
    // unsigned int ui = 0xffffffff;
    // int si = std::bit_cast<int>(ui);

    // std::cout << "Unsigned int = " << ui << '\n'
    //           << "Signed int   = " << si << '\n';

    //has_single_bit проверяет является ли интегральная переменная степенью 2-ки
    std::cout << std::has_single_bit(1u) << '\n'; //2^0
    std::cout << std::has_single_bit(2u) << '\n'; //2^1
    std::cout << std::has_single_bit(4u) << '\n'; //2^2

    //std::bit_ceil находит минимальное число которое является степенью 2-ки, но не ниже чем переданная интегральная переменная
    std::cout << std::bit_ceil(5u)  << '\n';// 101   -> 1000
    std::cout << std::bit_ceil(16u) << '\n';// 10000 -> 10000

    //std::bit_floor находит максимальную степерь 2-ки, которая не больше чем переданная интегральная переменная, при 0 вернет 0
    std::cout << std::bit_floor(0u) << '\n'; // 0   -> 0
    std::cout << std::bit_floor(1u) << '\n'; // 1   -> 1
    std::cout << std::bit_floor(7u) << '\n'; // 111 -> 100

    //std::bit_width считает кол-во бит необходимых для хранения переданного значения, при 0 вернет 0
    std::cout << std::bit_width(0u)   << '\n'; // 0   -> 0
    std::cout << std::bit_width(255u) << '\n'; // 255 -> 8
    std::cout << std::bit_width(256u) << '\n'; // 255 -> 9

    //std::rotl вычисляет результат битового поворота налево переданного значение на определенное кол-во позиций
    std::cout << std::rotl(5u, 0)   << '\n'; // 111 -> 111
    std::cout << std::rotl(1u, 2)   << '\n'; // 1   -> 100
    std::cout << std::rotl(1u, -30) << '\n'; // 1   -> 100

    //std::rotr вычисляет результат битового поворота направо переданного значение на определенное кол-во позиций
    std::cout << std::rotr(5u, 0)  << '\n'; // 111  -> 111
    std::cout << std::rotr(1u, 30) << '\n'; // 1    -> 100
    std::cout << std::rotr(4u, 2)  << '\n'; // 100  -> 1

    //std::countl_zero возвращает кол-во последоватьльных нулей, начиная со старшего бита
    std::cout << std::countl_zero(0u) << '\n';   // 32
    std::cout << std::countl_zero(128u) << '\n'; // 24

    //std::countl_one возвращает кол-во последоватьльных единиц, начиная со старшего бита
    unsigned char ch = 253;
    std::cout << std::countl_one(1u) << '\n'; // 0
    std::cout << std::countl_one(ch) << '\n'; // 6

    //std::countr_zero возвращает кол-во последоватьльных нулей, начиная с младшего бита
    std::cout << std::countr_zero(1u) << '\n'; // 0
    std::cout << std::countr_zero(8u) << '\n'; // 3

    //std::countr_one возвращает кол-во последоватьльных единиц, начиная с младшего бита
    std::cout << std::countr_one(7u) << '\n'; // 3
    std::cout << std::countr_one(8u) << '\n'; // 0

    //std::popcount возвращает кол-во единиц в переданной переменной
    std::cout << std::popcount(1u)   << '\n'; // 1
    std::cout << std::popcount(255u) << '\n'; // 8
}

void numbers()
{
    std::cout << "\n\nMathematical constants:\n";

    std::cout << "E = "          << std::numbers::e          << '\n'
              << "log2e = "      << std::numbers::log2e      << '\n'
              << "log10e = "     << std::numbers::log10e     << '\n'
              << "pi = "         << std::numbers::pi         << '\n'
              << "inv_pi = "     << std::numbers::inv_pi     << '\n'
              << "inv_sqrtpi = " << std::numbers::inv_sqrtpi << '\n'
              << "ln2 = "        << std::numbers::ln2        << '\n'
              << "ln10 = "       << std::numbers::ln10       << '\n'
              << "sqrt2 = "      << std::numbers::sqrt2      << '\n'
              << "sqrt3 = "      << std::numbers::sqrt3      << '\n'
              << "inv_sqrt3 = "  << std::numbers::inv_sqrt3  << '\n'
              << "egamma = "     << std::numbers::egamma     << '\n'
              << "phi = "        << std::numbers::phi        << '\n';

    constexpr two_t ²;
    std::cout << (std::sin(std::numbers::e)^²) + (std::cos(std::numbers::e)^²) << '\n'; // 1
}

void compare()
{
    //std::strong_ordering - подразумевает заменяемость, т.е если a эквивалентно b, то f(a) так же эквиваленто f(b). Иными словами
    //эквивалентные значения неразличимы. Так же не допускаются несравнимые значения, т.е a<b;a==b;a>b должны быть true;
    ordering<std::compare_three_way_result_t<char>>();
    //std::weak_ordering - тоже что и strong_ordering, только там не подрузамевается заменяемость, т.е. если a эквивалентно b, то
    //f(a) может быть не эквивалентен f(b), т.е. эквивалентные значения могут быть различимы
    ordering<std::compare_three_way_result_t<weakOrdering>>();
    //std::partial_ordering - похож на weak_ordering, но тут допускаются несравнимые значения, т.е a<b;a==b;a>b могут быть false
    ordering<std::compare_three_way_result_t<float>>();

    auto f1 = 0.f;
    auto f2 = 0.f;
    auto f3 = 0.1f;
    std::cout << std::is_eq  (f1 <=> f2) << '\n';
    std::cout << std::is_neq (f1 <=> f3) << '\n';
    std::cout << std::is_lt  (f1 <=> f3) << '\n';
    std::cout << std::is_lteq(f1 <=> f2) << '\n';
    std::cout << std::is_gt  (f3 <=> f2) << '\n';
    std::cout << std::is_gteq(f1 <=> f2) << '\n';
}

// void sourceLocation(const std::source_location& loc = std::source_location::current())
// {
//     std::cout << "File name: "     << loc.file_name()     << '\n'
//               << "Function name: " << loc.function_name() << '\n'
//               << "Line: "          << loc.line()          << '\n'
//               << "Column: "        << loc.column()        << '\n';
// }

void tokenFoo(std::stop_token token)
{
    for(size_t i = 0; !token.stop_requested(); ++i)
    {
        std::cout << i << '\n';
        std::this_thread::sleep_for(1s);
    }
    std::cout << "Stopped\n";
}

void stopToken()
{
    std::jthread jth(tokenFoo);

    std::stop_callback cb{jth.get_stop_token(), []{std::cout << "Callbacked\n";}};

    if(jth.get_stop_token().stop_possible())
    {
        std::this_thread::sleep_for(3s);
        jth.request_stop();
    }
}

void templatedLambda()
{
    auto tlambda1 = []<typename... Args>(Args&& ...args){(std::cout << ... << args) << '\n';};
    tlambda1(5, '\n', 6.1f, '\n', "string");

    auto tlambda2 = []<std::integral T>(T val){std::cout << val << '\n';};
    tlambda2(50);
//    tlambda2(2.f); // Error: float не является интегральным типом
}

consteval size_t fiboEval(size_t n)
{
    return std::round(std::pow(std::numbers::phi, n)/std::sqrt(5));
}

void othersExamples()
{
    span();
    bit();
    numbers();
    compare();
    stopToken();
    templatedLambda();

    std::cout << fiboEval(10) << '\n';
//    sourceLocation();
}
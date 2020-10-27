//Остальные нововведения С++20

#include <string_view>
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
#include <numeric>
/* Gcc 10.2 не поддерживает
 * #include <format>
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

void cinit()
{
    constinit static int x = 5;
    constinit thread_local int th_x = 5;
    //constinit int x = 5; // Error: constinit может быть применен только к статическим или потоковым переменным
}

void attribute(int val)
{
    //likely и unlikely помогают компилятору оптимизировать кейсы которые помечены как наиболее/наимение вероятные 
    switch (val)
    {
    [[likely]]   case 1:
        std::cout << "Likely\n";
        break;
    [[unlikely]] case 2:
        std::cout << "Unlikely\n";
        break;
    case 3:
        std::cout << "Fallthrough\n";
        [[fallthrough]];
    default:
        std::cout << "Default\n";
        break;
    }
}

struct str
{
    int m_i;
    double m_d;
    std::string_view m_sv;
    float m_f;
};

void designatedInitiallizer()
{
    str s{.m_i = 5, .m_d = 0.5, .m_sv = "Hello World"}; // m_f будет инициализированна 0
//    str s2{.m_d = 0.5, .m_i = 5, .m_sv = "Hello World"}; // Error: инициализация не соответствует порядку объявления
    std::cout << s.m_i << "|" << s.m_d << "|" << s.m_sv << "|" << s.m_f << '\n';
}

template<typename SortedContainter>
bool binSearch(const SortedContainter &cont, size_t begin, size_t end, const typename SortedContainter::value_type &val)
{
    if(end >= begin)
    {
        auto mid = std::midpoint(begin, end);
        if(cont[mid] == val) return true;
        else if(cont[mid] > val) return binSearch(cont, begin, mid - 1, val);
        else if(cont[mid] < val) return binSearch(cont, mid + 1, end, val);
    }
    return false;
}

void midPoint()
{
    int x = -5;
    int y = 5;
    std::cout << "Mid Point between " << x << " and " << y << " = " << std::midpoint(x,y) << '\n';

    std::vector<int> v(10,0);
    std::iota(std::begin(v), std::end(v), 0);
    for(int i = 0; i < 11; ++i)
    {
        std::cout << i << " - " << binSearch(v, 0, v.size(), i) << '\n';
    }    
}

void lerp()
{
    int x = 0;
    int y = 10;
    std::cout << "Interpolation:\n";
    std::cout << std::lerp(x,y,0.5f) << '\n'; // 3
    std::cout << std::lerp(x,y,0.3f) << '\n'; // 5
    std::cout << "Extrapolation:\n";
    std::cout << std::lerp(x,y,1.5f) << '\n'; // 15
    std::cout << std::lerp(x,y,2.0f) << '\n'; // 20
}

void erase()
{
    std::vector<int> v(10,5);
    std::iota(std::begin(v), std::end(v), 0);
    std::cout << "Before Erase:\n";
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, "|"));
    auto val = std::erase_if(v, [](int i){return i&1;}); // 0 2 4 6 8
    std::cout << "\nAfter Erase:\n";
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, "|"));
    std::cout << '\n' << val << " elements was erased\n";
}

void strStrVw()
{
    std::string      str{"Hello, World!"};
    std::string_view svw{"Welcome Cpp20"};

    std::cout << "Is str starts with Hallo? - " << str.starts_with("Hallo") << '\n';
    std::cout << "Is str ends with orld!? - "   << str.ends_with("orld!")   << '\n';
    std::cout << "Is svw starts with Welco? - " << svw.starts_with("Welco") << '\n';
    std::cout << "Is svw ends with Cpp23? - "   << str.ends_with("Cpp23")   << '\n';
}

void ssize()
{
    std::vector v{1,2,3,4,5};
    auto size  =  std::size(v);
    auto ssize = std::ssize(v);

    std::cout << std::is_signed<decltype(size)>::value  << '\n'; // false
    std::cout << std::is_signed<decltype(ssize)>::value << '\n'; // true

    std::cout << std::is_unsigned<decltype(size)>::value  << '\n'; // true
    std::cout << std::is_unsigned<decltype(ssize)>::value << '\n'; // false
}

void othersExamples()
{
    span();
    bit();
    numbers();
    compare();
    stopToken();
    templatedLambda();
    attribute(1);
    attribute(2);
    attribute(3);
    attribute(4);
    designatedInitiallizer();
    midPoint();
    lerp();
    erase();
    strStrVw();
    ssize();
    std::cout << fiboEval(10) << '\n';
//    sourceLocation();
}
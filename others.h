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

struct two_t{};
template<typename T>
constexpr auto operator^(T base, two_t) {return base*base;}

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

void othersExamples()
{
    span();
    bit();
    numbers();
}
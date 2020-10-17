/* Concepts - именованные требования для построения параметров шаблона
 * Предикаты вычисляются во время компиляции
 * Стандартная библиотека предоставляет некоторые готовые концепты 
 */

#include <compare>
#include <concepts>
#include <ranges>
#include <span>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <string_view>
#include <forward_list>
#include <deque>

struct A
{};

struct B : A
{};

struct C
{;
    ~C() noexcept(0) {};
};

struct D
{
private:
    int m_val;
public:
    friend bool operator==(const D& lhs, const D& rhs) {return lhs.m_val == rhs.m_val;};
    D(int val) : m_val(val) {};
};

struct E
{
    E() {};
    E(E&& rhs) = delete;
};

struct F
{
private:
    int m_val;
public:
    friend bool operator==(const F& lhs, const F& rhs) {return lhs.m_val == rhs.m_val;};
    friend bool operator<(const F& lhs, const F& rhs) {return lhs.m_val < rhs.m_val;};
    friend bool operator>(const F& lhs, const F& rhs) {return lhs.m_val > rhs.m_val;};
    friend bool operator<=(const F& lhs, const F& rhs) {return !(lhs.m_val > rhs.m_val);};
    friend bool operator>=(const F& lhs, const F& rhs) {return !(lhs.m_val < rhs.m_val);};
    F(int val) : m_val(val) {};
};

/*Концепты из concepts хэдера*/
/*--------Core language concepts--------*/
//1 - same_as указывает на то, что типы одинаковые
template<typename T, typename U> requires std::same_as<T, U>
bool isSame(const T& a, const U& b)
{
    return 1;
}
//2 - derived_from указывает на то, что один тип унаследован от другого
template<typename T, typename U> requires std::derived_from<T, U>
bool isDerived(const T& a, const U& b)
{
    return 1;
}
//3 - convertible_to указывает на то, что один тип неявно может быть сконвертирован в другой тип
template<typename T, typename U> requires std::convertible_to<T,U>
U convertible(const T& a)
{
    return a;
}
//4 - common_reference_with указывает на то, что типы имеют общий ссылочный тип
template<typename T, typename U> requires std::common_reference_with<T,U>
bool isCommonRefWith(const T& a, const U& b)
{
    return 1;
}
//5 - common_with указывает на то, что 2 типа имеют общий тип
template<typename T, typename U> requires std::common_with<T,U>
bool isCommonWith(const T& a, const U& b)
{
    return 1;
}
//6 - integral указывает на то, что тип является интегральным
template<std::integral T>
bool intergalFoo(const T& a, const T& b)
{
    return a == b;
}
//7 - signed_integral указывает на то, что тип является знаковым интегральным
template<std::signed_integral T>
bool signedFoo(const T& a, const T& b)
{
    return a == b;
}
//8 - unsigned_integral указывает на то, что тип является беззнаковым интегральным
template<std::unsigned_integral T>
bool unsignedFoo(const T& a, const T& b)
{
    return a == b;
}
//9 - floating_point указывает на то, что тип является плавующим
template<std::floating_point T>
bool floatingFoo(const T& a, const T& b)
{
    return std::abs(a - b) < 0.00001;
}

//10 - assignable_from указывает на то, что тип может быть присвоет из другого типа
template<typename T, typename U> requires std::assignable_from<T, U>
bool isAssignable(T a, U b)
{
    return 1;
}

//11 - std::swappable_with указывает на то, что 2 типа можно поменять друг с другом
template<typename T, typename U> requires std::swappable_with<T, U>
bool isSwapWith(const T& a, const U& b)
{
    return 1;
}

//12 - std::destructible указывает на то, что тип может быть уничножен
template<std::destructible T>
bool isDestruct(const T& a)
{
    return 1;
}

//13 - std::constructible_from указывает на то, что переменная типа может быть сконструирована из набора аргументов
template<typename T, typename... Args> requires std::constructible_from<T, Args...>
bool isConstruct(const T& a, const Args... args)
{
    return 1;
}

//14 - std::default_initializable указывает на то, что тип может дефолтно сконструирован
template<std::default_initializable T>
bool isDefaultConstruct(const T& a)
{
    return 1;
}

//15 - std::move_constructible указывает на то, что тип может быть перемещен
template<std::move_constructible T>
bool isMoveConstruct(const T& a)
{
    return 1;
}

//16 - std::copy_constructible указывает на то, что тип может быть скопирован
template<std::copy_constructible T>
bool isCopyConstruct(const T& a)
{
    return 1;
}
/*-----------------------------------*/
/*--------Comparison concepts--------*/
//17 - std::equality_comparable
//17 - std::equality_comparable_with
//указывает на то что, оператор == является эквивалентным, т.е. если t == u, то u == t
template<std::equality_comparable T>
bool isEqualityComparable(const T& a)
{
    return 1;
}
//18 - std::totally_ordered
//18 - std::totally_ordered_with
//указывает на то что, операторы сравнения дают общий(полный) порядок
template<std::totally_ordered T>
bool isTotallyOrdered(const T& a)
{
    return 1;
}
/*-----------------------------------*/
/*----------Object concepts----------*/
//19 - std::movable (указывает на то, что тип можно перемешать и свопать)
template<std::movable T>
bool isMovable(const T& val)
{
    return 1;
}
//20 - std::copyable (указывает на то, что тип можно перемешать, копировать и свопать)
template<std::copyable T>
bool isCopyable(const T& val)
{
    return 1;
}
//21 - std::semiregular (указывает на то, что тип можно перемешать, копировать, свопать и может быть дефолтно сконструирован)
template<std::semiregular T>
bool isSemiregular(const T& val)
{
    return 1;
}
//22 - std::regular (указывает на то, что тип является semiregular и equality_comparable)
template<std::regular T>
bool isRegular(const T& val)
{
    return 1;
}
/*-----------------------------------*/
/*---------Callable concepts---------*/
//23 - std::invocalbe (указывает на то, что тип может быть вызван с переданной пачкой аргументов)
template<typename T, typename... Args> requires std::invocable<T, Args...>
bool isInvokable(T t, Args... args)
{
    return 1;
}
//24 - std::predicate (указывает на то, что тип является булевым предикатов)
template<typename T, typename... Args> requires std::predicate<T, Args...>
bool isPredicate(T t, Args... args)
{
    return 1;
}
//25 - std::relation  (указывает на то, что тип является бинарным отношением)
//от predicate отличается тем что для любой комбинации U и I std::predicate должен вернуть true
//std::predicate<U,U> && std::predicate<I,I> && std::predicate<U,I> && std::predicate<I,U>
template<typename T, typename U, typename I> requires std::relation<T, U, I>
bool isRelation(T t, const U& a, const I& b)
{
    return 1;
}
//26 - std::equivalence_relation (указывает, что отношение является эквивалентным)
//от relation отличается тем что проверяется еще эквивалентность, т.е. r(x,x) всегда true; r(a,b) == r(b,a); +  транзитивность
//r(a,b) == true && r(b,c) == true -> r(a,c) == true
//Данные различия чисто семантические!
template<typename T, typename U, typename I> requires std::equivalence_relation<T, U, I>
bool isEquivalenceRelation(T t, const U& a, const I& b)
{
    return 1;
}
//27 - std::strict_weak_order (указывает, что отношение является со строго слабым порядком)
//от relation отличается тем что r(x,x) всегда false, транзитивностью как и в эквивалентности, 
//так же если e(a,b) !r(a,b) && !r(b,a) тогда е транзитавна e(a,b) && e(b,c) -> e(a,c)
//Данные различия чисто семантические!
template<typename T, typename U, typename I> requires std::strict_weak_order<T, U, I>
bool isStrictWeakOrdered(T t, const U& a, const I& b)
{
    return 1;
}
/*-----------------------------------*/
/*Концепты из concepts хэдера*/
/*Кастомные концепты*/
//1 - простой концепт указывает на наличие у типа метода custom
template<typename T>
concept Custom = requires(T& a)
{
    {a.custom()};
};

template<Custom T>
bool isCustom(const T& a)
{
    return 1;
}

struct G
{
    void custom() {};
};

//2 - простой концепт указывает на наличие у типа метода begin и end
template<typename T>
concept Container = requires(T& a)
{
    {a.begin()};
    {a.end()};
};

template<Container T>
class ContainerWrapper
{
    T m_val;
public:
    ContainerWrapper(const T& val) : m_val(val) {};
    void size() const {std::cout << "Size: " << m_val.size() << '\n';};
};
/*Кастомные концепты*/
/*Концепты из ranges хэдера*/
//1 - range указывает на то что, данный тип является диапазоном
template<std::ranges::range T>
bool isRange(const T& a)
{
    return 1;
}
//2 - sized_range указывает на то что, данный диапазон знает его размер за константное время
template<std::ranges::sized_range T>
bool isSizedRange(const T& a)
{
    return 1;
}
//3 - view указывает на то что, данный диапазон является представлением и исеет константное копирование/перемещение/присваивание
template<std::ranges::view T>
bool isView(const T& a)
{
    return 1;
}
//4 - input_range указывает на то что, данный диапазон c входным доступом
template<std::ranges::input_range T>
bool isInputRange(const T& a)
{
    return 1;
}
//5 - output_range указывает на то что, данный диапазон c выходным доступом
template<typename T, typename U> requires std::ranges::output_range<T,U>
bool isOutputRange(const T& a)
{
    return 1;
}
//6 - forward_range указывает на то что, данный диапазон c последовательным доступом
template<std::ranges::forward_range T>
bool isForwardRange(const T& a)
{
    return 1;
}
//7 - bidirectional_range указывает на то что, данный диапазон c двухсторонним доступом
template<std::ranges::bidirectional_range T>
bool isBidirectdRange(const T& a)
{
    return 1;
}
//8 - random_access_range указывает на то что, данный диапазон c произвольным доступом
template<std::ranges::random_access_range T>
bool isRandomAccessRange(const T& a)
{
    return 1;
}
//9 - contiguous_range указывает на то что, данный диапазон c последовательным расположением эл-тов
template<std::ranges::contiguous_range T>
bool isContiguousRange(const T& a)
{
    return 1;
}
//10 - common_range указывает на то что, данный диапазон возвращаят одинковый тип для begin и end
template<std::ranges::common_range T>
bool isCommonRange(const T& a)
{
    return 1;
}
//11 - viewable_range указывает на то что, данный диапазон можно безопасно конвертировать в представление
template<std::ranges::viewable_range T>
bool isViewableRange(const T& a)
{
    return 1;
}
/*Концепты из ranges хэдера*/

/*Концепты из compare хэдера*/
//1 - three_way_comparable/three_way_comparable_with указывает на то, что оператор <=> предоставляет устойчивый результат
//для переданных типов
template<typename T, typename U> requires std::three_way_comparable_with<T,U>
bool isThreeWay(const T& a, const T& b)
{
    return 1;
}
/*Концепты из compare хэдера*/
void conceptExamples()
{
    std::cout << "\nConcept Examples: \n";

    A a;
    B b;
    C c;
    D d(1);
    E e;
    F f(5);
    char ch1 = 'A';
    char ch2 = 1;
    int signedVal1 = 1;
    int signedVal2 = 1;
    unsigned int unsignedVal1 = 1;
    unsigned int unsignedVal2 = 1;
    float floatingVal1 = 1.0f;
    float floatingVal2 = 1.0f;
    char &ref1 = ch1;
    char &ref2 = ch2;
    int *ptr = new int{1};
    std::vector<int> vec;
    std::vector vec2{1,2,3};
    std::list list{1,2,3};
    std::string str{"Hello"};
    std::string_view str_view{"World"};
    int c_arr[42];
    std::span<int, 42> span{c_arr};
    std::forward_list<int> fl;
    std::deque<int> deq;

    /*Концепты из concepts хэдера*/
    std::cout << isSame(ch1, ch2) << '\n';
//    std::cout << isSame(ch1, unsignedVal1) << '\n'; // Error: не соответствие типов

    std::cout << isDerived(b, a) << '\n';
//    std::cout << isDerived(a, b) << '\n'; // Error: a не наследуется от b

    std::cout << convertible<char, int>(ch1) << '\n';
    std::cout << convertible<int, char>(signedVal1) << '\n';
//    std::cout << convertible<floatingVal1, char>(signedVal1) << '\n'; // Error: нельзя неявно привести float -> char

    std::cout << isCommonRefWith(list.begin(), list.end()) << '\n';
    std::cout << isCommonRefWith(vec2.begin(), vec.end()) << '\n';  
//    std::cout << isCommonRefWith(vec2.begin(), list.begin()) << '\n'; // Error

    std::cout << isCommonWith(list.begin(), list.end()) << '\n';
    std::cout << isCommonWith(vec2.begin(), vec.end()) << '\n';  
//    std::cout << isCommonWith(vec2.begin(), list.begin()) << '\n'; // Error

    std::cout << intergalFoo(signedVal1, signedVal2) << '\n';
    std::cout << intergalFoo(unsignedVal1, unsignedVal2) << '\n';
//    std::cout << intergalFoo(floatingVal1, floatingVal2) << '\n'; // Error: floatingVals - не интегральный тип

    std::cout << signedFoo(signedVal1, signedVal2) << '\n';
//    std::cout << signedFoo(signedVal1, unsignedVal1) << '\n'; // Error: unsignedVal1 - беззнаковый тип

    std::cout << unsignedFoo(unsignedVal1, unsignedVal2) << '\n';
//    std::cout << unsignedFoo(signedVal1, unsignedVal1) << '\n'; // Error: signedVal1 - знаковый тип

    std::cout << floatingFoo(floatingVal1, floatingVal2) << '\n';
//    std::cout << floatingFoo(floatingVal1, signedVal1) << '\n'; // Error: signedVal1 - интегральный тип

    std::cout << isAssignable<char&, int>(ref1, 2) << '\n';
//    std::cout << isAssignable(floatingVal1, floatingVal2) << '\n'; // Error: floatingVal1 - не lvalue ref

    std::cout << isSwapWith<std::vector<int>&, std::vector<int>&>(vec, vec2) << '\n';
//    std::cout << isSwapWith(vec, vec2) << '\n'; // Error: типы vec, vec2 выводятся как vector<int>, т.е. не как ссылочный тип 

    std::cout << isDestruct(a) << '\n';
    std::cout << isDestruct(ref1) << '\n';
    std::cout << isDestruct(ptr) << '\n';
//    std::cout << isDestruct(c) << '\n'; // Error: деструктор C может кинуть исключение
    delete ptr;

    std::cout << isConstruct(d, 5) << '\n';
//    std::cout << isConstruct(d, 5, 4) << '\n'; // Error: у класса D нет необходимого к-тора

    std::cout << isDefaultConstruct(ch1) << '\n';
    std::cout << isDefaultConstruct(vec) << '\n';
    std::cout << isDefaultConstruct(a) << '\n';
//    std::cout << isDefaultConstruct(d) << '\n'; // Error: у класса D нету дефолтного к-тора

    std::cout << isMoveConstruct(ch1) << '\n';
    std::cout << isMoveConstruct(a) << '\n';
//    std::cout << isMoveConstruct(c) << '\n'; // Error: у класса C определен деструктор который может кинуть исключение
//    std::cout << isMoveConstruct(e) << '\n'; // Error: move к-тор у класса Е помечен как delete

    std::cout << isCopyConstruct(ch1) << '\n';
    std::cout << isCopyConstruct(vec) << '\n';
    std::cout << isCopyConstruct(a) << '\n';
//    std::cout << isCopyConstruct(c) << '\n'; // Error: у класса C определен деструктор который может кинуть исключение
//    std::cout << isCopyConstruct(e) << '\n'; // Error: move к-тор у класса Е помечен как delete

    std::cout << isEqualityComparable(vec) << '\n';
    std::cout << isEqualityComparable(d) << '\n';
//    std::cout << isEqualityComparable(a) << '\n'; // Error: отсутствует оператор сравнения

    std::cout << isTotallyOrdered(vec) << '\n';
//    std::cout << isTotallyOrdered(d) << '\n'; //Error: оператор проверки на равенство есть,но остальных операторов сравнения нету
    std::cout << isTotallyOrdered(f) << '\n';

    std::cout << isMovable(ch1) << '\n';
    std::cout << isMovable(vec) << '\n'; 
//    std::cout << isMovable(c) << '\n'; // Error: у класса C определен деструктор который может кинуть исключение
//    std::cout << isMovable(e) << '\n'; // Error: move к-тор у класса Е помечен как delete

    std::cout << isCopyable(ch1) << '\n';
    std::cout << isCopyable(vec) << '\n'; 
//    std::cout << isCopyable(c) << '\n'; // Error: у класса C определен деструктор который может кинуть исключение
//    std::cout << isCopyable(e) << '\n'; // Error: move к-тор у класса Е помечен как delete

    std::cout << isSemiregular(ch1) << '\n';
    std::cout << isSemiregular(vec) << '\n'; 
//    std::cout << isSemiregular(c) << '\n'; // Error: у класса C определен деструктор который может кинуть исключение
//    std::cout << isSemiregular(e) << '\n'; // Error: move к-тор у класса Е помечен как delete

    std::cout << isRegular(vec) << '\n'; 
//    std::cout << isRegular(a) << '\n'; // Error: нету оператора сравнения

    auto lambda = [](int val){val += 1;};
    std::cout << isInvokable(lambda, 1) << '\n';
    std::cout << isInvokable(lambda, 1.f) << '\n';
//    std::cout << isInvokable(lambda, nullptr) << '\n'; // Error: несоответствие типов
//    std::cout << isInvokable(lambda, 1, 2) << '\n'; // Error: несоответствие кол-ву параметров

    auto predicateLambda = [](int val1, int val2) {return val1 == val2;};
    std::cout << isPredicate(predicateLambda, 1, 2) << '\n';
    std::cout << isPredicate(predicateLambda, 2, 2.f) << '\n'; 
//    std::cout << isPredicate(predicateLambda, 2, nullptr) << '\n'; // Error: несоответствие типов
//    std::cout << isPredicate(lambda, 1) << '\n'; // Error: возвращаемое значение не bool

    std::cout << isRelation(predicateLambda, 1, 2) << '\n';
//    std::cout << isRelation(predicateLambda, 1, nullptr) << '\n'; // Error: несоответствие типов
//    std::cout << isRelation(lambda, 1) << '\n'; // Error: возвращаемое значение не bool

    std::cout << isEquivalenceRelation(predicateLambda, 1, 2) << '\n';
//    std::cout << isEquivalenceRelation(predicateLambda, 1, nullptr) << '\n'; // Error: несоответствие типов
//    std::cout << isEquivalenceRelation(lambda, 1) << '\n'; // Error: возвращаемое значение не bool

    std::cout << isStrictWeakOrdered(predicateLambda, 1, 2) << '\n';
//    std::cout << isStrictWeakOrdered(predicateLambda, 1, nullptr) << '\n'; // Error: несоответствие типов
//    std::cout << isStrictWeakOrdered(lambda, 1) << '\n'; // Error: возвращаемое значение не bool

    /*Кастомные концепты*/
    G g;
    std::cout << isCustom(g) << '\n';
//    std::cout << isCustom(e) << '\n'; // Error: отсутствует метод custom()

    ContainerWrapper cont(vec2);
    cont.size(); // ok: у vector'a есть методы begin и end

    /*Концепты из ranges хэдера*/
    std::cout << isRange(vec) << '\n';
    std::cout << isRange(str) << '\n';
    std::cout << isRange(str_view) << '\n';
    std::cout << isRange(c_arr) << '\n';
    std::cout << isRange(span) << '\n';
    std::cout << isRange(fl) << '\n';
//    std::cout << isRange(ch1) << '\n'; // Error: собс-но char не является range'om

    std::cout << isSizedRange(vec) << '\n';
    std::cout << isSizedRange(str) << '\n';
    std::cout << isSizedRange(str_view) << '\n';
    std::cout << isSizedRange(c_arr) << '\n';
    std::cout << isSizedRange(span) << '\n';
//    std::cout << isSizedRange(fl) << '\n'; // Error: у forward_list нету метода size

    // std::cout << isView(vec) << '\n'; // Error: STL контейнеры не являются view
    // std::cout << isView(str) << '\n'; // Error: то же самое что и с вектором, стринга не унаследована от view_base
    std::cout << isView(str_view) << '\n'; // Ok: тут в самом название типа говорится что он view

    std::cout << isInputRange(vec) << '\n'; // Ok: т.к. категория итератора тут везде минимум forward_iterator 
    std::cout << isInputRange(str) << '\n';
    std::cout << isInputRange(str_view) << '\n';
    std::cout << isInputRange(c_arr) << '\n';
    std::cout << isInputRange(span) << '\n';
    std::cout << isInputRange(fl) << '\n';
    
    std::cout << isOutputRange<std::vector<int>, int>(vec) << '\n';
    std::cout << isOutputRange<std::vector<int>, long>(vec) << '\n';
//    std::cout << isOutputRange<std::vector<int>, std::string>(vec) << '\n';//Error: несовпадение типов + нету неявного приведения

    std::cout << isForwardRange(vec) << '\n'; // Ok: т.к. категория итератора тут везде минимум forward_iterator 
    std::cout << isForwardRange(str) << '\n';
    std::cout << isForwardRange(str_view) << '\n';
    std::cout << isForwardRange(c_arr) << '\n';
    std::cout << isForwardRange(span) << '\n';
    std::cout << isForwardRange(fl) << '\n';

    std::cout << isBidirectdRange(vec) << '\n';
    std::cout << isBidirectdRange(str) << '\n';
    std::cout << isBidirectdRange(str_view) << '\n';
    std::cout << isBidirectdRange(c_arr) << '\n';
    std::cout << isBidirectdRange(span) << '\n';
 //   std::cout << isBidirectdRange(fl) << '\n'; // Error: у forward_list's forward_iterator_tag

    std::cout << isRandomAccessRange(vec) << '\n';
    std::cout << isRandomAccessRange(str) << '\n';
    std::cout << isRandomAccessRange(str_view) << '\n';
    std::cout << isRandomAccessRange(c_arr) << '\n';
    std::cout << isRandomAccessRange(span) << '\n';
 //   std::cout << isRandomAccessRange(list) << '\n'; // Error: у list'a bidirectional_iterator_tag
 //   std::cout << isRandomAccessRange(fl) << '\n'; // Error: у forward_list'a forward_iterator_tag
    
    std::cout << isContiguousRange(vec) << '\n';
    std::cout << isContiguousRange(str) << '\n';
    std::cout << isContiguousRange(str_view) << '\n';
    std::cout << isContiguousRange(c_arr) << '\n';
    std::cout << isContiguousRange(span) << '\n';
 //   std::cout << isContiguousRange(deq) << '\n'; // Error: y deque'a random_access_iterator_tag

    std::cout << isCommonRange(vec) << '\n'; // Ok: все STL контейнеры являются common_rage
    std::cout << isCommonRange(str) << '\n';
    std::cout << isCommonRange(str_view) << '\n';
    std::cout << isCommonRange(c_arr) << '\n';
    std::cout << isCommonRange(span) << '\n';

//    std::cout << isViewableRange(vec) << '\n';  // Error: вектор владеет своими объектами
//    std::cout << isViewableRange(str) << '\n'; // Error: строка владеет своими объектами
    std::cout << isViewableRange(str_view) << '\n';
//    std::cout << isViewableRange(c_arr) << '\n'; // Error: си массив владеет своими объектами
    std::cout << isViewableRange(span) << '\n';

    /*Концепты из compare хэдера*/
    std::cout << isThreeWay<int, int>(signedVal2, signedVal1) << '\n';
    std::cout << isThreeWay<char, int>(ch1, signedVal1) << '\n';
//    std::cout << isThreeWay<std::string, int>(str, signedVal1) << '\n';
}

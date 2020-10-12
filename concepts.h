#include <concepts>
#include <string>
#include <cmath>
#include <iostream>

//Concepts - именованные требования для построения параметров шаблона
//Предикаты вычисляются во время компиляции
//Стандартная библиотека предоставляет некоторые готовые концепты

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

/*Библиотечные концепты*/
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
/*Библиотечные концепты*/
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
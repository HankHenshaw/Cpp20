#include <iostream>
#include <vector>
#include <ranges>
#include <iterator>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <string_view>
#include <span>
#include <forward_list>
#include <deque>
#include "concepts.h"


int main()
{
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
    return 0;
}
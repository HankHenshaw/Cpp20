#include <iostream>
#include <vector>
#include <ranges>
#include <iterator>
#include <string>
#include <algorithm>
#include <list>
#include <map>
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
    return 0;
}
/* Range - объект ссылающийся на последовательность/диапозон эл-тов
 * Схож с парой итераторов begin/end, но не заменяет их
 * Ranges:
 * - Предоставляют более убодный и легко читаемый синтакс
 * - Устраняет несоответствие итераторов begin/end (н-р когда один итератор из одного контейнера, и второй - из другого)
 * - Позволяет "адаптерам диапазона" лениво изменять/фильтровать(transform/filter) последовательность эл-тов
 * Ranges - основан на следующих основных компонентах:
 * - Range: концепт с определенными требования к итероторам(любой контейнер который поддерживает begin()/end() является валидным)
 * - Range-based algorithm: вся стандартная библиотека алгоритмов поддерживает диапазоны вместо пары итераторов
 * - Projection: изменение эл-тов до передачи в алгоритм
 * - Views: изменение/фильтрация диапазона: ленивое вычисление, без владения
 * - Range factories: конструирования views для предоставления значений по требования(н-р, последовательность интов)
 * - Pipelining: Views может быть использовать в конвеере(pipeline) исп. pipes |
 */

#include <iostream>
#include <set>
#include <ranges>
#include <algorithm>
#include <span>
#include <vector>

std::vector<int> foo();

void rangesExamples()
{
    std::cout << "Range Examples: \n\n";

    int arr[] {5,7,9,10,15,-3,5,0,-1};
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

    //2 - dangling плэйсхолдер для повисших итераторов
    auto min_iter = std::ranges::min_element(foo());

//    std::cout << *min_iter << '\n'; // тип min_iter std::ranges::dangling, а у этого типа нету оператора разыменования

    //dangling protection можно отключить для пользовательских типов специализировав трэйтс 
    //template<> inline constexpr bool
    //std::ranges::enable_borrowod_range<myClass> = true;
    //тогда не будет возвращаться dangling тип, такое поведение имеет место быть для представление(views)

    //borrowed range - это lvalue диапазон или rvalue c установленным enable_borrowod_range<T> = true
    //примеры borrowed: basic_string_view, span, subrange

    //views - диапазон которы не владеет его эл-тами
    //также у представления есть к-тор по умолчанию, константные операции перемещения, деструктор, и 
    //если есть константные операции копирования
    //пользовательский тип можно пометить как view, использовав трэйт enable_view или унаслодовавшись от ranges::view_base

    //borrowed range можно конвертировать во view используя views::all, а view в borrowed нельзя

    //Вместе views и borrowed диапазоны называются viewable диапазонами

    //range adaptors работают только на viewable диапазонах

    //3 - empty_view пустой вью без представления
    std::ranges::empty_view<int> ev;
    std::cout << ev.size() << '\n';
    //ew.begin() == ew.end() == nullptr

    //4 - single_view вью который содержит всего 1 объект 
    std::ranges::single_view<int> sv(5);
    std::cout << sv.size() << '\n';
    std::cout << *sv.begin() << '\n';

    //5 - iota_view вью который состоит из последовательности увеличивающихся на 1 эл-тов
    auto iv {std::views::iota(1) | std::views::take(9)};
    for(int val: iv)
        std::cout << val << "|"; 
    std::cout << '\n';

    //6 - counted создает поддиапазон из итератора и кол-ва
    for(int val: std::views::counted(arr, 6))
        std::cout << val << "|"; 
    std::cout << '\n';

    //7 - all вью который содержит все эл-ты диапазона
    for(const auto& val: std::views::all(vec))
            std::cout << val << "|";
    std::cout << '\n';

    //8 - ref_view вью из эл-тов из другого диапазона. Он содержит ссылку на этот диапазон
    std::ranges::ref_view rv(sv);
    std::cout << rv.size() << '\n';
    std::cout << rv.empty() << '\n';

    //9 - filter вью который содержит эл-ты удовлетвориющие предикату
    auto filtered {arr | std::views::filter([](const auto &val){return val%5 == 0;})};
    std::ranges::copy(filtered, std::ostream_iterator<int>(std::cout, "|"));
    std::cout << '\n';

    //10 - transform вью последовательности которай применяет трансформирующую ф-цию к каждому эл-ту(исх послед. не изменяется)
    auto transformed {arr | std::views::transform([](const auto &val){return val/2;})};
    std::ranges::copy(transformed, std::ostream_iterator<int>(std::cout, "|"));
    std::cout << '\n';

    //11 - take вью который содержит N кол-во эл-тов от начала другого вью
    std::ranges::copy(arr | std::views::take(3), std::ostream_iterator<int>(std::cout, "|"));
    std::cout << '\n';

    //12 - split вью над другим поддиапозоном полученное в результате разделения другого вью используя разделитель 
    std::string str{"H e ll o"};
    auto splitted {str | std::views::split(' ')};
    for(const auto &inner: splitted)
    {
        for(const auto &val : inner)
        {
            std::cout << val;
        }
    }
    std::cout << '\n';

    //13 - join сплющиаает все диапазоны в один
    for(auto val: splitted | std::views::join)
    {
        std::cout << val << ' ';
    }
    std::cout << '\n';

    //14 - common конвертирует вью в простой диапазон
    std::ranges::copy(std::views::common(sv), std::ostream_iterator<int>(std::cout, "|"));
    std::cout << '\n';

    //15 - reverse вью который итерируется по диапазону в обратном порядке
    std::ranges::copy(std::views::reverse(vec), std::ostream_iterator<int>(std::cout, "|"));
    std::cout << '\n';

    //C++20 пока не поддерживает range для numeric header'a, но можно написать свою реализацию необходимого алгоритма
    //В C++23 будет поддержка numeric'a
}

std::vector<int> foo()
{
    std::vector<int> v{1,2,3,4,5};
    return v;
}
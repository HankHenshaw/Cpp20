/*Coroutines:
/* это ф-ции с одним из следующих ключевых слов:
/* - co_await: приостанавливает корутину и ждет пока другое вычисление(асинхронное?) будет завершено
/* - co_yield: возвращает значение из корутины в вызывающую ф-цию, и приостанавливает корутину, при вызове этой корутины
/* выполнится данный шаг еще раз
/* - co_return - возвращение из корутины
/* Корутины могут быть использованны для:
/* - Генераторов
/* - Асинхронного I/O
/* - Ленивого вычисления
/* - Событийно управляемых приложений
*/


#include <coroutine>
#include <concepts>
#include <iostream>
#include <cassert>

template<typename T>
struct generator
{
    struct promise_type;

    using handle_type = std::coroutine_handle<promise_type>;
    handle_type handle;

    struct promise_type
    {
        T current_value;

        auto get_return_object()
        {
            return generator(*this);
        }

        auto initial_suspend()
        {
            return std::suspend_always{};
        }

        auto final_suspend()
        {
            return std::suspend_always{};
        }

        auto yield_value(const T& value)
        {
            current_value = value;
            return std::suspend_always{};
        }

        void return_void() {}

        void return_value(const T& value) {current_value = value;}

        void unhandled_exception()
        {
            std::terminate();
        }
    };

    generator(promise_type& promise) : handle(handle_type::from_promise(promise)) {}
    generator(const generator&) = delete;
    generator& operator=(const generator&) = delete;
    generator(generator&& other) : handle(other.handle) 
    {
        other.handle = nullptr;
    };
    generator& operator=(generator&& other)
    {
        if(this != &other)
        {
            handle = other.handle;
            other.handle = nullptr;
        }
        return *this;
    }
    ~generator()
    {
        if(handle) handle.destroy();
    }
    T operator()()
    {
        assert(handle != nullptr);
        handle.resume();
        return handle.promise().current_value;
    }

    class Iter {
        handle_type m_handle;
    public:
        void operator++() {m_handle.resume();}
        const T& operator*() const {return m_handle.promise().current_value;}
        bool operator==(std::default_sentinel_t) const {return !m_handle || m_handle.done();}
        explicit Iter(handle_type coro) : m_handle(coro) {}
    };
    Iter begin() {
        if(handle) handle.resume();
        return Iter(handle);
    }
    std::default_sentinel_t end() {return {};}
};

template<std::integral T>
generator<T> fib(T max)
{
    co_yield 0;
    co_yield 1;
    for(int i = 2, a = 0, b = 1 ; i <= max; ++i)
    {
        int res = a+b;
        co_yield res;
        i&1? b = res : a = res;
    }
}

template<std::integral T>
generator<T> fact(T end, T begin = 0)
{
    int res = 1;
    while(begin < end)
    {
        res = res * (++begin);
        co_yield res;
    }
}

void genUse()
{
    std::cout << "\n\nCoroutines Examples:\n";

    int max = 8;

    std::cout << "Fibonacci sequence: \n";
    generator<int> genFib = fib(max);
    for(int i = 0; i <= max; ++i)
        std::cout << genFib() << '\n';

    std::cout << "Factorials: \n";
    for(int val: fact(max))
        std::cout << val << '\n';
}
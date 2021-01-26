#include <bits/stdc++.h>
using namespace std;

// Begin Wrapper
template <class>
struct Cache;

template <class R, class... Args>
struct Cache<R(Args...)>
{
private:
    map<tuple<Args...>, R> m_memory;

public:
    Cache(std::function<R(Args...)> f) : f_(f) {}

    R operator()(Args... args)
    {
        auto key = make_tuple(args...);
        if (m_memory.count(key))
            return m_memory[key];
        else
            return m_memory[key] = f_(args...);
    }
    std::function<R(Args...)> f_;
};

template <class R, class... Args>
Cache<R(Args...)> memoize(R (*f)(Args...))
{
    return Cache<R(Args...)>(std::function<R(Args...)>(f));
}
// End Wrapper
/*
References: 
- https://stackoverflow.com/questions/30679445/python-like-c-decorators
*/
// Example
int fib(int n)
{
    static auto f = memoize(fib);
    printf("f(%d)\n",n);
    if (n <= 1)
        return n;
    return f(n - 1) + f(n - 2);
}
int main()
{
    int r = fib(5);
    printf("%d\n", r);
    return 0;
}

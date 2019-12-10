#include <chrono>
#include <utility>
template<typename R,typename... Args>
std::pair<unsigned long long,R> benchmark(R(*code)(Args...),Args... args) {
    using namespace std::chrono;
    R ret;
    auto start =high_resolution_clock::now();
    ret =code(args);
    auto end = high_resolution_clock::now();
    return std::make_pair(duration_cast<nanoseconds>(end-start).count(),ret);
}
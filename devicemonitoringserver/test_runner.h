#ifndef TEST_RUNNER
#define TEST_RUNNER

#include <exception>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

template <typename Type>
std::ostream&
commfold(std::ostream& os, const Type obj) {
    return os << ',' << ' ' << obj;
}

template <class KeyType, class ValueType>
std::ostream&
commfold(std::ostream& os, const std::pair<KeyType, ValueType> obj) {
    return os << ',' << ' ' << obj.first << ':' << ' ' << obj.second;
}

template <class Type>
std::ostream&
operator<<(std::ostream& os, const std::vector<Type>& vec) {
    os << '[';

    if (!vec.empty()) {
        std::accumulate(std::next(vec.begin()), vec.end(),
                        std::ref(os << vec.front()), commfold<Type>);
    }

    return os << ']';
}

template <class Type>
std::ostream&
operator<<(std::ostream& os, const std::set<Type>& set) {
    os << '{';

    if (!set.empty()) {
        std::accumulate(std::next(set.begin()), set.end(),
                        std::ref(os << *set.begin()), commfold<Type>);
    }

    return os << '}';
}

template <class KeyType, class ValueType>
std::ostream&
operator<<(std::ostream& os, const std::map<KeyType, ValueType>& map) {
    os << '{';

    if (!map.empty()) {
        std::accumulate(
            next(map.begin()), map.end(),
            ref(os << map.begin()->first << ':' << ' ' << map.begin()->second),
            commfold<KeyType, ValueType>);
    }

    return os << '}';
}

template <class KeyType, class ValueType>
std::ostream&
operator<<(std::ostream& os,
           const std::unordered_map<KeyType, ValueType>& umap) {

    os << '{';

    if (!umap.empty()) {
        std::accumulate(next(umap.begin()), umap.end(),
                        ref(os << umap.begin()->first << ':' << ' '
                               << umap.begin()->second),
                        commfold<KeyType, ValueType>);
    }

    return os << '}';
}

template <class T, class U>
void AssertEqual(const T& t, const U& u,
                 const std::string& hint)
{
    if (t != u)
    {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u
           << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

inline void Assert(bool b, const std::string& hint)
{
    AssertEqual(b, true, hint);
}

class TestRunner
{
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name)
    {
        try
        {
            func();
            std::cerr << test_name << " OK" << std::endl;
        }
        catch (std::runtime_error& e)
        {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        }
    }

    ~TestRunner()
    {
        if (fail_count > 0)
        {
            std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

#define UNIQUE_2(x) name##x
#define UNIQUE_1(x) UNIQUE_2(x)
#define UNIQUE      UNIQUE_1(__LINE__)

// После вставки все оказываются в одной строке -> Можно использовать UNIQUE
#define ASSERT_EQUAL(x, y)                                                   \
    {                                                                        \
        std::ostringstream UNIQUE;                                           \
        UNIQUE << #x << " != " << #y << ", " << __FILE__ << ":" << __LINE__; \
        AssertEqual(x, y, UNIQUE.str());                                     \
    }

#define ASSERT(x)                                                     \
    {                                                                 \
        std::ostringstream UNIQUE;                                    \
        UNIQUE << #x << " is false, " << __FILE__ << ":" << __LINE__; \
        Assert(x, UNIQUE.str());                                      \
    }

#define RUN_TEST(tr, func) \
    tr.RunTest(func, #func)

#endif //TEST_RUNNER

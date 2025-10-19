#pragma once

#include <vector>
#include <numeric>
#include <stdexcept>
#include <type_traits>

using std::invalid_argument;
using std::is_arithmetic;
using std::vector;

template <typename T>
T getMin(const vector<T> &values)
{
    static_assert(is_arithmetic<T>::value, "getMin requires a numeric (arithmetic) type");
    if (values.empty())
    {
        throw invalid_argument("getMin: values is empty");
    }
    T m = values.front();
    for (const auto &v : values)
    {
        if (v < m)
            m = v;
    }
    return m;
}

template <typename T>
T getMax(const vector<T> &values)
{
    static_assert(is_arithmetic<T>::value, "getMax requires a numeric (arithmetic) type");
    if (values.empty())
    {
        throw invalid_argument("getMax: values is empty");
    }
    T m = values.front();
    for (const auto &v : values)
    {
        if (m < v)
            m = v;
    }
    return m;
}

template <typename T>
double getAverage(const vector<T> &values)
{
    static_assert(is_arithmetic<T>::value, "getAverage requires a numeric (arithmetic) type");
    if (values.empty())
    {
        throw invalid_argument("getAverage: values is empty");
    }
    long double sum = 0.0L;
    for (const auto &v : values)
        sum += static_cast<long double>(v);
    return static_cast<double>(sum / static_cast<long double>(values.size()));
}

template <typename T>
class Statistics
{
    static_assert(is_arithmetic<T>::value, "Statistics<T> requires a numeric (arithmetic) type");

private:
    vector<T> data;

public:
    void addValue(const T &value) { data.push_back(value); }

    T getMin() const { return ::getMin(data); }
    T getMax() const { return ::getMax(data); }
    double getAverage() const { return ::getAverage(data); }

    const vector<T> &values() const noexcept { return data; }
};

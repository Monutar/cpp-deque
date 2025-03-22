#pragma once

#include <deque>
#include <vector>

using namespace std;

template<class T, class Comp>
inline deque<T> Merge(const deque<T>& arr1, const std::deque<T>& arr2, const Comp& comparator) {
    deque<T> out;
    vector<T> result;
    vector<T> q1;
    vector<T> q2;

    size_t idx1 = 0;
    size_t idx2 = 0;

    for(size_t i = 0; i < arr1.size(); ++i) {
        q1.push_back(arr1[i]);
    }
    for(size_t i = 0; i < arr2.size(); ++i) {
        q2.push_back(arr2[i]);
    }

    while (idx1 < q1.size() && idx2 < q2.size()) {
        bool less = comparator(q1[idx1],q2[idx2]);
        if (less) {
            result.push_back(q1[idx1]);
            idx1 += 1;
        } else {
            result.push_back(q2[idx2]);
            idx2 += 1;
        }
    }

    while (idx1 < q1.size()) {
        result.push_back(q1[idx1]);
        idx1 += 1;
    }
    while (idx2 < q2.size()) {
        result.push_back(q2[idx2]);
        idx2 += 1;
    }

    for (size_t i = 0; i < result.size(); ++i) {
        out.push_back(result[i]);
    }

    return out;
}



template<class T, class Comp>
inline deque<T> MergeSort(const deque<T>& arr, const Comp& comparator) {
    // Реализуйте рекурсивную функцию MergeSort
    // на основе задачи из урока о рекурсии.
    if (arr.size() <= 1) {
        return arr;
    }
    const size_t mid = arr.size() / 2;
    deque<T> first_half;
    deque<T> second_half;
    auto iter = arr.begin();
    advance(iter,mid);

    for (auto i = arr.begin(); i != iter; ++i) {
        first_half.push_back(*i);
    }
    for (auto i = iter; i != arr.end(); ++i) {
        second_half.push_back(*i);
    }

    const deque<T> left_sorted = MergeSort(first_half, comparator);
    const deque<T> right_sorted = MergeSort(second_half, comparator);

    return Merge(left_sorted, right_sorted, comparator);
}

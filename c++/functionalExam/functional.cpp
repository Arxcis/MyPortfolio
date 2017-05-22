// @file functional.cpp
// @author Jonas Solsvik
// @created 21.05.2017
// @brief implementing map, filter and reduce
//         These functions should only edit existing data
#include <cassert>
#include <iostream>

template<typename T, size_t S>
struct Collection {
    T data[S];
    size_t size  = S;
    size_t count = 0;
};

// auto add  = [](auto& collection, auto thing);
// auto swap = [](auto& thing, auto& otherThing);
// auto sort = [](auto collection, auto lambda);
// auto map  = [](auto collection, auto lambda);
// auto foreach   = [](const auto& collection, auto lambda);
// auto enumerate = [](const auto& collection, auto lambda);
// auto filter    = [](auto& collection, auto Filter);
// auto filterThenElse = [](auto& collection, auto Filter, auto Then, auto Else);
// auto findThenElse   = [](auto& collection, auto Find, auto Then, auto Else);
// auto reduce       = [](const auto& collection, auto lambda);
// auto countIf      = [](const auto& collection, auto lambda);



auto add = [](auto& collection, auto thing) {
    if(collection.count < collection.size){
        collection.data[collection.count++] = thing;
    }
    else {
        assert(0);
    }
};

auto swap = [](auto& thing, auto& otherThing) {
    auto temp = thing;
    thing = otherThing;
    otherThing = temp;
};

auto sort = [](auto collection, auto lambda) {
    bool sorted = false;
    if(!(collection.count <= 1)) {
        while(!sorted) {
            sorted = true;
            for(int i = collection.count-2; i >= 0; --i) {
                if(lambda(collection.data[i], collection.data[i+1])) {
                    swap(collection.data[i], collection.data[i+1]);
                    sorted = false;
                }
            }
        }
    }
    return collection;
};

auto map = [](auto& collection, auto lambda) {
    for(size_t i = 0; i < collection.count; ++i) {
        lambda(collection.data[i]);
    }
    return collection;
};

auto foreach = [](const auto& collection, auto lambda) {
    for(size_t i = 0; i < collection.count; ++i) {
        lambda(collection.data[i]);
    }
};

auto enumerate = [](const auto& collection, auto lambda) {
    for(size_t i = 0; i < collection.count; ++i) {
        lambda(collection.data[i], i);
    }
};

auto filter = [](auto collection, auto Filter) {
    for(int i = collection.count-1; i >= 0; --i) {
        if(!Filter(collection.data[i])) {
            collection.data[i] = collection.data[collection.count-1];
            collection.count--;
        }
    }
    return collection;
};

auto filterThenElse = [](auto& collection, auto Filter, auto Then, auto Else) {
    bool filtered = false;

    for(int i = collection.count-1; i >= 0; --i) {
        if (Filter(collection.data[i])) {
            Then(collection.data[i]);
            filtered = true;
        }
    }
    if(!filtered) Else();
};

auto findThenElse = [](auto& collection, auto Find, auto Then, auto Else) {
    for(int i = collection.count-1; i >= 0; --i) {
        if (Find(collection.data[i])) {
            Then(collection.data[i]);
            return 0;
        }
    }
    Else();
    return 1;
};

auto reduce = [](const auto& collection, auto lambda) {
    double sum = 0;
    for (size_t i = 0; i < collection.count; ++i) {
        sum += lambda(collection.data[i]);
    }
    return sum;
};

auto countIf = [](const auto& collection, auto lambda) {
    size_t count = 0;
    for (size_t i = 0; i < collection.count; ++i) {
        if(lambda(collection.data[i])) {
            count++;
        }
    }
    return count;
};

int test() {

    Collection<int, 4> myInts;
    add(myInts, 1);
    add(myInts, 2);
    add(myInts, 3);
    add(myInts, 4);

    map    (myInts,   [](auto x) { return x * x; });
    filter (myInts,   [](auto x) { return x > 3; });
    reduce (myInts,   [](auto x) { return x * 100; });
    foreach(myInts,   [](auto x) { std::cout << "Sum: " << x << "\n"; });
    sort(myInts,      [](auto x, auto y){ return x > y; });
    filter(myInts,    [](auto x) { return x == 4; });
    enumerate(myInts, [](auto x, int i){ std::cout << "Sum " << i << ": " << x << "\n"; });
    return 0;
}

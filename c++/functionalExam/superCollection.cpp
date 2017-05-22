#include <cassert>

template<typename T, size_t S>
struct Collection {
    T data[S];
    size_t size  = S;
    size_t count = 0;


    template<typename Map>
    Collection<T, S> map(const Map& lambda) {
        Collection<T, S> collection = *this;
        for(size_t i = 0; i < collection.count; ++i) {
            lambda(collection.data[i]);
        }
        return collection;
    };


    template<typename Filter>
    Collection<T, S> filter(const Filter& lambda) {
        Collection<T, S> collection;
        for(int i=0; i < count; ++i) {
            if (lambda(data[i])) {
                collection.add(data[i]);
            }
        }
        return collection;
    };

    template<typename Reducer>
    double reduce(const Reducer& lambda) {
        double sum = 0;
        for (size_t i = 0; i < count; ++i) {
            sum += lambda(data[i]);
        }
        return sum;
    };

    template<typename Counter>
    size_t countIf(const Counter& lambda) {
        size_t sum = 0;
        for (size_t i = 0; i < count; ++i) {
            if(lambda(data[i])) {
                sum++;
            }
        }
        return sum;
    }

    void add(const T thing) {
        if (count < size){
            data[count++] = thing;
        }
        else {
            assert(0); // To many items
        }
    };
};


int main() {

    Collection<int, 5> money;
    money.add(5);
    money.add(20);
    money.add(10);
    money.add(15);

    double sum = money.map([](auto x){ std::cout << x << '\n'; })
                        .filter([](auto x){ return x <= 10; })
                         .map([](auto x){ std::cout << '\n' << x << '\n'; })
                          .reduce([](auto x){ return x; });
    std::cout << "Sum:" << sum << '\n';

    return 0;
}

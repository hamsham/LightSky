/* 
 * File:   util.h
 * Author: miles
 *
 * Created on May 23, 2014, 7:10 PM
 */

#ifndef __LS_UTIL_H__
#define	__LS_UTIL_H__

#include <utility>
#include <vector>

namespace util {

/**
 * Simplified dynamic array interface that will be used to standardize a vector
 * type within LS.
 */
template <typename data_t>
class lsArray final {
    typedef std::vector<data_t> lsVector_t;
    
    private:
        lsVector_t dataArray;
        
    public:
        lsArray();
        lsArray(const lsArray&);
        lsArray(lsArray&&);
        
        ~lsArray() {
            clear();
        }
        
        lsArray& operator=(const lsArray&);
        lsArray& operator=(lsArray&&);
        
        const data_t& operator[] (unsigned) const;
        data_t& operator[] (unsigned);
        
        void add(const data_t&);
        void emplace(data_t&&);
        
        void remove(unsigned);
        
        void clear();
        
        unsigned size() const;
        unsigned capacity() const;
        
        bool empty() const;
        
        void resize(unsigned);
        
        void reserve(unsigned);
};

template <typename data_t>
lsArray<data_t>::lsArray() :
    dataArray{}
{}

template <typename data_t>
lsArray<data_t>::lsArray(const lsArray& a) :
    dataArray{a.dataArray}
{}

template <typename data_t>
lsArray<data_t>::lsArray(lsArray&& a) :
    dataArray{std::move(a)}
{}

template <typename data_t>
lsArray<data_t>& lsArray<data_t>::operator=(const lsArray& a) {
    dataArray = a.dataArray;
    return *this;
}

template <typename data_t>
lsArray<data_t>& lsArray<data_t>::operator=(lsArray&& a) {
    dataArray = std::move(a.dataArray);
    return *this;
}

template <typename data_t>
const data_t& lsArray<data_t>::operator[] (unsigned i) const {
    return dataArray[i];
}

template <typename data_t>
data_t& lsArray<data_t>::operator[] (unsigned i) {
    return dataArray[i];
}

template <typename data_t>
void lsArray<data_t>::add(const data_t& d) {
    dataArray.push_back(d);
}

template <typename data_t>
void lsArray<data_t>::emplace(data_t&& d) {
    dataArray.emplace_back(std::move(d));
}

template <typename data_t>
void lsArray<data_t>::remove(unsigned i) {
    dataArray.erase(dataArray.begin() + i);
}

template <typename data_t>
void lsArray<data_t>::clear() {
    dataArray.clear();
}

template <typename data_t>
unsigned lsArray<data_t>::size() const {
    return dataArray.size();
}

template <typename data_t>
unsigned lsArray<data_t>::capacity() const {
    return dataArray.capacity();
}

template <typename data_t>
bool lsArray<data_t>::empty() const {
    return dataArray.empty();
}

template <typename data_t>
void lsArray<data_t>::resize(unsigned s) {
    dataArray.resize(s);
}

template <typename data_t>
void lsArray<data_t>::reserve(unsigned r) {
    dataArray.reserve(r);
}

}

#endif	/* __LS_UTIL_H__ */


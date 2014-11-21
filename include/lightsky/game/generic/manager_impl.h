
namespace ls {
namespace game {

/*-------------------------------------
    Constructor
-------------------------------------*/
template <typename hash_t, typename data_t>
manager<hash_t, data_t>::manager() :
    dataMap{}
{}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
template <typename hash_t, typename data_t>
manager<hash_t, data_t>::manager(manager&& m) :
    dataMap{std::move(m.dataMap)}
{}

/*-------------------------------------
    Destructor
-------------------------------------*/
template <typename hash_t, typename data_t>
manager<hash_t, data_t>::~manager() {
    clear();
}

/*-------------------------------------
    Move Operator
-------------------------------------*/
template <typename hash_t, typename data_t>
manager<hash_t, data_t>& manager<hash_t, data_t>::operator=(manager&& m) {
    clear();
    dataMap = std::move(m.dataMap);
    return *this;
}

/*-------------------------------------
    Manage the dynamic memory of an object, given an ID that it can be
    referenced by.
-------------------------------------*/
template <typename hash_t, typename data_t>
inline void manager<hash_t, data_t>::manage(const hash_t& id, data_t* const pData) {
    if (this->contains(id) == false) {
        dataMap[id] = pData;
    }
}

/*-------------------------------------
    Remove an object from the list of things managed by *this.
-------------------------------------*/
template <typename hash_t, typename data_t>
data_t* manager<hash_t, data_t>::unmanage(const hash_t& id) {
    data_t* pData = nullptr;

    if (this->contains(id)) {
        pData = dataMap.at(id);
        dataMap.erase(id);
    }

    return pData;
}

/*-------------------------------------
    Free the memory used by an object that's managed by *this.
-------------------------------------*/
template <typename hash_t, typename data_t>
void manager<hash_t, data_t>::erase(const hash_t& id) {
    if (this->contains(id) == true) {
        data_t* const pData = dataMap.at(id);
        dataMap.erase(id);
        delete pData;
    }
}

/*-------------------------------------
    Determine if an object, referenced by ID, is managed by *this.
-------------------------------------*/
template <typename hash_t, typename data_t>
inline bool manager<hash_t, data_t>::contains(const hash_t& id) const {
    return dataMap.find(id) != dataMap.end();
}

/*-------------------------------------
    Retrieve the raw pointer to an object that is currently managed by
    *this.
-------------------------------------*/
template <typename hash_t, typename data_t>
inline data_t* manager<hash_t, data_t>::get(const hash_t& id) const {
    return this->contains(id) ? dataMap.at(id) : nullptr;
}

/*-------------------------------------
    Retrieve the raw pointer to an object that is currently managed by
    *this.
-------------------------------------*/
template <typename hash_t, typename data_t>
inline data_t* manager<hash_t, data_t>::get(const hash_t& id) {
    return this->contains(id) ? dataMap.at(id) : nullptr;
}

/*-------------------------------------
    Get a managed object using an index offset, rather tan an ID.
-------------------------------------*/
template <typename hash_t, typename data_t>
data_t* manager<hash_t, data_t>::elementAt(unsigned index) {
    if (index >= dataMap.size()) {
        return nullptr;
    }

    typename map_t::iterator iter = dataMap.begin();
    std::advance(iter, index);
    return iter->second;
}

/*-------------------------------------
    Release the memory of all objects managed by *this.
-------------------------------------*/
template <typename hash_t, typename data_t>
void manager<hash_t, data_t>::clear() {
    typename map_t::iterator iter;
    for (iter = dataMap.begin(); iter != dataMap.end(); ++iter) {
        delete iter->second;
    }
    dataMap.clear();
}

/*-------------------------------------
    Get the number of objects that are currently managed by *this.
    managed by *this.
-------------------------------------*/
template <typename hash_t, typename data_t>
inline unsigned manager<hash_t, data_t>::size() const {
    return dataMap.size();
}

/*-------------------------------------
    Retrieve the implementing hash table that is used internally by this
    object.
-------------------------------------*/
template <typename hash_t, typename data_t>
inline const typename manager<hash_t, data_t>::map_t&
manager<hash_t, data_t>::getDataMap() const {
    return dataMap;
}

/*-------------------------------------
    Retrieve the implementing hash table that is used internally by this
    object.
-------------------------------------*/
template <typename hash_t, typename data_t>
inline typename manager<hash_t, data_t>::map_t&
manager<hash_t, data_t>::getDataMap() {
    return dataMap;
}

} // end game namespace
} // end ls namespace

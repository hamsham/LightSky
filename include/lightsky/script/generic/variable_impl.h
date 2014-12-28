
namespace ls {
namespace script {

/*-----------------------------------------------------------------------------
    Variable Base Type
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Variable Object Copy Assignment
-------------------------------------*/
inline
variable& variable::operator =(const variable& v) {
    scriptable::operator =(v);
    return *this;
}

/*-------------------------------------
    Variable Object Move Assignment
-------------------------------------*/
inline
variable& variable::operator =(variable&& v) {
    scriptable::operator =(std::move(v));
    return *this;
}

/*-------------------------------------
    Variable Object Base Type Query
-------------------------------------*/
inline
script_base_t variable::getScriptType() const {
    return script_base_t::VARIABLE;
}

/*-----------------------------------------------------------------------------
    Extended Variable Template Type
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Variable Object Type Destructor
-------------------------------------*/
template <hash_t hashId, typename type>
variable_t<hashId, type>::~variable_t() {
}

/*-------------------------------------
    Variable Object Type Constructor
-------------------------------------*/
template <hash_t hashId, typename type>
variable_t<hashId, type>::variable_t() :
    variable{},
    data{}
{}

/*-------------------------------------
    Variable Object Type Copy Constructor
-------------------------------------*/
template <hash_t hashId, typename type>
variable_t<hashId, type>::variable_t(const variable_t& v) :
    variable{v},
    data{v.data}
{}

/*-------------------------------------
    Variable Object Type Move Constructor
-------------------------------------*/
template <hash_t hashId, typename type>
variable_t<hashId, type>::variable_t(variable_t&& v) :
    variable{std::move(v)},
    data{std::move(v.data)}
{}

/*-------------------------------------
    Variable Object Type Copy Assignment
-------------------------------------*/
template <hash_t hashId, typename type>
variable_t<hashId, type>& variable_t<hashId, type>::operator =(const variable_t& v) {
    variable::operator =(v);
    data = v.data;
    return *this;
}

/*-------------------------------------
    Variable Object Type Move Assignment
-------------------------------------*/
template <hash_t hashId, typename type>
variable_t<hashId, type>& variable_t<hashId, type>::operator =(variable_t&& v) {
    variable::operator =(std::move(v));
    data = std::move(v.data);
    return *this;
}

/*-------------------------------------
    Variable Object Type Data Loading
-------------------------------------*/
template <hash_t hashId, typename type>
bool variable_t<hashId, type>::load(std::istream& istr, varImportMap_t&, funcImportMap_t&) {
    istr >> data;
    return true;
}

/*-------------------------------------
    Variable Object Type Data Saving
-------------------------------------*/
template <hash_t hashId, typename type> inline
void variable_t<hashId, type>::save(std::ostream& ostr) const {
    ostr << data;
}

/*-------------------------------------
    Variable Object Type RTTI
-------------------------------------*/
template <hash_t hashId, typename type> inline
hash_t variable_t<hashId, type>::getScriptSubType() const {
    return hashId;
}

} // end script namespace
} // end ls namespace

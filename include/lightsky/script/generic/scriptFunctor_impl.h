
namespace ls {
namespace script {

/*-----------------------------------------------------------------------------
    Functor Base Class
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Retrieve the next function to run
-------------------------------------*/
inline
functor* functor::getNextFunc() {
    return nextFunc;
}

/*-------------------------------------
    Set the next function to run.
-------------------------------------*/
inline
void functor::setNextFunc(functor* const f) {
    nextFunc = f;
}

/*-------------------------------------
    Get the scriptable type.
-------------------------------------*/
inline
script_base_t functor::getScriptType() const {
    return script_base_t::FUNCTOR;
}

/*-------------------------------------
    Get a functor argument
-------------------------------------*/
inline
variable* functor::getArg(unsigned index) const {
    LS_DEBUG_ASSERT(index < this->getNumArgs());
    return pArgs[index];
}

/*-------------------------------------
    Set a functor argument
-------------------------------------*/
inline
void functor::setArg(unsigned index, variable* v) {
    LS_DEBUG_ASSERT(index < this->getNumArgs());
    pArgs[index] = v;
}
        
/*-------------------------------------
    Functor parameter type-checking for a single argument.
-------------------------------------*/
template <typename arg_t>
bool functor::checkSingleArg(const functor& f, unsigned i, arg_t* t) {
    if (i >= f.getNumArgs()) {
        std::cerr
            << "Error: Incorrect number of arguments being compiled: "
            << "\n\tFunction:   " << (void*)&f << '-' << f.getScriptSubType()
            << "\n\tParameter:  " << i << '/' << f.getNumArgs()
            << std::endl;
        return false;
    }
    
    if (f.getArg(i) == nullptr) {
        std::cerr
            << "Error: Function contains a null parameter: "
            << "\n\tFunction:    " << (void*)&f << '-' << f.getScriptSubType()
            << "\n\tParameter:   " << i << '/' << f.getNumArgs()
            << std::endl;
        return false;
    }

    if (dynamic_cast<const arg_t*>(f.getArg(i)) == nullptr) {
        std::cerr
            << "Error: TypeID of function argument does not match the type " \
            " declared in its parent function."
            << "\n\tFunction:    " << (void*)&f << '-' << f.getScriptSubType()
            << "\n\tInput type:  " << typeid(f.getArg(i)).name()
            << "\n\tActual type: " << typeid(t).name()
            << std::endl;
            return false;
    }
    return true;
}

/*-------------------------------------
    Run a functor
-------------------------------------*/
inline
void functor::run() {
    pFunction(pArgs);
}

/*-------------------------------------
    Functor parameter type-checking (Recursive)
-------------------------------------*/
template <typename arg_t, typename... args_t> inline
bool functor::checkArgs(const functor& f, unsigned i, arg_t* t, args_t*...) {
    return checkSingleArg<arg_t>(f, i, t)
    && checkArgs<args_t...>(f, i+1, ((args_t*)nullptr)...);
}

/*-------------------------------------
    Functor parameter type-checking (Sentinel)
-------------------------------------*/
template <typename arg_t> inline
bool functor::checkArgs(const functor& f, unsigned i, arg_t* t) {
    return checkSingleArg<arg_t>(f, i, t);
}

/*-----------------------------------------------------------------------------
    Functor Derived Template Types
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Destructor
-------------------------------------*/
template <hash_t hashId, typename... args_t>
functor_t<hashId, args_t...>::~functor_t() {
}

/*-------------------------------------
    Constructor
-------------------------------------*/
template <hash_t hashId, typename... args_t>
functor_t<hashId, args_t...>::functor_t() :
    functor{parameters, functionImpl}
{}

/*-------------------------------------
    Copy Constructor
-------------------------------------*/
template <hash_t hashId, typename... args_t>
functor_t<hashId, args_t...>::functor_t(const functor_t& f) :
    functor{parameters, functionImpl}
{
    functor::operator=(f);
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
template <hash_t hashId, typename... args_t>
functor_t<hashId, args_t...>::functor_t(functor_t&& f) :
    functor{parameters, functionImpl}
{
    functor::operator=(std::move(f));
}

/*-------------------------------------
    Copy Assignment
-------------------------------------*/
template <hash_t hashId, typename... args_t>
functor_t<hashId, args_t...>& functor_t<hashId, args_t...>::operator =(const functor_t& f) {
    functor::operator=(f);
    return *this;
}

/*-------------------------------------
    Move Assignment
-------------------------------------*/
template <hash_t hashId, typename... args_t>
functor_t<hashId, args_t...>& functor_t<hashId, args_t...>::operator =(functor_t&& f) {
    functor::operator=(std::move(f));
    return *this;
}

/*-------------------------------------
    RTTI
-------------------------------------*/
template <hash_t hashId, typename... args_t> inline
hash_t functor_t<hashId, args_t...>::getScriptSubType() const {
    return hashId;
}

/*-------------------------------------
    Argument Count Retrieval
-------------------------------------*/
template <hash_t hashId, typename... args_t> inline
unsigned functor_t<hashId, args_t...>::getNumArgs() const {
    return sizeof...(args_t);
}

/*-------------------------------------
    Load from an Input Stream
-------------------------------------*/
template <hash_t hashId, typename... args_t>
bool functor_t<hashId, args_t...>::load(std::istream& istr, varImportMap_t& vlm, funcImportMap_t& flm) {
    functor::load(istr, vlm, flm);

    for (unsigned i = 0; i < sizeof...(args_t); ++i) {
        void* ptr = nullptr;
        istr >> ptr;
        pArgs[i] = vlm[ptr].get();
    }
    
    return istr.good() || istr.eof();
}

/*-------------------------------------
    Save to an Output Stream
-------------------------------------*/
template <hash_t hashId, typename... args_t>
bool functor_t<hashId, args_t...>::save(std::ostream& ostr) const {
    functor::save(ostr);

    for (unsigned i = 0; i < sizeof...(args_t); ++i) {
        ostr << ' ' << (void*) pArgs[i];
    }
    return ostr.good();
}

/*-------------------------------------
    Argument Verification/Compilation
-------------------------------------*/
template <hash_t hashId, typename... args_t> inline
bool functor_t<hashId, args_t...>::compile() {
    return functor::checkArgs(*this, 0, ((args_t*)nullptr)...);
}

/*-----------------------------------------------------------------------------
    Functor Derived Template Types (Void Functor Specialization).
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Destructor
-------------------------------------*/
template <hash_t hashId>
functor_t<hashId, void>::~functor_t() {
}

/*-------------------------------------
    Constructor
-------------------------------------*/
template <hash_t hashId>
functor_t<hashId, void>::functor_t() :
    functor{nullptr, functionImpl}
{}

/*-------------------------------------
    Copy Constructor
-------------------------------------*/
template <hash_t hashId>
functor_t<hashId, void>::functor_t(const functor_t& f) :
    functor{nullptr, functionImpl}
{
    functor::operator=(f);
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
template <hash_t hashId>
functor_t<hashId, void>::functor_t(functor_t&& f) :
    functor{nullptr, functionImpl}
{
    functor::operator=(std::move(f));
}

/*-------------------------------------
    Copy Assignment
-------------------------------------*/
template <hash_t hashId>
functor_t<hashId, void>& functor_t<hashId, void>::operator =(const functor_t& f) {
    functor::operator=(f);
    return *this;
}

/*-------------------------------------
    Move Assignment
-------------------------------------*/
template <hash_t hashId>
functor_t<hashId, void>& functor_t<hashId, void>::operator =(functor_t&& f) {
    functor::operator=(std::move(f));
    return *this;
}

/*-------------------------------------
    RTTI
-------------------------------------*/
template <hash_t hashId> inline
hash_t functor_t<hashId, void>::getScriptSubType() const {
    return hashId;
}

/*-------------------------------------
    Argument Count Retrieval
-------------------------------------*/
template <hash_t hashId> inline
unsigned functor_t<hashId, void>::getNumArgs() const {
    return 0;
}

/*-------------------------------------
    Load from an Input Stream
-------------------------------------*/
template <hash_t hashId>
bool functor_t<hashId, void>::load(std::istream& istr, varImportMap_t& vlm, funcImportMap_t& flm) {
    return functor::load(istr, vlm, flm);
}

/*-------------------------------------
    Save to an Output Stream
-------------------------------------*/
template <hash_t hashId>
bool functor_t<hashId, void>::save(std::ostream& ostr) const {
    return functor::save(ostr);
}

/*-------------------------------------
    Argument Verification/Compilation
-------------------------------------*/
template <hash_t hashId> inline
bool functor_t<hashId, void>::compile() {
    return true;
}

} // end script namespace
} // end ls namespace

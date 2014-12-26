/* 
 * File:   functor.cpp
 * Author: Miles Lacey
 * 
 * Created on April 13, 2014, 9:07 PM
 */

#include <utility> // std::move

#include "lightsky/script/functor.h"

namespace ls {
namespace script {

/*-----------------------------------------------------------------------------
    Functor Base Class
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Destructor
-------------------------------------*/
functor::~functor() {
}

/*-------------------------------------
    Constructor
-------------------------------------*/
functor::functor(variable** const pArguments, func_ref_t pFunc) :
    scriptable{},
    nextFunc{nullptr},
    pFunction{pFunc},
    pArgs{pArguments}
{}

/*-------------------------------------
    Copy Operator
-------------------------------------*/
functor& functor::operator =(const functor& f) {
    scriptable::operator=(f);
    
    for (unsigned i = 0; i < f.getNumArgs(); ++i) {
        pArgs[i] = f.pArgs[i];
    }
    nextFunc = f.nextFunc;
    
    return *this;
}

/*-------------------------------------
    Move Operator
-------------------------------------*/
functor& functor::operator =(functor&& f) {
    scriptable::operator=(std::move(f));
    
    for (unsigned i = 0; i < f.getNumArgs(); ++i) {
        pArgs[i] = f.pArgs[i];
        f.pArgs[i] = nullptr;
    }
    
    nextFunc = f.nextFunc;
    f.nextFunc = nullptr;
    
    return *this;
}

/*-------------------------------------
    Loading a functor from an input stream
-------------------------------------*/
bool functor::load(std::istream& istr, varLoaderMap&, funcLoaderMap& flm) {
    hash_t nextType = 0;
    void* ptr = nullptr;

    istr >> nextType >> ptr;

    nextFunc = flm[ptr];

    // Create an instance of the next function if it wasn't in the functor loader
    if (nextFunc == nullptr && ptr != nullptr) {
        const funcFactory& pFactory = gFuncFactory.at(nextType);
        nextFunc = flm[ptr] = pFactory();
    }

    return true;
}

/*-------------------------------------
    Saving a functor to an output stream
-------------------------------------*/
void functor::save(std::ostream& ostr) const {
    if (nextFunc == nullptr) {
        ostr << 0 << ' ' << 0;
    }
    else {
        ostr << nextFunc->getScriptSubType() << ' ' << (void*)nextFunc;
    }
}

/*-----------------------------------------------------------------------------
    Built-In Types
-----------------------------------------------------------------------------*/
LS_SCRIPT_DEFINE_FUNC(empty, void) {
    (void)pArgs;
};

} // end script namespace
} // end ls namespace

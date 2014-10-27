
#include "lightsky/script/scriptable.h"

namespace ls {
namespace script {

/*-------------------------------------
    Destructor
-------------------------------------*/
scriptable::~scriptable() {
}

/*-------------------------------------
    Constructor
-------------------------------------*/
scriptable::scriptable() {
}

/*-------------------------------------
    Copy Constructor
-------------------------------------*/
scriptable::scriptable(const scriptable&) {
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
scriptable::scriptable(scriptable&&) {
}

/*-------------------------------------
    Copy Operator
-------------------------------------*/
scriptable& scriptable::operator=(const scriptable&) {
    return *this;
}

/*-------------------------------------
    Move Operator
-------------------------------------*/
scriptable& scriptable::operator=(scriptable&&) {
    return *this;
}

} // end script namespace
} // end ls namespace

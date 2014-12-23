/* 
 * File:   functor.h
 * Author: Miles Lacey
 *
 * Created on April 13, 2014, 9:07 PM
 */

#ifndef __LS_SCRIPT_FUNCTOR_H__
#define	__LS_SCRIPT_FUNCTOR_H__

#include <iostream> // std::cout, std::cin, std::cerr
#include <utility> // std::move()
#include <typeinfo> // typeid(x)

#include "lightsky/utils/assertions.h" // LS_DEBUG_ASSERT

#include "lightsky/script/setup.h"
#include "lightsky/script/scriptable.h"
#include "lightsky/script/variable.h"
#include "lightsky/script/factory.h"
#include "lightsky/script/paramBytes.h"

namespace ls {
namespace script {

/**
 *  @brief func_ref_t is a reference-to-function typedef to make things
 *  easier to understand in-code.
 *  
 *  Use this typedef to instantiate a reference to a scripted function
 *  which takes an array of script variables as its parameters.
 */
typedef void (&func_ref_t)(variable** const);

/**----------------------------------------------------------------------------
    @brief Functor Base Class
    
    The functor base class is constructed with a reference to a native C/C++
    function. It contains methods to store and load its parameters from a
    script file, self-compile, and change its arguments at runtime.
-----------------------------------------------------------------------------*/
class functor : public scriptable {
    protected:
        /**
         *  @brief A verification method for single arguments.
         *  
         *  This is similar to the 'compile' method, but allows one to check a
         *  single functor argument and verify that it is safe to operate at
         *  run-time. This is explicitly called for each argument when calling
         *  the 'compile()' method.
         *  
         *  @param g
         *  A constant reference to a functor object.
         *  
         *  @param i
         *  The index of the argument in 'f' to verify.
         *  
         *  @param t
         *  A dummy type which allows argument type information to be matched
         *  against something.
         *  
         *  @return TRUE if the argument in 'f', specified by 'i', is able
         *  to be used, FALSE if not.
         */
        template <typename arg_t>
        static bool checkSingleArg(const functor& f, unsigned i, arg_t* t);
        
        /**
         *  @brief A verification method for single arguments.
         *  
         *  This is similar to the 'compile' method, but allows one to check a
         *  single functor argument and verify that it is safe to operate at
         *  run-time. This is explicitly called for each argument when calling
         *  the 'compile()' method.
         *  
         *  @param g
         *  A constant reference to a functor object.
         *  
         *  @param i
         *  The index of the argument in 'f' to verify.
         *  
         *  @param t
         *  A dummy type which allows argument type information to be matched
         *  against something.
         *  
         *  @param ts
         *  Addition types for subsequent argument matching.
         *  
         *  @return TRUE if the argument in 'f', specified by 'i', is able
         *  to be used, FALSE if not.
         */
        template <typename arg_t, typename... args_t>
        static bool checkArgs(const functor& f, unsigned i, arg_t* t, args_t*... ts);
        
        /**
         *  @brief A verification method for single arguments.
         *  
         *  This is similar to the 'compile' method, but allows one to check a
         *  single functor argument and verify that it is safe to operate at
         *  run-time. This is explicitly called for each argument when calling
         *  the 'compile()' method.
         *  
         *  @param g
         *  A constant reference to a functor object.
         *  
         *  @param i
         *  The index of the argument in 'f' to verify.
         *  
         *  @param t
         *  A dummy type which allows argument type information to be matched
         *  against something.
         *  
         *  @return TRUE if the argument in 'f', specified by 'i', is able
         *  to be used, FALSE if not.
         */
        template <typename arg_t>
        static bool checkArgs(const functor& f, unsigned i, arg_t* t);
        
        /**
         *  @brief the 'nextFunc' member is a pointer to another function that
         *  can be run after *this.
         *  
         *  This member allows functions to be chained together at runtime,
         *  creating a linked-list of functions.
         */
        functor* nextFunc = nullptr;
        
        /**
         *  @brief 'pFunction' is a reference to a native function wrapper.
         *  
         *  This member references a wrapper function which takes an array of
         *  script variables as parameters. Use the wrapper function to map
         *  argument parameters to actual, native parameters and a return
         *  value.
         */
        func_ref_t pFunction;
        
        /**
         *  @brief An array of pointers to variables.
         *  
         *  Retaining an array of argument pointers allows variables to be
         *  mapped to functors at run-time.
         */
        variable** const pArgs;
        
        /**
         *  @brief Protected Constructor
         *  
         *  This constructor MUST be called by any derived functor constructors
         *  in order to properly initialize *this and all members contained in
         *  *this.
         */
        functor(variable** const pArguments, func_ref_t pFunc);

    public:
        /**
         *  @brief Functor Destructor
         * 
         *  Frees all resources used by *this.
         */
        virtual ~functor() = 0;
        
        /**
         *  @brief Basic constructor
         *  
         *  This constructor has been deleted due to the need for 
         *  construction of protected members by derived classes.
         */
        functor() = delete;
        
        /**
         *  @brief Copy Constructor
         *  
         *  This constructor has been deleted due to the need for 
         *  construction of protected members by derived classes.
         */
        functor(const functor& f) = delete;
        
        /**
         *  @brief Move Constructor
         *  
         *  This constructor has been deleted due to the need for 
         *  construction of protected members by derived classes.
         */
        functor(functor&& f) = delete;
        
        /**
         *  @brief Copy Assignment
         *  
         *  Copies pointers of arguments from the input parameter into *this.
         *  Remember to compile *this after a copy is performed in order to
         *  ensure program stability.
         *  
         *  @param f
         *  A constant reference to a functor object with the same signature as
         *  *this.
         *  
         *  @return a reference to *this.
         */
        functor& operator =(const functor& f);
        
        /**
         *  @brief Move Assignment
         *  
         *  Moves pointers of arguments from the input parameter into *this.
         *  Remember to compile *this after a move is performed in order to
         *  ensure program stability.
         *  
         *  @param f
         *  An r-value reference to a functor object with the same signature as
         *  *this.
         *  
         *  @return a reference to *this.
         */
        functor& operator =(functor&& f);
        
        /**
         *  @brief Get the function that has been assigned to run after *this.
         *  
         *  Functors in the scripting system are linked to each other by
         *  pointers. When another function is assigned as the 'next' functor,
         *  then it will run after *this one has completed.
         *  
         *  @return a pointer to the functor object which has been assigned to
         *  run after *this.
         */
        inline functor* getNextFunc();
        
        /**
         *  @brief Assign a functor to run after *this.
         *  
         *  Functors in the scripting system are linked to each other by
         *  pointers. When another function is assigned as the 'next' functor,
         *  then it will run after *this one has completed.
         *  
         *  @param f
         *  A pointer to a functor object. If the input parameter is NULL, then
         *  the function sequence will halt after this functor has completed
         *  its 'run()' method.
         */
        inline void setNextFunc(functor* const f);
        
        /**
         *  @brief Get *this object's scriptable type.
         *  
         *  @return script_base_t::SCRIPT_FUNC
         */
        inline script_base_t getScriptType() const final;
        
        /**
         *  @brief Get the run-time-type information of *this functor.
         *  
         *  This method will return a hash-code, indicating what type of
         *  functor *this is. The has code is unique to types of functors, not
         *  individual functor objects. This hash code is used by the global
         *  script factories in order to generate a functor at run-time.
         *  
         *  @return hash_t
         *  A hash-code that will identify the RTTI information of *this.
         */
        virtual hash_t getScriptSubType() const = 0;
        
        /**
         *  @brief Retrieve the number of arguments required to run *this.
         *  
         *  The number of arguments to the functor is not always the same
         *  number of arguments that *this functor's native function needs.
         *  Functor arguments can be mapped to return values, or to sequences
         *  of internal functions. It is up to the definition code to determine
         *  where functor arguments are mapped.
         *  
         *  @return An unsigned integral type, indicating how many arguments
         *  *this functor needs to run.
         */
        virtual unsigned getNumArgs() const = 0;
        
        /**
         *  @brief Retrieve an arguments from *this.
         *  
         *  The number of arguments to the functor is not always the same
         *  number of arguments that *this functor's native function needs.
         *  Functor arguments can be mapped to return values, or to sequences
         *  of internal functions. It is up to the definition code to determine
         *  where functor arguments are mapped.
         *  
         *  @return A pointer to an internal variable that will be used to run
         *  *this.
         */
        inline variable* getArg(unsigned index) const;
        
        /**
         *  @brief Assign a variable to be functor argument.
         *  
         *  The number of arguments to the functor is not always the same
         *  number of arguments that *this functor's native function needs.
         *  Functor arguments can be mapped to return values, or to sequences
         *  of internal functions. It is up to the definition code to determine
         *  where functor arguments are mapped.
         *  
         *  @note Always remember to recompile your functors after manipulating
         *  functor arguments to ensure they don't crash at run-time. The
         *  scripting system provides the means to verify type information but
         *  does not perform these checks for you.
         *  
         *  @param v
         *  A pointer to an variable object that will be used to run
         *  *this.
         */
        inline void setArg(unsigned index, variable* v);
        
        /**
         *  @brief Load functor data from an std::istream
         *  
         *  A serialization method to will help reload data from a standard
         *  input stream. This method uses the overloaded input stream operator
         *  'std::istream::operator>> (T)' in order to load functor data into
         *  *this.
         *  
         *  @param istr
         *  A reference to a std::istream object which contains functor data
         *  to be loaded into *this.
         *  
         *  @param vlm
         *  A variable-loading factory that will be used to map variable data
         *  from the input stream into *this.
         *  
         *  @param flm
         *  A function-loading factory that will be used to map functor data
         *  from the input stream into *this.
         *  
         *  @return a boolean value that will determine if data was
         *  successfully loaded into *this (TRUE) or not (FALSE).
         */
        virtual bool load(std::istream& istr, varLoaderMap& vlm, funcLoaderMap& flm);

        /**
         *  @brief Save all data from *this into an std::ostream.
         *  
         *  In this instance, functors, references to other functors, and
         *  variables are all saved using RTTI information. Scriptable objects
         *  are not saved, just their type-info. All data is mapped to/from the
         *  'loaderMap' objects in order to ensure cross-references are
         *  maintained when reloaded from an input stream.
         *  
         *  @param ostr
         *  A reference to an std::ostream object. 
         */
        virtual void save(std::ostream& ostr) const;
        
        /**
         *  @brief Compile/Verify function arguments
         *  
         *  This method ensures that a functor is safe to operate at run-time.
         *  It uses custom RTTI information, combined with derived-type's
         *  template parameters to ensure that the proper arguments are placed
         *  in the correct order at run-time.
         *  
         *  @note Because the scripting system does not manage the order in
         *  which you actually use arguments, please ensure that your
         *  functor-mapping code is consistent with the derived functor's
         *  template parameters.
         *  
         *  @return TRUE if a functor managed to compile correctly, FALSE if
         *  not. If this function returns false, please check std::cerr for
         *  information on what went wrong. This will be changed in the future
         *  in order to provide more convenient error tracking.
         */
        virtual bool compile() = 0;
        
        /**
         *  @brief Run a functor at run-time.
         */
        inline void run();
};

/**----------------------------------------------------------------------------
    @brief Functor Class Template Type
    
    The template functor type inherits all members and data from the functor
    base class.
-----------------------------------------------------------------------------*/
template <hash_t hashId, typename... args_t>
class functor_t final : public functor {
    private:
        /**
         *  @brief An array of pointers to scriptable variables.
         *  
         *  This member contains reference pointers to scriptable variables
         *  which will be manipulated/used by *this.
         */
        variable* parameters[sizeof...(args_t)] = {nullptr};
        
        /**
         *  @brief Implementation of the function to be run.
         *  
         *  This static member is defined through the LS_SCRIPT_DEFINE_FUNC
         *  macro. The static functionImpl member is what will actually be
         *  called when this function is run. Use this to define mappings of
         *  internal argument indices to actual native function parameters and
         *  return values.
         *  
         *  @param pArgs
         *  A pointer to an array of pointers to scriptable variables (this
         *  will actually be the 'parameters' member in *this).
         */
        static func_ref_t functionImpl;

    public:
        /**
         *  @brief Destructor
         *  
         *  Frees all resources used by *this.
         */
        virtual ~functor_t();
        
        /**
         *  @brief Constructor
         *  
         *  Initializes *this and all base classes.
         */
        functor_t();

        /**
         *  @brief Copy Constructor
         *  
         *  Copies all data from a functor of the same type into *this.
         *  
         *  @param f
         *  A constant reference to another functor of the same template type.
         */
        functor_t(const functor_t& f);
        
        /**
         *  @brief Move Constructor
         *  
         *  Moves all data from a functor of the same type into *this without
         *  performing any copies.
         *  
         *  @param f
         *  An r-value reference to another functor of the same template type.
         */
        functor_t(functor_t&& f);
        
        /**
         *  @brief Copy Assignment
         *  
         *  Copies all data from a functor of the same type into *this.
         *  
         *  @param f
         *  A constant reference to another functor of the same template type.
         *  
         *  @return a reference to *this.
         */
        functor_t& operator =(const functor_t&);
        
        /**
         *  @brief Move Assignment
         *  
         *  Moves all data from a functor of the same type into *this without
         *  performing any copies.
         *  
         *  @param f
         *  An r-value reference to another functor of the same template type.
         *  
         *  @return a reference to *this.
         */
        functor_t& operator =(functor_t&&);

        /**
         *  @brief Get the run-time-type information of *this functor.
         *  
         *  This method will return a hash-code, indicating what type of
         *  functor *this is. The has code is unique to types of functors, not
         *  individual functor objects. This hash code is used by the global
         *  script factories in order to generate a functor at run-time.
         *  
         *  @return hash_t
         *  A hash-code that identifies the RTTI information of *this.
         */
        inline hash_t getScriptSubType() const final;

        /**
         *  @brief Retrieve the number of arguments required to run *this.
         *  
         *  The number of arguments to the functor is not always the same
         *  number of arguments that *this functor's native function needs.
         *  Functor arguments can be mapped to return values, or to sequences
         *  of internal functions. It is up to the definition code to determine
         *  where functor arguments are mapped.
         *  
         *  @return An unsigned integral type, indicating how many arguments
         *  *this functor needs to run.
         */
        virtual unsigned getNumArgs() const final;

        /**
         *  @brief Load functor data from an std::istream
         *  
         *  A serialization method to will help reload data from a standard
         *  input stream. This method uses the overloaded input stream operator
         *  'std::istream::operator>> (T)' in order to load functor data into
         *  *this.
         *  
         *  @param istr
         *  A reference to a std::istream object which contains functor data
         *  to be loaded into *this.
         *  
         *  @param vlm
         *  A variable-loading factory that will be used to map variable data
         *  from the input stream into *this.
         *  
         *  @param flm
         *  A function-loading factory that will be used to map functor data
         *  from the input stream into *this.
         *  
         *  @return a boolean value that will determine if data was
         *  successfully loaded into *this (TRUE) or not (FALSE).
         */
        bool load(std::istream& istr, varLoaderMap& vlm, funcLoaderMap& flm) final;
        
        /**
         *  @brief Save all data from *this into an std::ostream.
         *  
         *  In this instance, functors, references to other functors, and
         *  variables are all saved using RTTI information. Scriptable objects
         *  are not saved, just their type-info. All data is mapped to/from the
         *  'loaderMap' objects in order to ensure cross-references are
         *  maintained when reloaded from an input stream.
         *  
         *  @param ostr
         *  A reference to an std::ostream object. 
         */
        void save(std::ostream& ostr) const final;

        /**
         *  @brief Compile/Verify function arguments
         *  
         *  This method ensures that a functor is safe to operate at run-time.
         *  It uses custom RTTI information, combined with derived-type's
         *  template parameters to ensure that the proper arguments are placed
         *  in the correct order at run-time.
         *  
         *  @note Because the scripting system does not manage the order in
         *  which you actually use arguments, please ensure that your
         *  functor-mapping code is consistent with the derived functor's
         *  template parameters.
         *  
         *  @return TRUE if a functor managed to compile correctly, FALSE if
         *  not. If this function returns false, please check std::cerr for
         *  information on what went wrong. This will be changed in the future
         *  in order to provide more convenient error tracking.
         */
        inline bool compile() final;
};

/**----------------------------------------------------------------------------
    @brief Functor Template Type with Void Parameters
-----------------------------------------------------------------------------*/
template <hash_t hashId>
class functor_t<hashId, void> final : public functor {
    private:
        /**
         *  @brief Implementation of the function to be run.
         *  
         *  This static member is defined through the LS_SCRIPT_DEFINE_FUNC
         *  macro. The static functionImpl member is what will actually be
         *  called when this function is run. Use this to define mappings of
         *  internal argument indices to actual native function parameters and
         *  return values.
         *  
         *  @param pArgs
         *  A pointer to an array of pointers to scriptable variables (this
         *  will actually be the 'parameters' member in *this).
         */
        static func_ref_t functionImpl;

    public:
        /**
         *  @brief Destructor
         *  
         *  Frees all resources used by *this.
         */
        virtual ~functor_t();

        /**
         *  @brief Constructor
         *  
         *  Initializes *this and all base classes.
         */
        functor_t();

        /**
         *  @brief Copy Constructor
         *  
         *  Copies all data from a functor of the same type into *this.
         *  
         *  @param f
         *  A constant reference to another functor of the same template type.
         */
        functor_t(const functor_t& f);
        
        /**
         *  @brief Move Constructor
         *  
         *  Moves all data from a functor of the same type into *this without
         *  performing any copies.
         *  
         *  @param f
         *  An r-value reference to another functor of the same template type.
         */
        functor_t(functor_t&& f);

        /**
         *  @brief Copy Assignment
         *  
         *  Copies all data from a functor of the same type into *this.
         *  
         *  @param f
         *  A constant reference to another functor of the same template type.
         *  
         *  @return a reference to *this.
         */
        functor_t& operator =(const functor_t& f);
        
        /**
         *  @brief Move Assignment
         *  
         *  Moves all data from a functor of the same type into *this without
         *  performing any copies.
         *  
         *  @param f
         *  An r-value reference to another functor of the same template type.
         *  
         *  @return a reference to *this.
         */
        functor_t& operator =(functor_t&& f);

        /**
         *  @brief Get the run-time-type information of *this functor.
         *  
         *  This method will return a hash-code, indicating what type of
         *  functor *this is. The has code is unique to types of functors, not
         *  individual functor objects. This hash code is used by the global
         *  script factories in order to generate a functor at run-time.
         *  
         *  @return hash_t
         *  A hash-code that identifies the RTTI information of *this.
         */
        inline hash_t getScriptSubType() const final;

        /**
         *  @brief Retrieve the number of arguments required to run *this.
         *  
         *  The number of arguments to the functor is not always the same
         *  number of arguments that *this functor's native function needs.
         *  Functor arguments can be mapped to return values, or to sequences
         *  of internal functions. It is up to the definition code to determine
         *  where functor arguments are mapped.
         *  
         *  @return An unsigned integral type, indicating how many arguments
         *  *this functor needs to run.
         */
        virtual unsigned getNumArgs() const final;

        /**
         *  @brief Load functor data from an std::istream
         *  
         *  A serialization method to will help reload data from a standard
         *  input stream. This method uses the overloaded input stream operator
         *  'std::istream::operator>> (T)' in order to load functor data into
         *  *this.
         *  
         *  @param istr
         *  A reference to a std::istream object which contains functor data
         *  to be loaded into *this.
         *  
         *  @param vlm
         *  A variable-loading factory that will be used to map variable data
         *  from the input stream into *this.
         *  
         *  @param flm
         *  A function-loading factory that will be used to map functor data
         *  from the input stream into *this.
         *  
         *  @return a boolean value that will determine if data was
         *  successfully loaded into *this (TRUE) or not (FALSE).
         */
        bool load(std::istream& istr, varLoaderMap& vlm, funcLoaderMap& flm) final;
        
        /**
         *  @brief Save all data from *this into an std::ostream.
         *  
         *  In this instance, functors, references to other functors, and
         *  variables are all saved using RTTI information. Scriptable objects
         *  are not saved, just their type-info. All data is mapped to/from the
         *  'loaderMap' objects in order to ensure cross-references are
         *  maintained when reloaded from an input stream.
         *  
         *  @param ostr
         *  A reference to an std::ostream object. 
         */
        void save(std::ostream& ostr) const final;

        /**
         *  @brief Compile/Verify function arguments
         *  
         *  This method ensures that a functor is safe to operate at run-time.
         *  It uses custom RTTI information, combined with derived-type's
         *  template parameters to ensure that the proper arguments are placed
         *  in the correct order at run-time.
         *  
         *  @note Because the scripting system does not manage the order in
         *  which you actually use arguments, please ensure that your
         *  functor-mapping code is consistent with the derived functor's
         *  template parameters.
         *  
         *  @return TRUE if a functor managed to compile correctly, FALSE if
         *  not. If this function returns false, please check std::cerr for
         *  information on what went wrong. This will be changed in the future
         *  in order to provide more convenient error tracking.
         */
        inline bool compile() final;
};

} // end script namespace
} // end ls namespace

#include "lightsky/script/generic/functor_impl.h"

/*-----------------------------------------------------------------------------
    Functor Utility Macros
-----------------------------------------------------------------------------*/
/**
 *  @brief Functor Declaration for Header Files
 *  
 *  Use this macro in a header file in order to declare a functor and provide
 *  global access to the script type to be used.
 *  
 *  For example, use it as follows:
 *      LS_SCRIPT_DECLARE_FUNC(addNums, scriptVar_int, scriptVar_int);
 *      LS_SCRIPT_DECLARE_FUNC(strcat, scriptVar_string, scriptVar_string, scriptVar_string);
 *  
 *  The sample above will provide the declarations, hashes, and factories for
 *  two new functors. These functors themselves can be referenced like so:
 *      'scriptFunc_addNums' and 'scriptFunc_strcat'
 *  
 *  The hashes can be referenced as such:
 *      'scriptHash_addNums' and 'scriptHash_strcat'
 *  
 *  And the factory methods are accessible like this:
 *      ls::script::functor* pFunc;
 *      pFunc = ls::script::createScriptFunc(scriptHash_addNums);
 *      ...
 *      delete pFunc;
 *  
 *      pFunc = ls::script::createScriptFunc(scriptHash_strcat);
 *      ...
 *      delete pFunc;
 */
#define LS_SCRIPT_DECLARE_FUNC(funcName, ...) \
    \
    enum : ls::script::hash_t { \
        scriptHash_##funcName = LS_SCRIPT_HASH_FUNC(LS_STRINGIFY(funcName)) \
    }; \
    \
    typedef ls::script::functor_t<scriptHash_##funcName, __VA_ARGS__> scriptFunc_##funcName; \
    \
    extern const ls::script::funcFactory& scriptFactory_##funcName; \
    \
    template <> \
    ls::script::func_ref_t scriptFunc_##funcName::functionImpl; \
    \
    extern template class ls::script::functor_t<scriptHash_##funcName, __VA_ARGS__>

/**
 *  @brief Function Definition for source files.
 *  
 *  The definition of functors MUST define how arguments will be mapped to
 *  native functions. For example, to use this, simply write as follows:
 *  
 *      LS_SCRIPT_DEFINE_FUNC(addNums, scriptVar_int, scriptVar_int) {
 *          LS_SCRIPT_PARAM(0, scriptVar_int) += LS_SCRIPT_PARAM(1, scriptVar_int);
 *      };
 *  
 *      LS_SCRIPT_DEFINE_FUNC(strcat, scriptVar_string, scriptVar_string, scriptVar_string) {
 *          LS_SCRIPT_PARAM(0, scriptVar_string)
 *              = LS_SCRIPT_PARAM(1, scriptVar_string)
 *              + LS_SCRIPT_PARAM(2, scriptVar_string);
 *      };
 *  
 *  Although a bit verbose, the process is actually quite painless once you get
 *  used to it. As shown above, functor arguments/parameters are accessible
 *  through both indices and types. In order to ensure that the proper types
 *  get used by a functor, make sure that the 'compile()' method is called and
 *  returns TRUE before running a functor.
 *  
 *  Finally, defining a functor using this macro enables linkage to the global
 *  factory methods. A functor can now be spawned in the following manner:
 *      ls::script::functor* pFunc;
 *      pFunc = ls::script::createScriptFunc(scriptHash_addNums);
 *      if (pFunc->compile()) {
 *          pFunc->run();
 *      }
 *      delete pFunc;
 *      
 */
#define LS_SCRIPT_DEFINE_FUNC(funcName, ...) \
    template class ls::script::functor_t<scriptHash_##funcName, __VA_ARGS__>; \
    \
    const ls::script::funcFactory& scriptFactory_##funcName = \
        ls::script::gFuncFactory[scriptHash_##funcName] = \
            []()->ls::script::functor* { return new scriptFunc_##funcName{}; }; \
    \
    template <> \
    ls::script::func_ref_t scriptFunc_##funcName::functionImpl = \
        *[](ls::script::variable** const pArgs)->void

/**
 *  @brief Function Argument Accessibility
 *  
 *  Use this macro to access arguments/parameters when defining the functor.
 *  For example, use it like this:
 *  
 *      LS_SCRIPT_DEFINE_FUNC(addNums, scriptVar_int, scriptVar_int) {
 *          LS_SCRIPT_PARAM(0, scriptVar_int) += LS_SCRIPT_PARAM(1, scriptVar_int);
 *      };
 *  
 *      LS_SCRIPT_DEFINE_FUNC(strcat, std::string, std::, std::string) {
 *          LS_SCRIPT_PARAM(0, std::string)
 *              = LS_SCRIPT_PARAM(1, std::string)
 *              + LS_SCRIPT_PARAM(2, std::string);
 *      };
 */
#define LS_SCRIPT_PARAM(index, varType) \
    static_cast<ls::script::variable_t<LS_SCRIPT_HASH_FUNC(LS_STRINGIFY(varType)), varType>*>(pArgs[index])->data

/*-----------------------------------------------------------------------------
    Built-In Types
-----------------------------------------------------------------------------*/
LS_SCRIPT_DECLARE_FUNC(empty, void);

#endif	/* __LS_SCRIPT_FUNCTOR_H__ */

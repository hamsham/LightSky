
namespace ls {
namespace draw {

/*-------------------------------------
    Get a pointer to the SDL_GLContext that is used by the active
    renderer.
-------------------------------------*/
inline void* context::getContext() const {
    return pContext;
}

} // end draw namespace
} // end ls namespace

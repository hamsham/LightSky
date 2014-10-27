
namespace ls {
namespace draw {

/*-------------------------------------
    Determine if this object holds a handle to an open window.
-------------------------------------*/
inline bool display::isRunning() const {
    return pWindow != nullptr;
}

/*-------------------------------------
    Determine if the current display is using a native window handle.
-------------------------------------*/
inline bool display::usingNativeWindow() const {
    return windowIsNative;
}

} // end draw namespace
} // end ls namespace

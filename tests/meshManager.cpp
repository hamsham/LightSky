
/**
 * Testing a mesh manager for use within the LS framework.
 */

#include <iostream>
#include <unordered_map>

class mesh {
    private:
    protected:
    public:
        mesh();
        mesh(const mesh&);
        mesh(mesh&&);
        
        ~mesh() {
            clear();
        }
        
        mesh& operator=(const mesh&);
        mesh& operator=(mesh&&);
        
        bool operator== (const mesh&) const;
        bool operator!= (const mesh&) const;
        
        tmeplate<typename mesh_type, typename ...arg_t>
        bool load(const sceneManager&, const arg_t...&);
};

class meshManager {
    private:
    protected:
    public:
        typedef unordered_map<vbo_t, mesh> meshMap;
        
        meshManager();
        meshManager(const meshManager&);
        meshManager(meshManager&&);
        
        ~meshManager() {
            clear();
        }
        
        meshManager& operator=(const meshManager&);
        meshManager& operator=(meshManager&&);
        
        void clear();
};

int main() {
    return 0;
}
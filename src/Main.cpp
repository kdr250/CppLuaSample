#include <lua.hpp>

int main() {
    lua_State* pL = luaL_newstate();

    lua_close(pL);
    return 0;
}

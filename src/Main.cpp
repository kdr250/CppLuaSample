#include <iostream>
#include <lua.hpp>

int main() {
    lua_State* pL = luaL_newstate();

    if (luaL_dofile(pL, "resources/sample.lua") != LUA_OK) {
        // Error
        std::cerr << lua_tostring(pL, lua_gettop(pL)) << std::endl;
        lua_close(pL);
        return EXIT_FAILURE;
    }

    lua_close(pL);
    return EXIT_SUCCESS;
}

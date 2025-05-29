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

    std::cout << "Sample: variable" << std::endl;
    {
        lua_getglobal(pL, "test1");
        lua_getglobal(pL, "test3");
        lua_getglobal(pL, "test2");
        lua_getglobal(pL, "test4");

        const int num = lua_gettop(pL);
        for (int i = 1; i <= num; ++i) {
            const int type = lua_type(pL, i);
            std::cout << "type=" << type << ", name=" << lua_typename(pL, type)
                      << ", val=" << lua_tonumber(pL, i) << ", str=" << lua_tostring(pL, i)
                      << std::endl;
        }
        lua_pop(pL, num);
    }

    lua_close(pL);
    return EXIT_SUCCESS;
}

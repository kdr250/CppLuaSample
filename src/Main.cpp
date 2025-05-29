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

    std::cout << "Sample: function C++ call Lua" << std::endl;
    {
        // 0: Calculate Fibonacci
        const int nargs0 = 1;
        const int nresults0 = 1;
        const int msgh0 = 0;
        lua_getglobal(pL, "fibonacci");
        lua_pushnumber(pL, 10);
        if (lua_pcall(pL, nargs0, nresults0, msgh0) != LUA_OK) {
            std::cerr << lua_tostring(pL, lua_gettop(pL)) << std::endl;
            lua_close(pL);
            return EXIT_FAILURE;
        }
        std::cout << "\t" << "fibonacci=" << lua_tointeger(pL, 1) << std::endl;

        const int num1 = lua_gettop(pL);
        lua_pop(pL, num1);

        // 1: calculate multiple values
        const int nargs1 = 2;
        const int nresults1 = 3;
        const int msgh1 = 0;
        lua_getglobal(pL, "multi");
        lua_pushnumber(pL, 3);
        lua_pushnumber(pL, 7);
        if (lua_pcall(pL, nargs1, nresults1, msgh1) != LUA_OK) {
            std::cerr << lua_tostring(pL, lua_gettop(pL)) << std::endl;
            lua_close(pL);
            return EXIT_FAILURE;
        }
        std::cout << "\t" << "return=" << lua_tointeger(pL, 1) << ", " << lua_tointeger(pL, 2)
                  << ", " << lua_tostring(pL, 3) << std::endl;

        const int num2 = lua_gettop(pL);
        lua_pop(pL, num2);
    }

    lua_close(pL);
    return EXIT_SUCCESS;
}

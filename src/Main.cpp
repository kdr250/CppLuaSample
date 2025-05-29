#include <iostream>
#include <lua.hpp>

int UltimateFunction(lua_State* pL) {
    // Retrieve arguments from Lua
    const lua_Number ret = lua_tonumber(pL, 1);
    lua_pop(pL, lua_gettop(pL));

    // Set return value to Lua
    const int val = static_cast<int>(ret) * 2;
    lua_pushnumber(pL, val);

    const int returnLuaNum = 1;
    return returnLuaNum;
}

int main() {
    lua_State* pL = luaL_newstate();

    if (luaL_dofile(pL, "resources/sample.lua") != LUA_OK) {
        // Error
        std::cerr << lua_tostring(pL, lua_gettop(pL)) << std::endl;
        lua_close(pL);
        return EXIT_FAILURE;
    }

    std::cout << "Sample: function Lua call C++" << std::endl;
    {
        // Register callback function
        const char luaFuncName[] = "Ultimate";
        lua_register(pL, luaFuncName, &UltimateFunction);

        const int nargs = 0;
        const int nresults = 1;
        const int msgh = 0;
        lua_getglobal(pL, "master");
        if (lua_pcall(pL, nargs, nresults, msgh) != LUA_OK) {
            std::cerr << lua_tostring(pL, lua_gettop(pL)) << std::endl;
            lua_close(pL);
            return EXIT_FAILURE;
        }
        std::cout << "\t" << "master=" << lua_tointeger(pL, 1) << std::endl;
    }

    lua_close(pL);
    return EXIT_SUCCESS;
}

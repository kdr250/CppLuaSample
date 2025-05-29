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

    std::cout << "Sample: Coroutine" << std::endl;
    {
        luaL_openlibs(pL);

        lua_State* pCoroutine = lua_newthread(pL);

        lua_getglobal(pCoroutine, "co_routine");

        lua_State* from = nullptr;
        const int nargs = 0;
        int nret = 0;
        int count = 0;
        while (true) {
            const int ret = lua_resume(pCoroutine, from, nargs, &nret); // Start or Restart
            if (ret == LUA_OK) {
                break;
            }

            // Error handling
            if (ret != LUA_YIELD) {
                std::cerr << lua_tostring(pCoroutine, lua_gettop(pCoroutine)) << std::endl;
                lua_close(pL);
                return EXIT_FAILURE;
            }

            // Coroutine
            std::cout << "\t" << "count=" << count++ << ", ret=" << nret;
            for (int i = 0; i < nret; ++i) {
                std::cout << ", " << lua_tostring(pCoroutine, i + 1);
            }
            std::cout << std::endl;
        }

        const int num = lua_gettop(pL);
        lua_pop(pL, num);
    }

    lua_close(pL);
    return EXIT_SUCCESS;
}

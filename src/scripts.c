//
// Created by pkulik0 on 30/08/2022.
//

#include "scripts.h"

void scripts_run() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    char* code = "print('Hello World')";

    if(luaL_loadstring(L, code) == LUA_OK) {
        if(lua_pcall(L, 0, 0, 0) == LUA_OK) {
            lua_pop(L, lua_gettop(L));
        }
    }

    lua_close(L);
}



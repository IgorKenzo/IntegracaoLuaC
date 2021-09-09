// https://www.lua.org/pil/25.2.html

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function declaration */
float f (lua_State* L, const char* funcName, const char **x, int tam);
void error (lua_State *L, const char *fmt, ...);

int main(int argc, const char* argv[]){

    if (argc == 1) {
        printf("Forneca parametros");
        return 1;
    }

    //Pega o nome da função, e add o .lua
    char filename[20];
    memcpy(filename, argv[1], strlen(argv[1]));
    strcat(filename, ".lua");

    //Pega o numero de argumentos
    // long n = strtol(argv[2], NULL, 10); 
    // int argNum = n;
    int argNum = argc - 3; //Valor de parametros passado menos 3 (o proprio arquivo, nome da func, e o que seria esse valor)

    const char **start = &argv[3];

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // carrega o arquivo e executa suas as ações
    luaL_dofile(L, filename);
    printf("Puxando do arquivo: %s\n", filename);
    float valor = f(L, argv[1], start, argNum);

    // printf("Valor de resultado %f\n", valor);

    lua_close(L);
    return 0;
}

/* call a function `calculo' defined in Lua */
float f (lua_State* L, const char* funcName, const char **x, int tam) {
  //double z;

  /* push functions and arguments */
  lua_getglobal(L, funcName);  /* function to be called */
//   lua_pushnumber(L, x);   /* push 1st argument */
//   lua_pushnumber(L, y);   /* push 2nd argument */
    for(int i = 0; i < tam; i++) {
        long n = strtol(x[i], NULL, 10);
        lua_pushnumber(L, n);
    }

  /* do the call (2 arguments, 1 result) */
  if (lua_pcall(L, tam, 1, 0) != 0)
    error(L, "error running function %s: %s\n",funcName,
              lua_tostring(L, -1));

//   /* retrieve result */
//   if (!lua_isnumber(L, -1))
//     error(L, "function must return a number\n");
    
    if (lua_isnumber(L, -1)) {
        float res = lua_tonumber(L, -1);
        lua_pop(L, 1);  /* pop returned value */

        printf("Valor de resultado: %f\n", res);
    }
    else {
        char* res = lua_tostring(L, -1);
        lua_pop(L, 1);  /* pop returned value */

        printf("Valor de resultado: %s\n", res);
    }

  return 0;
}

// https://www.lua.org/pil/24.1.html#first-ex
void error (lua_State *L, const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
  lua_close(L);
  exit(EXIT_FAILURE);
}
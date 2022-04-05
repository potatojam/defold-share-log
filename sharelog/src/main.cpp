
#define LIB_NAME "ShareLog"
#define MODULE_PRIVATE_NAME "sharelog_private"

#include <dmsdk/sdk.h>

#ifdef DM_PLATFORM_HTML5

static dmExtension::Result AppInitializeShareLog(dmExtension::AppParams *params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeShareLog(dmExtension::Params *params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeShareLog(dmExtension::AppParams *params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeShareLog(dmExtension::Params *params)
{
    return dmExtension::RESULT_OK;
}

#else

#include <string>
#include <dmsdk/dlib/log.h>

static std::string stringLog;

static void LogListener(dmLog::Severity severity, const char *type, const char *message)
{
    //dmLog::LOG_SEVERITY_USER_DEBUG
    stringLog = stringLog + message;
}

static int GetShareLogString(lua_State *L)
{
    char *cstr = strcpy(new char[stringLog.length() + 1], stringLog.c_str());
    lua_pushstring(L, cstr);
    return 1;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] =
    {
        {"get_log_string", GetShareLogString},
        {0, 0}};

static void LuaInit(lua_State *L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, MODULE_PRIVATE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

static dmExtension::Result AppInitializeShareLog(dmExtension::AppParams *params)
{
    stringLog = "";
    dmLog::RegisterLogListener(&LogListener);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeShareLog(dmExtension::Params *params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeShareLog(dmExtension::AppParams *params)
{
    dmLog::UnregisterLogListener(&LogListener);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeShareLog(dmExtension::Params *params)
{
    return dmExtension::RESULT_OK;
}

#endif

DM_DECLARE_EXTENSION(ShareLog, LIB_NAME, AppInitializeShareLog, AppFinalizeShareLog, InitializeShareLog, NULL, NULL, FinalizeShareLog)
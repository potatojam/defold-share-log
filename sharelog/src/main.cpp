
#define LIB_NAME "ShareLog"
#define MODULE_PRIVATE_NAME "sharelog_private"

#include <dmsdk/sdk.h>

#if defined(DM_RELEASE)
static const bool is_release_version = true;
#else
static const bool is_release_version = false;
#endif
bool block_release_version = true;

#ifdef DM_PLATFORM_HTML5

extern "C"
{
    void ShareLog_Init();
}

static dmExtension::Result AppInitializeShareLog(dmExtension::AppParams *params)
{
    const char *brv_str = dmConfigFile::GetString(params->m_ConfigFile, "share_log.block_release_version", "true");
    block_release_version = brv_str == "true" || brv_str == "1";
    if (!block_release_version || !is_release_version)
    {
        ShareLog_Init();
    }
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

static std::string string_log;

static void LogListener(LogSeverity severity, const char *type, const char *message)
{
    // dmLog::LOG_SEVERITY_USER_DEBUG
    string_log = string_log + message;
}

static int GetShareLogString(lua_State *L)
{
    char *cstr = strcpy(new char[string_log.length() + 1], string_log.c_str());
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
    const char *brv_str = dmConfigFile::GetString(params->m_ConfigFile, "share_log.block_release_version", "true");
    block_release_version = brv_str == "true" || brv_str == "1";
    string_log = "";
    if (!block_release_version || !is_release_version)
    {
        dmLog::RegisterLogListener(&LogListener);
    }
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeShareLog(dmExtension::Params *params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeShareLog(dmExtension::AppParams *params)
{
    if (!block_release_version || !is_release_version)
    {
        dmLog::UnregisterLogListener(&LogListener);
    }
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeShareLog(dmExtension::Params *params)
{
    return dmExtension::RESULT_OK;
}

#endif

DM_DECLARE_EXTENSION(ShareLog, LIB_NAME, AppInitializeShareLog, AppFinalizeShareLog, InitializeShareLog, NULL, NULL, FinalizeShareLog)
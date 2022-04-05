
#define LIB_NAME "HtmlLog"

#include <dmsdk/sdk.h>

static dmExtension::Result AppInitializeSentinel(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeSentinel(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeSentinel(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeSentinel(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(HtmlLog, LIB_NAME, AppInitializeSentinel, AppFinalizeSentinel, InitializeSentinel, NULL, NULL, FinalizeSentinel)
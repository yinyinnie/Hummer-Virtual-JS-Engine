#ifndef SRC_JS_NATIVE_API_TYPES_H_
#define SRC_JS_NATIVE_API_TYPES_H_

#ifdef __cplusplus
#define EXTERN_C_START                                                                                                 \
    extern "C"                                                                                                         \
    {
#define EXTERN_C_END }
#else
#define EXTERN_C_START
#define EXTERN_C_END
#endif

#define NAPI_EXPORT __attribute__((visibility("default")))

EXTERN_C_START

typedef struct OpaqueNAPIRuntime *NAPIRuntime;
typedef struct OpaqueNAPIEnv *NAPIEnv;
typedef struct OpaqueNAPIValue *NAPIValue;
typedef struct OpaqueNAPIRef *NAPIRef;
typedef struct OpaqueNAPIHandleScope *NAPIHandleScope;
typedef struct OpaqueNAPIEscapableHandleScope *NAPIEscapableHandleScope;
typedef struct OpaqueNAPICallbackInfo *NAPICallbackInfo;

typedef enum
{
    // { writable: false, enumerable: false, configurable: false }
    // napi_set_property 默认为 { writable: true, enumerable: true, configurable: true }
    NAPIDefault = 0,
    NAPIWritable = 1 << 0,
    NAPIEnumerable = 1 << 1,
    NAPIConfigurable = 1 << 2,

    // napi_define_class 用于区分静态属性和实例属性，napi_define_properties 忽略该枚举
    NAPIStatic = 1 << 10,

    // 方法默认
    NAPIDefaultMethod = NAPIWritable | NAPIConfigurable,

    // 属性默认
    NAPIDefaultJSProperty = NAPIWritable | NAPIEnumerable | NAPIConfigurable,
} NAPIPropertyAttributes;

typedef enum
{
    NAPIUndefined,
    NAPINull,
    NAPIBoolean,
    NAPINumber,
    NAPIString,
    // 未来建议判断到 Object 即可，提供 NAPIIsFunction 和 NAPIIsExternal
    NAPIObject,
    NAPIFunction,
    NAPIExternal,
} NAPIValueType;

typedef enum
{
#define NAPI_STATUS(status) NAPICommon##status,
#include <napi/napi_common_status.def>
#undef NAPI_STATUS
} NAPICommonStatus;

typedef enum
{
#define NAPI_STATUS(status) NAPIError##status,
#include <napi/napi_common_status.def>
#include <napi/napi_error_status.def>
#undef NAPI_STATUS
} NAPIErrorStatus;

typedef enum
{
#define NAPI_STATUS(status) NAPIException##status,
#include <napi/napi_common_status.def>
#include <napi/napi_error_status.def>
#include <napi/napi_exception_status.def>
#undef NAPI_STATUS
} NAPIExceptionStatus;

typedef NAPIValue (*NAPICallback)(NAPIEnv env, NAPICallbackInfo callbackInfo);

typedef void (*NAPIFinalize)(void *finalizeData, void *finalizeHint);

EXTERN_C_END

#endif // SRC_JS_NATIVE_API_TYPES_H_

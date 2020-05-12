#include "myobject.h"
#include "myobject2.h"
napi_value Init(napi_env env, napi_value exports) {
    MyObject2::Init(env);
    MyObject::Init(env, exports);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
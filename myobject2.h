#ifndef TEST_ADDONS_NAPI_8_PASSING_WRAPPED_MYOBJECT_H_
#define TEST_ADDONS_NAPI_8_PASSING_WRAPPED_MYOBJECT_H_

#include <node_api.h>

class MyObject2 {
 public:
  static napi_status Init(napi_env env);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);
  static napi_status NewInstance(napi_env env,
                                 napi_value arg,
                                 napi_value* instance);
  double Val() const { return value_; }

 private:
  MyObject2();
  ~MyObject2();

  static napi_ref constructor;
  static napi_value New(napi_env env, napi_callback_info info);
  static napi_value GetValue(napi_env env, napi_callback_info info);
  static napi_value SetValue(napi_env env, napi_callback_info info);
  double value_;
  napi_env env_;
  napi_ref wrapper_;
};

#endif  // TEST_ADDONS_NAPI_8_PASSING_WRAPPED_MYOBJECT_H_
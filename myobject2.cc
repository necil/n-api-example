#include "myobject2.h"
#include <assert.h>
#include <iostream>

MyObject2::MyObject2() : env_(nullptr), wrapper_(nullptr) {}

MyObject2::~MyObject2() {
  napi_delete_reference(env_, wrapper_);
}

void MyObject2::Destructor(napi_env env,
                          void* nativeObject,
                          void* /*finalize_hint*/) {
  reinterpret_cast<MyObject2*>(nativeObject)->~MyObject2();
}

napi_ref MyObject2::constructor;

napi_status MyObject2::Init(napi_env env) {
  napi_status status;

  napi_property_descriptor properties[] = {
      {"value", 0, 0, GetValue, SetValue, 0, napi_default, 0},
  };

  napi_value cons;
  status = napi_define_class(
      env, "MyObject2", NAPI_AUTO_LENGTH, New, nullptr, 1, properties, &cons);
  if (status != napi_ok) return status;

  status = napi_create_reference(env, cons, 1, &constructor);
  if (status != napi_ok) return status;

  return napi_ok;
}

napi_value MyObject2::New(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  napi_value jsthis;
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  MyObject2* obj = new MyObject2();

  napi_valuetype valuetype;
  status = napi_typeof(env, args[0], &valuetype);
  assert(status == napi_ok);

  if (valuetype == napi_undefined) {
    obj->value_ = 0;
  } else {
    status = napi_get_value_double(env, args[0], &obj->value_);
    assert(status == napi_ok);
  }

  std::cout << "val should be:" << obj->value_ << std::endl;
  obj->env_ = env;
  status = napi_wrap(env,
                     jsthis,
                     reinterpret_cast<void*>(obj),
                     MyObject2::Destructor,
                     nullptr,  // finalize_hint
                     &obj->wrapper_);
  assert(status == napi_ok);

  return jsthis;
}

napi_status MyObject2::NewInstance(napi_env env,
                                  napi_value arg,
                                  napi_value* instance) {
  napi_status status;

  const int argc = 1;
  napi_value argv[argc] = {arg};
  napi_value cons;
  status = napi_get_reference_value(env, constructor, &cons);
  if (status != napi_ok) return status;

  status = napi_new_instance(env, cons, argc, argv, instance);
  if (status != napi_ok) return status;

  return napi_ok;
}


napi_value MyObject2::GetValue(napi_env env, napi_callback_info info) {
  napi_status status;

  napi_value jsthis;
  status = napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr);
  assert(status == napi_ok);

  MyObject2* obj;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  napi_value num;
  status = napi_create_double(env, obj->value_, &num);
  assert(status == napi_ok);

  return num;
}

napi_value MyObject2::SetValue(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 1;
  napi_value value;
  napi_value jsthis;
  status = napi_get_cb_info(env, info, &argc, &value, &jsthis, nullptr);
  assert(status == napi_ok);

  MyObject2* obj;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  status = napi_get_value_double(env, value, &obj->value_);
  assert(status == napi_ok);

  return nullptr;
}
/**
 * @file addon.cc
 * node version: 16.xx
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "object.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return MyObject::Init(env, exports);
}

NODE_API_MODULE(addon, InitAll)
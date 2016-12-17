#include "GameObject.hpp"
#include "Simulate.hpp"
#include <memory>
#include <node.h>
#include <v8.h>

void getData(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  auto result = simulate(isolate, args[0]->NumberValue());

  args.GetReturnValue().Set(result);
}

void init(v8::Local<v8::Object> exports) {
  initWorld();

  NODE_SET_METHOD(exports, "getData", getData);
}

NODE_MODULE(pancake, init);

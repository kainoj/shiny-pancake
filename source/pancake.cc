#include <node.h>
#include <v8.h>

void getData(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  v8::Local<v8::Array> data = v8::Array::New(isolate, 2);

  v8::Local<v8::Object> object1 = v8::Object::New(isolate);
  object1->Set(v8::String::NewFromUtf8(isolate, "_id_"),
               v8::Number::New(isolate, 0));
  object1->Set(v8::String::NewFromUtf8(isolate, "posx"),
               v8::Number::New(isolate, 20));
  object1->Set(v8::String::NewFromUtf8(isolate, "posy"),
               v8::Number::New(isolate, 50));
  object1->Set(v8::String::NewFromUtf8(isolate, "team"),
               v8::Number::New(isolate, 1));
  object1->Set(v8::String::NewFromUtf8(isolate, "type"),
               v8::String::NewFromUtf8(isolate, "dummy"));

  data->Set(0, object1);

  v8::Local<v8::Object> object2 = v8::Object::New(isolate);
  object2->Set(v8::String::NewFromUtf8(isolate, "_id_"),
               v8::Number::New(isolate, 1));
  object2->Set(v8::String::NewFromUtf8(isolate, "posx"),
               v8::Number::New(isolate, 200));
  object2->Set(v8::String::NewFromUtf8(isolate, "posy"),
               v8::Number::New(isolate, 370));
  object2->Set(v8::String::NewFromUtf8(isolate, "team"),
               v8::Number::New(isolate, 2));
  object2->Set(v8::String::NewFromUtf8(isolate, "type"),
               v8::String::NewFromUtf8(isolate, "dummy"));

  data->Set(1, object2);

  args.GetReturnValue().Set(data);
}

void init(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "getData", getData);
}

NODE_MODULE(pancake, init);

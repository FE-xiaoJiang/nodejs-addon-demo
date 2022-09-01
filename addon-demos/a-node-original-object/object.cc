#include "object.h"

namespace __addon1__ {

using v8::Isolate;
using v8::FunctionTemplate;
using v8::String;
using v8::Number;

MyObject::MyObject(double value) : value_(value)
{
}

MyObject::~MyObject()
{
}

void MyObject::Init(Local<Object> exports)
{
    Isolate* isolate = exports->GetIsolate();
    
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "MyObject", v8::NewStringType::kNormal).ToLocalChecked());
    // tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    NODE_SET_PROTOTYPE_METHOD(tpl, "plusOne", PlusOne);
    
    exports->Set(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "MyObject"), tpl->GetFunction(isolate->GetCurrentContext()).ToLocalChecked());
}

void MyObject::New(const FunctionCallbackInfo<Value>& args)
{
    double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue(args.GetIsolate()->GetCurrentContext()).ToChecked();
    MyObject* obj = new MyObject(value);
    obj->Wrap(args.This());
    
    args.GetReturnValue().Set(args.This());
}

void MyObject::PlusOne(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
    obj->value_ += 1;

    args.GetReturnValue().Set(Number::New(isolate, obj->value_));
}

}

#include <node.h>
#include <iostream>
namespace __inherit__ {

using v8::FunctionCallbackInfo;
using v8::HandleScope;
using v8::ObjectTemplate;
using v8::FunctionTemplate;
using v8::Function;
using v8::Isolate;
using v8::Local;
using v8::Persistent;
using v8::External;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;
using v8::Array;
using v8::MaybeLocal;
using namespace std;

Persistent<Function> cons;

char* transNameChars(Isolate* isolate, Local<Value> name)
{
    Local<String> nameS = name->ToString(isolate);
    String::Utf8Value _u(isolate, nameS);
    char* c = *_u;
    return c;
}

char* transNameChars2(char* _u)
{
    char* c = _u;
    return c;
}

void SetName(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    Local<Object> self = args.Holder();
    // char* name1 = transNameChars(isolate, args[0]);
    // char* name2 = transNameChars(isolate, args[1]);
    // cout<<name1<<" "<<name2;
    char* t1 = "ttttx";
    char* t2 = "tttty";
    char* c1 = transNameChars2(t1);
    char* c2 = transNameChars2(t2);
    cout<<c1<<" "<<c2;
    self->Set(String::NewFromUtf8(isolate, "name"), args[0]);
}

void Summary(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    Local<Object> self = args.Holder();
    char temp[512];

    String::Utf8Value type(isolate, self->Get(String::NewFromUtf8(isolate, "type"))->ToString(isolate));
    String::Utf8Value name(isolate, self->Get(String::NewFromUtf8(isolate, "name"))->ToString(isolate));

    snprintf(temp, 511, "%s is a/an %s.", *name, *type);

    args.GetReturnValue().Set(String::NewFromUtf8(isolate, temp));
}

void Pet(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    Local<Object> self = args.Holder();
    self->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, "Unknown"));
    self->Set(String::NewFromUtf8(isolate, "type"), String::NewFromUtf8(isolate, "animal"));

    args.GetReturnValue().Set(self);
}

void Dog(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    Local<Object> self = args.Holder();
    Local<Function> super = cons.Get(isolate);

    super->Call(isolate->GetCurrentContext(), self, 0, NULL);
    self->Set(String::NewFromUtf8(isolate, "type"), String::NewFromUtf8(isolate, "dog"));

    args.GetReturnValue().Set(self);
}

void Init(Local<Object> exports, Local<Object> module)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local<FunctionTemplate> pet = FunctionTemplate::New(isolate, Pet);
    pet->PrototypeTemplate()->Set(
            String::NewFromUtf8(isolate, "setName"),
            FunctionTemplate::New(isolate, SetName));
    pet->PrototypeTemplate()->Set(
            String::NewFromUtf8(isolate, "summary"),
            FunctionTemplate::New(isolate, Summary));

    Local<Function> pet_cons = pet->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();

    cons.Reset(isolate, pet_cons);

    Local<FunctionTemplate> dog = FunctionTemplate::New(isolate, Dog);
    dog->Inherit(pet);

    Local<Function> dog_cons = dog->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();

    exports->Set(String::NewFromUtf8(isolate, "Pet"), pet_cons);
    exports->Set(String::NewFromUtf8(isolate, "Dog"), dog_cons);
}

NODE_MODULE(_template, Init)

}

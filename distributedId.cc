#include "distributedId.h"

#include <string>
#include <sstream>

using namespace std;
using namespace v8;

Persistent<Function> DistributedID::constructor;

void DistributedID::Init(Handle<Object> exports) {
    Isolate* isolate = Isolate::GetCurrent();

    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "DistributedID"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    NODE_SET_PROTOTYPE_METHOD(tpl, "generateId", generateId);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "DistributedID"), tpl->GetFunction());
}

void DistributedID::New(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    
    if (args.IsConstructCall()) {
        int _id = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
        DistributedID* generator = new DistributedID(_id);
        generator->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    } else { 
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        args.GetReturnValue().Set(cons->NewInstance(isolate->GetCurrentContext(), argc, argv).ToLocalChecked());
    }
}

void DistributedID::generateId(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    DistributedID* generator = ObjectWrap::Unwrap<DistributedID>(args.Holder());
    // Local<Number> num = Number::New(isolate, generator->generateKey());
    // args.GetReturnValue().Set(num);
    ostringstream oss;
    oss << generator->generateKey();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, oss.str().c_str()));
}

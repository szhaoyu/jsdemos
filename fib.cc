// addon.cc
#include <node.h>

namespace demo {    
    using v8::Exception;
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Number;
    using v8::Object;
    using v8::String;
    using v8::Value;

    
    unsigned int Fib_Recursive(unsigned int fib) {
        if (fib > 2) {
            return (Fib_Recursive(fib - 1) + Fib_Recursive(fib - 2));
        }
        else if (2 == fib) {
            return 1;
        }
        else if (1 == fib) {
            return 1;
        }
        return 1;
    }

    void Fib(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
       

        if (!args[0]->IsNumber()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }

        //int value = Fib_Recursive(args[0]->NumberValue());
	unsigned long value = 1L << 63;
        Local<Number> num = Number::New(isolate, value);

        args.GetReturnValue().Set(num);
    }

    void Init(Local<Object> exports) {
        NODE_SET_METHOD(exports, "fib", Fib);
    }

    NODE_MODULE(Fib, Init)
}  // namespace demo


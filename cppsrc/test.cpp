#include <napi.h>

std::string func(){ //Creating a function
    return "Hy! I am a c++ function build with node-gyp and imported in your js";
}

Napi::String Wrapper(const Napi::CallbackInfo& info){
    Napi::Env env=info.Env();
    Napi::String returnValue=Napi::String::New(env,func());
    return returnValue;

}
Napi::Object InitAll(Napi::Env env, Napi::Object exports){
    exports.Set(
        "hello",Napi::Function::New(env,Wrapper)
    );
    return exports;
}
NODE_API_MODULE(NODE_GYP_MODULE_NAME,InitAll)


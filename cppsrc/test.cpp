#include <napi.h>
#include<thread>
#include<iostream>
std::string func(std::string a,std::string b){
    std::cout<<"Checking threads\n"; //Creating a function
    std::thread t1([a](){
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout<<a<<std::endl;});
    std::thread t2([b](){std::cout<<b<<std::endl;});
    t1.join();
    t2.join();
    return "";
}

 /*Wrapping the function in a function wrapper.This function is called with a callback info from which we set env.
 Return type of this function is same as the function it is wrapping(from Napi scope).This function returns A New function 
 with env and original function*/
Napi::String Wrapper(const Napi::CallbackInfo& info){ 
    Napi::Env env=info.Env();
    Napi::String returnValue=Napi::String::New(env,func(info[0].ToString(),info[1].ToString()));
    return returnValue;

}

/*This is a register function which returns an exports Napi::object that has all the wrapped functions under different keys.
This function takes in as argument,the env and exports object which it populates and return.*/
Napi::Object InitAll(Napi::Env env, Napi::Object exports){
    exports.Set(
        "hello",Napi::Function::New(env,Wrapper)
    );
    return exports;
}
NODE_API_MODULE(NODE_GYP_MODULE_NAME,InitAll)


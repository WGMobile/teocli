/**
 * File:   teo_exeption.cpp
 * Author: Alexander Ksenofontov <aksenofo@yahoo.ru>
 *
 * Created on August 3, 2016, 12:32 PM
 */

#include "teo_exeption.h"
#include <string.h>

//https://gist.github.com/bellbind/a68620383e0180b3afc6

using namespace Nan;
using namespace v8;

Nan::Persistent<v8::Function> TeoExeption::constructor;

NAN_METHOD(TeoExeption::New) {
    Nan::HandleScope scope;

    if (!info.IsConstructCall()) {
	std::vector<v8::Local<v8::Value>> args(info.Length());
	for (std::size_t i = 0; i < args.size(); ++i) args[i] = info[i];
	auto inst = Nan::NewInstance(info.Callee(), args.size(), args.data());
	if (!inst.IsEmpty()) info.GetReturnValue().Set(inst.ToLocalChecked());
	return;
    }

    auto object = new TeoExeption(*Nan::Utf8String(info[0]), *Nan::Utf8String(info[1]));
    object->Wrap(info.This()); // `Wrap` bind C++ object to JS object.
}

NAN_MODULE_INIT(TeoExeption::Init) {
    Nan::HandleScope scope;
    auto cname = Nan::New("TeoExeption").ToLocalChecked();
    auto ctor = Nan::New<v8::FunctionTemplate>(New);
    auto ctorInst = ctor->InstanceTemplate(); // target for member functions
    ctor->SetClassName(cname); // as `ctor.name` in JS
    ctorInst->SetInternalFieldCount(1); // for ObjectWrap, it should set 1

    constructor.Reset(ctor->GetFunction());

    auto pcall_name(Nan::New("call_name").ToLocalChecked());
    auto ptext(Nan::New("text").ToLocalChecked());

    Nan::SetAccessor(ctorInst, pcall_name, CallNameGet, CallNameSet);
    Nan::SetAccessor(ctorInst, ptext, TextGet, TextSet);

    Nan::Set(target, cname, Nan::GetFunction(ctor).ToLocalChecked());
}

NAN_GETTER(TeoExeption::CallNameGet) {
    Nan::HandleScope scope;
    auto object(Nan::ObjectWrap::Unwrap<TeoExeption>(info.Holder()));
    info.GetReturnValue().Set(Nan::New(object->call_name_).ToLocalChecked());
}

NAN_SETTER(TeoExeption::CallNameSet) {
    Nan::HandleScope scope;
    auto object(Nan::ObjectWrap::Unwrap<TeoExeption>(info.Holder()));
    object->call_name_ = *Nan::Utf8String(Nan::To<v8::String>(value).ToLocalChecked());
}

NAN_GETTER(TeoExeption::TextGet) {
    Nan::HandleScope scope;
    auto object(Nan::ObjectWrap::Unwrap<TeoExeption>(info.Holder()));
    info.GetReturnValue().Set(Nan::New(object->text_).ToLocalChecked());
}

NAN_SETTER(TeoExeption::TextSet) {
    Nan::HandleScope scope;
    auto object(Nan::ObjectWrap::Unwrap<TeoExeption>(info.Holder()));
    object->text_ = *Nan::Utf8String(Nan::To<v8::String>(value).ToLocalChecked());
}

Local<Value> TeoExeption::createNewInstance(const std::string& call_name, const std::string& text) {
    const int argc (2);
    v8::Local<v8::Value> argv[argc] = {
	Nan::New<String>(call_name).ToLocalChecked(),
	Nan::New<String>(text).ToLocalChecked()
    };
    return Nan::New<v8::Function>(constructor)->NewInstance(argc, argv);
}

/**
 * File:   teo_exeption.h
 * Author: Alexander Ksenofontov <aksenofo@yahoo.ru>
 *
 * Created on August 3, 2016, 12:32 PM
 */

#pragma once


#include <stddef.h>
#include <sys/types.h>
#include "libteol0/teonet_l0_client.h"
#include <string>

#include <nan.h>


class TeoExeption: public Nan::ObjectWrap {

public:

    static NAN_MODULE_INIT(Init);

    static v8::Local<v8::Value> createNewInstance(const std::string& call_name, const std::string& text);

private:

    TeoExeption()
    : call_name_("")
    , text_("")
    {}

    TeoExeption(const std::string& call_name, const std::string& text)
    : call_name_(call_name)
    , text_(text)
    {}


    static NAN_GETTER(CallNameGet);

    static NAN_SETTER(CallNameSet);

    static NAN_GETTER(TextGet);

    static NAN_SETTER(TextSet);

    static NAN_METHOD(New); // constructor

    static Nan::Persistent<v8::Function> constructor;

private:

    std::string call_name_;  	// operation
    std::string text_;       	// readable text

};


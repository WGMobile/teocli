/**
 * File:   errno_exeption.h
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


class TeoErrnoExeption: public Nan::ObjectWrap {

public:

    static NAN_MODULE_INIT(Init);

    static v8::Local<v8::Value> createNewInstance(int errn, const std::string& call_name);

private:

    TeoErrnoExeption()
    : errno_(0)
    , call_name_("")
    , text_("")
    {}

    TeoErrnoExeption(int errn, const std::string& call_name, const std::string& text)
    : errno_(errn)
    , call_name_(call_name)
    , text_(text)
    {}


    static NAN_GETTER(ErrnoGet);

    static NAN_SETTER(ErrnoSet);

    static NAN_GETTER(CallNameGet);

    static NAN_SETTER(CallNameSet);

    static NAN_GETTER(TextGet);

    static NAN_SETTER(TextSet);

    static NAN_METHOD(New); // constructor

    static Nan::Persistent<v8::Function> constructor;

private:

    int errno_;			// rerrno code
    std::string call_name_;  	// operation
    std::string text_;       	// readable text

};


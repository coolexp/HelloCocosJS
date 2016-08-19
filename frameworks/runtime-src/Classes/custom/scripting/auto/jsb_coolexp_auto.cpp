#include "custom/scripting/auto/jsb_coolexp_auto.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "Eray.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}
JSClass  *jsb_ErayUIHelper_class;
JSObject *jsb_ErayUIHelper_prototype;

bool js_coolexp_ErayUIHelper_log(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        cocos2d::Node* arg1 = nullptr;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_coolexp_ErayUIHelper_log : Error processing arguments");
        ErayUIHelper::log(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_coolexp_ErayUIHelper_log : wrong number of arguments");
    return false;
}


void js_register_coolexp_ErayUIHelper(JSContext *cx, JS::HandleObject global) {
    jsb_ErayUIHelper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_ErayUIHelper_class->name = "ErayUIHelper";
    jsb_ErayUIHelper_class->addProperty = JS_PropertyStub;
    jsb_ErayUIHelper_class->delProperty = JS_DeletePropertyStub;
    jsb_ErayUIHelper_class->getProperty = JS_PropertyStub;
    jsb_ErayUIHelper_class->setProperty = JS_StrictPropertyStub;
    jsb_ErayUIHelper_class->enumerate = JS_EnumerateStub;
    jsb_ErayUIHelper_class->resolve = JS_ResolveStub;
    jsb_ErayUIHelper_class->convert = JS_ConvertStub;
    jsb_ErayUIHelper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("log", js_coolexp_ErayUIHelper_log, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_ErayUIHelper_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_ErayUIHelper_class,
        dummy_constructor<ErayUIHelper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_ErayUIHelper_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ErayUIHelper"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<ErayUIHelper>(cx, jsb_ErayUIHelper_class, proto, JS::NullPtr());
}

JSClass  *jsb_ErayLayer_class;
JSObject *jsb_ErayLayer_prototype;

bool js_coolexp_ErayLayer_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ErayLayer* cobj = (ErayLayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_coolexp_ErayLayer_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_coolexp_ErayLayer_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_coolexp_ErayLayer_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ErayLayer* cobj = (ErayLayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_coolexp_ErayLayer_setDelegate : Invalid Native Object");
    if (argc == 1) {
        ErayDelegate* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (ErayDelegate*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_coolexp_ErayLayer_setDelegate : Error processing arguments");
        cobj->setDelegate(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_coolexp_ErayLayer_setDelegate : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_coolexp_ErayLayer_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = ErayLayer::create();
        js_type_class_t *typeClass = js_get_type_from_native<ErayLayer>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "ErayLayer"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_coolexp_ErayLayer_create : wrong number of arguments");
    return false;
}

bool js_coolexp_ErayLayer_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    ErayLayer* cobj = new (std::nothrow) ErayLayer();

    js_type_class_t *typeClass = js_get_type_from_native<ErayLayer>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "ErayLayer"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_coolexp_ErayLayer_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    ErayLayer *nobj = new (std::nothrow) ErayLayer();
    auto newproxy = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &newproxy->obj, nobj, "ErayLayer");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_Layer_prototype;

    
void js_register_coolexp_ErayLayer(JSContext *cx, JS::HandleObject global) {
    jsb_ErayLayer_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_ErayLayer_class->name = "ErayLayer";
    jsb_ErayLayer_class->addProperty = JS_PropertyStub;
    jsb_ErayLayer_class->delProperty = JS_DeletePropertyStub;
    jsb_ErayLayer_class->getProperty = JS_PropertyStub;
    jsb_ErayLayer_class->setProperty = JS_StrictPropertyStub;
    jsb_ErayLayer_class->enumerate = JS_EnumerateStub;
    jsb_ErayLayer_class->resolve = JS_ResolveStub;
    jsb_ErayLayer_class->convert = JS_ConvertStub;
    jsb_ErayLayer_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("init", js_coolexp_ErayLayer_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDelegate", js_coolexp_ErayLayer_setDelegate, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_coolexp_ErayLayer_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_coolexp_ErayLayer_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Layer_prototype);
    jsb_ErayLayer_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_ErayLayer_class,
        js_coolexp_ErayLayer_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_ErayLayer_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ErayLayer"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<ErayLayer>(cx, jsb_ErayLayer_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { .ErayLayer.extend = cc.Class.extend; })()");
}

void register_all_coolexp(JSContext* cx, JS::HandleObject obj) {
    // Get the global ns
    JS::RootedObject ns(cx, ScriptingCore::getInstance()->getGlobalObject());

    js_register_coolexp_ErayUIHelper(cx, ns);
    js_register_coolexp_ErayLayer(cx, ns);
}


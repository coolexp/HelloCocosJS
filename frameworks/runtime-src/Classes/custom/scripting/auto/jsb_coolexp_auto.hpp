#include "base/ccConfig.h"
#ifndef __coolexp_h__
#define __coolexp_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_ErayUIHelper_class;
extern JSObject *jsb_ErayUIHelper_prototype;

bool js_coolexp_ErayUIHelper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_coolexp_ErayUIHelper_finalize(JSContext *cx, JSObject *obj);
void js_register_coolexp_ErayUIHelper(JSContext *cx, JS::HandleObject global);
void register_all_coolexp(JSContext* cx, JS::HandleObject obj);
bool js_coolexp_ErayUIHelper_log(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ErayLayer_class;
extern JSObject *jsb_ErayLayer_prototype;

bool js_coolexp_ErayLayer_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_coolexp_ErayLayer_finalize(JSContext *cx, JSObject *obj);
void js_register_coolexp_ErayLayer(JSContext *cx, JS::HandleObject global);
void register_all_coolexp(JSContext* cx, JS::HandleObject obj);
bool js_coolexp_ErayLayer_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_coolexp_ErayLayer_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_coolexp_ErayLayer_ErayLayer(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __coolexp_h__

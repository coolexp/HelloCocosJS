/*
 * Created by James Chen on 3/11/13.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "custom/scripting/jsb_coolexp_manual.hpp"

#include "custom/scripting/auto/jsb_coolexp_auto.hpp"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/auto/jsb_cocos2dx_auto.hpp"
#include "Eray.h"
using namespace cocos2d;
class JSB_ErayDelegate :public ErayDelegate {
public:
	JSB_ErayDelegate() {

	}
	virtual void onClick(const std::string& value) override {
		JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
		jsval arg = std_string_to_jsval(cx, value);
		JS::RootedValue delegateVal(cx, _JSDelegate);
		ScriptingCore::getInstance()->executeFunctionWithOwner(delegateVal, "onClick", 1, &arg);

		JSContext * context = ScriptingCore::getInstance()->getGlobalContext();
		JS::RootedObject object(context, ScriptingCore::getInstance()->getGlobalObject());
		JS::RootedValue owner(context);
		jsval arg1 = INT_TO_JSVAL(1001);

		JS_GetProperty(context, object, "Config", &owner);
		ScriptingCore::getInstance()->executeFunctionWithOwner(owner, "sendNumber", 1, &arg1);
	}
	void setJSDelegate(JS::HandleValue pJSDelegate)
	{
		_JSDelegate = pJSDelegate;
	}
private:
	JS::Heap<JS::Value> _JSDelegate;
};
static bool jsb_ErayLayer_setJSHandler(JSContext *cx, uint32_t argc, jsval *vp) {
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ErayLayer* cobj = (ErayLayer *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "Invalid Native Object");
	if (argc == 1)
	{
		// save the delegate
		JSB_ErayDelegate* nativeDelegate = new (std::nothrow) JSB_ErayDelegate();
		nativeDelegate->setJSDelegate(args.get(0));
		cobj->setDelegate(nativeDelegate);
		args.rval().setUndefined();
		nativeDelegate->release();
		return true;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

extern JSObject *jsb_ErayLayer_prototype;
void register_all_coolexp_manual(JSContext* cx, JS::HandleObject global)
{
	JS::RootedObject proto(cx, jsb_ErayLayer_prototype);
	JS_DefineFunction(cx, proto, "setJSDelegate", jsb_ErayLayer_setJSHandler, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}

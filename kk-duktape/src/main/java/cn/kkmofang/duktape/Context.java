package cn.kkmofang.duktape;

import android.os.Handler;
import android.renderscript.Script;

import java.lang.ref.WeakReference;
import java.lang.reflect.Array;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import cn.kkmofang.script.IScriptFunction;
import cn.kkmofang.script.IScriptObject;
import cn.kkmofang.script.ScriptContext;

/**
 * Created by zhanghailong on 2018/1/25.
 */

public class Context extends ScriptContext {


    public static final int DUK_TYPE_MIN = 0;
    public static final int DUK_TYPE_NONE = 0;
    public static final int DUK_TYPE_UNDEFINED = 1;
    public static final int DUK_TYPE_NULL = 2;
    public static final int DUK_TYPE_BOOLEAN = 3;
    public static final int DUK_TYPE_NUMBER = 4;
    public static final int DUK_TYPE_STRING = 5;
    public static final int DUK_TYPE_OBJECT = 6;
    public static final int DUK_TYPE_BUFFER = 7;
    public static final int DUK_TYPE_POINTER = 8;
    public static final int DUK_TYPE_LIGHTFUNC = 9;
    public static final int DUK_TYPE_MAX = 9;

    public static final int DUK_EXEC_SUCCESS = 0;
    public static final int DUK_EXEC_ERROR = 1;

    public static final IScriptFunction Getter = new IScriptFunction() {
        @Override
        public int call() {

            Context ctx = (Context) Context.currentContext();

            ctx.pushThis();

            Object object = ctx.toObject(-1);

            ctx.pop();

            if(object != null) {
                int top = ctx.getTop();

                if(top > 0 && ctx.isString(-top)) {
                    String key = ctx.toString(-top);
                    Object v = get(object,key);
                    ctx.pushValue(v);
                    return 1;
                }
            }

            return 0;
        }
    };

    public static final IScriptFunction Setter = new IScriptFunction() {
        @Override
        public int call() {

            Context ctx = (Context) Context.currentContext();

            ctx.pushThis();

            Object object = ctx.toObject(-1);

            ctx.pop();

            if(object != null) {

                int top = ctx.getTop();

                if(top > 1 && ctx.isString(-top) ) {
                    String key = ctx.toString(-top);
                    Object v = ctx.toValue(-top +1);
                    set(object,key,v);
                }
            }

            return 0;
        }
    };

    protected final long _ptr;
    private final boolean _alloced;

    static {
        System.loadLibrary("duktape");
        System.loadLibrary("kk-duktape");
    }

    private final Handler _handler;

    public Context() {
        _ptr = alloc();
        _alloced = true;
        _handler = new Handler();
    }

    protected Context(long ptr) {
        _ptr = ptr;
        _alloced = false;
        _handler = new Handler();
    }

    public void post(final Runnable runnable) {

        final WeakReference<Context> v = new WeakReference<Context>(this);

        _handler.post(new Runnable() {
            @Override
            public void run() {
                Context ctx = v.get();
                if(ctx != null) {
                    ScriptContext.pushContext(ctx);
                    runnable.run();
                    ScriptContext.popContext();
                }

            }
        });
    }

    @Override
    protected void finalize() throws Throwable {
        if(_alloced) {
            dealloc(_ptr);
        }
        super.finalize();
    }

    public long ptr() {
        return _ptr;
    }

    public void push(String value) {
        if(value == null) {
            push_null(_ptr);
        } else {
            push_string(_ptr, value);
        }
    }

    public void push(int value) {
        push_int(_ptr,value);
    }

    public void push(double value) {
        push_number(_ptr,value);
    }

    public void push(boolean value) {
        push_boolean(_ptr,value);
    }

    public void pushNull() {
        push_null(_ptr);
    }

    public void pushUndefined() {
        push_undefined(_ptr);
    }

    public void pushHeapptr(long heapptr) {
        if(heapptr == 0xffffffffffffffffl) {
            System.out.println();
        }
        push_heapptr(_ptr,heapptr);
    }

    public void pushEnum(int idx) {
        push_enum(_ptr,idx);
    }

    public int getTop() {
        return get_top(_ptr);
    }

    public void pop(int n) {
        pop(_ptr,n);
    }

    public void pop(){
        pop(_ptr,1);
    }

    public int pcall(int n ) {
        return pcall(_ptr,n);
    }

    public int pcallMethod(int n) {
        return pcall_method(_ptr,n);
    }

    public int getType(int idx) {
        return get_type(_ptr,idx);
    }

    public void eval(String string) {
        eval(_ptr,string);
    }

    public void compile(String string,String name) {
        compile(_ptr,string,name);
    }

    public void pushGlobalObject() {
        push_global_object(_ptr);
    }

    public void gc() {
        gc(_ptr);
    }

    public String toString(int idx) {
        return to_string(_ptr,idx);
    }

    public boolean toBoolean(int idx) {
        return to_boolean(_ptr,idx);
    }

    public int toInt(int idx) {
        return to_int(_ptr,idx);
    }

    public double toNumber(int idx) {
        return to_number(_ptr,idx);
    }

    public long getHeapptr(int idx) {
        return get_heapptr(_ptr,idx);
    }

    public void dup(int idx) {
        dup(_ptr,idx);
    }

    public boolean next(int idx, boolean hasValue) {
        return next(_ptr,idx,hasValue);
    }

    public void pushThis() {
        push_this(_ptr);
    }

    public void getProp(int idx) {
        get_prop(_ptr,idx);
    }

    public void putProp(int idx) {
        put_prop(_ptr,idx);
    }

    public void delProp(int idx) {
        del_prop(_ptr,idx);
    }

    public void defProp(int idx,IScriptFunction getter, IScriptFunction setter) {
        def_prop(_ptr,idx,getter,setter);
    }

    public void pushCurrFunction() {
        push_curr_func(_ptr);
    }

    public void pushFunction(IScriptFunction func) {
        push_Function(_ptr, func);
    }

    public void pushObject() {
        push_object(_ptr);
    }

    public void pushObject(Object object) {

        if(object == null) {
            push_null(_ptr);
        } else if(object instanceof Heapptr) {
            push_heapptr(_ptr,((Heapptr) object).heapptr());
        } else if(object instanceof IScriptFunction) {
            push_Function(_ptr,(IScriptFunction) object);
        } else if(object instanceof IScriptObject) {
            push_Object(_ptr,object);
            for(String key : ((IScriptObject) object).keys()) {
                push_string(_ptr,key);
                def_prop(_ptr,-2,Getter,Setter);
            }
        } else if(object instanceof Map) {
            push_Object(_ptr, object);
            Map<String, Object> m = (Map<String, Object>) object;
            for (String key : m.keySet()) {
                push_string(_ptr, key);
                def_prop(_ptr, -2, Getter, Setter);
            }
        } else {
            push_Object(_ptr,object);
        }
    }

    public void push(byte[] bytes) {
        push_bytes(_ptr,bytes);
    }

    public void pushValue(Object value) {
        if(value == null) {
            push_undefined(_ptr);
        } else if(value instanceof Integer || value instanceof Short ) {
            push_int(_ptr,((Number) value).intValue());
        } else if(value instanceof Double || value instanceof Float) {
            push_number(_ptr,((Number) value).doubleValue());
        } else if(value instanceof Long) {
            push_string(_ptr, value.toString());
        } else if(value instanceof String) {
            push_string(_ptr,(String) value);
        } else if(value instanceof Boolean) {
            push_boolean(_ptr, (boolean) value);
        } else if(value instanceof byte[]) {
            push_bytes(_ptr,(byte[]) value);
        } else if(value instanceof Iterable) {
            push_array(_ptr);
            int i = 0;
            for (Object v : (Iterable) value) {
                push_int(_ptr, i);
                pushValue(v);
                put_prop(_ptr, -3);
                i++;
            }
        } else if(value.getClass().isArray()){
            push_array(_ptr);
            int n = Array.getLength(value);
            for(int i=0;i<n;i++) {
                Object v = Array.get(value,i);
                push_int(_ptr,i);
                pushValue(v);
                put_prop(_ptr,-3);
            }
        } else {
            pushObject(value);
        }
    }

    public Object toValue(int idx) {
        int type = get_type(_ptr,idx);
        switch(type) {
            case DUK_TYPE_BOOLEAN:
                return to_boolean(_ptr,idx);
            case DUK_TYPE_NUMBER: {
                double v = to_number(_ptr, idx);
                if ((double) (int) v == v) {
                    return (int) v;
                }
                return v;
            }
            case DUK_TYPE_STRING:
                return to_string(_ptr,idx);
            case DUK_TYPE_BUFFER:
                return to_bytes(_ptr,idx);
            case DUK_TYPE_LIGHTFUNC:
            case DUK_TYPE_OBJECT:
                if(is_array(_ptr,idx)) {
                    {
                        List<Object> vs = new LinkedList<>();
                        int n = get_length(_ptr, idx);
                        for (int i = 0; i < n; i++) {
                            push_int(_ptr, i);
                            get_prop(_ptr, -2);
                            Object v = toValue(-1);
                            pop(_ptr, 1);
                            if (v != null) {
                                vs.add(v);
                            }
                        }
                        return vs;
                    }
                } else {
                    {
                        Object v = to_Object(_ptr, idx);
                        if (v == null) {
                            Map<String,Object> m = new TreeMap<String,Object>();

                            push_enum(_ptr,idx);

                            while(next(_ptr,-1,true)) {

                                String key = to_string(_ptr,-2);
                                Object vv = toValue(-1);

                                if(vv != null && key != null) {
                                    m.put(key,vv);
                                }
                                pop(_ptr,2);
                            }

                            pop(_ptr,1);

                            return m;
                        }
                        return v;
                    }
                }
        }
        return null;
    }

    public Object toObject(int idx) {
        return to_Object(_ptr,idx);
    }

    public byte[] toBytes(int idx) {
        return to_bytes(_ptr,idx);
    }

    public boolean isString(int idx) {
        return is_string(_ptr,idx);
    }

    public boolean isNumber(int idx) {
        return is_number(_ptr,idx);
    }

    public boolean isBoolean(int idx) {
        return is_boolean(_ptr,idx);
    }

    public boolean isObject(int idx) {
        return is_object(_ptr,idx);
    }

    public boolean isFunction(int idx) {
        return is_function(_ptr,idx);
    }

    public boolean isArray(int idx) {
        return is_array(_ptr,idx);
    }

    public boolean isBytes(int idx) {
        return is_bytes(_ptr,idx);
    }

    public int getLength(int idx) {
        return get_length(_ptr,idx);
    }

    public String getErrorString(int idx) {

        return get_error_string(_ptr,idx);
    }

    private native static final long alloc();
    private native static final void dealloc(long ptr);
    private final static native void push_object(long ptr);
    private final static native void push_array(long ptr);
    private final static native void push_string(long ptr,String value);
    private final static native void push_int(long ptr, int value);
    private final static native void push_boolean(long ptr, boolean value);
    private final static native void push_number(long ptr, double value);
    private final static native void push_null(long ptr);
    private final static native void push_undefined(long ptr);
    private final static native void push_heapptr(long ptr, long heapptr);
    private final static native void push_enum(long ptr, int idx);
    private final static native void push_bytes(long ptr, byte[] bytes);
    private final static native int get_top(long ptr);
    private final static native void pop(long ptr, int count);
    private final static native int pcall(long ptr, int n);
    private final static native int pcall_method(long ptr, int n);
    private final static native int get_type(long ptr,int idx);
    private final static native void eval(long ptr, String string);
    private final static native void compile(long ptr, String string,String name);
    private final static native void push_Object(long ptr, Object object);
    private final static native void push_global_object(long ptr);
    private final static native void push_Function(long ptr, IScriptFunction func);
    private final static native void gc(long ptr);
    private final static native String to_string(long ptr,int idx);
    private final static native int to_int(long ptr, int idx);
    private final static native boolean to_boolean(long ptr, int idx);
    private final static native double to_number(long ptr, int idx);
    private final static native Object to_Object(long ptr, int idx);
    private final static native byte[] to_bytes(long ptr,int idx);
    private final static native long get_heapptr(long ptr, int idx);
    private final static native void dup(long ptr, int idx);
    private final static native boolean next(long ptr, int idx, boolean hasValue);
    private final static native void push_this(long ptr);
    private final static native void push_curr_func(long ptr);
    private final static native void get_prop(long ptr,int idx);
    private final static native void put_prop(long ptr,int idx);
    private final static native void del_prop(long ptr,int idx);
    private final static native void def_prop(long ptr,int idx,IScriptFunction getter, IScriptFunction setter);
    private final static native boolean is_array(long ptr,int idx);
    private final static native int get_length(long ptr,int idx);
    private final static native boolean is_string(long ptr,int idx);
    private final static native boolean is_number(long ptr,int idx);
    private final static native boolean is_boolean(long ptr,int idx);
    private final static native boolean is_object(long ptr,int idx);
    private final static native boolean is_function(long ptr,int idx);
    private final static native boolean is_bytes(long ptr, int idx);
    private final static native String get_error_string(long ptr,int idx);
    private final static native void set_prototype(long ptr,int idx);
}

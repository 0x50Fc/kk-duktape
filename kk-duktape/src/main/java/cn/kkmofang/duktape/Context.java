package cn.kkmofang.duktape;

import android.os.Handler;
import android.renderscript.Script;

import java.lang.ref.WeakReference;
import java.lang.reflect.Array;
import java.nio.charset.Charset;
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

public class Context extends BasicContext {

    private final Handler _handler;

    public Context() {
        super(alloc());
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
        dealloc(_ptr);
        super.finalize();
    }

    private native static final long alloc();
    private native static final void dealloc(long ptr);
}

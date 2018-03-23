package cn.kkmofang.duktape;

import java.lang.ref.WeakReference;

import cn.kkmofang.script.IScriptObject;
import cn.kkmofang.script.ScriptContext;

/**
 * Created by hailong11 on 2018/3/13.
 */

public class Heapptr  {

    private final WeakReference<Context> _context;
    private final long _heapptr;
    private final String _key;

    public Heapptr(Context context,long heapptr) {
        _context = new WeakReference<Context>(context);
        _heapptr = heapptr;
        _key = "0x" + Long.toHexString(heapptr);

        context.pushGlobalObject();
        context.push(_key);
        context.pushHeapptr(heapptr);
        context.putProp(-3);
        context.pop();
    }

    @Override
    protected void finalize() throws Throwable {

        Context ctx = _context.get();

        if(ctx != null) {

            final String key = _key;

            ctx.post(new Runnable() {
                @Override
                public void run() {
                    Context ctx = (Context) ScriptContext.currentContext();
                    ctx.pushGlobalObject();
                    ctx.push(_key);
                    ctx.delProp(-2);
                    ctx.pop();
                }
            });

        }

        super.finalize();
    }

    public Context context() {
        return _context.get();
    }

    public long heapptr() {
        return _heapptr;
    }

}

package cn.kkmofang.duktape;

import java.lang.ref.WeakReference;
import cn.kkmofang.script.ScriptContext;

/**
 * Created by zhanghailong on 2018/3/13.
 */

public class Heapptr  {

    private final WeakReference<BasicContext> _context;
    private final long _heapptr;
    private final String _key;

    public Heapptr(BasicContext context,long heapptr) {
        _context = new WeakReference<>(context);
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

        BasicContext ctx = _context.get();

        if(ctx != null) {

            final String key = _key;

            ctx.post(new Runnable() {
                @Override
                public void run() {
                    BasicContext ctx = (Context) ScriptContext.currentContext();
                    ctx.pushGlobalObject();
                    ctx.push(_key);
                    ctx.delProp(-2);
                    ctx.pop();
                }
            });

        }

        super.finalize();
    }

    public BasicContext context() {
        return _context.get();
    }

    public long heapptr() {
        return _heapptr;
    }

}

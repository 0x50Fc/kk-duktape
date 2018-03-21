#include <jni.h>
#include "kk.h"
#include "duktape/src/duktape.h"

static void Java_cn_kkmofang_duktape_Context_fail_func (void *udata, const char *msg);
static duk_ret_t Java_cn_kkmofang_duktape_Context_print_func(duk_context * ctx);

JNIEXPORT jlong JNICALL
Java_cn_kkmofang_duktape_Context_alloc(JNIEnv *env, jclass type) {

    duk_context * ctx = duk_create_heap(NULL, NULL, NULL, NULL, Java_cn_kkmofang_duktape_Context_fail_func);

    duk_push_global_object(ctx);

    duk_push_c_function(ctx,Java_cn_kkmofang_duktape_Context_print_func,DUK_VARARGS);
    duk_put_prop_string(ctx,-2,"print");

    duk_push_object(ctx);

    duk_pop(ctx);

    return (jlong) (long) ctx;
}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_dealloc(JNIEnv *env, jclass type, jlong ptr) {
    duk_context * ctx = (duk_context *) (long) ptr;
    duk_destroy_heap(ctx);
}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1object(JNIEnv *env, jclass type, jlong ptr) {
    duk_context * ctx = (duk_context *) (long) ptr;
    duk_push_object(ctx);
}


JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1array(JNIEnv *env, jclass type, jlong ptr) {

    duk_context * ctx = (duk_context *) (long) ptr;
    duk_push_array(ctx);

}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1string(JNIEnv *env, jclass type, jlong ptr, jstring value_) {
    const char *value = (*env)->GetStringUTFChars(env, value_, 0);

    duk_context * ctx = (duk_context *) (long) ptr;
    duk_push_string(ctx,value);

    (*env)->ReleaseStringUTFChars(env, value_, value);
}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1int(JNIEnv *env, jclass type, jlong ptr, jint value) {

    duk_context * ctx = (duk_context *) (long) ptr;
    duk_push_int(ctx,value);

}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1boolean(JNIEnv *env, jclass type, jlong ptr,
                                               jboolean value) {

    duk_context * ctx = (duk_context *) (long) ptr;
    duk_push_boolean(ctx,value);

}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1number(JNIEnv *env, jclass type, jlong ptr, jdouble value) {

    duk_context * ctx = (duk_context *) (long) ptr;
    duk_push_number(ctx,value);

}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1null(JNIEnv *env, jclass type, jlong ptr) {
    duk_context * ctx = (duk_context *) (long) ptr;
    duk_push_null(ctx);
}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1undefined(JNIEnv *env, jclass type, jlong ptr) {

    duk_context * ctx = (duk_context *) (long) ptr;
    duk_push_undefined(ctx);

}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1heapptr(JNIEnv *env, jclass type, jlong ptr, jlong heapptr) {

    duk_context * ctx = (duk_context *) (long) ptr;
    duk_push_heapptr(ctx,(void *)(long) heapptr);

}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1enum(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;
    duk_enum(ctx,idx,DUK_ENUM_INCLUDE_SYMBOLS);

}

JNIEXPORT jint JNICALL
Java_cn_kkmofang_duktape_Context_get_1top(JNIEnv *env, jclass type, jlong ptr) {

    duk_context * ctx = (duk_context *) (long) ptr;
    return duk_get_top(ctx);

}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_pop(JNIEnv *env, jclass type, jlong ptr, jint count) {

    duk_context * ctx = (duk_context *) (long) ptr;

    duk_pop_n(ctx,count);

}

JNIEXPORT jint JNICALL
Java_cn_kkmofang_duktape_Context_pcall(JNIEnv *env, jclass type, jlong ptr, jint n) {

    duk_context * ctx = (duk_context *) (long) ptr;
    duk_pcall(ctx,n);

}

JNIEXPORT jint JNICALL
Java_cn_kkmofang_duktape_Context_pcall_1method(JNIEnv *env, jclass type, jlong ptr, jint n) {

    duk_context * ctx = (duk_context *) (long) ptr;
    duk_pcall_method(ctx,n);

}

JNIEXPORT jint JNICALL
Java_cn_kkmofang_duktape_Context_get_1type(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;
    return duk_get_type(ctx,idx);

}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_eval(JNIEnv *env, jclass type, jlong ptr, jstring string_) {
    const char *string = (*env)->GetStringUTFChars(env, string_, 0);

    duk_context * ctx = (duk_context *) (long) ptr;

    duk_eval_string(ctx,string);

    (*env)->ReleaseStringUTFChars(env, string_, string);
}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1global_1object(JNIEnv *env, jclass type, jlong ptr) {

    duk_context * ctx = (duk_context *) (long) ptr;

    duk_push_global_object(ctx);

}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_gc(JNIEnv *env, jclass type, jlong ptr) {

    duk_context * ctx = (duk_context *) (long) ptr;
    duk_gc(ctx,DUK_GC_COMPACT);
}

JNIEXPORT jstring JNICALL
Java_cn_kkmofang_duktape_Context_to_1string(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;

    const char * v = duk_to_string(ctx,idx);

    return (*env)->NewStringUTF(env, v);
}

JNIEXPORT jint JNICALL
Java_cn_kkmofang_duktape_Context_to_1int(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;

    return duk_to_int(ctx,idx);

}

JNIEXPORT jboolean JNICALL
Java_cn_kkmofang_duktape_Context_to_1boolean(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;

    return duk_to_boolean(ctx,idx);

}

JNIEXPORT jdouble JNICALL
Java_cn_kkmofang_duktape_Context_to_1number(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;

    return duk_to_number(ctx,idx);

}

JNIEXPORT jlong JNICALL
Java_cn_kkmofang_duktape_Context_get_1heapptr(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;

    return (jlong) (long) duk_get_heapptr(ctx,idx);

}

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_dup(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;

    duk_dup(ctx,idx);

}

JNIEXPORT jboolean JNICALL
Java_cn_kkmofang_duktape_Context_next(JNIEnv *env, jclass type, jlong ptr, jint idx,
                                      jboolean hasValue) {

    duk_context * ctx = (duk_context *) (long) ptr;

    return duk_next(ctx,idx,hasValue) != 0;

}

static duk_ret_t Java_cn_kkmofang_duktape_Context_Object_dealloc_func(duk_context * ctx);

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1Object(JNIEnv *env, jclass type, jlong ptr, jobject object) {

    duk_context * ctx = (duk_context *) (long) ptr;

    if(object == NULL) {
        duk_push_null(ctx);
    } else {
        duk_push_object(ctx);
        duk_push_pointer(ctx, (*env)->NewGlobalRef(env,object));
        duk_put_prop_string(ctx,-2,"__object");
        duk_push_c_function(ctx,Java_cn_kkmofang_duktape_Context_Object_dealloc_func,1);
        duk_set_finalizer(ctx,-2);
    }

}

static duk_ret_t Java_cn_kkmofang_duktape_Context_Function_func(duk_context * ctx);

JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1Function(JNIEnv *env, jclass type, jlong ptr, jobject func) {

    duk_context * ctx = (duk_context *) (long) ptr;

    if(func == NULL) {
        duk_push_null(ctx);
    } else {
        duk_push_c_function(ctx,Java_cn_kkmofang_duktape_Context_Function_func,DUK_VARARGS);
        duk_push_pointer(ctx, (*env)->NewGlobalRef(env,func));
        duk_put_prop_string(ctx,-2,"__object");
        duk_push_c_function(ctx,Java_cn_kkmofang_duktape_Context_Object_dealloc_func,1);
        duk_set_finalizer(ctx,-2);
    }

}

JNIEXPORT jobject JNICALL
Java_cn_kkmofang_duktape_Context_to_1Object(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;

    jobject v = NULL;

    if(duk_is_object(ctx, idx)) {
        duk_get_prop_string(ctx,idx,"__object");
        if(duk_is_pointer(ctx,-1)) {
            v = (*env)->NewLocalRef(env,(jobject) duk_to_pointer(ctx,-1));
        }
        duk_pop(ctx);
    }

    return v;
}


JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1this(JNIEnv *env, jclass type, jlong ptr) {

    duk_context * ctx = (duk_context *) (long) ptr;

    duk_push_this(ctx);

}


JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_get_1prop(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;
    duk_get_prop(ctx,idx);

}


JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_put_1prop(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;

    duk_put_prop(ctx,idx);

}


JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_del_1prop(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;

    duk_del_prop(ctx,idx);

}


JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_def_1prop(JNIEnv *env, jclass type, jlong ptr, jint idx,
                                           jobject getter, jobject setter) {

    duk_context * ctx = (duk_context *) (long) ptr;

    duk_uint_t flags = DUK_DEFPROP_HAVE_GETTER;

    Java_cn_kkmofang_duktape_Context_push_1Function(env,type,ptr,getter);

    idx --;

    if(setter) {
        Java_cn_kkmofang_duktape_Context_push_1Function(env,type,ptr,setter);
        idx --;
        flags = flags | DUK_DEFPROP_HAVE_SETTER;
    }

    duk_def_prop(ctx,idx,flags);

}


JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_push_1curr_1func(JNIEnv *env, jclass type, jlong ptr) {

    duk_context * ctx = (duk_context *) (long) ptr;

    duk_push_current_function(ctx);

}


JNIEXPORT jboolean JNICALL
Java_cn_kkmofang_duktape_Context_is_1array(JNIEnv *env, jclass type, jlong ptr, jint idx) {
    duk_context * ctx = (duk_context *) (long) ptr;
    return duk_is_array(ctx,idx);
}


JNIEXPORT jint JNICALL
Java_cn_kkmofang_duktape_Context_get_1length(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;
    return duk_get_length(ctx,idx);
}



JNIEXPORT jboolean JNICALL
Java_cn_kkmofang_duktape_Context_is_1string(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;
    return duk_is_string(ctx,idx);

}

JNIEXPORT jboolean JNICALL
Java_cn_kkmofang_duktape_Context_is_1number(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;
    return duk_is_number(ctx,idx);

}

JNIEXPORT jboolean JNICALL
Java_cn_kkmofang_duktape_Context_is_1boolean(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;
    return duk_is_boolean(ctx,idx);

}

JNIEXPORT jboolean JNICALL
Java_cn_kkmofang_duktape_Context_is_1object(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;
    return duk_is_object(ctx,idx);

}

JNIEXPORT jboolean JNICALL
Java_cn_kkmofang_duktape_Context_is_1function(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;
    return duk_is_function(ctx,idx);

}


JNIEXPORT jstring JNICALL
Java_cn_kkmofang_duktape_Context_get_1error_1string(JNIEnv *env, jclass type, jlong ptr, jint idx) {

    duk_context * ctx = (duk_context *) (long) ptr;
    jstring v = NULL;

    if(duk_is_error(ctx, idx)) {
        duk_get_prop_string(ctx, idx, "lineNumber");
        int lineNumber = duk_to_int(ctx, -1);
        duk_pop(ctx);
        duk_get_prop_string(ctx, idx, "stack");
        const char * error = duk_to_string(ctx, -1);
        duk_pop(ctx);
        duk_get_prop_string(ctx, idx, "fileName");
        const char * fileName = duk_to_string(ctx, -1);
        duk_pop(ctx);
        duk_push_sprintf(ctx,"%s(%d): %s",fileName,lineNumber,error);
        v = (*env)->NewStringUTF(env, duk_to_string(ctx,-1));
        duk_pop(ctx);
    } else {
        v = (*env)->NewStringUTF(env, duk_to_string(ctx,idx));
    }

    return v;
}


JNIEXPORT void JNICALL
Java_cn_kkmofang_duktape_Context_set_1prototype(JNIEnv *env, jclass type, jlong ptr, jint idx) {
    duk_context * ctx = (duk_context *) (long) ptr;
    duk_set_prototype(ctx,idx);
}

// internal

static void Java_cn_kkmofang_duktape_Context_fail_func (void *udata, const char *msg) {
    kk_log("%s",msg);
}

static duk_ret_t Java_cn_kkmofang_duktape_Context_print_func(duk_context * ctx) {

    int top = duk_get_top(ctx);

    for(int i=0;i<top;i++) {

        if(duk_is_string(ctx, - top + i)) {
            kk_log("%s",duk_to_string(ctx, - top + i));
        } else if(duk_is_number(ctx, - top + i)) {
            kk_log("%g",duk_to_number(ctx, - top + i));
        } else if(duk_is_boolean(ctx, - top + i)) {
            kk_log("%s",duk_to_boolean(ctx, - top + i) ? "true":"false");
        } else if(duk_is_buffer_data(ctx, - top + i)) {
            kk_log("[bytes]:");
            {
                size_t n;
                unsigned char * bytes = (unsigned char *) duk_get_buffer_data(ctx, - top + i, &n);
                while(n >0) {
                    printf("%u",*bytes);
                    bytes ++;
                    n --;
                    if(n != 0) {
                        printf(",");
                    }
                }
                printf("\n");
            }
        } else if(duk_is_function(ctx, - top + i)) {
            kk_log("[function]");
        } else if(duk_is_array(ctx, - top + i)) {
            kk_log("[array]");
        } else if(duk_is_object(ctx, - top + i)) {
            kk_log("[object]");
        } else if(duk_is_undefined(ctx, - top + i)) {
            kk_log("[undefined]");
        } else if(duk_is_null(ctx, - top + i)) {
            kk_log("[null]");
        }

    }

    return 0;
}

static duk_ret_t Java_cn_kkmofang_duktape_Context_Object_dealloc_func(duk_context * ctx) {

    duk_get_prop_string(ctx,-1,"__object");

    if(duk_is_pointer(ctx,-1)) {

        jobject v = (jobject) duk_to_pointer(ctx,-1);

        if(v) {
            jboolean isAttach = 0;
            JNIEnv * env = kk_env(&isAttach);

            (*env)->DeleteGlobalRef(env,v);

            if(isAttach) {
                (*gJavaVm)->DetachCurrentThread(env);
            }
        }
    }

    duk_pop(ctx);

    return 0;
}

static duk_ret_t Java_cn_kkmofang_duktape_Context_Function_func(duk_context * ctx) {

    duk_ret_t ret = 0;
    jobject v = NULL;

    duk_push_current_function(ctx);

    duk_get_prop_string(ctx,-1,"__object");

    if(duk_is_pointer(ctx,-1)) {

        v = (jobject) duk_to_pointer(ctx,-1);

    }

    duk_pop_2(ctx);

    if(v) {

        jboolean isAttach = 0;
        JNIEnv * env = kk_env(&isAttach);

        jclass func = (*env)->FindClass(env,"cn/kkmofang/script/IScriptFunction");

        if(func) {

            jmethodID call = (*env)->GetMethodID(env,func,"call","()I");

            if(call) {
                ret = (*env)->CallIntMethod(env,v,call);
            }

        }

        if(isAttach) {
            (*gJavaVm)->DetachCurrentThread(env);
        }
    }

    return ret;
}

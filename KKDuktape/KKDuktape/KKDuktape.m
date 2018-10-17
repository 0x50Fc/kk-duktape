//
//  KKDuktape.m
//  KKDuktape
//
//  Created by zhanghailong on 2018/9/28.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KKDuktape.h"

void duk_push_NSObject(duk_context * ctx, id object) {
    
    if(object == nil) {
        duk_push_undefined(ctx);
        return;
    }
    
    if([object isKindOfClass:[NSString class]]) {
        duk_push_string(ctx, [object UTF8String]);
        return;
    }
    
    if([object isKindOfClass:[NSNumber class]]) {
        if(strcmp( [object objCType],@encode(BOOL)) == 0) {
            duk_push_boolean(ctx, [object boolValue]);
        } else {
            duk_push_number(ctx, [object doubleValue]);
        }
        return ;
    }
    
    if([object isKindOfClass:[NSValue class]]) {
        duk_push_string(ctx, [[object description] UTF8String]);
        return;
    }
    
    if([object isKindOfClass:[NSArray class]]) {
        duk_push_array(ctx);
        duk_uarridx_t i = 0;
        for(id v in object) {
            duk_push_NSObject(ctx, v);
            duk_put_prop_index(ctx, -2, i);
            i++;
        }
        return;
    }
    
    if([object isKindOfClass:[NSDictionary class]]) {
        duk_push_object(ctx);
        NSEnumerator * keyEnum = [object keyEnumerator];
        id key;
        while((key = [keyEnum nextObject])) {
            id v = [object objectForKey:key];
            duk_push_string(ctx, [key UTF8String]);
            duk_push_NSObject(ctx, v);
            duk_put_prop(ctx, -3);
        }
        return;
    }
    
    duk_push_undefined(ctx);
    return;
    
}

id duk_to_NSObject(duk_context * ctx,duk_idx_t idx) {
    
    duk_int_t type = duk_get_type(ctx, idx);
    
    switch (type) {
        case DUK_TYPE_STRING:
            return [NSString stringWithCString:duk_to_string(ctx, idx) encoding:NSUTF8StringEncoding];
        case DUK_TYPE_NUMBER:
            return [NSNumber numberWithDouble:duk_to_number(ctx, idx)];
        case DUK_TYPE_BOOLEAN:
            return [NSNumber numberWithBool:duk_to_boolean(ctx, idx)];
        case DUK_TYPE_OBJECT:
            if(duk_is_array(ctx, idx)) {
                NSMutableArray * vs = [NSMutableArray arrayWithCapacity:4];
                duk_enum(ctx, idx, DUK_ENUM_ARRAY_INDICES_ONLY);
                while(duk_next(ctx, -1, 1)) {
                    id v = duk_to_NSObject(ctx, -1);
                    if(v) {
                        [vs addObject:v];
                    }
                    duk_pop_2(ctx);
                }
                duk_pop(ctx);
                return vs;
            } else {
                NSMutableDictionary * data = [NSMutableDictionary dictionaryWithCapacity:4];
                duk_enum(ctx, idx, DUK_ENUM_INCLUDE_SYMBOLS);
                while(duk_next(ctx, -1, 1)) {
                    id key = duk_to_NSObject(ctx, -2);
                    id v = duk_to_NSObject(ctx, -1);
                    if(key && v) {
                        [data setObject:v forKey:key];
                    }
                    duk_pop_2(ctx);
                }
                duk_pop(ctx);
                return data;
            }
        case DUK_TYPE_BUFFER:
            if(duk_is_buffer_data(ctx, idx)) {
                duk_size_t size = 0;
                void * bytes = duk_get_buffer_data(ctx, idx, &size);
                return [NSData dataWithBytes:bytes length:size];
            } else {
                duk_size_t size = 0;
                void * bytes = duk_get_buffer(ctx, idx, &size);
                return [NSData dataWithBytes:bytes length:size];
            }
        default:
            return nil;
    }
    
}
                   

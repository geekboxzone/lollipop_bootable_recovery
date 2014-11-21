/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef RECOVERY_COMMON_H
#define RECOVERY_COMMON_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// #define LOGE(...) ui_print("E:" __VA_ARGS__)

#define LOGE(fmt, args...)\
{\
    ui_print("E:" fmt, ## args);\
    fprintf(stdout, "E/ [File] : %s; [Line] : %d; [Func] : %s; " fmt, __FILE__, __LINE__, __FUNCTION__, ## args);\
}
#define E(fmt, args...)     LOGE(fmt "\n", ## args)

// #define LOGW(...) fprintf(stdout, "W:" __VA_ARGS__)
#define LOGW(fmt, args...)\
    { fprintf(stdout, "W/ [File] : %s; [Line] : %d; [Func] : %s; " fmt, __FILE__, __LINE__, __FUNCTION__, ## args); }
#define W(fmt, args...)     LOGW(fmt "\n", ## args)

// #define LOGI(...) fprintf(stdout, "I:" __VA_ARGS__)
#define LOGI(fmt, args...)\
{ \
    fprintf(stdout, "I/ [File] : %s; [Line] : %d; [Func] : %s; " fmt, __FILE__, __LINE__, __FUNCTION__, ## args); \
}
#define I(fmt, args...)     LOGI(fmt "\n", ## args)


#define ENABLE_DEBUG_LOG
#ifdef ENABLE_DEBUG_LOG
// #define LOGD(...) fprintf(stdout, "D:" __VA_ARGS__)
#define LOGD(fmt, args...)\
    { fprintf(stdout, "D/ [File] : %s; [Line] : %d; [Func] : %s; " fmt, __FILE__, __LINE__, __FUNCTION__, ## args); }
#ifdef D
#undef D
#endif
#define D(fmt, args...)     LOGD(fmt "\n", ## args)
#else
#define LOGD(...) do {} while (0)
#endif


#define ENABLE_VERBOSE_LOG
#ifdef ENABLE_VERBOSE_LOG
// #define LOGV(...) fprintf(stdout, "V:" __VA_ARGS__)
#define LOGV(fmt, args...)\
    { fprintf(stdout, "V/ [File] : %s; [Line] : %d; [Func] : %s; " fmt, __FILE__, __LINE__, __FUNCTION__, ## args); }
#define V(fmt, args...)     LOGV(fmt "\n", ## args)
#else
#define LOGV(...) do {} while (0)
#endif

/**
 * ���ú���, ����鷵��ֵ, ���ݷ���ֵ�����Ƿ���ת��ָ���Ĵ��������. 
 * @param functionCall
 *          ���ض������ĵ���, �ú����ķ���ֵ������ ���� �ɹ� or err �� ������. 
 *          ����, �����ú��� "����" �Ǳ�����Ϊ "���� 0 ��ʾ�����ɹ�". 
 * @param result
 *		    ���ڼ�¼�������ص� error code �� ���ͱ���, ͨ���� "ret" or "result" ��.
 * @param label
 *		    ���������ش���, ����Ҫ��ת���� �������� ���, ͨ������ "EXIT". 
 */
#define CHECK_FUNC_CALL(functionCall, result, label) \
{\
	if ( 0 != ( (result) = (functionCall) ) )\
	{\
		E("Function call returned error : " #result " = %d.", result);\
		goto label;\
	}\
}

/**
 * ���ض�������, �ж� error ����, �Ա��� 'retVar' ���� 'errCode', 
 * Log �����Ӧ�� Error Caution, Ȼ����ת 'label' ָ���Ĵ��봦ִ��. 
 * @param msg
 *          ���ִ���ʽ����ʾ��Ϣ. 
 * @param retVar
 *		    ��ʶ����ִ��״̬���߽���ı���, �������þ���� Error Code. 
 *		    ͨ���� 'ret' or 'result'. 
 * @param errCode
 *          �����ض� error �ĳ�����ʶ, ͨ���� �����̬. 
 * @param label
 *          ����Ҫ��ת���Ĵ��������ı��, ͨ������ 'EXIT'. 
 * @param args...
 *          ��Ӧ 'msgFmt' ʵ���� '%s', '%d', ... �� ת��˵���� �ľ���ɱ䳤ʵ��. 
 */
#define SET_ERROR_AND_JUMP(msgFmt, retVar, errCode, label, args...) \
{\
    E("To set '" #retVar "' to %d('" #errCode "') : " msgFmt, (errCode), ## args);\
	(retVar) = (errCode);\
	goto label;\
}

/**
 * ����ָ�������е�Ԫ�ظ���. 
 * @param array
 *      ��Ч������ʵ����ʶ��. 
 */
#define ELEMENT_NUM(array)      ( sizeof(array) /  sizeof(array[0]) )

/*-------------------------------------------------------*/

/** ʹ�� D(), ��ʮ���Ƶ���ʽ��ӡ���� 'var' �� value. */
#define D_DEC(var) \
{ \
    long long num = (var); \
    D(#var " = %lld.", num); \
}

/** ʹ�� D(), ��ʮ�����Ƶ���ʽ��ӡ���� 'var' �� value. */
#define D_HEX(var) \
{ \
    long long num = (var); \
    D(#var " = 0x%llx.", num); \
}

/** ʹ�� D(), ��ʮ�����Ƶ���ʽ ��ӡָ�����ͱ��� 'ptr' �� value. */
#define D_PTR(ptr)  D(#ptr " = %p.", ptr);

/** ʹ�� D(), ��ӡ char �ִ�. */
#define D_STR(pStr) \
{\
    if ( NULL == pStr )\
    {\
        D(#pStr" = NULL.");\
    }\
    else\
    {\
        D(#pStr" = '%s'.", pStr);\
    }\
}

/**
 * �� 'pIndentsBuf' ָ��� buf ��, ��ͷ���� 'indentNum' �� '\t' �ַ�(����), ������һ�� '\0'. 
 * ͨ�� pIndentsBuf ָ��һ�� 16 �ֽڵ� buffer. 
 */
inline static void setIndents(char* pIndentsBuf, unsigned char indentNum)
{
    unsigned char i = 0; 

    const unsigned char MAX_NUM_OF_INDENT = 16 - sizeof('\0');
    if ( indentNum > MAX_NUM_OF_INDENT )
    {
        indentNum = MAX_NUM_OF_INDENT;
    }

    *pIndentsBuf = '\0';
    for ( i = 0; i < indentNum; i++ )
    {
        strcat(pIndentsBuf, "\t");
    }
    *(pIndentsBuf + indentNum) = '\0';
}

/*---------------------------------------------------------------------------*/

#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

typedef struct fstab_rec Volume;

/*-------------------------------------------------------*/
typedef unsigned char boolean;
#ifdef TRUE
#undef TRUE
#endif
#define TRUE        ( (boolean)(1) )

#ifdef FALSE
#undef FALSE
#endif
#define FALSE       ( (boolean)(0) )
/*-------------------------------------------------------*/

// fopen a file, mounting volumes and making parent dirs as necessary.
FILE* fopen_path(const char *path, const char *mode);

void ui_print(const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif  // RECOVERY_COMMON_H

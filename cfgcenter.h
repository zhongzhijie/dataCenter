#ifndef __CFG_CENTER_H__
#define __CFG_CENTER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

typedef uint32 (*obj_func_ptr)(uint32 objCmo, uint32 instance��stCfgContext* cfgContext);
typedef uint32 (*obj_instance_add)(uint32 objCmo);

typedef enum
{
    OBJ_OPERATION_ADD,
    OBJ_OPERATION_DEL,
    OBJ_OPERATION_GET,
    OBJ_OPERATION_SET,
}OPERATION_E;

typedef enum
{
    CFG_PRIORITY_COMMON,
    CFG_PRIORITY_LOW = 10,
    CFG_PRIORITY_MID = 50,
    CFG_PRIORITY_HIGH = 100,
}CFG_OBJ_PRIORITY_E;

/* ���Խṹ�� */
typedef struct cfg_para
{
    uint32 type;        /* �������� */
    uint32 length;      /* �������� */
    void* value;        /* ����ֵ�ĵ�ַ */
}stCfgPara;

/* ʾ���Ľṹ�� */
typedef struct cfg_para_info
{
    uint32 instanceId;      /* ʵ���� */
    uint32 paraNum;         /* �������� */
    stCfgPara* paraObj;     /* ����ָ��,paraObj[0]��ָ���һ������,�Դ����� */
}stCfgParaInfo;

/* ���������Ľṹ�� */
typedef struct cfg_context
{
    uint32 operation;
    stCfgParaInfo* cfgPara;
    uint32 outLen;
    void* outData;
}stCfgContext;

typedef struct functions
{
    obj_func_ptr add;
    obj_func_ptr del;
    obj_func_ptr check;
    obj_func_ptr get;
    obj_func_ptr set;
    obj_instance_add add_inst;
}OBJ_FUNCTIONS;

typedef struct cfg_process_item
{
    uint32 priority;
    OBJ_FUNCTIONS function;
}cfgProcessItem;

typedef struct cfg_obj_item
{
    uint32 objCmo;
    struct linkList* objInstanceList;
    struct linkList* objProcessList;
}cfgObjItem;

uint32 cfg_obj_register(uint32 objCmo, OBJ_FUNCTIONS* func, uint32 priority)

#ifdef __cplusplus
}
#endif

#endif /* __CFG_CENTER_H__ */

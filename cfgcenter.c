#include "cfgcenter.h"

struct linkList* g_cmo_list = NULL;

stLinkList* cmo_list_get()
{
    uint32 ret = FAIL;
    
    if (NULL == g_cmo_list)
    {
        ret = listNew(&g_cmo_list);
        if (SUCCESS != ret)
        {
            return NULL;
        }
    }

    return g_cmo_list;
}

uint32 cmo_item_add(uint32 cmo)
{
    linkList* comList = NULL;
    cfgObjItem item;
    uint32 ret = SUCCESS;

    cmoList = cmo_list_get();
    if (NULL == cmoList)
    {
        return FAIL;
    }

    memset(&item, 0, sizeof(cfgObjItem));
    item.objCmo = cmo;

    ret = cmoList->objGet(cmoList, &item, 0, sizeof(uint32));
    if (SUCCESS != ret)
    {
        ret = cmoList->objAdd(cmoList, &item, sizeof(cfgObjItem));
    }

    return ret;
}

linkList* process_list_get(uint32 cmo)
{
    uint32 ret = FAIL;
    linkList* cmoList = NULL;
    cfgObjItem item;

    cmoList = cmo_list_get();

    if (NULL == cmoList)
    {
        return NULL;
    }

    memset(&item, 0, sizeof(cfgObjItem));
    item.objCmo = cmo;

    /* 存在返回 */
    ret = cmoList->objGet(cmoList, &item, 0, sizeof(item.objCmo));
    if (SUCCESS == ret && NULL != item.objProcessList)
    {
        return item.objProcessList;
    }

    /* 不存在创建 */
    ret = listNew(&(item.objProcessList))
    if (SUCCESS != ret)
    {
        return NULL;
    }

    return item.objProcessList;
}

linkList* instance_list_get(uint32 cmo)
{
    uint32 ret = FAIL;
    linkList* cmoList = NULL;
    cfgObjItem item;

    cmoList = cmo_list_get();

    if (NULL == cmoList)
    {
        return NULL;
    }

    memset(&item, 0, sizeof(cfgObjItem));
    item.objCmo = cmo;

    /* 存在返回 */
    ret = cmoList->objGet(cmoList, &item, 0, sizeof(item.objCmo));
    if (SUCCESS == ret && NULL != item.objInstanceList)
    {
        return item.objInstanceList;
    }

    /* 不存在创建 */
    ret = listNew(&(item.objInstanceList))
    if (SUCCESS != ret)
    {
        return NULL;
    }

    return item.objInstanceList;
}

/* 添加cmo对象下的示例节点 */
uint32 cfg_add_instance(uint32 cmo, uint32 instance)
{
    linkList* cmoList = NULL;
    linkList* instanceList = NULL;
    stCfgParaInfo cfgInstance;
    uint32 ret = SUCCESS;
    
    instanceList = instance_list_get(cmo);
    if (NULL == instanceList)
    {
        return SUCCESS;
    }

    memset(&cfgInstance, 0, sizeof(stCfgParaInfo));
    cfgInstance.instanceId = instance;

    ret = instanceList.objAdd(instanceList, &cfgInstance, sizeof(stCfgParaInfo));
    return ret;
}

int32 compareItem(void* itemL, void* itemR)
{
    cfgProcessItem* itemLeft = (cfgProcessItem*)itemL;
    cfgProcessItem* itemRight = (cfgProcessItem*)itemR;

    if (itemLeft->priority == itemRight->priority)
    {
        return 0;
    }
    else if (itemLeft->priority > itemRight->priority)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

uint32 cfg_obj_register(uint32 objCmo, OBJ_FUNCTIONS* func, uint32 priority)
{
    cfgProcessItem procItem;
    linkList* procList = NULL;
    uint32 ret = SUCCESS;

    /* 创建cmo链表头(首次调用reg函数时)，创建cmo对象 */
    ret = cmo_item_add(objCmo);
    if (SUCCESS != ret)
    {
        return FAIL;
    }
    
    memset(&procItem, 0, sizeof(cfgProcessItem));
    memcpy(&(procItem.function), func, sizeof(OBJ_FUNCTIONS));
    procItem.priority = priority;

    /* 创建cmo对象的处理函数链表头 */
    procList = process_list_get(objCmo);
    if (NULL == procList)
    {
        return FAIL;
    }

    ret = procList->objAdd(procList, &procItem, sizeof(cfgProcessItem));
    if (SUCCESS == ret)
    {
        ret = procList->sort(procList, compareItem, TRUE);
    }

    return ret;
}

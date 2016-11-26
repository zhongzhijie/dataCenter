#ifndef __SELFDEF_LINKLIST_H__
#define __SELFDEF_LINKLIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "types.h"

typedef struct listNode
{
    uint32 objLen;
    void* objPtr;
    struct listNode* next;
    struct listNode* prev;
}stListNode;

typedef struct linkList
{
    struct listNode* head;
    struct listNode* tail;
    uint32 count;
    uint32 (*objAdd)(struct linkList* list, void* obj, uint32 objLen);
    uint32 (*objDel)(struct linkList* list, void* obj);
    uint32 (*objGet)(struct linkList* list, void* obj, uint32 indexOffset, uint32 indexLen);
    uint32 (*clearList)(struct linkList* list);
    uint32 (*freeList)(struct linkList* list);
    uint32 (*getLength)(struct linkList* list);
    uint32 (*sort)(struct linkList* list, uint32 (*compareFunc)(void* objSrc, void* objDst), uint8 descendFlag);
}stLinkList;

uint32 listNew(struct linkList** list);
uint32 listInit(struct linkList* list);
uint32 listDataPrint(struct linkList* list);


#ifdef __cplusplus
}
#endif

#endif /* __SELFDEF_LINKLIST_H__ */


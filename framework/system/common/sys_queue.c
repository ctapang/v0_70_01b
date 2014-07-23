#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "system/common/sys_common.h"
#include "system/common/sys_queue.h"

QUEUE_OBJECT *test;

// *****************************************************************************
/******************************************************************************
  Function:
    QUEUE_OBJECT *QUEUE_Create();
 *****************************************************************************/

void QUEUE_Initialize(QUEUE_OBJECT *queue, int size, QUEUE_ELEMENT_OBJECT *qelementPool)
{

    //SYS_ASSERT((queue != (QUEUE_OBJECT *)NULL),"Queue is NULL ");

    {
        queue->head         = NULL;
        //queue->tail         = NULL;
        queue->numElements  = 0;
        queue->size         = size;
        queue->qElementPool = qelementPool;
    }

}


// *****************************************************************************
/******************************************************************************
  Function:
    void QUEUE_Reset(QUEUE_OBJECT *queue);
 *****************************************************************************/

void QUEUE_Reset(QUEUE_OBJECT *queue)
{
        queue->head         = NULL;
        //queue->tail         = NULL;
        queue->numElements  = 0;
        queue->size         = 0;
}


// *****************************************************************************
/******************************************************************************
  Function:
    int8_t QUEUE_PushBuffer(QUEUE_OBJECT *queue, DRV_HANDLE handle, uint8_t buffer,
        uint32_t size);

 *****************************************************************************/

int QUEUE_Push(QUEUE_OBJECT *queue, void *data)
{
int i =0;
int elementIndex = 0;
QUEUE_ELEMENT_OBJECT *queue_element = NULL;
bool isInInterruptContext;

    isInInterruptContext = TMRMutexOpen(0);

    for(i = 0 ; i < queue->size ; i++)
    {
        if(!queue->qElementPool[i].inUse)
        {
            queue->qElementPool[i].inUse = true;
            queue_element = &queue->qElementPool[i];
            elementIndex = i;
            break;
        }
    }

    SYS_ASSERT((queue_element != NULL), "bad allocation");

    //SYS_ASSERT((queue_element!= (QUEUE_ELEMENT_OBJECT *)NULL), "Unable to create queue elements ");

    queue_element->next = NULL;
    queue_element->data = data;

    /* OSAL Lock Mutex - TODO */
    if(queue->head == (QUEUE_ELEMENT_OBJECT *)NULL)
    {
        queue->head = queue_element;
    }
    else
    {
        queue_element->next = (struct QUEUE_ELEMENT_OBJECT *)queue->head;
        queue->head = queue_element;
    }

    queue->numElements++;

    TMRMutexClose( isInInterruptContext, 0 );

    return(elementIndex);

}

bool QUEUE_ElementActive(QUEUE_OBJECT *queue, int qIndex)
{
    return queue->qElementPool[qIndex].inUse;
}


// *****************************************************************************
/******************************************************************************
  Function:
    void QUEUE_PopBuffer(QUEUE_OBJECT *queue, DRV_HANDLE handle, uint8_t buffer,
        uint32_t size);

 *****************************************************************************/

QUEUE_ELEMENT_OBJECT * QUEUE_Pop(QUEUE_OBJECT *queue)
{
QUEUE_ELEMENT_OBJECT *queue_element = NULL;
bool isInInterruptContext;

    isInInterruptContext = TMRMutexOpen(0);

    test = queue;

    queue_element = queue->head;

    /* OSAL Lock Mutex - TODO */
    if(queue_element != (QUEUE_ELEMENT_OBJECT *)NULL)
    {
        queue->head = (QUEUE_ELEMENT_OBJECT *)queue_element->next;

        queue_element->data = NULL;
        queue_element->next   = NULL;
        queue_element->inUse  = false;
        queue->numElements--;
    }

    TMRMutexClose(isInInterruptContext, 0);

    return queue_element;

}

void QUEUE_RemoveElement(QUEUE_OBJECT *queue, QUEUE_ELEMENT_OBJECT * queueObject)
{
    int i = 0;
    QUEUE_ELEMENT_OBJECT *one_behind = queue->head;
    QUEUE_ELEMENT_OBJECT *queue_element = (QUEUE_ELEMENT_OBJECT *)one_behind->next;

    if (one_behind == queueObject)
    {
        queue->head = queue_element;
        queue_element = one_behind;
    }
    while (queue_element != queueObject)
    {
        if (queue_element == NULL)
            break;
        if (i >= queue->numElements) // quard against loop
            break;
        one_behind = queue_element;
        queue_element = (QUEUE_ELEMENT_OBJECT *)queue_element->next;
        i++;
    }
    if (i < queue->numElements)
    {
        if (one_behind != queue_element)
        {
            one_behind->next = queue_element->next;
        }
        queue->numElements--;
        queue_element->data = NULL;
        queue_element->next = NULL;
        queue_element->inUse = false;
    }
}

/*******************************************************************************
 End of File
*/

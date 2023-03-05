/*
 * Author: binyxia
 * Usage: Realize classic memory pool management
 */

#include <iostream>

template <int ObjectSize, int NumofObjects = 20>
class MemPool
{
private:
   // 空闲节点结构体
   struct FreeNode
   {
      FreeNode *pNext;
      char data[ObjectSize];
   };

   // 内存块结构体
   struct MemBlock
   {
      MemBlock *pNext;
      FreeNode data[NumofObjects];
   };

   // head node
   FreeNode *freeNodeHeader;
   MemBlock *memBlockHeader;

public:
   MemPool()
   {
      freeNodeHeader = NULL;
      memBlockHeader = NULL;
   }

   ~MemPool()
   {
      MemBlock *ptr;
      while (memBlockHeader)
      {
         ptr = memBlockHeader->pNext;
         delete memBlockHeader;
         memBlockHeader = ptr;
      }
   }
   void *malloc();
   void free(void *);
};

// void *malloc()实现，分配空闲内存节点
template <int ObjectSize, int NumofObjects>
void *MemPool<ObjectSize, NumofObjects>::malloc()
{
   // 无空闲节点，申请新内存块
   if (freeNodeHeader->pNext == NULL)
   {
      MemBlock *newBlock = new MemBlock;
      newBlock->pNext = NULL;

      freeNodeHeader= &newBlock->data[0]; //设置内存块第一个节点为空闲节点链表的表头
                                          //->的优先级高于&,所以可以理解为&(newBlock->data[0])
      
      //将内存块其他节点串起
      for(int i=0;i<NumofObjects;++i){
         newBlock->data[i-1].pNext = &newBlock->data[i];
      }
      newBlock->data[NumofObjects-1].pNext=NULL;
   }
}

// void free(void*)实现，释放已分配节点

int main()
{

   return 0;
}

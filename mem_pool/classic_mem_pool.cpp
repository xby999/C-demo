/*
 * Author: binyxia
 * Usage: Realize classic memory pool management
 */

#include <iostream>

template <int ObjectSize, int NumofObjects = 20>
class MemPool
{
private:
   // ���нڵ�ṹ��
   struct FreeNode
   {
      FreeNode *pNext;
      char data[ObjectSize];
   };

   // �ڴ��ṹ��
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

// void *malloc()ʵ�֣���������ڴ�ڵ�
template <int ObjectSize, int NumofObjects>
void *MemPool<ObjectSize, NumofObjects>::malloc()
{
   // �޿��нڵ㣬�������ڴ��
   if (freeNodeHeader->pNext == NULL)
   {
      MemBlock *newBlock = new MemBlock;
      newBlock->pNext = NULL;

      freeNodeHeader= newBlock->data[0];
   }
}

// void free(void*)ʵ�֣��ͷ��ѷ���ڵ�

int main()
{

   return 0;
}
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
      std::cout<<"sadas"<<std::endl;
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
   if (freeNodeHeader == NULL)
   {
      std::cout<<"sadas"<<std::endl;
      MemBlock *newBlock = new MemBlock;
      newBlock->pNext = NULL;

      freeNodeHeader = &newBlock->data[0]; // 设置内存块第一个节点为空闲节点链表的表头
                                           //->的优先级高于&,所以可以理解为&(newBlock->data[0])

      // 将内存块其他节点串起
      for (int i = 0; i < NumofObjects; ++i)
      {
         newBlock->data[i - 1].pNext = &newBlock->data[i];
      }
      newBlock->data[NumofObjects - 1].pNext = NULL;

      // allocate memory for the first time
      if (memBlockHeader == NULL)
      {
         memBlockHeader = newBlock;
      }
      else
      {
         newBlock->pNext = memBlockHeader;
         memBlockHeader = newBlock;
      }
   }

   void *freeNode = freeNodeHeader;
   freeNodeHeader = freeNodeHeader->pNext;
   return freeNode;
}

// void free(void*)实现，释放已分配节点
template <int ObjectSize, int NumofObject>
void MemPool<ObjectSize, NumofObject>::free(void *p)
{
   FreeNode *pNode = (FreeNode *)p;
   pNode->pNext = freeNodeHeader;
   freeNodeHeader = pNode;
   std::cout<<"sadas";
}

class ActualClass
{
   static int count;
   int No;

public:
   ActualClass()
   {
      No = count;
      count++;
   }
   void print()
   {
      std::cout << ": ";
      std::cout << this << ": ";
      std::cout << "the " << No << "th obj" << std::endl;
   }

   void *operator new(size_t size);
   void operator delete(void *p);
};

MemPool<sizeof(ActualClass), 2> MP; // 这一步是预先申请一个内存池

void *ActualClass::operator new(size_t size)
{
   return MP.malloc();
}

void ActualClass::operator delete(void *p)
{
   return MP.free(p);
}

int ActualClass::count = 0;

int main()
{
   ActualClass *p1= new ActualClass;
   p1->print();
   std::cout<<"asdasd"<<std::endl;

   delete p1;

   // ActualClass *p2= new ActualClass;
   // p2->print();

   // delete p1;
   // p1= new ActualClass;
   // p1->print();

   // ActualClass *p3= new ActualClass;
   // p3->print();

   // delete p1;
   // delete p2;
   // delete p3;
   return 0;
}

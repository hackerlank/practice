#include "func.h"
#include <string.h>
//这里不能包含new.h(间接的也不行)

#ifdef DEBUG
const int FILE_SIZE = 32;
struct Node
{
    char file[FILE_SIZE];
    size_t line;
    size_t size;
    Node *next;
};
const int NODE_LEN = 1024;
static Node* nodeArray[NODE_LEN];

int hashIndex(void *p)
{
    unsigned long val = reinterpret_cast<unsigned long>(p);
    return val % NODE_LEN;
}

bool insert(Node *pn,void *p)
{
    bool ret = false;
    do
    {
        if(!pn || !p)
        {
            break;
        }
        int val = hashIndex(p);
        pn->next = nodeArray[val];
        nodeArray[val] = pn;
        ret = true;
    }while(false);
    printf("[分配内存](%s,文件名:%s,行数:%d,大小:%d)\n",(ret ? "成功" : "失败"),pn->file,pn->line,pn->size);
#if 0
    std::cout << "[分配内存](" << (ret ? "成功" : "失败") << ",文件名:" << pn->file << ",行数:" << pn->line << ",大小:" << pn->size << ")" << std::endl;
#endif
    return ret;
}

void* erase(void *pv)
{
    Node *ret = NULL;
    do
    {
        int val = hashIndex(pv);
        Node *pre = nodeArray[val];
        if((char*)pre == ((char*)pv - sizeof(Node)))
        {
            ret = pre;
            nodeArray[val] = pre->next;
        }
        else
        {
            while(pre)
            {
                Node *pn = pre->next;
                if((char*)pn == ((char*)pv - sizeof(Node)))
                {
                    ret = pn;
                    pre->next = pn->next;
                    break;
                }
                pre = pn;
            }
        }
    }while(false);
    if(ret)
    {
        printf("[释放内存](%s,文件名:%s,行数:%d,大小:%d)\n",(true ? "成功" : "失败"),ret->file,ret->line,ret->size);
    }
    else
    {
        printf("[释放内存](失败)\n");
    }
#if 0
        std::cout << "[释放内存](成功" << ",文件:" << ret->file << ",行数:" << ret->line << ",大小:" << ret->size << ")" << std::endl;
    }
    else
    {
        std::cout << "[释放内存](失败)" << std::endl;
    }
#endif
    return ret;
}
                


void* operator new(const size_t size,const char *file,const size_t line)
{
    void *ret = NULL;
    do
    {
        if(!size)
        {
            break;
        }
        size_t total = size + sizeof(Node);
        void *pv = malloc(total);
        Node *pn = (Node*)(pv);
        if(!pn)
        {
            break;
        }
        strncpy(pn->file,file,sizeof(pn->file)-1);
        pn->line = line;
        pn->size = size;
        ret = insert(pn,(char*)pv+sizeof(Node)) ? (char*)pv + sizeof(Node) : NULL;
    }while(false);
    return ret;
}

void operator delete (void *pv)
{
    void *ret = (void*)(erase(pv));
    free(ret);
}
#endif




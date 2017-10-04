// MyList.h: interface for the CMyList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLIST_H__D6BE30F0_74F3_491F_B428_514AA00B8B07__INCLUDED_)
#define AFX_MYLIST_H__D6BE30F0_74F3_491F_B428_514AA00B8B07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFX_H__
#define CList CMyList
typedef void* POSITION;
#endif // __AFX_H__

#ifndef NULL 
#define NULL 0
#endif

/************************************************************************/
/*                                ����                                  */
/************************************************************************/
template <typename T>
class CMyList
{
public:
    CMyList();
    CMyList(const CMyList<T>& obj);
    virtual ~CMyList();

public:
    //������
    inline int GetCount() const;
    //�Ƿ�Ϊ��
    inline bool IsEmpty() const;

    //��ȡͷ�������
    inline T& GetHead() const;
    //��ȡβ�������
    inline T& GetTail() const;

    //��ȡָ��λ������
    inline static T& GetAt(POSITION posDest);
    //����ָ��λ������
    inline CMyList<T>& SetAt(POSITION posDest, const T& Data);
    
    //��ȡǰһ���������
    inline T& GetPrev(POSITION& posDest) const;
    //��ȡ��һ���������
    inline T& GetNext(POSITION& posDest) const;

    //��ȡָ��λ������
    inline POSITION GetPosition(int nIndex) const;
    //��ȡͷ���λ��
    inline POSITION GetHeadPosition() const;
    //��ȡβ���λ��
    inline POSITION GetTailPosition() const;
    //��ȡǰһ�����λ��
    inline static POSITION GetPrevPosition(POSITION posDest);
    //��ȡ��һ�����λ��
    inline static POSITION GetNextPosition(POSITION posDest);

    //��ȡָ��Ԫ��λ��
    POSITION Find(const T& Data, POSITION posBegin = NULL) const;
    //��ȡָ������λ��
    POSITION FindIndex(int nIndex) const;

    //����ͷ���
    POSITION AddHead(const T& Data);
    //����β�ڵ�
    POSITION AddTail(const T& Data);
    //��ָ��λ��ǰ��������
    POSITION InsertBefore(POSITION posDest, const T& Data);
    //��ָ��λ�ú��������
    POSITION InsertAfter(POSITION posDest, const T& Data);

    //�Ƴ�ָ�����
    bool Remove(const T& Data);
    //�Ƴ�ͷ���
    void RemoveHead();
    //�Ƴ�β�ڵ�
    void RemoveTail();
    //�Ƴ�ָ�����
    void RemoveAt(POSITION posDest);
    //�Ƴ����н��
    void RemoveAll();

    CMyList<T>& operator= (const CMyList<T>& obj);
    inline T& operator[] (int nIndex);

protected:
    class CNode
    {
    public:
        inline CNode();
        inline CNode(const T& Data);
        inline CNode(const T& Data, CNode *pPrev, CNode *pNext);
        
    public:
        T m_Data;
        CNode *m_pPrev;
        CNode *m_pNext;
    };

public:
    //������
    class iterator
    {
    public:
        friend class CMyList<T>;
        inline iterator(CNode *pNode = NULL);
        inline iterator& operator++();
        inline const iterator operator++(int);
        inline iterator& operator--();
        inline const iterator operator--(int);
        inline T& operator*() const;
        inline iterator& operator= (const iterator& obj);
        inline bool operator== (const iterator& obj) const;
        inline bool operator!= (const iterator& obj) const;
    private:
        CNode *m_pNode;
    };
    
    iterator begin();
    iterator end();

protected:
    CNode *m_pHead; //ͷ���
    CNode *m_pTail; //β�ڵ�
    int m_nCount; //������

private:
    //��������
    CMyList<T>& Copy(const CMyList<T>& obj);
};

template <typename T>
CMyList<T>::CMyList()
    : m_pHead(NULL), m_pTail(NULL), m_nCount(0)
{
    
}

template <typename T>
CMyList<T>::CMyList(const CMyList<T>& obj)
    : m_pHead(NULL), m_pTail(NULL), m_nCount(0)
{
    Copy(obj);
}

template <typename T>
CMyList<T>::~CMyList()
{
    RemoveAll();
}

//������
template <typename T>
inline int CMyList<T>::GetCount() const
{
    return m_nCount;
}

//�Ƿ�Ϊ��
template <typename T>
inline bool CMyList<T>::IsEmpty() const
{
    return m_nCount == 0;
}

//��ȡͷ�������
template <typename T>
inline T& CMyList<T>::GetHead() const
{
    return m_pHead->m_Data;
}

//��ȡβ�������
template <typename T>
inline T& CMyList<T>::GetTail() const
{
    return m_pTail->m_Data;
}

//��ȡָ��λ������
template <typename T>
inline T& CMyList<T>::GetAt(POSITION posDest)
{
    return ((CNode*)posDest)->m_Data;
}

//����ָ��λ������
template <typename T>
inline CMyList<T>& CMyList<T>::SetAt(POSITION posDest, const T& Data)
{
    ((CNode*)posDest)->m_Data = Data;
    
    return *this;
}

//��ȡǰһ���������
template <typename T>
inline T& CMyList<T>::GetPrev(POSITION& posDest) const
{
    CNode* pNode = (CNode*)posDest;
    posDest = pNode->m_pPrev;
    return pNode->m_Data;
}

//��ȡ��һ���������
template <typename T>
inline T& CMyList<T>::GetNext(POSITION& posDest) const
{
    CNode* pNode = (CNode*)posDest;
    posDest = pNode->m_pNext;
    return pNode->m_Data;
}

//��ȡָ��λ������
template <typename T>
inline POSITION CMyList<T>::GetPosition(int nIndex) const
{
    if (nIndex < m_nCount)
    {
        CNode *pNode = m_pHead;

        for (int i = 0; i < nIndex; i++)
        {
            pNode = pNode->m_pNext;
        }

        return (POSITION)pNode;
    }

    return NULL;
}

//��ȡͷ���λ��
template <typename T>
inline POSITION CMyList<T>::GetHeadPosition() const
{
    return (POSITION)m_pHead;
}

//��ȡβ���λ��
template <typename T>
inline POSITION CMyList<T>::GetTailPosition() const
{
    return (POSITION)m_pTail;
}

//��ȡǰһ�����λ��
template <typename T>
inline POSITION CMyList<T>::GetPrevPosition(POSITION posDest)
{
    return (POSITION)((CNode*)posDest)->m_pPrev;
}

//��ȡ��һ�����λ��
template <typename T>
inline POSITION CMyList<T>::GetNextPosition(POSITION posDest)
{
    return (POSITION)((CNode*)posDest)->m_pNext;
}

//��ȡָ��Ԫ��λ��
template <typename T>
POSITION CMyList<T>::Find(const T& Data, POSITION posBegin) const
{
    CNode *pNodeDest = posBegin == NULL ? m_pHead : (CNode*)posBegin;

    while (pNodeDest != NULL)
    {
        if (pNodeDest->m_Data == Data)
        {
            return (POSITION)pNodeDest;
        }

        pNodeDest = pNodeDest->m_pNext;
    }

    return NULL;
}

//��ȡָ������λ��
template <typename T>
POSITION CMyList<T>::FindIndex(int nIndex) const
{
    if (nIndex < 0 || nIndex >= m_nCount)
    {
        return NULL;
    }

    CNode *pNodeDest = m_pHead;
    
    for (int i = 0; i < nIndex; i++)
    {
        pNodeDest = pNodeDest->m_pNext;
    }
    
    return (POSITION)pNodeDest;
}

//����ͷ���
template <typename T>
POSITION CMyList<T>::AddHead(const T& Data)
{
    CNode *pNodeHead = new CNode(Data);

    if (!IsEmpty())
    {
        pNodeHead->m_pNext = m_pHead;
        m_pHead->m_pPrev = pNodeHead;
        m_pHead = pNodeHead;
    }
    else
    {
        m_pHead = m_pTail = pNodeHead;
    }

    m_nCount++;

    return (POSITION)m_pHead;
}

//����β�ڵ�
template <typename T>
POSITION CMyList<T>::AddTail(const T& Data)
{
    CNode *pNodeTail = new CNode(Data);

    if (!IsEmpty())
    {
        pNodeTail->m_pPrev = m_pTail;
        m_pTail->m_pNext = pNodeTail;
        m_pTail = pNodeTail;
    }
    else
    {
        m_pHead = m_pTail = pNodeTail;
    }

    m_nCount++;

    return (POSITION)m_pTail;
}

//��ָ��λ��ǰ��������
template <typename T>
POSITION CMyList<T>::InsertBefore(POSITION posDest, const T& Data)
{
    CNode *pNodeNext = (CNode*)posDest;
    CNode *pNodePrev = pNodeNext->m_pPrev;
    CNode *pNodeInsert = new CNode(Data, pNodePrev, pNodeNext);

    if (pNodePrev != NULL)
    {
        pNodePrev->m_pNext = pNodeInsert;
    }
    else
    {
        m_pHead = pNodeInsert;
    }

    pNodeNext->m_pPrev = pNodeInsert;
    m_nCount++;

    return (POSITION)pNodeInsert;
}

//��ָ��λ�ú��������
template <typename T>
POSITION CMyList<T>::InsertAfter(POSITION posDest, const T& Data)
{
    CNode *pNodePrev = (CNode*)posDest;
    CNode *pNodeNext = pNodePrev->m_pNext;
    CNode *pNodeInsert = new CNode(Data, pNodePrev, pNodeNext);
    
    if (pNodeNext != NULL)
    {
        pNodeNext->m_pPrev = pNodeInsert;
    }
    else
    {
        m_pTail = pNodeInsert;
    }
    
    pNodePrev->m_pNext = pNodeInsert;
    m_nCount++;
    
    return (POSITION)pNodeInsert;
}

//��������
template <typename T>
CMyList<T>& CMyList<T>::Copy(const CMyList<T>& obj)
{
    if (!obj.IsEmpty())
    {
        CNode *pNodeTemp = obj.m_pHead;
        
        while (pNodeTemp != NULL)
        {
            AddTail(pNodeTemp->m_Data);
            pNodeTemp = pNodeTemp->m_pNext;
        }
    }
    else
    {
        m_pHead = m_pTail = NULL;
        m_nCount = 0;
    }

    return *this;
}

//�Ƴ�ָ�����
template <typename T>
bool CMyList<T>::Remove(const T& Data)
{
    CNode *pNodeTemp = m_pHead;

    while (pNodeTemp != NULL)
    {
        if (pNodeTemp->m_Data == Data)
        {
            RemoveAt((POSITION)pNodeTemp);
            return true;
        }
    }

    return false;
}

//�Ƴ�ͷ���
template <typename T>
void CMyList<T>::RemoveHead()
{
    CNode *pNodeRemove = m_pHead;
    m_pHead = pNodeRemove->m_pNext;

    if (m_pHead != NULL)
    {
        m_pHead->m_pPrev = NULL;
    }
    else
    {
        m_pTail = NULL;
    }

    T Data = pNodeRemove->m_Data;
    delete pNodeRemove;
    m_nCount--;
}

//�Ƴ�β�ڵ�
template <typename T>
void CMyList<T>::RemoveTail()
{
    CNode *pNodeRemove = m_pTail;
    m_pTail = pNodeRemove->m_pPrev;
    
    if (m_pTail != NULL)
    {
        m_pTail->m_pNext = NULL;
    }
    else
    {
        m_pHead = NULL;
    }
    
    T Data = pNodeRemove->m_Data;
    delete pNodeRemove;
    m_nCount--;
}

//�Ƴ�ָ�����
template <typename T>
void CMyList<T>::RemoveAt(POSITION posDest)
{
    CNode *pNodeRemove = (CNode*)posDest;
    CNode *pNodePrev = pNodeRemove->m_pPrev;
    CNode *pNodeNext = pNodeRemove->m_pNext;

    if (pNodePrev != NULL)
    {
        pNodePrev->m_pNext = pNodeNext;
    }
    else
    {
        m_pHead = pNodeNext;
    }

    if (pNodeNext != NULL)
    {
        pNodeNext->m_pPrev = pNodePrev;
    }
    else
    {
        m_pTail = pNodePrev;
    }
    
    delete pNodeRemove;
    m_nCount--;
}

//�Ƴ����н��
template <typename T>
void CMyList<T>::RemoveAll()
{
    CNode *pNodeTemp = m_pHead;

    while (pNodeTemp != NULL) 
    {
        CNode *pNodeRemove = pNodeTemp;
        pNodeTemp = pNodeRemove->m_pNext;
        delete pNodeRemove;
    }

    m_pHead = m_pTail = NULL;
    m_nCount = 0;
}

template <typename T>
CMyList<T>& CMyList<T>::operator= (const CMyList<T>& obj)
{
    if (this == &obj)
    {
        return *this;
    }

    if (!IsEmpty())
    {
        RemoveAll();
    }

    Copy(obj);

    return *this;
}

template <typename T>
T& CMyList<T>::operator[] (int nIndex)
{
    CNode *pNode = m_pHead;

    for (int i = 0; i < nIndex; i++)
    {
        pNode = pNode->m_pNext;
    }

    return pNode->m_Data;
}

template <typename T>
CMyList<T>::CNode::CNode()
    : m_pPrev(NULL), m_pNext(NULL)
{

}

template <typename T>
CMyList<T>::CNode::CNode(const T& Data)
    : m_Data(Data), m_pPrev(NULL), m_pNext(NULL)
{

}

template <typename T>
CMyList<T>::CNode::CNode(const T& Data, CNode *pPrev, CNode *pNext)
    : m_Data(Data), m_pPrev(pPrev), m_pNext(pNext)
{

}

template <typename T>
CMyList<T>::iterator::iterator(CNode *pNode)
    : m_pNode(pNode)
{

}

template <typename T>
typename CMyList<T>::iterator& CMyList<T>::iterator::operator++()
{
    m_pNode = m_pNode->m_pNext;
    return *this;
}

template <typename T>
typename const CMyList<T>::iterator CMyList<T>::iterator::operator++(int)
{
    iterator it = *this;
    m_pNode = m_pNode->m_pNext;
    return it;
}

template <typename T>
typename CMyList<T>::iterator& CMyList<T>::iterator::operator--()
{
    m_pNode = m_pNode->m_pPrev;
    return *this;
}

template <typename T>
typename const CMyList<T>::iterator CMyList<T>::iterator::operator--(int)
{
    iterator it = *this;
    m_pNode = m_pNode->m_pPrev;
    return it;
}

template <typename T>
T& CMyList<T>::iterator::operator*() const
{
    return m_pNode->m_Data;
}

template <typename T>
typename CMyList<T>::iterator& CMyList<T>::iterator::operator= (const iterator& obj)
{
    m_pNode = obj.m_pNode;
    return *this;
}

template <typename T>
typename bool CMyList<T>::iterator::operator== (const iterator& obj) const
{
    return m_pNode == obj.m_pNode;
}

template <typename T>
typename bool CMyList<T>::iterator::operator!= (const iterator& obj) const
{
    return m_pNode != obj.m_pNode;
}

template <typename T>
typename CMyList<T>::iterator CMyList<T>::begin()
{
    iterator it;
    it.m_pNode = m_pHead;
    return it;
}

template <typename T>
typename CMyList<T>::iterator CMyList<T>::end()
{
    iterator it;
    it.m_pNode = NULL;
    return it;
}


/************************************************************************/
/*                                 ջ                                   */
/************************************************************************/
template <typename T>
class CStack : private CMyList<T>
{
public:
    CStack();
    virtual ~CStack();
    
    //��ջ
    inline CStack& Push(const T& data);
    //��ջ
    inline T Pop();

    //ȡջ��Ԫ��
    inline const T& Top() const;

public:
    CMyList<T>::IsEmpty;
    CMyList<T>::GetCount;
    CMyList<T>::RemoveAll;
};

template <typename T>
CStack<T>::CStack()
{
    
}

template <typename T>
CStack<T>::~CStack()
{

}

//��ջ
template <typename T>
inline CStack<T>& CStack<T>::Push(const T& data)
{
    AddTail(data);
    
    return *this;
}

//��ջ
template <typename T>
inline T CStack<T>::Pop()
{
    return RemoveTail();
}

//ȡջ��Ԫ��
template <typename T>
inline const T& CStack<T>::Top() const
{
    return m_pTail->m_Data;
}


/************************************************************************/
/*                                ����                                  */
/************************************************************************/
template <typename T>
class CQueue : private CMyList<T>
{
public:
    CQueue();
    virtual ~CQueue();
    
    //�����
    CQueue<T>& EnQueue(const T& data);
    //������
    T DeQueue();
    
    //ȡ��ͷԪ��
    const T& Front();
    
public:
    CMyList<T>::IsEmpty;
    CMyList<T>::GetCount;
    CMyList<T>::RemoveAll;
};

template <typename T>
CQueue<T>::CQueue()
{

}

template <typename T>
CQueue<T>::~CQueue()
{
    
}

//��ջ
template <typename T>
CQueue<T>& CQueue<T>::EnQueue(const T& data)
{
    AddTail(data);

    return *this;
}

//��ջ
template <typename T>
T CQueue<T>::DeQueue()
{
    return RemoveHead();
}

//ȡ��ͷԪ��
template <typename T>
const T& CQueue<T>::Front()
{
    return m_pHead->m_Data;
}

#endif // !defined(AFX_MYLIST_H__D6BE30F0_74F3_491F_B428_514AA00B8B07__INCLUDED_)

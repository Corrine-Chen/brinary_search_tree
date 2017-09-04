#include<iostream>
using namespace std;
#include<vector>

template<class K, class V>
struct BSTNode
{
	BSTNode(const K& key, const V& value)
		: _pLeft(NULL)
		, _pRight(NULL)
		, _key(key)
		, _value(value)
	{}

	BSTNode<K, V>* _pLeft;
	BSTNode<K, V>* _pRight;
	K _key;
	V _value;
};


template<class K, class V>
class BinarySearchTree
{
	typedef BSTNode<K, V> Node;
	typedef BinarySearchTree<K, V> Self;
public:
	BinarySearchTree()
		: _pRoot(NULL)
	{}

	BinarySearchTree(const Self& bst);
	Self& operator=(const Self& bst)
	{}
	~BinarySearchTree()
	{
		if(_pRoot)
			delete _pRoot;
	}

	bool Find_Nor(const K& key)  // 查找非递归
	{
		while(_pRoot)
		{
			if(key == _pRoot->_key)
			{
				return true;
			}
			else if(_pRoot->_key > key)
			{
				_pRoot = _pRoot->_pLeft；
			}
			else
			{
				_pRoot = _pRoot->_pRight;
			}
		}
		return false;
	}
	bool Find(const K& key)  // 查找递归
    {
            return _Find(_pRoot, key);
    }

 
	bool Insert_Nor(const K& key, const V& value)// 插入非递归
	{
		Node* pos = new Node(key,value);
		if(_pRoot == NULL)
		{
			_pRoot = pos;
			return true;
		}
		else
		{
			Node* pCur = _pRoot;
			while(pCur)//寻找要插入的节点
			{
				if(pCur->_key > key)
				{
					if(NULL == pCur->_pLeft)
					{
						pCur->_pLeft = pos;
						pos->_key = key;
						pos->_value = value;
					}
					else
					{
						pCur = pCur->_pLeft;
					}
					
				}
				else if(pCur->_key < key)
				{
					if(NULL == pCur->_pRight )
					{
						pCur->_pRight = pos;
						pos->_key = key;
						pos->_value = value;
					}
					else
					{
						pCur =  pCur->_pRight;
					}
				}
				else
				{
					return false;
				}
			}

		}
		delete pos;
	}
	bool Insert(const K& key, const V& value)// 插入递归
	{
	     return _Insert(_pRoot, key, value);
	}

 
	bool Remove_Nor(const K& key)   // 删除非递归
	{
		Node* pCur = _pRoot;
		Node* pParent =NULL;
		if(NULL == _pRoot)//如果根节点为空
		{
			return false;
		}
		else if(NULL == _pRoot->_pLeft && NULL == _pRoot->_pRight)//只有根节点
		{
			delete _pRoot ;
			_pRoot = NULL;
			return true;
		}
		else
		{
			while(NULL != pCur)
			{
				if(key < pCur->_key)
				{
					pParent = pCur;
					pCur = pCur->_pLeft;
				}
				else if(key > pCur->_key)
				{
					pParent = pCur;
					pCur = pCur->_pRight;
				}
				else//找到要删除的节点
				{
					if(pCur->_pLeft == NULL)//要删除的节点只有右孩子
					{
						if(NULL != pParent)//要删除的节点不是根节点
						{
							if(pCur == pParent->_pRight)//要删除的节点是其父节点的右孩子
							{
								pParent ->_pRight = pCur->_pRight;
								delete pCur;
								pCur = NULL;
								return true;
							}
							else if(pCur == pParent->_pLeft)//要删除的节点是其父节点的左孩子
							{
								pParent->_pLeft = pCur->_pRight;
								delete pCur;
								pCur = NULL;
								return true;
							}
						}
						else//要删除的节点是根节点
						{
							_pRoot = pCur->_pRight;
							delete pCur;
							pCur = NULL;
							return true;
						}
					}
					else if(pCur->_pRight == NULL)//要删除的节点只有左孩子
					{
						if(NULL != pParent)//要删除的节点不是根节点
						{
							if(pParent->_pRight = pCur)//要删除的节点是其父节点的右孩子
							{
								pParent->_pRight = pCur->_pLeft;
								delete pCur;
								pCur = NULL;
								return true;
							}
							if(pParent->_pLeft =pCur)//要删除的节点是其父节点的左孩子
							{
								pParent->_pLeft = pCur->_pLeft;
								delete pCur;
								pCur = NULL;
								return true;
							}
						}
						else//要删除的节点是根节点
						{
							_pRoot = pCur->_pLeft;
							delete pCur;
							pCur = NULL;
							return true;
						}
					}
					else//要删除的节点左右孩子都存在
					{
						Node* firstInorder = pCur->_pRight;//寻找要删除节点的右子树的中序遍历第一个节点
						if(firstInorder ->_pLeft == NULL)
						{
							pCur->_key = firstInorder->_key;
							pCur->_value = firstInorder->_value;
							delete firstInorder;
							firstInorder = NULL;
							pCur->_pRight = NULL;
							return true;
						}
						while(firstInorder ->_pLeft)
						{
							pParent = firstInorder;
							firstInorder = firstInorder->_pLeft;
						}
						pCur->_key = firstInorder->_key;
						pCur->_value = firstInorder->_value;
						pParent->_pLeft = firstInorder->_pRight;
						delete firstInorder;
						return true;
					}
				}
			}
		}
	}
	bool Remove(const K& key)    // 删除递归
	{
	     return _Remove(_pRoot, key);
	}

	void InOrder()
	{
		cout<<"InOrder:";
		_InOrder(_pRoot);
		cout<<endl;
	}

	private:
		bool _Find(Node* pRoot, const K& key)
		{
			if(_pRoot)
			{
				if(key == _pRoot->_key)
				{
					return true;
				}
				else if(_pRoot->_key > key)
				{
					_Find(_pRoot->_pLeft,key);
				}
				else
				{
					_Find(_pRoot->_pRight,key);
				}
			}
			return false;
		}
		bool _Insert(Node* &pRoot, const K& key, const V& value)
		{
			Node* pCur=pRoot;
			if(NULL == pRoot)//若为空节点则直接插入
			{
				pRoot =new Node(key,value);
				pRoot->_key = key;
				pRoot->_value = value;
				return true;
			}
			else if(key == pCur->_key)//二叉树中有需要插入的值则直接返回
			{
				return false;
			}
			else if(key < pCur->_key)//要插入的之小于二叉树的根节点，在他的左子树中寻找
			{
				_Insert(pCur->_pLeft,key,value);
			}
			else if(key > pCur->_key)
			{
				_Insert(pCur->_pRight ,key,value);//要插入的之大于二叉树的根节点，在他的右子树中寻找
			}
			return true;
		}
		bool _Remove(Node*& pRoot, const K& key)
		{
			Node* pDel = NULL;
			if(NULL == pRoot)//如果根节点为空
			{
				return false;
			}
			else if(NULL == pRoot->_pLeft && NULL == pRoot->_pRight)//只有根节点
			{
				delete pRoot ;
				pRoot = NULL;
				return true;
			}
			else
			{
				if(pRoot != NULL)//找到要删除的元素
				{
					if(key < pRoot->_key)
					{
						_Remove(pRoot->_pLeft,key);
					}
					else if(key > pRoot->_key)
					{
						_Remove(pRoot->_pRight,key);
					}
					else
					{
						if(pRoot->_pRight == NULL)//要删除的节点只有左孩子
						{
							pDel = pRoot;
							pRoot = pRoot->_pLeft;
							delete pDel;
							pDel = NULL;
							return true;
						}
						else if(pRoot->_pLeft ==NULL)//要删除的节点只有右孩子
						{
							pDel = pRoot;
							pRoot = pRoot->_pRight;
							delete pDel;
							pDel = NULL;
							return true;
						}
						else //要删除的节点左右孩子都有
						{
							Node* firstInorder = NULL;
							firstInorder = pRoot->_pRight;

							while(firstInorder ->_pLeft)
								firstInorder = firstInorder->_pLeft;

							swap(firstInorder->_key,pRoot->_key);
							swap(firstInorder->_value , pRoot ->_value);

							_Remove(pRoot->_pRight,key);
							return true;
						}
					}
					return false;
				}
			}
		}
		void _InOrder(Node* pRoot)
		{
			if(pRoot)
			{
				_InOrder(pRoot->_pLeft);
				cout<<pRoot->_key<<" ";
				_InOrder(pRoot->_pRight);
			}
		}
private:
	Node* _pRoot;
};

// 测试非递归的三种情况
void Test1()
{
	int a [] = {5,3,4,1,7,8,2,6,0,9};
	BinarySearchTree<int, int> Node;
	for(int i=0; i<sizeof(a)/sizeof(a[0]); ++i)
		Node.Insert_Nor(a[i],a[i]);
	Node.InOrder();
	Node.Remove_Nor(7);
	Node.InOrder();

}

// 测试递归的三种情况
void Test2()
{
	int a [] = {5,3,4,1,7,8,2,6,0,9};
	BinarySearchTree<int, int> Node;
	for(int i=0; i<sizeof(a)/sizeof(a[0]); ++i)
		Node.Insert(a[i],a[i]);
	Node.InOrder();
	Node.Remove(3);
	Node.InOrder();
}


void Test3()
{
	int a [] = {5,3,4,1,7,8,2,6,0,9};
	vector<int> v(a,a+sizeof(a)/sizeof(a[0]));

}
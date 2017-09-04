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

	bool Find_Nor(const K& key)  // ���ҷǵݹ�
	{
		while(_pRoot)
		{
			if(key == _pRoot->_key)
			{
				return true;
			}
			else if(_pRoot->_key > key)
			{
				_pRoot = _pRoot->_pLeft��
			}
			else
			{
				_pRoot = _pRoot->_pRight;
			}
		}
		return false;
	}
	bool Find(const K& key)  // ���ҵݹ�
    {
            return _Find(_pRoot, key);
    }

 
	bool Insert_Nor(const K& key, const V& value)// ����ǵݹ�
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
			while(pCur)//Ѱ��Ҫ����Ľڵ�
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
	bool Insert(const K& key, const V& value)// ����ݹ�
	{
	     return _Insert(_pRoot, key, value);
	}

 
	bool Remove_Nor(const K& key)   // ɾ���ǵݹ�
	{
		Node* pCur = _pRoot;
		Node* pParent =NULL;
		if(NULL == _pRoot)//������ڵ�Ϊ��
		{
			return false;
		}
		else if(NULL == _pRoot->_pLeft && NULL == _pRoot->_pRight)//ֻ�и��ڵ�
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
				else//�ҵ�Ҫɾ���Ľڵ�
				{
					if(pCur->_pLeft == NULL)//Ҫɾ���Ľڵ�ֻ���Һ���
					{
						if(NULL != pParent)//Ҫɾ���Ľڵ㲻�Ǹ��ڵ�
						{
							if(pCur == pParent->_pRight)//Ҫɾ���Ľڵ����丸�ڵ���Һ���
							{
								pParent ->_pRight = pCur->_pRight;
								delete pCur;
								pCur = NULL;
								return true;
							}
							else if(pCur == pParent->_pLeft)//Ҫɾ���Ľڵ����丸�ڵ������
							{
								pParent->_pLeft = pCur->_pRight;
								delete pCur;
								pCur = NULL;
								return true;
							}
						}
						else//Ҫɾ���Ľڵ��Ǹ��ڵ�
						{
							_pRoot = pCur->_pRight;
							delete pCur;
							pCur = NULL;
							return true;
						}
					}
					else if(pCur->_pRight == NULL)//Ҫɾ���Ľڵ�ֻ������
					{
						if(NULL != pParent)//Ҫɾ���Ľڵ㲻�Ǹ��ڵ�
						{
							if(pParent->_pRight = pCur)//Ҫɾ���Ľڵ����丸�ڵ���Һ���
							{
								pParent->_pRight = pCur->_pLeft;
								delete pCur;
								pCur = NULL;
								return true;
							}
							if(pParent->_pLeft =pCur)//Ҫɾ���Ľڵ����丸�ڵ������
							{
								pParent->_pLeft = pCur->_pLeft;
								delete pCur;
								pCur = NULL;
								return true;
							}
						}
						else//Ҫɾ���Ľڵ��Ǹ��ڵ�
						{
							_pRoot = pCur->_pLeft;
							delete pCur;
							pCur = NULL;
							return true;
						}
					}
					else//Ҫɾ���Ľڵ����Һ��Ӷ�����
					{
						Node* firstInorder = pCur->_pRight;//Ѱ��Ҫɾ���ڵ�������������������һ���ڵ�
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
	bool Remove(const K& key)    // ɾ���ݹ�
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
			if(NULL == pRoot)//��Ϊ�սڵ���ֱ�Ӳ���
			{
				pRoot =new Node(key,value);
				pRoot->_key = key;
				pRoot->_value = value;
				return true;
			}
			else if(key == pCur->_key)//������������Ҫ�����ֵ��ֱ�ӷ���
			{
				return false;
			}
			else if(key < pCur->_key)//Ҫ�����֮С�ڶ������ĸ��ڵ㣬��������������Ѱ��
			{
				_Insert(pCur->_pLeft,key,value);
			}
			else if(key > pCur->_key)
			{
				_Insert(pCur->_pRight ,key,value);//Ҫ�����֮���ڶ������ĸ��ڵ㣬��������������Ѱ��
			}
			return true;
		}
		bool _Remove(Node*& pRoot, const K& key)
		{
			Node* pDel = NULL;
			if(NULL == pRoot)//������ڵ�Ϊ��
			{
				return false;
			}
			else if(NULL == pRoot->_pLeft && NULL == pRoot->_pRight)//ֻ�и��ڵ�
			{
				delete pRoot ;
				pRoot = NULL;
				return true;
			}
			else
			{
				if(pRoot != NULL)//�ҵ�Ҫɾ����Ԫ��
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
						if(pRoot->_pRight == NULL)//Ҫɾ���Ľڵ�ֻ������
						{
							pDel = pRoot;
							pRoot = pRoot->_pLeft;
							delete pDel;
							pDel = NULL;
							return true;
						}
						else if(pRoot->_pLeft ==NULL)//Ҫɾ���Ľڵ�ֻ���Һ���
						{
							pDel = pRoot;
							pRoot = pRoot->_pRight;
							delete pDel;
							pDel = NULL;
							return true;
						}
						else //Ҫɾ���Ľڵ����Һ��Ӷ���
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

// ���Էǵݹ���������
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

// ���Եݹ���������
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
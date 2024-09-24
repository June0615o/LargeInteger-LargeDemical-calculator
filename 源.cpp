#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;


struct Node
{
	int data;
	Node* next;
};

void insert(Node*& head,int num)       //在链表头部插入一个新节点，然后将数字存储到新节点中;
{
	Node* p = nullptr;
	Node* s = nullptr;
	if (head == NULL)
	{
		s = new Node;
		s->data = num;
		head = s;
	}
	else if(head != NULL)
	{
		s = new Node;
		s->data = num;
		s->next = head;
		head = s;
	}
}


void addEnd(Node*& head, int num)   //在一个链表的末端添加数字num
{
	Node* s = new Node{ num, nullptr };
	if (head == nullptr) 
	{
		head = s;
	}
	else 
	{
		Node* p = head;
		while (p->next != nullptr) 
		{
			p = p->next;
		}
		p->next = s;
	}
}
Node* InsertEnd(Node* head, int data)    //他的功能与addEnd类似，但他的返回值是一个链表的头指针在头结点），与getTheList配合
{
	Node* newNode = new Node{ data,nullptr };
	if (head == nullptr)
	{
		return newNode;
	}
	Node* p = head;
	while (p->next != nullptr)
	{
		p = p->next;
	}
	p->next = newNode;
	return head;
}

void ShowList(Node* head)               //遍历链表
{
	/*if (resultIsNegative)
	{
		cout << "-";
	}*/
	if (head == nullptr)
		return;
	int count = 0; //计数节点
	Node* current = head;
	while (current!=nullptr)
	{
		count++;
		current = current->next;
	}
	current = head;
	while (current != nullptr)
	{
		cout << current->data;
		count--;
		if (count % 3 == 0 && count != 0)
		{
			cout << ",";
		}
		current = current->next;
	}
	cout << endl;
}

int ListLength(Node* head) 
{           //获取链表的长度（返回值为整数）
	int length = 0;
	while (head != nullptr) 
	{
		length++;
		head = head->next;
	}
	return length;
}

int CountDigits(int number)
{
	if (number == 0) return 1; // 如果数字为0，则长度为1(较特殊情况)
	int digits = 0;
	while (number > 0)
	{
		digits++;
		number /= 10;
	}
	return digits;
}
int CalculateNumLength(Node* head)
{
	int numLength = 0;
	while (head != nullptr)
	{
		numLength += CountDigits(head->data); // 累加每个节点数据的数字长度
		head = head->next;
	}
	return numLength;
}
void BL(Node*& head, int diff)
{
	for (int i = 0; i < diff; i++) //补0数=差距位数
	{
		Node* newNode = new Node{ 0, head }; // 创建值为0的新节点
		head = newNode; // 将新节点设置为头节点
	}
}

void SameLength(Node*& head1, Node*& head2)  //函数用于在链表的头部补零，使两个链表的长度相等
{
	int len1, len2;
	len1 = ListLength(head1);
	len2 = ListLength(head2);
	int numLength1 = CalculateNumLength(head1);
	int numLength2 = CalculateNumLength(head2);
	int diff = abs(numLength1 - numLength2);
	if (numLength1 < numLength2)
	{
		BL(head1, diff); // 如果链表1较短，则在其前面补零
	}
	else if (numLength2 < numLength1)
	{
		BL(head2, diff); // 如果链表2较短，则在其前面补零
	}
}




int FindBigger(Node* head1, Node* head2)  //从头结点开始比较两个链表的大小
{
	SameLength(head1, head2);
	while (head1 != nullptr && head2 != nullptr) //从头开始比较，如果相等那么比较他们各自的下一位
	{
		if (head1->data > head2->data)
		{
			return 1; //链表1(头指针为head1的链表)更大
		}
		if (head1->data < head2->data)
		{
			return 2;//链表2(头指针为head2的链表)更大
		}
		head1 = head1->next;
		head2 = head2->next;
	}
    return 3;//链表1、2完全相等
}


Node* getTheList(string s)
{
	bool isNegative1 = false;
	bool isNegative2 = false;
	Node* head = nullptr;
	for (char c : s) //是一个范围基于的循环（range-based for loop），它用于遍历字符串 s 中的每个字符。在这个循环中，c 代表了 s 中的当前字符
	{
		if (c != ','&&c!='-'&&c!='\12') // 忽略逗号和负号
		{
			int num = c - '0'; // 将字符转换为整数
			addEnd(head, num); // 在链表后面添加新节点
		}
	}
	return head;
}

Node* change(Node* head)        //将处理完备的链表逆序用于送入加减算法中
{
	Node* pre = nullptr;
	Node* s = head;
	Node* next = nullptr;
	while (s != nullptr)
	{
		next = s->next;//这一步是在更改当前节点的next指针之前，先保存下一个节点的地址。这样做是为了在更改指针指向后仍能找到原链表的下一个节点。
		s->next = pre;//这一步将当前节点的next指针指向前一个节点，实现了反转。[在第一次迭代时，prev是nullptr，这意味着链表的第一个节点将成为逆序后链表的最后一个节点。]
		pre = s; //将prev移动到当前节点，因为在下一次迭代中，当前节点将成为下一个节点的前一个节点。
		s = next;//同上,将s移动到下一个节点
	}
	head = pre;
	return head;
}

Node* Add(Node* head1, Node* head2)
{
	SameLength(head1, head2);
	Node* head3 = nullptr;
	Node* head4 = nullptr;
	head3 = change(head1);
	head4 = change(head2);//将两组链表分别逆序，他们新的头指针为head3,head4.准备加法
	//此时，一开始在头节点前插入的0/最大位变为了末位、而从首位开始则是最小位、次小位
	Node* current1 = nullptr;
	Node* current2 = nullptr;
	current1 = head3;
	current2 = head4;
	int jw = 0;        //定义并初始化存储进位数据jw,这个数据显然不会超过1
	Node* new_head = nullptr;
	while (current1 != nullptr || current2 != nullptr)
	{
		int sum = jw; // 开始时加上前一次的进位
		if (current1 != nullptr)
		{
			sum += current1->data;
			current1 = current1->next;
		}
		if (current2 != nullptr)
		{
			sum += current2->data;
			current2 = current2->next;
		}
		jw = sum / 10; // 计算新的进位
		int n = sum % 10; // 计算当前位的值
		addEnd(new_head, n); // 在结果链表末尾添加新节点
	}
	if (jw > 0) // 检查最后是否有剩余进位
	{
		addEnd(new_head, jw); // 在结果链表末尾添加存储剩余进位的新节点
	}
	return change(new_head); // 将结果链表逆序回来，并返回新头指针
}

Node* DeleteFrontZero(Node* head)
{
	Node* newhead = change(head);
	while (newhead!=nullptr && newhead->data == 0)
	{
		Node* prev = newhead;
		newhead = newhead->next;
		delete prev;
	}
	return newhead; //他返回的是：传入链表先逆序后删除前导0的结果链表
}
Node* Minus(Node* head1, Node* head2)
{
	SameLength(head1, head2);
	int X = FindBigger(head1, head2); //X=1时,链表1大于链表2，=2时反之，=3时相等
	Node* head3 = change(head1);
	Node* head4 = change(head2);
	Node* current1 = head3;
	Node* current2 = head4;
	Node* new_head = nullptr;
	bool isNegative = false; //[重要]它判断结果是否为负数
	if (X == 1)
	{
		int n = 0;
		int jw = 0;//借位
		while (current1 != nullptr)
		{
			if (jw == 0)
			{
				if (current1->data - current2->data < 0)
				{
					jw = 1;
					n = current1->data + 10 - current2->data;
					addEnd(new_head, n);
				}
				if (current1->data - current2->data >= 0)
				{
					jw = 0;
					n = current1->data - current2->data;
					addEnd(new_head, n);
				}
			}
			else if (jw == 1)
			{
				if (current1->data - 1 - current2->data < 0)
				{
					jw = 1;
					n = current1->data - 1 + 10 - current2->data;
					addEnd
					
					
					(new_head, n);
				}
				if (current1->data - 1 - current2->data >= 0)
				{
					jw = 0;
					n = current1->data - 1 - current2->data;
					addEnd(new_head, n);
				}
			}
			current1 = current1->next;
			current2 = current2->next;
		}
		//在while循环结束之后，我们会得到一个逆序的结果链表(它的头指针为new_head)
		//现在,我们需要考虑删除前导0.逆序，在读取到他的第一个非0节点前删除所有节点.
		Node* final_head=DeleteFrontZero(new_head);
		return final_head;
	}
	if (X == 2)//这代表结果是负数（小数减大数）
	{
		isNegative = true;
		int n = 0;
		int jw = 0;//借位
		while (current2 != nullptr)
		{
			if (jw == 0)
			{
				if (current2->data - current1->data < 0)
				{
					jw = 1;
					n = current2->data + 10 - current1->data;
					addEnd(new_head, n);
				}
				if (current2->data - current1->data >= 0)
				{
					jw = 0;
					n = current2->data - current1->data;
					addEnd(new_head, n);
				}
			}
			else if (jw == 1)
			{
				if (current2->data - 1 - current1->data < 0)
				{
					jw = 1;
					n = current2->data - 1 + 10 - current1->data;
					addEnd(new_head, n);
				}
				if (current2->data - 1 - current1->data >= 0)
				{
					jw = 0;
					n = current2->data - 1 - current1->data;
					addEnd(new_head, n);
				}
			}
			current2 = current2->next;
			current1 = current1->next;
		}
		//在while循环结束之后，我们会得到一个逆序的结果链表(它的头指针为new_head)
		//现在,我们需要考虑删除前导0.逆序，在读取到他的第一个非0节点前删除所有节点.
		Node* final_head = DeleteFrontZero(new_head);
		return final_head;
	}
	if (X == 3)
	{
		addEnd(new_head, 0);
	}
}

bool This_isNegative(string s)
{
	for (char c : s)
	{
		if (c == '-')
		{
			return true;
		}
	}
	return false;
}
void freeList(Node* head) 
{
	Node* p = head;
	while (p != NULL)
	{
		Node* temp = p;
		p = p->next;
		free(temp);
	}
}


int main()
{
	int N = 0;
	while (cin >> N)
	{
		for (int i = 0; i < N; i++)
		{
			char calculate_way = '0';
			string input1, input2;
			Node* head1 = nullptr;
			Node* head2 = nullptr;
			cin >> calculate_way >> input1 >> input2;
			head1 = getTheList(input1);
			head2 = getTheList(input2);
			bool isNegative1 = This_isNegative(input1);
			bool isNegative2 = This_isNegative(input2);
			if (calculate_way == '+')
			{
				bool A = (isNegative1 == true && isNegative2 == true && FindBigger(head1, head2) == 1);//两数均为负数，为负.add
				bool A1 = (isNegative1 == true && isNegative2 == true && FindBigger(head1, head2) == 2);//两数均为负数，为负.add

				bool B = (isNegative1 == true && isNegative2 == false && FindBigger(head1, head2) == 1);//大负数加小正数，为负.minus
				bool B1 = (isNegative1 == true && isNegative2 == false && FindBigger(head1, head2) == 2);//小负数加大正数，为正.minus
				bool C = (isNegative1 == false && isNegative2 == true && FindBigger(head1, head2) == 2);//小正数加大负数，为负.minus
				bool C1 = (isNegative1 == false && isNegative2 == true && FindBigger(head1, head2) == 1);//大正数加小负数，为正.minus
				bool D = (isNegative1 == false && isNegative2 == false);//两数均为正数，为正.add
				if (A || A1)
				{
					Node* head3 = Add(head1, head2);
					cout << "-";
					ShowList(head3);
					//cout << "+A|A1" << endl;
				}
				if (B || C)
				{
					Node* head3 = Minus(head1, head2);
					cout << "-";
					ShowList(head3);
					//cout << "+B|C" << endl;
				}
				if (B1 || C1)
				{
					Node* head3 = Minus(head1, head2);
					ShowList(head3);
					//cout << "+B1|C1" << endl;
				}
				if (D)
				{
					Node* head3 = Add(head1, head2);
					ShowList(head3);
					//cout << "+D" << endl;
				}
			}
			if (calculate_way == '-')
			{
				bool A = (isNegative1 == true && isNegative2 == true && FindBigger(head1, head2) == 2);//小负数减大负数，为正.minus
				bool A1 = (isNegative1 == true && isNegative2 == true && FindBigger(head1, head2) == 1);//大负数减小负数，为负.minus-
				bool B = (isNegative1 == false && isNegative2 == false && FindBigger(head1, head2) == 1);//大正数减小正数，为正.minus
				bool B1 = (isNegative1 == false && isNegative2 == false && FindBigger(head1, head2) == 2);//小正数减大正数，为负.minus-

				bool C = (isNegative1 == false && isNegative2 == true && FindBigger(head1, head2) == 2);//小正数减大负数，为正 add
				bool Ca = (isNegative1 == false && isNegative2 == true && FindBigger(head1, head2) == 1);//大正数减小负数，显然为正 add

				bool C1 = (isNegative1 == true && isNegative2 == false && FindBigger(head1, head2) == 1);//大负数减小正数，为负 add
				bool C1a = (isNegative1 == true && isNegative2 == false && FindBigger(head1, head2) == 2);//小负数减大正数，显然为负 add
				if (A || B )
				{
					Node* head3 = Minus(head1, head2);
					ShowList(head3);
					//cout << "-A|B|Ca" << endl;
				}
				if (A1 || B1)
				{
					Node* head3 = Minus(head1, head2);
					cout << "-";
					ShowList(head3);
					//cout << "-A1||B1" << endl;
				}
				if (C||Ca)
				{
					Node* head3 = Add(head1, head2);
					ShowList(head3);
					//cout << "-C||C1||C1a" << endl;
				}
				if (C1 || C1a)
				{
					Node* head3 = Add(head1, head2);
					cout << "-";
					ShowList(head3);
				}
				freeList(head1);
				freeList(head2);
			}
		}
		/*string s1, s2;
		while (cin >> s1 >> s2)
		{
			Node* head1 = getTheList(s1);
			Node* head2 = getTheList(s2);
			cout << "获取的链表:" << endl;
			ShowList(head1);
			ShowList(head2);
			SameLength(head1, head2);
			cout << "补0的链表:" << endl;
			ShowList(head1);
			ShowList(head2);
			cout << "倒置后的链表:" << endl;
			Node* head3 =change(head1);
			Node* head4 =change(head2);
			ShowList(head3);
			ShowList(head4);//截至目前，getTheList ShowList SameLength change函数都是正确的
			cout << "加减算法后的链表:" << endl;
			Node*head5=Minus(head1, head2);
			ShowList(head5);
		}*/
		return 0;
	}
}
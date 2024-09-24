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

void insert(Node*& head,int num)       //������ͷ������һ���½ڵ㣬Ȼ�����ִ洢���½ڵ���;
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


void addEnd(Node*& head, int num)   //��һ�������ĩ���������num
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
Node* InsertEnd(Node* head, int data)    //���Ĺ�����addEnd���ƣ������ķ���ֵ��һ�������ͷָ����ͷ��㣩����getTheList���
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

void ShowList(Node* head)               //��������
{
	/*if (resultIsNegative)
	{
		cout << "-";
	}*/
	if (head == nullptr)
		return;
	int count = 0; //�����ڵ�
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
{           //��ȡ����ĳ��ȣ�����ֵΪ������
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
	if (number == 0) return 1; // �������Ϊ0���򳤶�Ϊ1(���������)
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
		numLength += CountDigits(head->data); // �ۼ�ÿ���ڵ����ݵ����ֳ���
		head = head->next;
	}
	return numLength;
}
void BL(Node*& head, int diff)
{
	for (int i = 0; i < diff; i++) //��0��=���λ��
	{
		Node* newNode = new Node{ 0, head }; // ����ֵΪ0���½ڵ�
		head = newNode; // ���½ڵ�����Ϊͷ�ڵ�
	}
}

void SameLength(Node*& head1, Node*& head2)  //���������������ͷ�����㣬ʹ��������ĳ������
{
	int len1, len2;
	len1 = ListLength(head1);
	len2 = ListLength(head2);
	int numLength1 = CalculateNumLength(head1);
	int numLength2 = CalculateNumLength(head2);
	int diff = abs(numLength1 - numLength2);
	if (numLength1 < numLength2)
	{
		BL(head1, diff); // �������1�϶̣�������ǰ�油��
	}
	else if (numLength2 < numLength1)
	{
		BL(head2, diff); // �������2�϶̣�������ǰ�油��
	}
}




int FindBigger(Node* head1, Node* head2)  //��ͷ��㿪ʼ�Ƚ���������Ĵ�С
{
	SameLength(head1, head2);
	while (head1 != nullptr && head2 != nullptr) //��ͷ��ʼ�Ƚϣ���������ô�Ƚ����Ǹ��Ե���һλ
	{
		if (head1->data > head2->data)
		{
			return 1; //����1(ͷָ��Ϊhead1������)����
		}
		if (head1->data < head2->data)
		{
			return 2;//����2(ͷָ��Ϊhead2������)����
		}
		head1 = head1->next;
		head2 = head2->next;
	}
    return 3;//����1��2��ȫ���
}


Node* getTheList(string s)
{
	bool isNegative1 = false;
	bool isNegative2 = false;
	Node* head = nullptr;
	for (char c : s) //��һ����Χ���ڵ�ѭ����range-based for loop���������ڱ����ַ��� s �е�ÿ���ַ��������ѭ���У�c ������ s �еĵ�ǰ�ַ�
	{
		if (c != ','&&c!='-'&&c!='\12') // ���Զ��ź͸���
		{
			int num = c - '0'; // ���ַ�ת��Ϊ����
			addEnd(head, num); // �������������½ڵ�
		}
	}
	return head;
}

Node* change(Node* head)        //�������걸������������������Ӽ��㷨��
{
	Node* pre = nullptr;
	Node* s = head;
	Node* next = nullptr;
	while (s != nullptr)
	{
		next = s->next;//��һ�����ڸ��ĵ�ǰ�ڵ��nextָ��֮ǰ���ȱ�����һ���ڵ�ĵ�ַ����������Ϊ���ڸ���ָ��ָ��������ҵ�ԭ�������һ���ڵ㡣
		s->next = pre;//��һ������ǰ�ڵ��nextָ��ָ��ǰһ���ڵ㣬ʵ���˷�ת��[�ڵ�һ�ε���ʱ��prev��nullptr������ζ������ĵ�һ���ڵ㽫��Ϊ�������������һ���ڵ㡣]
		pre = s; //��prev�ƶ�����ǰ�ڵ㣬��Ϊ����һ�ε����У���ǰ�ڵ㽫��Ϊ��һ���ڵ��ǰһ���ڵ㡣
		s = next;//ͬ��,��s�ƶ�����һ���ڵ�
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
	head4 = change(head2);//����������ֱ����������µ�ͷָ��Ϊhead3,head4.׼���ӷ�
	//��ʱ��һ��ʼ��ͷ�ڵ�ǰ�����0/���λ��Ϊ��ĩλ��������λ��ʼ������Сλ����Сλ
	Node* current1 = nullptr;
	Node* current2 = nullptr;
	current1 = head3;
	current2 = head4;
	int jw = 0;        //���岢��ʼ���洢��λ����jw,���������Ȼ���ᳬ��1
	Node* new_head = nullptr;
	while (current1 != nullptr || current2 != nullptr)
	{
		int sum = jw; // ��ʼʱ����ǰһ�εĽ�λ
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
		jw = sum / 10; // �����µĽ�λ
		int n = sum % 10; // ���㵱ǰλ��ֵ
		addEnd(new_head, n); // �ڽ������ĩβ����½ڵ�
	}
	if (jw > 0) // �������Ƿ���ʣ���λ
	{
		addEnd(new_head, jw); // �ڽ������ĩβ��Ӵ洢ʣ���λ���½ڵ�
	}
	return change(new_head); // ��������������������������ͷָ��
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
	return newhead; //�����ص��ǣ����������������ɾ��ǰ��0�Ľ������
}
Node* Minus(Node* head1, Node* head2)
{
	SameLength(head1, head2);
	int X = FindBigger(head1, head2); //X=1ʱ,����1��������2��=2ʱ��֮��=3ʱ���
	Node* head3 = change(head1);
	Node* head4 = change(head2);
	Node* current1 = head3;
	Node* current2 = head4;
	Node* new_head = nullptr;
	bool isNegative = false; //[��Ҫ]���жϽ���Ƿ�Ϊ����
	if (X == 1)
	{
		int n = 0;
		int jw = 0;//��λ
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
		//��whileѭ������֮�����ǻ�õ�һ������Ľ������(����ͷָ��Ϊnew_head)
		//����,������Ҫ����ɾ��ǰ��0.�����ڶ�ȡ�����ĵ�һ����0�ڵ�ǰɾ�����нڵ�.
		Node* final_head=DeleteFrontZero(new_head);
		return final_head;
	}
	if (X == 2)//��������Ǹ�����С����������
	{
		isNegative = true;
		int n = 0;
		int jw = 0;//��λ
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
		//��whileѭ������֮�����ǻ�õ�һ������Ľ������(����ͷָ��Ϊnew_head)
		//����,������Ҫ����ɾ��ǰ��0.�����ڶ�ȡ�����ĵ�һ����0�ڵ�ǰɾ�����нڵ�.
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
				bool A = (isNegative1 == true && isNegative2 == true && FindBigger(head1, head2) == 1);//������Ϊ������Ϊ��.add
				bool A1 = (isNegative1 == true && isNegative2 == true && FindBigger(head1, head2) == 2);//������Ϊ������Ϊ��.add

				bool B = (isNegative1 == true && isNegative2 == false && FindBigger(head1, head2) == 1);//������С������Ϊ��.minus
				bool B1 = (isNegative1 == true && isNegative2 == false && FindBigger(head1, head2) == 2);//С�����Ӵ�������Ϊ��.minus
				bool C = (isNegative1 == false && isNegative2 == true && FindBigger(head1, head2) == 2);//С�����Ӵ�����Ϊ��.minus
				bool C1 = (isNegative1 == false && isNegative2 == true && FindBigger(head1, head2) == 1);//��������С������Ϊ��.minus
				bool D = (isNegative1 == false && isNegative2 == false);//������Ϊ������Ϊ��.add
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
				bool A = (isNegative1 == true && isNegative2 == true && FindBigger(head1, head2) == 2);//С������������Ϊ��.minus
				bool A1 = (isNegative1 == true && isNegative2 == true && FindBigger(head1, head2) == 1);//������С������Ϊ��.minus-
				bool B = (isNegative1 == false && isNegative2 == false && FindBigger(head1, head2) == 1);//��������С������Ϊ��.minus
				bool B1 = (isNegative1 == false && isNegative2 == false && FindBigger(head1, head2) == 2);//С��������������Ϊ��.minus-

				bool C = (isNegative1 == false && isNegative2 == true && FindBigger(head1, head2) == 2);//С������������Ϊ�� add
				bool Ca = (isNegative1 == false && isNegative2 == true && FindBigger(head1, head2) == 1);//��������С��������ȻΪ�� add

				bool C1 = (isNegative1 == true && isNegative2 == false && FindBigger(head1, head2) == 1);//������С������Ϊ�� add
				bool C1a = (isNegative1 == true && isNegative2 == false && FindBigger(head1, head2) == 2);//С����������������ȻΪ�� add
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
			cout << "��ȡ������:" << endl;
			ShowList(head1);
			ShowList(head2);
			SameLength(head1, head2);
			cout << "��0������:" << endl;
			ShowList(head1);
			ShowList(head2);
			cout << "���ú������:" << endl;
			Node* head3 =change(head1);
			Node* head4 =change(head2);
			ShowList(head3);
			ShowList(head4);//����Ŀǰ��getTheList ShowList SameLength change����������ȷ��
			cout << "�Ӽ��㷨�������:" << endl;
			Node*head5=Minus(head1, head2);
			ShowList(head5);
		}*/
		return 0;
	}
}
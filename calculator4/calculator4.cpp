#include <iostream>
using namespace std;
template <class T>
struct stack{
	T data;
	stack* next;
};
template<class T>
void stack_init(stack<T>* elem, T d){
	elem->data=d;
	elem->next=NULL;
}
template<class T>
void list_print(stack<T>* first) {
	stack<T>* cur = first;
	while (cur != NULL) {
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;
}
template<class T>
stack<T>* push(stack<T>* first, T lastelem){
	stack<T>* newelem = new stack<T>;
	stack_init (newelem, lastelem);
	if (first == NULL ){
		return newelem;
	}
	stack<T>* cur = first;
	while(cur -> next != NULL){
		cur = cur-> next;
	}
	cur->next = newelem;
	return first;

}
template<class T>
stack<T>* pop(stack<T>* list){
	stack<T>* cur = list;
	if(cur->next==NULL){
		cur=NULL;
		return cur;
	}
	while (cur->next->next!=NULL){
		cur=cur->next;
	}
	cur->next = NULL;
	return list;
}
template<class T>
T pick(stack<T>* list){
	stack<T>*cur = list;
	if (cur->next!=NULL){
		while (cur->next!=NULL){
			cur = cur->next;
		}
	}
	return cur->data;
}


int OPResult(const int left, const char op, const int right) {
	int result = 0;
	switch (op) {
		case '*':
			result = left * right;
			break;
		case '+':
			result = left + right;
			break;
		case '-':
			result = left - right;
			break;
		case '/':
			result = left / right;
			break;
	}
	return result;
}

int FindNum( int& i, char* a){
	int ch = 0;
	int numb = 0;
	int razr = 1;
	while (a[i]>='0' ){
		ch = a[i] - '0';
		numb= numb*razr+ch;
		razr = 0xA;
		i++;
	}
	return numb;
}
int Prior_Op(char el, int & prior_op){
	switch (el) {
				case ')':
					return prior_op = 4;	
				case '(':
					return prior_op = 1;	
				case '*':
				case '/':
					return prior_op = 3;
				case '+':
				case '-':
					return prior_op = 2;
	}
}

void FindOperator (int &prior_op, int &prior_op2, stack <int>* &myStack2, stack <char>* &myStack1, char*a , int& i, int result){
	if(prior_op>prior_op2 && prior_op!=4 || prior_op == 1){myStack1 = push(myStack1, a[i]);
	}
	if(prior_op<=prior_op2 && prior_op != 1 || prior_op==4){
		if(myStack1!=NULL){
			int b = pick(myStack2);
			myStack2 = pop(myStack2);
			int a = pick(myStack2);
			myStack2 = pop(myStack2);
			result = OPResult(a , pick(myStack1), b);
		}
		myStack2=push(myStack2,result);
		if(myStack1!=NULL){myStack1=pop(myStack1);
		}
		if(myStack1!=NULL){
			if(pick(myStack1)=='+'|| pick(myStack1)=='-'){prior_op2 = 2;}
			if(pick(myStack1)=='*'|| pick(myStack1)=='/'){prior_op2 = 3;}
			if(pick(myStack1)==')'){prior_op2 = 4;}
			if(pick(myStack1)=='('){prior_op2 = 1;}
			prior_op=prior_op2;
			i--;
			if(a[i+1]==')' && pick(myStack1)=='(' ){
				myStack1=pop(myStack1);
				prior_op=0;
				prior_op2 = prior_op;
				i++;
			}
		}
	}
}
void FinishCheck( stack<char>* &myStack1, stack<int>* &myStack2){
	int result = 0;
	if(myStack1!=NULL){
		int b = pick(myStack2);
		myStack2 = pop(myStack2);
		int a = pick(myStack2);
		myStack2 = pop(myStack2);
		result = OPResult( a , pick(myStack1), b);
		myStack2=push(myStack2,result);
		myStack1=pop(myStack1);
	}
}
int main(){
	int countStack1 = 0;
	int memCountSt1 = 0;
	stack<char>* myStack1=NULL;
	stack<int>* myStack2=NULL;
	char *a = "( 9+(3+1))-  6";
	const int n = strlen(a);
	int prior_op = 0; 
	int prior_op2 = 0;
	int result = 0;
	for(int i=0; i<n; i++){
		if (a[i] == 0x20){ while(a[i]==0x20){ i++;
		}
		}
		if(a[i] >= '0'){
			int numb = FindNum(i, a);
			myStack2 = push(myStack2,numb);
			prior_op2 = prior_op;
		}
		if(a[i]<='/'){
			Prior_Op(a[i], prior_op);	
			FindOperator (prior_op, prior_op2, myStack2, myStack1, a , i, result);
		}
		else{
			cout<< "There are some bugs!!! " << "  ";
			break;
		}
	}
	FinishCheck(myStack1 , myStack2 );		
	cout<< " the answer is  -   ";
	list_print(myStack2);
	system("pause");
	return 0;
}
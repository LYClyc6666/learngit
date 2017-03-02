#include<stdio.h>
#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量
#define LISTINCLUMENT 10 //线性表存储空间的分配增量
typedef struct {
	ElemType *elem; //存储空间基址
	int length;  //当前长度
	int listsize; //当前分配的存储容量(以sizeof(ElemType)为单位)
}SqList;

///////////////////////////////////////////
void union(List &La,List Lb) {
	//将所有线性表Lb中但是不在La中的数据元素插入到La中
	La_len = ListLength(La);
	Lb_len = ListLength(Lb); //求线性表的长度
	for(i=1;i<=Lb_len;i++) {
		GetElem(Lb,i,e); //取Lb中的第i个数据元素赋给e
		if(!LocateElem(La,e,equal))
		 ListInsert(La,++La_len,e)  //La中不存在和e相同的数据元素,则插入之
	}
}  //union

/*************算法2.1*********************/
///////////////////////////////////////////
void MergeList(List La,List Lb,List &Lc) {
	//已知线性表La和Lb中的数据元素按值非递减排列
	//归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列
	InitList(Lc);
	i=j=1;k=0;
	La_len =ListLength(La);
	Lb_len = ListLength(Lb);
	while((i<=La_len)&&(j<=La_len)) { //La和Lb均非空
		GetElem(La,i,ai);
		GetElem(Lb,j,bj);
		if(ai<=bj) {
			ListInsert(Lc,++k,ai);
			i++;
		} else {
			ListInsert(Lc,++k,bj);
		}
		while(i<=La_len) {
			GetElem(La,i,ai);
			ListInsert(Lc,++k,ai);
		}
		while(i<=Lb_len) {
			GetElem(Lb,i,bj);
			ListInsert(Lc,++k,aj);
		}
	
	} //MergeList

/*************算法2.2*********************/
	///////////////////////////////////////

	Status InitList_Sq(SqList &L) {
		//构造一个空的线性表L
		L.elem = (ElemType *)malloc(LISTINCLUMENT*sizeof(ElemType));
		if(!L.elem) exit(OVERFLOW); //存储分配失败
		L.length = 0; //空表长度为0
		L.listsize = LIST_INIT_SIZE; //初始化存储容量
		return ok;

	} //InitList_Sq


/*************算法2.3*********************/	

/////////////////////////////////////////
	Status ListInsert_Sq(SqList &L,int i,ElemType e) {
		//在顺序线性表L中第i个位置之前插入新元素e
		//i的合法值为1<=i<=ListLength_Sq(L) + 1
		if(i<1||i>L.length+1)
			return ERROR; //i值不合法
		if(L.length>=L.listsize) { //当前存储空间已满,增加分配
			newbase = (ElemType *)
			realloc(L.elem,(L.listsize+LISTINCLUMENT)*sizeof(ElemType));
			if(!newbase) 
				exit(OVERFLOW); //存储分配失败
			L.elem = newbase; //新基址
			L.listsize +=LISTINCLUMENT; //增加存储容量

		}
		q = &(L.elem[i-1]); //q为插入位置
		for(p=&(L.elem[L.length-1]);p>=q;--p)
			*(p+1) = *p; //插入位置及之后的元素右移
		*q=e; //插入e
		++L.length; //边长增1
		return OK;
	} //ListInsert_Sq

/*************算法2.4*********************/

//////////////////////////////////////////	


	Status ListDelete_Sq(SqList &L,int i,ElemType e) {
		//在顺序线性表L中删除第i个元素,并用e返回其值
		//i的合法值为1<=i<=ListLength_Sq(L)
		if(i<1||i>L.length+1)
			return ERROR; //i值不合法
		
		p = &(L.elem[i-1]); //p为被删除元素的位置
		e=*p;//被删除元素的值赋给e
		q=L.elem+L.length-1; //表尾元素的位置
		for(++p;p<=q;++p)
			*(p-1) =*p;//被删除元素之后的位置左移
		--L.length;
		return OK;
		
	} //ListDelete_Sq


/*************算法2.5*********************/

	//////////////////////////////////////////	

	int LocateElem_Sq(SqList L,ElemType e,
		Status (*compare)(ElemType,ElemType)) {
		//在顺序线性表L中查找第一个值与e满足compare()
		i=1; //i的初始值为第一个元素的位序
		p=L.elem; //p的初值为第一个元素的存储位置
		while(i<=L.length&&!(*compare)(*p++,e))
			++i;
		if(i<=L.length)
			return i;
		else
			return 0;
	} //LocateElem_Sq


/*************算法2.6*********************/



	
/////////////////////////////////////////

void MergeList(List La,List Lb,List &Lc) {
	//已知线性表La和Lb中的数据元素按值非递减排列
	//归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列

	pa = La.elem;
	pb=Lb.elem;
	Lc.listsize =Lc.length=La.length + Lb.length;
	pc=Lc.elem=(ElemType*)malloc(Lc.listsize*sizeof(ElemType));
	if(!Lc.elem)
		exit(OVERFLOW); //存储分配失败
	pa_last = La.elem + La.length -1;
	pb_last = Lb.elem + Lb.length -1;
	while(pa<=pa_last&&pb<=pb_last) { //归并
		if(*pa <=*pb)
			*pc++=*pa++;
		else *pc++=*pb++;
	}
	while(pa<=pa_last) *pc++ =*pa++; //插入La的剩余元素
	while(pb<=pb_last) *pc++ =*pb++; //插入Lb的剩余元素

}

/*************算法2.7*********************/
//////////////////////////////////////////

	Status GetElem_L(LinkList,int i,ElemType &e) {
		//L为带头结点的单链表的头指针
		//当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR
		p =L->next;
		j=1; //初始化,p指向第一个结点,j为计数器
		while(p&&j<i) { //顺指针向后查找,直到p指向第i个元素或者p为空
			p =p->next;
			++j;
		}
		if(!p||j>i)
			return ERROR; //第i个元素不存在
		e=p->data;
		return OK;
	} //GetElem_L


/*************算法2.8*********************/
/////////////////////////////////////////

	Status ListInsert_L(LinkList &L,int i,ElemType e) {
		//在带头结点的单链线性表L中第i个位置之前插入元素e
		p =L;
		j=0;
		while(p&&j<i-1) {
			p=p->next;
			++j;
		} //寻找第i-1个结点
		if(!p||j>i-1)
			return ERROR; //i小于1或者大于表长+1
		s=(LinkList) malloc(sizeof(LNode)); //生成新结点
		s->data=e;
		s->next=p->next; //插入L中
		p->next = s;
		return OK;
	}

/*************算法2.9*********************/
/////////////////////////////////////////

	Status ListDelete_L(LinkList &L,int i,ElemType &e) {
		//在带头结点的单链线性表L中,删除第i个元素,并由e返回其值
		p=L;
		j=0;
		while(p->next && j<i-1) { //寻找第i个结点,并令p指向其前趋
			p->next;
			++j;

		}
		if(!(p->next)||j>i-1)
			return ERROR; //删除位置不合理
		q = p->next;
		p->next = q->next; //删除并释放结点
		e =q->data;
		free(q);
		return OK;
	} //ListDelete_L

/*************算法2.10*********************/
/////////////////////////////////////////

	void CreateList_L(LinkList &L,int n) {
		//逆位序输出n个元素的值,建立带表头结点的单链线性表L
		L =(LinkList) malloc(sizeof (LNode));
		L->next =NULL; //先建立一个带头结点的单链表
		for(i=n;i>0;--i) {
			p=(LinkList) malloc(sizeof(LNode)); //生成新结点
			scanf(&p->data);  //输入元素值
			p->next =L->next;
			L->next =p;  //插入到表头
		}
	} //CreateList_L




/*************算法2.11*********************/
/////////////////////////////////////////

	void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc) {
		//已知单链线性表La和Lb的元素按值非递减排列
		//归并La和Lb得到新的单链线性表Lc,Lc的元素也按值非递减排列
		pa =La->next;
		pb =Lb->next;
		Lc=pc=La;  //用La的头结点作为Lc的头结点
		while(pa&&pb) {
			if(pa->data<=pb->data) {
				pc->next =pa;
				pc=pa;
				pa=pa->next;
			} else {
				pc->next =pb;
				pc=pb;
				pb=pb->next;
			}
			pc->next =pa?pa:pb; //插入剩余字段
			free(Lb);  //释放Lb的头结点
		}  //MergeList_L
	}



/*************算法2.12*********************/
/////////////////////////////////////////


///////////////////////////////////////

//-----------线性表的静态单链表存储结构----------------------//
	#define MAXSIZE 1000 //链表的最大长度
	typedef struct {
		ElemType data;
		int cur;

	}component,SLinkList[MAXSIZE];



///////////////////////////////////////
	int LocateElem_SL(SLinkList S,ElemType e) {
		//在静态单链线性表L中查找第一个值为e的元素
		//若找到,则返回它在L中的位序,否则返回0
		i=S[0].cur; //i指示表中的第一个结点
		while(i&&S[i].data!=e)
			i=S[i].cur;//在链表中顺链查找
		return i;


	}//LocateElem_SL




/*************算法2.13*********************/
/////////////////////////////////////////

	void InitSpace_SL(SLinkList &space) {
		//将一维数组space中各分量链接成一个备用链表,space[0].cur为头指针
		//"0"表示空指针
		for(int i=0;i<MAXSIZE-1;i++)
			space[i].cur =i+1;
		space[MAXSIZE -1].cur = 0;
	}


/*************算法2.14*********************/
/////////////////////////////////////////	

	int Malloc_SL(SLinkList &space) {
		//若备用空间链表非空,则返回分配的结点下标,否则返回0
		i=space[0].cur;
		if(space[0].cur)
			space[0].cur=space[i].cur;
		return i;
	}

/*************算法2.15*********************/
/////////////////////////////////////////

	void Free_SL(SLinkList &space,int k) {
		//将下标为k的空闲结点回收到备用链表
		space[k].cur=space[0].cur;
		space[0].cur=k;
	}

/*************算法2.16*********************/
/////////////////////////////////////////	

	void difference(SLinkList &space,int &S) {
		//依次输入集合A和B的元素,在一维数组space中建立表示集合(A-B)(B-A)
		//的静态链表,S为其头指针.假设备用空间足够大,space[0].cur为其头指针
		InitSpace_SL(space); //初始化备用空间
		S=Malloc_SL(space);  //生成S的头结点
		r=S; //r指向s的当前最后结点
		scanf(m,n); //输入A和B的元素个数
		for(j=0;j<=m;++j) { //建立集合A的链表
			i=Malloc_SL(space);  //分配结点
			scanf(space[i].data); 输入A的元素值
			space[r].cur=i;
			r=i; //插入到表尾
			space[r].cur=0; //尾结点的指针为空
		}
		for(j=1;j<=n;++j) { //依次输入B的元素,若不在当前表中,则插入,否则删除
			scanf(b);
			p=S;
			k=space[S].cur;  //k指向集合A的第一个结点
			while(k!=space[r].cur&&space[k].data!=b) { //在当前表中查找
				p=k;
				k=space[k].cur;

			} //while
			if(k==space[r].cur) { //当前表中不存在该元素,插入在r所指结点
				//之后,且r的位置不变
				i=Malloc_SL(space);
				space[i].data = b;
				space[i].cur = space[r].cur;
				space[r].cur =i;

			} //if
			else { //该元素已在表中,删除之
				space[p].cur =space[k].cur;
				Free_SL(space,k);
				if(r==k)
					r=p; //若删除的是r所指结点,则需修改尾指针

			} //else

		} //for
	} //difference




/*************算法2.17*********************/
/////////////////////////////////////////	

	//-----------线性表的双向链表的存储结构-----------------
	typedef struct DuLNode {
		ElemType data;
		struct DuLNode *prior;
		struct DuLNode *next;
	}DuLNode,*DuLinkList;

	////////////////////////////////
	Status ListInsert_DuL(DuLinkList &L,int i,ElemType e) {
		//在带头结点的双链线性表L中第i个位置之前插入元素e
		//i的表长为1<=i<=表长+1
		if(!(p=GetElemP_DuL(L,i))) //在L中确定插入位置
			return ERROR; //P==NULL,即插入位置不合法
		if(!(s=(DuLinkList)malloc(sizeof(DuLNode))))
			return ERROR;
		s->data = e;
		s->prior  = p->prior;
		p->prior->next =s;
		s->next =p;
		p->prior =s;
		return OK;
	}




/*************算法2.18*********************/
/////////////////////////////////////////

	Status ListInsert_DuL(DuLinkList &L,int i,ElemType &e) {
		//在带头结点的双链线性表L中第i个位置之前插入元素e
		//i的表长为1<=i<=表长+1
		if(!(p=GetElemP_DuL(L,i))) //在L中确定第i个元素的位置指针p
			return ERROR; //p=null,即第i个元素不存在
		e=p->data;
		p->prior->data;
		p->prior->next =p->next;
		p->next->prior =p->prior;
		free(p);
		return OK;
	}



/*************算法2.19*********************/
/////////////////////////////////////////

	Status ListInsert_L(LinkList &L,int i,ElemType e) {
		//在带头结点的单链线性表的第i个元素之前插入元素e
		if(!LocatePos(L,i-1,h)) 
			return ERROR; //i值不合法
		if(!MakeNode(s,e))
			return ERROR; //结点存储分配失败
		InsFirst(h,s); //对于从第i个结点开始的链表,第i-1个结点是它的头结点
		return OK;
	} //ListInsert_L



/*************算法2.20*********************/
/////////////////////////////////////////

	Status MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc
		int(*compare)(ElemType,ElemType)) {
		//已知单链线性表La和Lb的元素按值非递减排列
		//归并La和Lb得到新的单链线性表Lc,Lc 的元素也按值非递减排列
		if(!InitList(Lc))
			return ERROR; //存储空间分配失败
		ha = GetHead(La);
		hb = GetHead(Lb);  //ha和hb分别指向La和Lb的头结点
		pa=NextPos(La,ha);
		pb=NextPos(Lb,hb); //pa和hb分别指向La和Lb的当前结点
		while(pa&&pb) { //La和Lb均非空
			a=GetCurElem(pa);
			b=GetCurElem(pb); //a和b为两表中当前比较元素
			if((*compare)(a,b)<=0) { //a<=b
				DelFirst(hb,q);Append(Lc,q);
				pa=NextPos(La,ha);

			} else { //a>b
				DelFirst(hb,q);
				Append(Lc,q);
				pb=NextPos(Lb,hb);

			} //while
			if(pa)
				Append(Lc,pa);  //链接La中剩余字段
			else Append(Lc,pb); //链接Lb中剩余字段
			FreeNode(ha);
			FreeNode(hb);  //释放La和Lb的头结点
			return OK;
		}


	}




/*************算法2.21*********************/
/////////////////////////////////////////


int main()
{
	return 0;
}
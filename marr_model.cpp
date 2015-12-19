#include<iostream>  
  
using namespace std;  

//�û�(��);���飨Ů��
#define USERNUM 5  //�û���Ŀ
#define APNUM 4  //������Ŀ
#define NIL -1  

int GetPositionFromAP(int apArray[APNUM][USERNUM], int ap, int user)  
{  
    for(int i=0; i<USERNUM; i++)  
        if(apArray[ap-1][i] == user)  
            return i;  
    return NIL;  
}  

int getRowLen(int rowArray[USERNUM])
{
	int n=0;
	for(int i=0; i<USERNUM; i++)
		if(rowArray[i]!=0)
			n++;
	return n;
}

int PPLLen(int userArray[USERNUM][APNUM])
{
	int n=0;
	for(int i=0; i<USERNUM; i++)
		for(int j=0; j<APNUM; j++)
		{
			if(userArray[i][j]==0 && (j>=n))
				n=j;
			if(userArray[i][APNUM-1]!=0)
				n=APNUM;
		}
	return n;
}

void ChoosePartener(int userPos, int userArray[USERNUM][APNUM], int apArray[APNUM][USERNUM], int userPerfer[USERNUM], int userStartPos, int apNow[APNUM], int apFinal[APNUM][USERNUM])
{  
    //�û�ѡ���Լ�PPL��������λ�ĵ��飬������������ 
        int perferAP = userArray[userPos][userStartPos];  
        //����õ����ڱ���û�н��ܹ�����������������ܸ��û�������  
        if(apNow[perferAP-1] == NIL)  
        {  
            apNow[perferAP-1] = userPos+1; //���ֵ���������û���
            userPerfer[userPos] = 1;   //�µ����Ϊ����״̬
			apFinal[perferAP-1][userPos] = 1;
        }  
        //����õ����Ѿ��ڱ���ͬĳ�û��������ٴ��յ��¹�������ʱ��
		//���յ���������û���PPL��������յ�������PPL������ߣ�������������û���ͬ���û����������򣬼������ϵ������  
        else  
        {  
            int oldPos = GetPositionFromAP(apArray, perferAP, apNow[perferAP-1]);  
            int newPos = GetPositionFromAP(apArray, perferAP, userPos+1);   
            if(newPos < oldPos)  
            {  //���û������ȶȸ��ߣ�����ѡ���뿪���û������û����� 
				userPerfer[(apNow[perferAP-1])-1] = 0;  //�������ĵ���ָ�����δ����״̬
				apFinal[perferAP-1][(apNow[perferAP-1])-1] = 0;

                apNow[perferAP-1] = userPos+1; //���µ����ʱ�Ĺ����û�			
				userPerfer[userPos] = 1;  //�µ����Ϊ����״̬ 
				apFinal[perferAP-1][userPos] = 1;  
            }  
        }  
}  


int main()  
{  
    int userArray[USERNUM][APNUM] ={{1,2,3},{3,4},{1,3,2},{2,1},{3,2,4,1}};  //�û���PPL  
    int apArray[APNUM][USERNUM] = {{1,3,4,5},{1,4,3,5},{3,5,2,1},{5,2}};  //�����PPL 

	int userState[USERNUM] = {0}; // �û������б���¼ÿ���û��Ƿ��Ѿ��͵�������˹�����һ����һ������������Ϊ1 
	int userPerfer[USERNUM] = {0}; // �����û������б���¼ÿ���û��Ƿ��Ѿ��͵�������˹�����һ����һ������������Ϊ1 
	int userStartPos = 0;// �û���PPLѡ����ţ���ѡ��PPL�еĵڼ�����Ը�������
	int apNow[APNUM] = {NIL,NIL,NIL,NIL}; // ���ֵ�����������ֵ����Ӧ�ķ�����û��������ʼֵ����Ϊ-1����������δ��������ÿ�ֽ������ֵ����ˢ��Ϊ��ʼֵ 
	int apFinal[APNUM][USERNUM] = {{NIL,NIL,NIL,NIL,NIL},{NIL,NIL,NIL,NIL,NIL},{NIL,NIL,NIL,NIL,NIL},{NIL,NIL,NIL,NIL,NIL}}; // ȫ�ֹ�����ȫ�ֵ����Ӧ�ķ�����û��������ʼֵ����Ϊ-1����������δ������

	int PPLLength; //�û�PPL�����󳤶�
	int Iteration=0; //�Ѿ������˵ĵ�������
	int Len=0; //�ѹ������û���

	int pos;
	int a,b;

	PPLLength=PPLLen(userArray);
	//PPLLength=4; //����ȡ�ȵĲ���

    //���е�һ�ֵ�����ÿ���û���ѡ���Լ�PPL��������λ�ĵ��鷢������  
    for(pos=0; pos<USERNUM; pos++)  
    {  
		//ChoosePartener(userStack, pos, userArray, apArray, userPerfer, userStartPos, apNow); 
        ChoosePartener(pos, userArray, apArray, userPerfer, userStartPos, apNow, apFinal); 

    }  
	Iteration++;
	userStartPos++;
	
	// �û������б�		
	for(pos=0; pos<USERNUM; pos++)   
		userState[pos]=userState[pos]+userPerfer[pos];
	
	Len=getRowLen(userState);
  
    while((Len<USERNUM)&&(Iteration<PPLLength))
    {		
		for(a=0;a<USERNUM;a++)
			userPerfer[a] = 0; 
		for(b=0;b<APNUM;b++)
			apNow[b] = NIL; //��ձ����û�/��������б��ֵ
		//�ٴν��е�������
		for(pos=0; pos<USERNUM; pos++)  
		{  
			ChoosePartener(pos, userArray, apArray, userPerfer, userStartPos, apNow, apFinal); 
		}  
 		Iteration++;
		userStartPos++;	

		// �����û������б�
		for(pos=0; pos<USERNUM; pos++)   
			userState[pos]=userState[pos]+userPerfer[pos];
		
		Len=getRowLen(userState);
    }  
  
	//���������
    for(int i=0;i<APNUM;i++)
	{
		for(int j=0;j<USERNUM;j++)
		{
			if(apFinal[i][j]==1)
			cout<<"AP NO.: "<<i+1<<" User NO.: "<<j+1<<endl;
		}
	}  
	cout<<getchar()<<getchar()<<endl;
	    
}  
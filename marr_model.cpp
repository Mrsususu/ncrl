#include<iostream>  
  
using namespace std;  

//用户(男);灯组（女）
#define USERNUM 5  //用户数目
#define APNUM 4  //灯组数目
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
    //用户选择自己PPL上排在首位的灯组，发出关联请求 
        int perferAP = userArray[userPos][userStartPos];  
        //如果该灯组在本轮没有接受过其他关联请求，则接受该用户的请求  
        if(apNow[perferAP-1] == NIL)  
        {  
            apNow[perferAP-1] = userPos+1; //本轮灯组关联的用户号
            userPerfer[userPos] = 1;   //新灯组变为关联状态
			apFinal[perferAP-1][userPos] = 1;
        }  
        //如果该灯组已经在本轮同某用户关联，再次收到新关联请求时。
		//对照灯组自身对用户的PPL，如果新收到的请求PPL排序更高，则灯组抛弃老用户，同新用户关联；否则，继续和老灯组关联  
        else  
        {  
            int oldPos = GetPositionFromAP(apArray, perferAP, apNow[perferAP-1]);  
            int newPos = GetPositionFromAP(apArray, perferAP, userPos+1);   
            if(newPos < oldPos)  
            {  //新用户的优先度更高，灯组选择离开老用户和新用户关联 
				userPerfer[(apNow[perferAP-1])-1] = 0;  //被抛弃的灯组恢复至还未关联状态
				apFinal[perferAP-1][(apNow[perferAP-1])-1] = 0;

                apNow[perferAP-1] = userPos+1; //更新灯组此时的关联用户			
				userPerfer[userPos] = 1;  //新灯组变为关联状态 
				apFinal[perferAP-1][userPos] = 1;  
            }  
        }  
}  


int main()  
{  
    int userArray[USERNUM][APNUM] ={{1,2,3},{3,4},{1,3,2},{2,1},{3,2,4,1}};  //用户的PPL  
    int apArray[APNUM][USERNUM] = {{1,3,4,5},{1,4,3,5},{3,5,2,1},{5,2}};  //灯组的PPL 

	int userState[USERNUM] = {0}; // 用户关联列表：记录每个用户是否已经和灯组进行了关联，一旦和一个关联，则标记为1 
	int userPerfer[USERNUM] = {0}; // 本轮用户关联列表：记录每个用户是否已经和灯组进行了关联，一旦和一个关联，则标记为1 
	int userStartPos = 0;// 用户的PPL选择序号，即选择PPL中的第几个意愿进入迭代
	int apNow[APNUM] = {NIL,NIL,NIL,NIL}; // 本轮灯组关联表：本轮灯组对应的服务的用户结果（初始值，都为-1，表明均还未关联），每轮结束后此值重新刷新为初始值 
	int apFinal[APNUM][USERNUM] = {{NIL,NIL,NIL,NIL,NIL},{NIL,NIL,NIL,NIL,NIL},{NIL,NIL,NIL,NIL,NIL},{NIL,NIL,NIL,NIL,NIL}}; // 全局关联表：全局灯组对应的服务的用户结果（初始值，都为-1，表明均还未关联）

	int PPLLength; //用户PPL表的最大长度
	int Iteration=0; //已经进行了的迭代次数
	int Len=0; //已关联的用户数

	int pos;
	int a,b;

	PPLLength=PPLLen(userArray);
	//PPLLength=4; //类似取秩的操作

    //进行第一轮迭代，每个用户都选择自己PPL上排在首位的灯组发出申请  
    for(pos=0; pos<USERNUM; pos++)  
    {  
		//ChoosePartener(userStack, pos, userArray, apArray, userPerfer, userStartPos, apNow); 
        ChoosePartener(pos, userArray, apArray, userPerfer, userStartPos, apNow, apFinal); 

    }  
	Iteration++;
	userStartPos++;
	
	// 用户关联列表		
	for(pos=0; pos<USERNUM; pos++)   
		userState[pos]=userState[pos]+userPerfer[pos];
	
	Len=getRowLen(userState);
  
    while((Len<USERNUM)&&(Iteration<PPLLength))
    {		
		for(a=0;a<USERNUM;a++)
			userPerfer[a] = 0; 
		for(b=0;b<APNUM;b++)
			apNow[b] = NIL; //清空本轮用户/灯组关联列表的值
		//再次进行迭代操作
		for(pos=0; pos<USERNUM; pos++)  
		{  
			ChoosePartener(pos, userArray, apArray, userPerfer, userStartPos, apNow, apFinal); 
		}  
 		Iteration++;
		userStartPos++;	

		// 更新用户关联列表
		for(pos=0; pos<USERNUM; pos++)   
			userState[pos]=userState[pos]+userPerfer[pos];
		
		Len=getRowLen(userState);
    }  
  
	//分配结果输出
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
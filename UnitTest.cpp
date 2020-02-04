#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
struct Var{  //定义结构体，将汉字和英文变量一一对应 
		int engv;          //英文变量 
		char chi[20];      //汉字变量 
	};
struct Var var[100]={0,""};
void error()  //错误输出 
{
	printf("你写错啦!!!\n");
}
int num_legal(char num2[])  //数字合法性 
{
	int i;
	char num[10],chi[20][5]={"零","一","二","三","四","五","六","七","八","九","十"};
	strcpy(num,num2);
	if(strlen(num)==2){	
		for(i=0;i<=10;i++)
			if(strcmp(num,chi[i])==0)
				return 1;
		return 0;
	}
	else if(strlen(num)==4){
		if(num_legal(&num[2])==1){  //第二个字是零到十		
			if(strcmp(&num[2],"十")==0){   //第二个字是十 
				num[2]=0;
				if(strcmp(num,"零")==0||strcmp(num,"一")==0||strcmp(num,"十")==0)
					return 0;
				return num_legal(num);
			}
			if(strcmp(&num[2],"零")==0)return 0; //第二个字不能是零 
			if(num_legal(&num[2])==1){ //第二个字是一到九
				 num[2]=0;
				 if(strcmp(num,"十")==0)  //第一个字是十
				 	return 1;
				return 0;
			}
		}
		return 0;
	}
	else if(strlen(num)==6){  //三个字 
		if(num_legal(&num[4])==1){  //第三个字是零到十 
			if(strcmp(&num[4],"零")==0||strcmp(&num[4],"十")==0)
				return 0;
			num[4]=0;
			if(strcmp(&num[2],"十")!=0)
				return 0;
			num[2]=0;
			if(num_legal(num)==0||strcmp(num,"零")==0||strcmp(num,"十")==0)
				return 0;
			return 1;
		}
	return 0;
	}
}
int to_num(char num2[])  //汉字转数字 
{
	int i;
	char num[10],chi[20][5]={"零","一","二","三","四","五","六","七","八","九","十"};
	strcpy(num,num2);
	if(strlen(num)==2){	  //输入一位数 
		for(i=0;i<=10;i++)
			if(strcmp(num,chi[i])==0)
				return i;
	}
	else if(strlen(num)==4){  //输入2个汉字，十几或几十 
		if(num[0]==-54&&num[1]==-82)  //十几
			return 10+to_num(&num[2]);  //&num[2]是个位数 
		else{     //几十 
			num[2]=0; //只有第一个汉字有效
			return to_num(num)*10; 
		}
	}
	else{  //三个汉字，几十几 
		num[2]=0;
		return to_num(num)*10+to_num(&num[4]);
	}
}
void print_chi(int engv)  //数字转汉字并输出 
{
	char chi[20][5]={"零","一","二","三","四","五","六","七","八","九","十"};
	if(engv<=10){
		printf("%s",chi[engv]);
	}
	else if(engv<20){
		printf("十");
		print_chi(engv%10);
	}
	else{
		print_chi(engv/10);
		printf("十");
		if(engv%10!=0)   //如果是整十的数，不出几十零,而是几十 
			print_chi(engv%10);
	}
}
int main()  //主函数 
{
	int num[10]={0,3,10,13,17,20,25,30,37,77},i;
	char chi[20][10]={"零","一","五","十","十一","十三","二十","七十","二十六","三十八","七十五","九十九","一百","三七","增加","看看","零三","哈哈","六六","作业"};
	printf("开始测试数字合法性函数\n");
	for(i=0;i<20;i++){
		if(i<=11){
			printf("chi=%s legal=%d ",chi[i],num_legal(chi[i]));
			if(num_legal(chi[i])==1)
				printf("Pass\n");
			else
				printf("Fail\n");
		}
		else{
			printf("chi=%s legal=%d ",chi[i],num_legal(chi[i]));
			if(num_legal(chi[i])==0)
				printf("Pass\n");
			else
				printf("Fail\n");
		}
	}
	printf("开始测试数字转汉字函数\n");
	for(i=0;i<10;i++){
		printf("num=%d chi=",num[i]);
		print_chi(num[i]);
		printf(" Pass\n");
	}
	printf("开始测试汉字转数字函数\n");
	for(i=0;i<=11;i++){
		printf("chi=%s num=%d ",chi[i],to_num(chi[i]));
		printf("Pass\n");
	}
	printf("测试完毕\n");
	system("pause");
	return 0;
}

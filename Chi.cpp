#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
struct Var{  //定义结构体，将汉字和英文变量一一对应 
		int engv;          //英文变量 
		char chi[20];      //汉字变量 
	};
struct Var var[100]={0,""};
void error()  //错误输出 
{
	printf("你写错啦!!!\n");
}
int op_legal(char op[])  //操作合法性 
{
	int num_legal(char num2[]);
	if(strcmp(op,"等于")==0||strcmp(op,"增加")==0||strcmp(op,"减少")==0||num_legal(op)==1)
		return 0;
	return 1;
}
int var_legal(char vari[])  //变量合法性 
{
	int i;
	if(strcmp(vari,"整数")==0||strcmp(vari,"等于")==0||
	strcmp(vari,"增加")==0||strcmp(vari,"减少")==0||strcmp(vari,"看看")==0)
		return 0;
	for(i=0;strlen(var[i].chi)!=0;i++)
		if(strcmp(vari,var[i].chi)==0)  //变量已被定义过 
			return 0;
	return 1;
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
int equal_legal(char equal[])  //等于合法性 
{
	if(strcmp(equal,"等于")==0)
		return 1;
	return 0;
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
int is_defined(char vari[])  //判断变量是否已经被定义 
{
	int i;
	for(i=0;strlen(var[i].chi)!=0;i++)
		if(strcmp(vari,var[i].chi)==0)
			return 1;
	return 0;
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
void look(char vari[])  //看看函数 
{
	int i;
	for(i=0;strlen(var[i].chi)!=0;i++)
		if(strcmp(vari,var[i].chi)==0){		
			print_chi(var[i].engv);
			break;
		}
	printf("\n");
}
int compute_legal(char compute[])  //运算汉字合法性 
{
	if(strcmp(compute,"增加")==0||strcmp(compute,"减少")==0)
		return 1;
	return 0;
}
void computef(char vari[],char com[],char num[])  //计算加减法 
{
	int i;
	if(strcmp(com,"增加")==0){
		for(i=0;strlen(var[i].chi)!=0;i++)
			if(strcmp(vari,var[i].chi)==0){
				if((var[i].engv+to_num(num))>=100)
					printf("增加的数值过大\n");
				else 
					var[i].engv+=to_num(num);
				break;
			}
	}
	else{
		for(i=0;strlen(var[i].chi)!=0;i++)
			if(strcmp(vari,var[i].chi)==0){
				if((var[i].engv-to_num(num))<0)
					printf("减少的数值过大\n");
				else 
					var[i].engv-=to_num(num);
				break;
			}
	}
}
void OpDefine()
{
	int i=0;
	char vari[10],num[10],equal[10];
	scanf("%s%s%s",vari,equal,num);
	if(var_legal(vari)==0||num_legal(num)==0||equal_legal(equal)==0)
		error();
	else{
		var[i].engv=to_num(num);
		strcpy(var[i].chi,vari);
		i++;
	}
}
void OpLook()
{
	char vari[10];
	scanf("%s",vari);
	if(is_defined(vari)==0)
		error();
	else
		look(vari);
}
void OpCom(char op[10])
{
	int i=0,j;
	char num[10],compute[10];
	if(is_defined(op)==0)
		error(); 
	else{
		scanf("%s%s",compute,num);
		if(compute_legal(compute)==0||num_legal(num)==0)
			error();
		else{
			computef(op,compute,num);
		}
	}
}
int main()  //主函数 
{
	int i=0,j;
	char op[10],vari[10],num[10],compute[10],equal[10];
	while(1){
		scanf("%s",op);  //输入第一个词 
		if(op_legal(op)==0)
			error(); 
		else{
			if(strcmp(op,"整数")==0)  //第一个词是整数就进行变量定义 
				OpDefine();
			else if(strcmp(op,"看看")==0)  //第一个词是看看 
				OpLook();
			else     //第一个词是变量名,进行计算 
				OpCom(op);			
		}
	}
	return 0;
}

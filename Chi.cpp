#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
struct Var{  //����ṹ�壬�����ֺ�Ӣ�ı���һһ��Ӧ 
		int engv;          //Ӣ�ı��� 
		char chi[20];      //���ֱ��� 
	};
struct Var var[100]={0,""};
void error()  //������� 
{
	printf("��д����!!!\n");
}
int op_legal(char op[])  //�����Ϸ��� 
{
	int num_legal(char num2[]);
	if(strcmp(op,"����")==0||strcmp(op,"����")==0||strcmp(op,"����")==0||num_legal(op)==1)
		return 0;
	return 1;
}
int var_legal(char vari[])  //�����Ϸ��� 
{
	int i;
	if(strcmp(vari,"����")==0||strcmp(vari,"����")==0||
	strcmp(vari,"����")==0||strcmp(vari,"����")==0||strcmp(vari,"����")==0)
		return 0;
	for(i=0;strlen(var[i].chi)!=0;i++)
		if(strcmp(vari,var[i].chi)==0)  //�����ѱ������ 
			return 0;
	return 1;
}
int num_legal(char num2[])  //���ֺϷ��� 
{
	int i;
	char num[10],chi[20][5]={"��","һ","��","��","��","��","��","��","��","��","ʮ"};
	strcpy(num,num2);
	if(strlen(num)==2){	
		for(i=0;i<=10;i++)
			if(strcmp(num,chi[i])==0)
				return 1;
		return 0;
	}
	else if(strlen(num)==4){
		if(num_legal(&num[2])==1){  //�ڶ��������㵽ʮ		
			if(strcmp(&num[2],"ʮ")==0){   //�ڶ�������ʮ 
				num[2]=0;
				if(strcmp(num,"��")==0||strcmp(num,"һ")==0||strcmp(num,"ʮ")==0)
					return 0;
				return num_legal(num);
			}
			if(strcmp(&num[2],"��")==0)return 0; //�ڶ����ֲ������� 
			if(num_legal(&num[2])==1){ //�ڶ�������һ����
				 num[2]=0;
				 if(strcmp(num,"ʮ")==0)  //��һ������ʮ
				 	return 1;
				return 0;
			}
		}
		return 0;
	}
	else if(strlen(num)==6){  //������ 
		if(num_legal(&num[4])==1){  //�����������㵽ʮ 
			if(strcmp(&num[4],"��")==0||strcmp(&num[4],"ʮ")==0)
				return 0;
			num[4]=0;
			if(strcmp(&num[2],"ʮ")!=0)
				return 0;
			num[2]=0;
			if(num_legal(num)==0||strcmp(num,"��")==0||strcmp(num,"ʮ")==0)
				return 0;
			return 1;
		}
	return 0;
	}
}
int equal_legal(char equal[])  //���ںϷ��� 
{
	if(strcmp(equal,"����")==0)
		return 1;
	return 0;
}
int to_num(char num2[])  //����ת���� 
{
	int i;
	char num[10],chi[20][5]={"��","һ","��","��","��","��","��","��","��","��","ʮ"};
	strcpy(num,num2);
	if(strlen(num)==2){	  //����һλ�� 
		for(i=0;i<=10;i++)
			if(strcmp(num,chi[i])==0)
				return i;
	}
	else if(strlen(num)==4){  //����2�����֣�ʮ����ʮ 
		if(num[0]==-54&&num[1]==-82)  //ʮ��
			return 10+to_num(&num[2]);  //&num[2]�Ǹ�λ�� 
		else{     //��ʮ 
			num[2]=0; //ֻ�е�һ��������Ч
			return to_num(num)*10; 
		}
	}
	else{  //�������֣���ʮ�� 
		num[2]=0;
		return to_num(num)*10+to_num(&num[4]);
	}
}
int is_defined(char vari[])  //�жϱ����Ƿ��Ѿ������� 
{
	int i;
	for(i=0;strlen(var[i].chi)!=0;i++)
		if(strcmp(vari,var[i].chi)==0)
			return 1;
	return 0;
}
void print_chi(int engv)  //����ת���ֲ���� 
{
	char chi[20][5]={"��","һ","��","��","��","��","��","��","��","��","ʮ"};
	if(engv<=10){
		printf("%s",chi[engv]);
	}
	else if(engv<20){
		printf("ʮ");
		print_chi(engv%10);
	}
	else{
		print_chi(engv/10);
		printf("ʮ");
		if(engv%10!=0)   //�������ʮ������������ʮ��,���Ǽ�ʮ 
			print_chi(engv%10);
	}
}
void look(char vari[])  //�������� 
{
	int i;
	for(i=0;strlen(var[i].chi)!=0;i++)
		if(strcmp(vari,var[i].chi)==0){		
			print_chi(var[i].engv);
			break;
		}
	printf("\n");
}
int compute_legal(char compute[])  //���㺺�ֺϷ��� 
{
	if(strcmp(compute,"����")==0||strcmp(compute,"����")==0)
		return 1;
	return 0;
}
void computef(char vari[],char com[],char num[])  //����Ӽ��� 
{
	int i;
	if(strcmp(com,"����")==0){
		for(i=0;strlen(var[i].chi)!=0;i++)
			if(strcmp(vari,var[i].chi)==0){
				if((var[i].engv+to_num(num))>=100)
					printf("���ӵ���ֵ����\n");
				else 
					var[i].engv+=to_num(num);
				break;
			}
	}
	else{
		for(i=0;strlen(var[i].chi)!=0;i++)
			if(strcmp(vari,var[i].chi)==0){
				if((var[i].engv-to_num(num))<0)
					printf("���ٵ���ֵ����\n");
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
int main()  //������ 
{
	int i=0,j;
	char op[10],vari[10],num[10],compute[10],equal[10];
	while(1){
		scanf("%s",op);  //�����һ���� 
		if(op_legal(op)==0)
			error(); 
		else{
			if(strcmp(op,"����")==0)  //��һ�����������ͽ��б������� 
				OpDefine();
			else if(strcmp(op,"����")==0)  //��һ�����ǿ��� 
				OpLook();
			else     //��һ�����Ǳ�����,���м��� 
				OpCom(op);			
		}
	}
	return 0;
}

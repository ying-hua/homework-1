#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
struct Var{  //����ṹ�壬�����ֺ�Ӣ�ı���һһ��Ӧ 
		int engv;          //Ӣ�ı��� 
		char chi[20];      //���ֱ��� 
	};
struct Var var[100]={0,""};
void error()  //������� 
{
	printf("��д����!!!\n");
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
int main()  //������ 
{
	int num[10]={0,3,10,13,17,20,25,30,37,77},i;
	char chi[20][10]={"��","һ","��","ʮ","ʮһ","ʮ��","��ʮ","��ʮ","��ʮ��","��ʮ��","��ʮ��","��ʮ��","һ��","����","����","����","����","����","����","��ҵ"};
	printf("��ʼ�������ֺϷ��Ժ���\n");
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
	printf("��ʼ��������ת���ֺ���\n");
	for(i=0;i<10;i++){
		printf("num=%d chi=",num[i]);
		print_chi(num[i]);
		printf(" Pass\n");
	}
	printf("��ʼ���Ժ���ת���ֺ���\n");
	for(i=0;i<=11;i++){
		printf("chi=%s num=%d ",chi[i],to_num(chi[i]));
		printf("Pass\n");
	}
	printf("�������\n");
	system("pause");
	return 0;
}

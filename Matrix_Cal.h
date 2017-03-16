#ifndef _MATRIX_H
#define _MATRIX_H

//ͷ�ļ�
#include "define.h"

//�������ݽṹ
//��ά����
class Matrix
{
private:
public:
    int m;
    int n;
    float *arr;

    //��ʼ��
    Matrix(int mm = 0,int nn = 0);
    //����m
    void set_m(int mm);
    //����n
    void set_n(int nn);
    //��ʼ��
    void init_matrix();
    //�ͷ�
    void free_matrix();
    //��ȡi,j���������
    //ʧ�ܷ���-31415,�ɹ�����ֵ
    float read(int i,int j);
    //д��i,j���������
    //ʧ�ܷ���-1,�ɹ�����1
    int write(int i,int j,float val);
	//��ӡ����
	void print();
	//�������
	void scan();
};

//��ά������
class Matrix_Cal:public Calculator
{
private:
public:
    Matrix_Cal();
    //C = A + B
    //�ɹ�����1,ʧ�ܷ���-1
    int add(Matrix *A,Matrix *B,Matrix *C);
    //C = A - B
    //�ɹ�����1,ʧ�ܷ���-1
    int sub(Matrix *A,Matrix *B,Matrix *C);
    //C = A * B
    //�ɹ�����1,ʧ�ܷ���-1
    int mul(Matrix *A,Matrix *B,Matrix *C);
    //����ʽ��ֵ,ֻ�ܼ���2 * 2,3 * 3
    //ʧ�ܷ���-31415,�ɹ�����ֵ
    float det(Matrix *A);
    //��ת�þ���,B = AT
    //�ɹ�����1,ʧ�ܷ���-1
    int transpos(Matrix *A,Matrix *B);
    //�������,B = A^(-1)
    //�ɹ�����1,ʧ�ܷ���-1
    int inverse(Matrix *A,Matrix *B);
	void Clear();   //����	  
	virtual void MainMenu();     //���˵�  
	virtual int GetInput();      //�������벢����
	virtual void ShowAnswer();   //�����               

};

#endif

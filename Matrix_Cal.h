#ifndef _MATRIX_H
#define _MATRIX_H

//头文件
#include "define.h"

//矩阵数据结构
//二维矩阵
class Matrix
{
private:
public:
    int m;
    int n;
    float *arr;

    //初始化
    Matrix(int mm = 0,int nn = 0);
    //设置m
    void set_m(int mm);
    //设置n
    void set_n(int nn);
    //初始化
    void init_matrix();
    //释放
    void free_matrix();
    //读取i,j坐标的数据
    //失败返回-31415,成功返回值
    float read(int i,int j);
    //写入i,j坐标的数据
    //失败返回-1,成功返回1
    int write(int i,int j,float val);
	//打印矩阵
	void print();
	//读入矩阵
	void scan();
};

//二维运算类
class Matrix_Cal:public Calculator
{
private:
public:
    Matrix_Cal();
    //C = A + B
    //成功返回1,失败返回-1
    int add(Matrix *A,Matrix *B,Matrix *C);
    //C = A - B
    //成功返回1,失败返回-1
    int sub(Matrix *A,Matrix *B,Matrix *C);
    //C = A * B
    //成功返回1,失败返回-1
    int mul(Matrix *A,Matrix *B,Matrix *C);
    //行列式的值,只能计算2 * 2,3 * 3
    //失败返回-31415,成功返回值
    float det(Matrix *A);
    //求转置矩阵,B = AT
    //成功返回1,失败返回-1
    int transpos(Matrix *A,Matrix *B);
    //求逆矩阵,B = A^(-1)
    //成功返回1,失败返回-1
    int inverse(Matrix *A,Matrix *B);
	void Clear();   //清屏	  
	virtual void MainMenu();     //主菜单  
	virtual int GetInput();      //接受输入并处理
	virtual void ShowAnswer();   //输出答案               

};

#endif

#include "Matrix_Cal.h"
#include "exception.h"

//矩阵类方法
//初始化
Matrix::Matrix(int mm,int nn)
{
    m = mm;
    n = nn;
}

//设置m
void Matrix::set_m(int mm)
{
    m = mm;
}

//设置n
void Matrix::set_n(int nn)
{
    n = nn;
}

//初始化
void Matrix::init_matrix()
{
    arr = new float[m * n];
}

//释放
void Matrix::free_matrix()
{
    delete []arr;
}

//读取i,j坐标的数据
//失败返回-31415,成功返回值
float Matrix::read(int i,int j)
{
    if (i >= m || j >= n)
    {
        return -31415;
    }

    return *(arr + i * n + j);
}

//写入i,j坐标的数据
//失败返回-1,成功返回1
int Matrix::write(int i,int j,float val)
{
    if (i >= m || j >= n)
    {
        return -1;
    }

    *(arr + i * n + j) = val;
    return 1;
}

//打印2维矩阵
void Matrix::print()
{
    int i = 0;
    int j = 0;
    for (i = 0;i < m;i++)
    {
        for (j = 0;j < n;j++)
        {
            printf("%f ",read(i,j));
        }
        printf("\n");
    }
}

void Matrix::scan()
{
	int x,y;
	char buf;
	cout<<"输入行数和列数(格式为:行数  列数):"<<endl;
	cin>>x>>y;
	if(cin.fail()){
		cin.clear();
		cin>>buf;
		cin.ignore(1024,'\n');
		Input_Error e(buf);
		throw e;
	}
	cin.ignore(1024,'\n');
	m=x;n=y;
	init_matrix();
	cout<<"请逐个输入数据："<<endl;
	for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
			int k;
			cin>>k;
			if(cin.fail()){
				cin.clear();
				cin>>buf;
				cin.ignore(1024,'\n');
				Input_Error e(buf);
				throw e;
			}
            write(i,j,k);
        }
    }
	cin.ignore(1024,'\n');
}


/*****************************以下为矩阵计算器部分*******************************/

//矩阵运算类方法
//初始化
Matrix_Cal::Matrix_Cal()
{
}

//C = A + B
//成功返回1,失败返回-1
int Matrix_Cal::add(Matrix *A,Matrix *B,Matrix *C)
{
    int i = 0;
    int j = 0;
    //判断是否可以运算
    if (A->m != B->m || A->n != B->n || \
        A->m != C->m || A->n != C->n)
    {
        Math_Error e(6);
		throw e;
    }
    //运算
    for (i = 0;i < C->m;i++)
    {
        for (j = 0;j < C->n;j++)
        {
            C->write(i,j,A->read(i,j) + B->read(i,j));
        }
    }
    return 1;
}

//C = A - B
//成功返回1,失败返回-1
int Matrix_Cal::sub(Matrix *A,Matrix *B,Matrix *C)
{
    int i = 0;
    int j = 0;
    //判断是否可以运算
    if (A->m != B->m || A->n != B->n || \
        A->m != C->m || A->n != C->n)
    {
        Math_Error e(6);
		throw e;
    }
    //运算
    for (i = 0;i < C->m;i++)
    {
        for (j = 0;j < C->n;j++)
        {
            C->write(i,j,A->read(i,j) - B->read(i,j));
        }
    }
    return 1;
}

//C = A * B
//成功返回1,失败返回-1
int Matrix_Cal::mul(Matrix *A,Matrix *B,Matrix *C)
{
    int i = 0;
    int j = 0;
    int k = 0;
    float temp = 0;

    //判断是否可以运算
    if (A->m != C->m || B->n != C->n || \
        A->n != B->m)
    {
        Math_Error e(6);
		throw e;
    }
    //运算
    for (i = 0;i < C->m;i++)
    {
        for (j = 0;j < C->n;j++)
        {
            temp = 0;
            for (k = 0;k < A->n;k++)
            {
                temp += A->read(i,k) * B->read(k,j);
            }
            C->write(i,j,temp);
        }
    }

    return 1;
}

//行列式的值,只能计算2 * 2,3 * 3
//失败返回-31415,成功返回值
float Matrix_Cal::det(Matrix *A)
{
    float value = 0;

    //判断是否可以运算
    if (A->m != A->n || (A->m != 2 && A->m != 3))
    {
        Math_Error e(6);
		throw e;
    }
    //运算
    if (A->m == 2)
    {
        value = A->read(0,0) * A->read(1,1) - A->read(0,1) * A->read(1,0);
    }
    else
    {
        value = A->read(0,0) * A->read(1,1) * A->read(2,2) + \
                A->read(0,1) * A->read(1,2) * A->read(2,0) + \
                A->read(0,2) * A->read(1,0) * A->read(2,1) - \
                A->read(0,0) * A->read(1,2) * A->read(2,1) - \
                A->read(0,1) * A->read(1,0) * A->read(2,2) - \
                A->read(0,2) * A->read(1,1) * A->read(2,0);
    }

    return value;
}

//求转置矩阵,B = AT
//成功返回1,失败返回-1
int Matrix_Cal::transpos(Matrix *A,Matrix *B)
{
    int i = 0;
    int j = 0;

    //判断是否可以运算
    if (A->m != B->n || A->n != B->m)
    {
        Math_Error e(6);
		throw e;
    }
    //运算
    for (i=0;i<B->m;i++)
    {
        for (j=0;j<B->n;j++)
        {
            B->write(i,j,A->read(j,i));
        }
    }
    return 1;
}



//求逆矩阵,B = A^(-1)
//成功返回1,失败返回-1
int Matrix_Cal::inverse(Matrix *A,Matrix *B)
{
    int i = 0;
    int j = 0;
    int k = 0;
    Matrix m(A->m,2 * A->m);
    float temp = 0;
    float b = 0;

    //判断是否可以运算
    if (A->m != A->n || B->m != B->n || A->m != B->m)
    {
        Math_Error e(6);
		throw e;
    }

    
    //如果是2维或者3维求行列式判断是否可逆
    if (A->m == 2 || A->m == 3)
    {
        if (det(A) == 0)
        {
			Math_Error e(6);
			throw e;
        }
    }
    

    //增广矩阵m = A | B初始化
    m.init_matrix();
    for (i = 0;i < m.m;i++)
    {
        for (j = 0;j < m.n;j++)
        {
            if (j <= A->n - 1)
            {
                m.write(i,j,A->read(i,j));
            }
            else
            {
                if (i == j - A->n)
                {
                    m.write(i,j,1);
                }
                else
                {
                    m.write(i,j,0);
                }
            }
        }
    }

    //高斯消元
    //变换下三角
    for (k = 0;k < m.m - 1;k++)
    {
        //如果坐标为k,k的数为0,则行变换
        if (m.read(k,k) == 0)
        {
            for (i = k + 1;i < m.m;i++)
            {
                if (m.read(i,k) != 0)
                {
                    break;
                }
            }
            if (i >= m.m)
			{
				Math_Error e(6);
				throw e;
            }
            else
            {
                //交换行
                for (j = 0;j < m.n;j++)
                {
                    temp = m.read(k,j);
                    m.write(k,j,m.read(k + 1,j));
                    m.write(k + 1,j,temp);
                }
            }
        }

        //消元
        for (i = k + 1;i < m.m;i++)
        {
            //获得倍数
            b = m.read(i,k) / m.read(k,k);
            //行变换
            for (j = 0;j < m.n;j++)
            {
                temp = m.read(i,j) - b * m.read(k,j);
                m.write(i,j,temp);
            }
        }
    }
    //变换上三角
    for (k = m.m - 1;k > 0;k--)
    {
        //如果坐标为k,k的数为0,则行变换
        if (m.read(k,k) == 0)
        {
            for (i = k + 1;i < m.m;i++)
            {
                if (m.read(i,k) != 0)
                {
                    break;
                }
            }
            if (i >= m.m)
            {
				Math_Error e(6);
				throw e;
            }
            else
            {
                //交换行
                for (j = 0;j < m.n;j++)
                {
                    temp = m.read(k,j);
                    m.write(k,j,m.read(k + 1,j));
                    m.write(k + 1,j,temp);
                }
            }
        }

        //消元
        for (i = k - 1;i >= 0;i--)
        {
            //获得倍数
            b = m.read(i,k) / m.read(k,k);
            //行变换
            for (j = 0;j < m.n;j++)
            {
                temp = m.read(i,j) - b * m.read(k,j);
                m.write(i,j,temp);
            }
        }
    }
    //将左边方阵化为单位矩阵
    for (i = 0;i < m.m;i++)
    {
        if (m.read(i,i) != 1)
        {
            //获得倍数
            b = 1 / m.read(i,i);
            //行变换
            for (j = 0;j < m.n;j++)
            {
                temp = m.read(i,j) * b;
                m.write(i,j,temp);
            }
        }
    }
    //求得逆矩阵
    for (i = 0;i < B->m;i++)
    {
        for (j = 0;j < B->m;j++)
        {
            B->write(i,j,m.read(i,j + m.m));
        }
    }
    //释放增广矩阵
    m.free_matrix();

    return 1;
}

void Matrix_Cal::MainMenu()
{
	int n=1;
	system("cls");
	cout<<"*********************************矩阵计算器*************************************"<<endl;
	cout<<"     R:返回主菜单     L:清屏    "<<endl<<endl;
	while(n){
		try{
			cout<<"请选择运算:\n1.加法\n2.减法\n3.乘法\n4.行列式\n5.转置\n6.求逆"<<endl;
			n=GetInput();
		}
		catch(Error &e){
			e.OnError();
		}	
	}
}

int Matrix_Cal::GetInput()
{
	int command;
    Matrix m1;
    Matrix m2;
    Matrix m3;
 
	cin.getline(read,1000);
	Pretreat();
	if(strcmp(read,"r")==0) return 0;
	if(strcmp(read,"l")==0){
		Clear();
		return 1;
	}
	command=CharToNum(read[0]);

	if(!read[1]){
		switch(command){
		case 1:
			{
				m1.scan();
				m2.scan();
				m3.m=m1.m;m3.n=m1.n;
				m3.init_matrix();
				add(&m1,&m2,&m3);
				cout<<"运算结果为:"<<endl;
				m3.print();
				m1.free_matrix();
				m2.free_matrix();
				m3.free_matrix();
				break;
			}
		case 2:
			{
				m1.scan();
				m2.scan();
				m3.m=m1.m;m3.n=m1.n;
				m3.init_matrix();
				sub(&m1,&m2,&m3);
				cout<<"运算结果为:"<<endl;
				m3.print();
				m1.free_matrix();
				m2.free_matrix();
				m3.free_matrix();
				break;
			}
		case 3:
			{
				m1.scan();
				m2.scan();
				m3.m=m1.m;m3.n=m2.n;
				m3.init_matrix();
				mul(&m1,&m2,&m3);
				cout<<"运算结果为:"<<endl;
				m3.print();
				m1.free_matrix();
				m2.free_matrix();
				m3.free_matrix();
				break;
			}
		case 4:
			{
				m1.scan();
				cout<<"运算结果为:"<<det(&m1)<<endl;
				m1.free_matrix();
				break;
			}
	    case 5:
			{
				m1.scan();
				m2.m=m2.n=m1.m;
				m2.init_matrix();
				transpos(&m1,&m2);
				cout<<"运算结果为:"<<endl;
				m2.print();
				m1.free_matrix();
				m2.free_matrix();
				break;
			}
		case 6:
			{
				m1.scan();
				m2.m=m2.n=m1.m;
				m2.init_matrix();
				inverse(&m1,&m2);
				cout<<"运算结果为:"<<endl;
				m2.print();
				m1.free_matrix();
				m2.free_matrix();
				break;
			}
		default:
			Input_Error e;
			throw e;
		}
	}
	else{
		Input_Error e;
		throw e;
	}
    return 1;
}

void Matrix_Cal::ShowAnswer()
{
}

void Matrix_Cal::Clear()
{
	system("cls");
	cout<<"*********************************矩阵计算器*************************************"<<endl;
	cout<<"     R:返回主菜单     L:清屏    "<<endl<<endl;
}
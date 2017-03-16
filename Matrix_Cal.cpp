#include "Matrix_Cal.h"
#include "exception.h"

//�����෽��
//��ʼ��
Matrix::Matrix(int mm,int nn)
{
    m = mm;
    n = nn;
}

//����m
void Matrix::set_m(int mm)
{
    m = mm;
}

//����n
void Matrix::set_n(int nn)
{
    n = nn;
}

//��ʼ��
void Matrix::init_matrix()
{
    arr = new float[m * n];
}

//�ͷ�
void Matrix::free_matrix()
{
    delete []arr;
}

//��ȡi,j���������
//ʧ�ܷ���-31415,�ɹ�����ֵ
float Matrix::read(int i,int j)
{
    if (i >= m || j >= n)
    {
        return -31415;
    }

    return *(arr + i * n + j);
}

//д��i,j���������
//ʧ�ܷ���-1,�ɹ�����1
int Matrix::write(int i,int j,float val)
{
    if (i >= m || j >= n)
    {
        return -1;
    }

    *(arr + i * n + j) = val;
    return 1;
}

//��ӡ2ά����
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
	cout<<"��������������(��ʽΪ:����  ����):"<<endl;
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
	cout<<"������������ݣ�"<<endl;
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


/*****************************����Ϊ�������������*******************************/

//���������෽��
//��ʼ��
Matrix_Cal::Matrix_Cal()
{
}

//C = A + B
//�ɹ�����1,ʧ�ܷ���-1
int Matrix_Cal::add(Matrix *A,Matrix *B,Matrix *C)
{
    int i = 0;
    int j = 0;
    //�ж��Ƿ��������
    if (A->m != B->m || A->n != B->n || \
        A->m != C->m || A->n != C->n)
    {
        Math_Error e(6);
		throw e;
    }
    //����
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
//�ɹ�����1,ʧ�ܷ���-1
int Matrix_Cal::sub(Matrix *A,Matrix *B,Matrix *C)
{
    int i = 0;
    int j = 0;
    //�ж��Ƿ��������
    if (A->m != B->m || A->n != B->n || \
        A->m != C->m || A->n != C->n)
    {
        Math_Error e(6);
		throw e;
    }
    //����
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
//�ɹ�����1,ʧ�ܷ���-1
int Matrix_Cal::mul(Matrix *A,Matrix *B,Matrix *C)
{
    int i = 0;
    int j = 0;
    int k = 0;
    float temp = 0;

    //�ж��Ƿ��������
    if (A->m != C->m || B->n != C->n || \
        A->n != B->m)
    {
        Math_Error e(6);
		throw e;
    }
    //����
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

//����ʽ��ֵ,ֻ�ܼ���2 * 2,3 * 3
//ʧ�ܷ���-31415,�ɹ�����ֵ
float Matrix_Cal::det(Matrix *A)
{
    float value = 0;

    //�ж��Ƿ��������
    if (A->m != A->n || (A->m != 2 && A->m != 3))
    {
        Math_Error e(6);
		throw e;
    }
    //����
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

//��ת�þ���,B = AT
//�ɹ�����1,ʧ�ܷ���-1
int Matrix_Cal::transpos(Matrix *A,Matrix *B)
{
    int i = 0;
    int j = 0;

    //�ж��Ƿ��������
    if (A->m != B->n || A->n != B->m)
    {
        Math_Error e(6);
		throw e;
    }
    //����
    for (i=0;i<B->m;i++)
    {
        for (j=0;j<B->n;j++)
        {
            B->write(i,j,A->read(j,i));
        }
    }
    return 1;
}



//�������,B = A^(-1)
//�ɹ�����1,ʧ�ܷ���-1
int Matrix_Cal::inverse(Matrix *A,Matrix *B)
{
    int i = 0;
    int j = 0;
    int k = 0;
    Matrix m(A->m,2 * A->m);
    float temp = 0;
    float b = 0;

    //�ж��Ƿ��������
    if (A->m != A->n || B->m != B->n || A->m != B->m)
    {
        Math_Error e(6);
		throw e;
    }

    
    //�����2ά����3ά������ʽ�ж��Ƿ����
    if (A->m == 2 || A->m == 3)
    {
        if (det(A) == 0)
        {
			Math_Error e(6);
			throw e;
        }
    }
    

    //�������m = A | B��ʼ��
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

    //��˹��Ԫ
    //�任������
    for (k = 0;k < m.m - 1;k++)
    {
        //�������Ϊk,k����Ϊ0,���б任
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
                //������
                for (j = 0;j < m.n;j++)
                {
                    temp = m.read(k,j);
                    m.write(k,j,m.read(k + 1,j));
                    m.write(k + 1,j,temp);
                }
            }
        }

        //��Ԫ
        for (i = k + 1;i < m.m;i++)
        {
            //��ñ���
            b = m.read(i,k) / m.read(k,k);
            //�б任
            for (j = 0;j < m.n;j++)
            {
                temp = m.read(i,j) - b * m.read(k,j);
                m.write(i,j,temp);
            }
        }
    }
    //�任������
    for (k = m.m - 1;k > 0;k--)
    {
        //�������Ϊk,k����Ϊ0,���б任
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
                //������
                for (j = 0;j < m.n;j++)
                {
                    temp = m.read(k,j);
                    m.write(k,j,m.read(k + 1,j));
                    m.write(k + 1,j,temp);
                }
            }
        }

        //��Ԫ
        for (i = k - 1;i >= 0;i--)
        {
            //��ñ���
            b = m.read(i,k) / m.read(k,k);
            //�б任
            for (j = 0;j < m.n;j++)
            {
                temp = m.read(i,j) - b * m.read(k,j);
                m.write(i,j,temp);
            }
        }
    }
    //����߷���Ϊ��λ����
    for (i = 0;i < m.m;i++)
    {
        if (m.read(i,i) != 1)
        {
            //��ñ���
            b = 1 / m.read(i,i);
            //�б任
            for (j = 0;j < m.n;j++)
            {
                temp = m.read(i,j) * b;
                m.write(i,j,temp);
            }
        }
    }
    //��������
    for (i = 0;i < B->m;i++)
    {
        for (j = 0;j < B->m;j++)
        {
            B->write(i,j,m.read(i,j + m.m));
        }
    }
    //�ͷ��������
    m.free_matrix();

    return 1;
}

void Matrix_Cal::MainMenu()
{
	int n=1;
	system("cls");
	cout<<"*********************************���������*************************************"<<endl;
	cout<<"     R:�������˵�     L:����    "<<endl<<endl;
	while(n){
		try{
			cout<<"��ѡ������:\n1.�ӷ�\n2.����\n3.�˷�\n4.����ʽ\n5.ת��\n6.����"<<endl;
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
				cout<<"������Ϊ:"<<endl;
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
				cout<<"������Ϊ:"<<endl;
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
				cout<<"������Ϊ:"<<endl;
				m3.print();
				m1.free_matrix();
				m2.free_matrix();
				m3.free_matrix();
				break;
			}
		case 4:
			{
				m1.scan();
				cout<<"������Ϊ:"<<det(&m1)<<endl;
				m1.free_matrix();
				break;
			}
	    case 5:
			{
				m1.scan();
				m2.m=m2.n=m1.m;
				m2.init_matrix();
				transpos(&m1,&m2);
				cout<<"������Ϊ:"<<endl;
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
				cout<<"������Ϊ:"<<endl;
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
	cout<<"*********************************���������*************************************"<<endl;
	cout<<"     R:�������˵�     L:����    "<<endl<<endl;
}
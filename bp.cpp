#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

class Matrix
{
public:
    double **matrix;
    int row;
    int column;
    Matrix()
    {
        this->row=0;
        this->column=0;
        this->matrix=NULL;
    }
    Matrix(Matrix *a)
    {
        init(a->row, a->column);
        for(int i=0;i<row;i++)
            for(int j=0;j<row;j++)
                this->matrix[i][j]=a->matrix[i][j];
    }
    void init(int row, int column)
    {
        this->row=row;
        this->column=column;
        this->matrix=new double*[row];
        for(int i=0; i<row; i++)
        {
            this->matrix[i]=new double[column];
            for(int j=0;j<column;j++)
                this->matrix[i][j]=0;
        }
    }

    double gaussRand(double u=0.0, double sigma=1.0)
    {
        static double V1, V2, S;
        static int phase = 0;
        double X;
        if ( phase == 0 ) {
            do
            {
                double U1 = (double)rand() / RAND_MAX;
                double U2 = (double)rand() / RAND_MAX;
                V1 = 2 * U1 - 1;
                V2 = 2 * U2 - 1;
                S = V1 * V1 + V2 * V2;
            } while(S >= 1 || S == 0);
            X = V1 * sqrt(-2 * log(S) / S);
        } else
            X = V2 * sqrt(-2 * log(S) / S);
        phase = 1 - phase;
        return X;
    }
    void randomInit(int row, int column)
    {
        this->init(row, column);
        for(int i=0; i<row; i++)
        {
            for(int j=0;j<column;j++)
            {
                this->matrix[i][j]=gaussRand(0,0.05);
            }
        }
    }
    void assign(Matrix *a)
    {
        if(this->row!=a->row || this->column!=a->column)
        {
            cout<<"Row<>Column in assign"<<endl;
            cout<<"This: "<<row<<"*"<<column<<endl;
            cout<<"a: "<<a->row<<"*"<<a->column<<endl;
            return;
        }
        for(int i=0; i<row; i++)
        {
            for(int j=0;j<column;j++)
            {
                this->matrix[i][j]=a->matrix[i][j];
            }
        }
    }
    Matrix(int row, int column, bool randInit=false)
    {
        if(randInit)
        {
            this->randomInit(row, column);
        }
        else
        {
            this->init(row, column);
        }
    }
    void set(int row, int column, double value)
    {
        this->matrix[row][column]=value;
    }
    void dot(Matrix* a, Matrix* b)
    {
        if(a->column!=b->row || this->row!=a->row || this->column!=b->column)
        {
            cout<<"ROW<>COLUMN in dot"<<endl;
            return;
        }
        for(int i=0;i<this->row;i++)
        {
            for(int j=0;j<this->column;j++)
            {
                this->matrix[i][j]=0.0;
                for(int k=0;k<a->column;k++)
                {
                    this->matrix[i][j]+=a->matrix[i][k]*b->matrix[k][j];
                }
            }
        }
    }
    void Tdot(Matrix* a, Matrix* b)
    {
        if(a->row!=b->row || this->row!=a->column || this->column!=b->column)
        {
            cout<<"ROW<>COLUMN in dotT"<<endl;
            return;
        }
        for(int i=0;i<this->row;i++)
        {
            for(int j=0;j<this->column;j++)
            {
                this->matrix[i][j]=0.0;
                for(int k=0;k<a->row;k++)
                {
                    this->matrix[i][j]+=a->matrix[k][i]*b->matrix[k][j];
                }
            }
        }
    }
    void dotT(Matrix* a, Matrix* b)
    {
        if(a->column!=b->column || this->row!=a->row || this->column!=b->row)
        {
            cout<<"ROW<>COLUMN in dotT"<<endl;
            return;
        }
        for(int i=0;i<this->row;i++)
        {
            for(int j=0;j<this->column;j++)
            {
                this->matrix[i][j]=0.0;
                for(int k=0;k<a->column;k++)
                {
                    this->matrix[i][j]+=a->matrix[i][k]*b->matrix[j][k];
                }
            }
        }
    }
    void zero()
    {
        for(int i=0;i<this->row;i++)
        {
            for(int j=0;j<this->column;j++)
            {
                this->matrix[i][j]=0;
            }
        }
    }
    void add(Matrix* a)
    {
        if(this->row!=a->row || this->column!=a->column)
        {
            cout<<"ROW<>ROW || COLUMN<>COLUMN in add"<<endl;
        }
        for(int i=0;i<this->row;i++)
        {
            for(int j=0;j<this->column;j++)
            {
                this->matrix[i][j]+=a->matrix[i][j];
            }
        }
    }
    void multiplication(double t)
    {
        for(int i=0;i<this->row;i++)
        {
            for(int j=0;j<this->column;j++)
            {
                this->matrix[i][j]*=t;
            }
        }
    }
    void multiplication(Matrix *a)
    {
        if(this->row!=a->row || this->column!=a->column)
        {
            cout<<"ROW<>ROW || COLUMN<>COLUMN in multiplication"<<endl;
        }
        for(int i=0;i<this->row;i++)
        {
            for(int j=0;j<this->column;j++)
            {
                this->matrix[i][j]*=a->matrix[i][j];
            }
        }
    }
    void division(double t)
    {
        if(t==0)
        {
            cout<<"Divied by zero!!!"<<endl;
            return;
        }
        for(int i=0;i<this->row;i++)
        {
            for(int j=0;j<this->column;j++)
            {
                this->matrix[i][j]/=t;
            }
        }
    }
    void minus(Matrix* a)
    {
        if(this->row!=a->row || this->column!=a->column)
        {
            cout<<"ROW<>ROW || COLUMN<>COLUMN in minus"<<endl;
        }
        for(int i=0;i<this->row;i++)
        {
            for(int j=0;j<this->column;j++)
            {
                this->matrix[i][j]-=a->matrix[i][j];
            }
        }
    }
    void show(string info="")
    {
        if(info!="")
        {
            cout<<info<<endl;
        }
        cout<<"Row: "<<row<<endl;
        cout<<"Column: "<<column<<endl;
        cout<<"["<<endl;
        for(int i=0;i<row;i++)
        {
            cout<<"\t";
            for(int j=0;j<column;j++)
            {
                cout<<matrix[i][j]<<", ";
            }
            cout<<""<<endl;
        }
        cout<<"]"<<endl;
    }

    ~Matrix()
    {
        for(int i=0;i<row;i++)
        {
            delete []matrix[i];
            matrix[i]=NULL;
        }
        delete []matrix;
    }
};
class Network
{
public:
    int L;
    Matrix** W;
    int *NodesCount;
    Matrix **X;
    Matrix **Y;
    Matrix **A;
    Matrix **Z;
    //Matrix **B;
    Matrix **Delta;
    Matrix **WDelta;
    //Matrix **BDelta;
    int DataCount;
    int XDinention;
    int YDinention;

    Network()
    {
        getData("data.txt");
        cout<<"This is a Network"<<endl;
        cout<<"Please input the count of layer: ";
        cin>>L;
        W=new Matrix*[L-1];
        //B=new Matrix*[L-1];
        NodesCount=new int[L];
        NodesCount[0]=XDinention;
        NodesCount[L-1]=YDinention;
        for(int i=0;i<L-2;i++)
        {
            cout<<"Please input the count of nodes in layer "<<i+1<<endl;
            cin>>NodesCount[i+1];
        }
        for(int i=0;i<L-1;i++)
        {
            W[i]=new Matrix(NodesCount[i+1], NodesCount[i], true);
            //B[i]=new Matrix(NodesCount[i+1],1, true);
        }
        A=new Matrix*[L];
        Z=new Matrix*[L];
        for(int i=0;i<L;i++)
        {
            A[i]=new Matrix(this->NodesCount[i],1);
            Z[i]=new Matrix(this->NodesCount[i],1);
        }
    }
    double f(double z)
    {
        return 1.0/(1+exp(-1*z));
    }
    double ff(double z)
    {
        return exp(-1*z)/((1+exp(-1*z))*(1+exp(-1*z)));
    }
    void F(Matrix *a, Matrix *b)
    {
        for(int i=0;i<a->row;i++)
        {
            for(int j=0;j<a->column;j++)
            {
                b->matrix[i][j]=f(a->matrix[i][j]);
            }
        }
    }
    void FF(Matrix *a, Matrix *b)
    {
        for(int i=0;i<a->row;i++)
        {
            for(int j=0;j<a->column;j++)
            {
                b->matrix[i][j]=ff(a->matrix[i][j]);
            }
        }
    }
    void getData(string fileName)
    {
        ifstream fin(fileName);
        fin>>this->DataCount;
        fin>>this->YDinention;
        fin>>this->XDinention;
        XDinention+=1;
        X=new Matrix*[DataCount];
        Y=new Matrix*[DataCount];

        if(!fin.is_open())
        {
            cout<<"Error in opening %s"<<fileName<<endl;
            return;
        }
        for(int i=0;i<DataCount;i++)
        {
            X[i]=new Matrix(XDinention,1);
            Y[i]=new Matrix(YDinention,1);
            for(int j=0;j<YDinention;j++)
            {
                fin>>Y[i]->matrix[j][0];
            }
            for(int j=0;j<XDinention-1;j++)
            {
                double tmp;
                fin>>X[i]->matrix[j][0];
            }
            X[i]->matrix[XDinention-1][0]=1;
        }
        cout<<X[0]->row<<"*"<<X[0]->column<<endl;
        fin.close();
    }
    void Propagation(int index)
    {
        A[0]->assign(X[index]);
        Z[0]->assign(X[index]);
        for(int i=1;i<L;i++)
        {
            Z[i]->dot(W[i-1], A[i-1]);
            //Z[i]->add(B[i-1]);
            FF(Z[i], A[i]);
        }
    }
    void BackPropagation(int index)
    {
        Matrix* tmp1=new Matrix(NodesCount[L-1],1);
        Matrix* tmp2=new Matrix(NodesCount[L-1],1);
        tmp1->assign(Y[index]);
        tmp1->minus(A[L-1]);
        tmp1->multiplication(-1);
        FF(Z[L-1],tmp2);
        tmp1->multiplication(tmp2);
        Delta[L-1]->assign(tmp1);

        for(int i=1;i<L-1;i++)
        {
            tmp1=new Matrix(NodesCount[i],1);
            tmp2=new Matrix(NodesCount[i],1);
            tmp1->Tdot(W[i],Delta[i+1]);
            FF(Z[i],tmp2);
            tmp1->multiplication(tmp2);
            Delta[i]->assign(tmp1);
        }
        for(int i=0;i<L-1;i++)
        {
            Matrix *tmp3=new Matrix(NodesCount[i+1],NodesCount[i]);
            tmp3->dotT(Delta[i+1],A[i]);
            WDelta[i]->add(tmp3);
            //BDelta[i]->add(Delta[i+1]);
        }
    }
    void solve()
    {
        Delta=new Matrix*[L];
        WDelta=new Matrix*[L];
        //BDelta=new Matrix*[L];
        for(int i=0;i<L;i++)
        {
            Delta[i]=new Matrix(NodesCount[i],1);
        }
        for(int i=0;i<L-1;i++)
        {
            WDelta[i]=new Matrix(NodesCount[i+1], NodesCount[i]);
            //BDelta[i]=new Matrix(NodesCount[i+1],1);
        }
        int interationCount=0;
        cout<<"输入迭代次数：";
        cin>>interationCount;
        for(int t=0;t<interationCount;t++)
        {
            cout<<"====================="<<endl;
            cout<<"第"<<t<<"次迭代"<<endl;
            for(int i=0;i<L;i++)
            {
                Delta[i]->zero();
            }
            cout<<X[0]->row<<"*"<<X[0]->column<<endl;
            for(int i=0;i<DataCount;i++)
            {
                Propagation(i);
                Y[i]->show("Y");
                A[L-1]->show("A");
                BackPropagation(i);
            }
            for(int i=0;i<L-1;i++)
            {
                double alpha=0.05;
                WDelta[i]->multiplication(alpha/DataCount);
                //BDelta[i]->multiplication(alpha/DataCount);
                W[i]->minus(WDelta[i]);
                //B[i]->minus(BDelta[i]);
            }
        }
    }
};
int main()
{
    srand(time(0));
    Network *a=new Network();
    a->solve();
    return 0;
}

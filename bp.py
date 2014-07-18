#-*-coding:utf-8-*-
import numpy as np

class BP:
    data=[]
    n=0
    mx=0
    my=0
    def __init__(self):
        print('Start')

    def getData(self, fname='data.txt'):
        fdata=open(fname,'r').readlines()
        try:
            self.n=int(fdata[0])
            self.my=int(fdata[1].split(' ')[0])
            self.mx=int(fdata[1].split(' ')[1])
        except:
            print('Error in data.txt')
            return

        for i in range(0,self.n):
            self.data.append({'x':[],'y':[]})
            d=fdata[i+2].split(' ')
            for j in range(self.my):
                self.data[i]['y'].append(float(d[j]))
            self.data[i]['y']=np.transpose(np.matrix(self.data[i]['y']))
            for j in range(self.mx):
                self.data[i]['x'].append(float(d[j+self.my]))
            self.data[i]['x']=np.transpose(np.matrix(self.data[i]['x']))

        for i in self.data:
            print i


    def f(self,z):
        return 1/(1+np.exp(-1*z))


    def vector_dot(self,a,b):
        tmp=a.reshape(1,a.size).tolist()[0]
        return np.matrix(np.diag(tmp)*b)


    def ff(self,z):
        #if(z>1000):
        #    z=100
        tmp=(1+np.exp(-1*z))
        tmp=self.vector_dot(tmp,tmp)
        return 1/self.vector_dot(tmp,np.exp(z))


    def calSigleLayer(self, l, x, y):
        if(l==0):
            self.Z[l]=x
            self.A[l]=x
            return x
        a=self.calSigleLayer(l-1, x, y)
        z=self.W[l-1]*a+self.B[l-1]
        self.Z[l]=z
        z=self.f(z)
        self.A[l]=z
        return z


    def gradient_J(self,l,x,y):
        if(l==self.L-1):
            tmp=-1*(y-self.A[l])
            self.delta[l]=self.vector_dot(tmp,self.ff(self.Z[l]))
            return self.delta[l]
        else:
            tmp=self.W[l].T*self.delta[l+1]
            self.delta[l]=self.vector_dot(tmp,self.ff(self.Z[l]))
            return self.delta[l]


    def cal(self):
        self.L=3
        self.nodes_count=[0]*self.L
        self.nodes_count[0]=self.mx#+1
        self.nodes_count[self.L-1]=self.my
        for l in range(1,self.L-1):
            n=raw_input('Please input the count of nodes in layer '+str(l)+':')
            try:
                n=int(n)
            except:
                print('Oh, god!')
            self.nodes_count[l]=n#+1

        self.W=[]
        self.B=[]
        for l in range(0,self.L-1):
            tmp=[[0]*self.nodes_count[l]]*self.nodes_count[l+1]
            sigma=0.1
            u=0
            for i in range(self.nodes_count[l]):
                for j in range(self.nodes_count[l+1]):
                    tmp[j][i]=sigma*np.random.randn()+u
            self.W.append(np.matrix(tmp))
            tmp=[]
            for j in range(0,self.nodes_count[l+1]):
                tmp.append(sigma*np.random.randn()+u)
            self.B.append(np.transpose(np.matrix(tmp)))
        #
        for kk in range(0,3):
            self.A=[0]*self.L
            self.Z=[0]*self.L
            self.W_delta=[]
            self.B_delta=[]
            for l in range(0,self.L-1):
                tmp=[[0]*self.nodes_count[l]]*self.nodes_count[l+1]
                self.W_delta.append(np.matrix(tmp))
                tmp=[0]*self.nodes_count[l+1]
                self.B_delta.append(np.transpose(np.matrix(tmp)))

            print('-----------')
            print('第'+str(kk+1)+'次')
            for data in self.data:
                x=data['x']
                y=data['y']
                self.calSigleLayer(self.L-1, x, y)
                print(self.A)
                self.delta=[0]*self.L
                for l in range(0,self.L-1):
                    self.gradient_J(self.L-1-l,x,y)
                for l in range(0,self.L-1):
                    self.W_delta[l]=self.W_delta[l]+self.delta[l+1]*self.A[l].T
                for l in range(0,self.L-1):
                    self.B_delta[l]=self.B_delta[l]+self.delta[l+1]

            alpha=0.1
            lamda=0.00
            print('Delta:')
            print(self.delta)
            for l in range(0,self.L-1):
                self.W[l]=self.W[l]+alpha*(self.W_delta[l]/len(self.data)+lamda*self.W[l])
            for l in range(0,self.L-1):
                self.B[l]=self.B[l]+alpha*self.B_delta[l]/len(self.data)
            print('W:')
            for ww in self.W:
                print(ww)
            print('B:')
            for bb in self.B:
                print(bb)

    def getAns(self):
        self.cal()
        print('最终结果:')
        for data in self.data:
            x=data['x']
            y=data['y']
            print(x)
            tmp=self.calSigleLayer(self.L-1, x, y)
            print(y,tmp)

#include "Tool.h"

struct Node{
    double x;
    double y;
    Node(): x(0), y(0){}
    Node(double x, double y): x(x), y(y){}
};

//拉格朗日插值
void LagrangeInterpolation(){
    cout<<"\n--------拉格朗日插法值求值--------"<<endl;
    cout<<"请输入所求值的横坐标x:";
    Node n[10];
    double x = inputDouble();//横坐标
    cout<<"请输入已知节点个数(1<n<10):";
    int num = inputInt();//节点个数
    if (num>10 || num<2){
        throw myExpection("节点个数数据错误，拉格朗日插值法中止。");
    }
    for (int i = 0; i < num; ++i) {
        cout<<"请输入第"<<i+1<<"个节点值的信息(x y):";
        n[i]=Node(inputDouble(), inputDouble());
    }

    //拉格朗日插值法
    double numerator = 1,L = 0;
    for (int i = 0; i < num; ++i) {
        numerator *= (x - n[i].x);
    }
    for(int i = 0; i < num; ++i){
        double denominator = 1;
        for(int j = 0; j < num; ++j){
            if (i != j) {
                denominator *= (n[i].x - n[j].x);
            }
        }
        L += ((numerator/(x-n[i].x))/(denominator))*(n[i].y);
    }
    cout<<"横坐标为"<<x<<"的点的近似值由拉格朗日插值法得到为:"<<L<<endl;
}

//牛顿插值法
void NewtonInterpolation(){
    cout<<"\n---------牛顿插法值求值----------"<<endl;
    cout<<"由于牛顿插值法具有承袭性，程序将在您每输入一个节点后重新计算对应的近似值"<<endl;
    cout<<"牛顿插值法对多次函数具有较好对精确度，可以尝试对多次函数进行近似"<<endl;
    cout<<"请输入所求值的横坐标x:";
    Node n[10];
    double dv[10][10];//插值
    double x = inputDouble();//横坐标
    double N = 0,w=1;//结果

    //牛顿插值法
    for (int i = 0; i<10 ; ++i) {
        cout<<"您可以输入第"<<i+1<<"个节点值的信息(x y):";
        n[i]=Node(inputDouble(), inputDouble());
        dv[i][0] = n[i].y;
        for (int j = 1; j <= i; ++j) {
            dv[i][j] = (dv[i][j-1] - dv[i-1][j-1])/(n[i].x-n[i-j].x);
        }
        if (i>0) {
            w *= (x - n[i-1].x);
        }
        N += (w * dv[i][i]);
        cout<<"横坐标为"<<x<<"的点的近似值在"<<i+1<<"个节点时由牛顿插值法得到为:"<<N<<endl;
    }
    cout<<"您输入节点数已达10个，程序结束。";
}

int main() {
    cout<<"这里是插值法"<<endl;
    cout<<"您可以随时输入'q'来结束当前任务"<<endl;
    try {
        LagrangeInterpolation();
    }catch (myExpection e){
        cout<<e.what()<<endl;
    }
    try {
        NewtonInterpolation();
    }catch (myExpection e){
        cout<<e.what()<<endl;
    }
    return 0;
}

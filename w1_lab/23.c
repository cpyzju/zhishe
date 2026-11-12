#include<stdio.h>
/*struct carpet{
  int a,b;
  int g,k;
};*/
int number(int x,int y,struct carpet carpet[],int n);
int main(){
  /*int n,x,y;
  struct carpet carpet[10001];
  scanf("%d", &n);
  for(int i=1;i<=n;i++){
    scanf("%d %d %d %d", &carpet[i].a, &carpet[i].b, &carpet[i].g, &carpet[i].k);
  }
  scanf("%d %d", &x, &y);
  int num=number(x,y,carpet,n);
  printf("%d", num);*/
  int n;
  scanf("%d", &n);
  
}
int number(int x,int y,struct carpet carpet[],int n){
  int num=-1;
  for (int i=1;i<=n;i++){
    if(x>=carpet[i].a && x<=carpet[i].g+carpet[i].a && y>=carpet[i].b && y<=carpet[i].k+carpet[i].b){
      num=i;
    }
  }
  return num;
}
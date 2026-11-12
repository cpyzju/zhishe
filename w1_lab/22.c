/*#include<stdio.h>
int mem[100][100];
int matrix(int l,int r,int a[]);
int max(int a,int b);

int main(){
  int row,col;
  scanf("%d %d", &row, &col);
  int a[100][100];
  int sum=0;
  for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
      scanf("%d", &a[i][j]);
    }
  }
  for(int i=0;i<row;i++){
    // 每次新一行，清空记忆数组
    for(int p=0;p<100;p++)
      for(int q=0;q<100;q++)
        mem[p][q] = -1;
    sum += 2*matrix(0, col-1, a[i]);
  }
  printf("%d", sum);
  return 0;
}

int max(int a,int b){
  return a>b?a:b;
}

int matrix(int l,int r,int a[]){
  if(mem[l][r] != -1) return mem[l][r];
  if(l == r){
    return mem[l][r] = a[l];
  }
  int left = matrix(l+1, r, a)*2 + a[l];
  int right = matrix(l, r-1, a)*2 + a[r];
  return mem[l][r] = max(left, right);
}*/
#include <stdio.h>
#include <string.h>

#define MAXLEN 120
#define M 85

typedef struct {
    int num[MAXLEN];
    int len;
} BigInt;

void big_zero(BigInt *x) {
    memset(x->num, 0, sizeof(x->num));
    x->len = 0;
}

void big_fromint(BigInt *x, int v) {
    big_zero(x);
    if (v == 0) {
        x->len = 1;
        return;
    }
    while (v > 0) {
        x->num[x->len++] = v % 10;
        v /= 10;
    }
}

void big_add(BigInt *res, const BigInt *a, const BigInt *b) {
    big_zero(res);
    int carry = 0;
    int ml = (a->len > b->len) ? a->len : b->len;
    for (int i = 0; i < ml; i++) {
        int s = a->num[i] + b->num[i] + carry;
        res->num[i] = s % 10;
        carry = s / 10;
        res->len++;
    }
    if (carry != 0) {
        res->num[res->len++] = carry;
    }
}

void big_mulint(BigInt *res, const BigInt *a, int k) {
    big_zero(res);
    long long carry = 0;
    for (int i = 0; i < a->len; i++) {
        long long s = 1LL * a->num[i] * k + carry;
        res->num[i] = s % 10;
        carry = s / 10;
        res->len++;
    }
    while (carry > 0) {
        res->num[res->len++] = carry % 10;
        carry /= 10;
    }
}

int big_greater(const BigInt *a, const BigInt *b) {
    if (a->len != b->len) return a->len > b->len;
    for (int i = a->len - 1; i >= 0; i--) {
        if (a->num[i] != b->num[i]) return a->num[i] > b->num[i];
    }
    return 0;
}

void big_copy(BigInt *to, const BigInt *from) {
    memcpy(to->num, from->num, sizeof(to->num));
    to->len = from->len;
}

void big_print(const BigInt *x) {
    for (int i = x->len - 1; i >= 0; i--) {
        printf("%d", x->num[i]);
    }
    printf("\n");
}

BigInt dp[M][M];
BigInt pow2[M];
int arr[M];

void solve_one_row(BigInt *ans, int m) {
    for (int l = 1; l <= m; l++) {
        for (int r = 1; r <= m; r++) {
            big_zero(&dp[l][r]);
        }
    }
    for (int len = 1; len <= m; len++) {
        for (int l = 1; l + len - 1 <= m; l++) {
            int r = l + len - 1;
            int k = m - len + 1;
            BigInt opt1, opt2;
            BigInt left;
            big_mulint(&left, &pow2[k], arr[l]);
            big_add(&opt1, &left, &dp[l+1][r]);
            BigInt right;
            big_mulint(&right, &pow2[k], arr[r]);
            big_add(&opt2, &right, &dp[l][r-1]);

            if (big_greater(&opt1, &opt2)) {
                big_copy(&dp[l][r], &opt1);
            } else {
                big_copy(&dp[l][r], &opt2);
            }
        }
    }
    big_copy(ans, &dp[1][m]);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    // pow2[k] = 2^k
    big_fromint(&pow2[1], 2);
    for (int i = 2; i <= m; i++) {
        big_mulint(&pow2[i], &pow2[i-1], 2);
    }

    BigInt total, row_ans;
    big_zero(&total);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &arr[j]);
        }
        solve_one_row(&row_ans, m);
        BigInt temp;
        big_copy(&temp, &total);
        big_add(&total, &temp, &row_ans);
    }
    big_print(&total);
    return 0;
}
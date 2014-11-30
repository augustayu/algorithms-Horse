#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<cstring>
#include<stack>
using namespace std;
// 非递归DFS中树节点的结构体
struct Node {
	int x, y, num; // x, y 为矩阵坐标（0~7， 0~7 ，num为对应的数值，由x，y算出
	int neighbor[8]; // 下一步数组，每一个为对应的方向数组，在运算中使用坐标值，可以访问为0， 反之为1；
};

int dirx[8] = {2,1,-1,-2,-2,-1,1,2};  // x方向数组
int diry[8] = {-1,-2,-2,-1,1,2,2,1}; // y方向数组
int seq[64];  // 记录走的过程
int step;    // 指向seq对应的下标进行赋值, 每走一步step + 1，回溯一次step - 1
int board[8][8]; // 记录已访问的位置，已访问为 1 ，未访问为0
int xy_to_num(int x, int y);     // 计算坐标对应数值，参数为坐标
bool canmove(int x, int y);      // 计算该位置是否可行，参数为坐标
int next_neighbor(int x, int y); // 计算下一位置的可行步数,参数为坐标

int main() {
	int N, min, flag, step, i, nextloc;
	
	while(scanf("%d", &N) && N != -1) {
		stack<Node> t_route;  // 树节点栈
		step = 0;
		memset(board, 0, sizeof(int) * 64);
		// 初始化根节点状态，压栈
		Node ini;
		ini.y = (N-1) % 8;
		ini.x = (N-1) / 8;
		ini.num = N;
		for (i = 0; i < 8; i++) {
			if(canmove(ini.x + dirx[i], ini.y + diry[i]))
				ini.neighbor[i] = 0;
			else
				ini.neighbor[i] = 1;				
		}
		t_route.push(ini);

		while (!t_route.empty()) {
			Node temp = t_route.top();
			board[temp.x][temp.y] = 1; // 栈顶已访问
			seq[step++] = temp.num; // 路径数组赋值
			// 找到路径，退出
			if (step == 64)
				break;
			flag = -1; // 记录有最少可行步数的邻居节点的下标
			min = 8;  // 最少步数
			// 寻找最小步数的节点
			for (i = 0; i < 8; i++) {
				if (temp.neighbor[i] == 0) {
					int t = next_neighbor(temp.x + dirx[i], temp.y + diry[i]);
					if (t <= min ) {
						min = t;
						flag = i;
					}
				}
		    }
			// 找到最小步数的邻居节点
			if (flag != -1) {
				temp.neighbor[flag] = 1; // 在栈顶结点中将该节点设置为已访问	
				// 初始化下一步节点的值，压栈
				Node newnode;
				newnode.x = temp.x + dirx[flag];
				newnode.y = temp.y + diry[flag];
				newnode.num = xy_to_num(newnode.x, newnode.y);
		        for (i = 0; i < 8; i++) {
			       if(canmove(newnode.x + dirx[i], newnode.y + diry[i]))
				     newnode.neighbor[i] = 0;
			       else
				     newnode.neighbor[i] = 1;				
		       }
				t_route.push(newnode);
			}
			// 栈顶节点没有可以行走的下一位置，出栈，设为未访问
			else  {
				t_route.pop();
				board[temp.x][temp.y] = 0;		   
			}
		}
		// output
		if (step == 64) {
			for( i = 0; i < 63; i++)
				printf("%d ", seq[i]);
		     printf("%d\n", seq[i]);
		}	
		else
			printf("-1\n");
    }
	return 0;
}

int xy_to_num(int x, int y) {
	return x * 8 + y + 1;
}
bool canmove(int x, int y) {
	if(x >= 0 && x <= 7 && y >= 0 && y <= 7 && board[x][y] == 0)
		return true;
	return false;
}
int next_neighbor(int x, int y) {
	int i, num;
	for (i = 0, num = 0; i < 8; i++)
		if(canmove(x + dirx[i], y + diry[i]))
			num++;
	return num;
}

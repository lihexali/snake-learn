// snake-learn.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <time.h>

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)? true : false)

//位置信息结构体
struct sPos {
	int nRow;
	int nCol;
	int nRowBk;
	int nColBk;
};

//蛇头移动方向
enum E_DIR {
	E_NULL,
	E_UP,
	E_DOWN,
	E_LEFT,
	E_RIGHT
};

using namespace std;
int main()
{
	//地图数据
	int const iMapCol = 20;
	int const iMapRow = 15;
	int arrMap[iMapRow][iMapCol] = {
		 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1
	};

	//蛇头的位置
	sPos snakeHead;
	snakeHead.nRow = 5;
	snakeHead.nCol = 10;
	
	//蛇头移动方向
	E_DIR mvDir = E_NULL;

	//食物的位置
	sPos food;
	//设置随机种子
	srand((unsigned int)time(nullptr));
	while (true) {
		//食物位置在地图空白处随机
		food.nRow = rand() % (iMapRow - 2) + 1; //rand() % (15 - 2) + 1
		food.nCol = rand() % (iMapCol - 2) + 1; //rand() % (20 - 2) + 1
		//避免与蛇头重叠
		if (food.nRow != snakeHead.nRow || food.nCol != snakeHead.nCol) {
			break;
		}
	}

	while (true) {
		system("cls");

		//备份蛇头坐标
		snakeHead.nRowBk = snakeHead.nRow;
		snakeHead.nColBk = snakeHead.nCol;

		//玩家控制蛇头移动方向
		if (KEY_DOWN(VK_UP)) {
			mvDir = E_UP;
		}
		if (KEY_DOWN(VK_DOWN)) {
			mvDir = E_DOWN;
		}
		if (KEY_DOWN(VK_LEFT)) {
			mvDir = E_LEFT;
		}
		if (KEY_DOWN(VK_RIGHT)) {
			mvDir = E_RIGHT;
		}

		//根据移动方向持续移动蛇头
		switch (mvDir) {
			case E_NULL:
				break;
			case E_UP:
				snakeHead.nRow--;
				break;
			case E_DOWN:
				snakeHead.nRow++;
				break;
			case E_LEFT:
				snakeHead.nCol--;
				break;
			case E_RIGHT:
				snakeHead.nCol++;
				break;
			default:
				break;
		}

		//撞墙判断
		for (int row = 0; row < iMapRow; row++) {
			for (int col = 0; col < iMapCol; col++) {
				if (1 == arrMap[row][col]
					&& (snakeHead.nRow == row && snakeHead.nCol == col)) { //蛇头撞墙了
					//还原蛇头坐标
					snakeHead.nRow = snakeHead.nRowBk;
					snakeHead.nCol = snakeHead.nColBk;
				}
			}
		}

		//画地图
		for (int row = 0; row < iMapRow; row++) {
			for (int col = 0; col < iMapCol; col++) {
				if (1 == arrMap[row][col]) {
					cout << "■";
				}
				else {
					if (food.nRow == row && food.nCol == col) { //绘制食物
						cout << "△";
					}else if (snakeHead.nRow == row && snakeHead.nCol == col) { //绘制蛇头
						cout << "☆";
					}
					else {
						cout << "  ";
					}
				}
			}
			cout << endl;
		}
	}

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

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

	//最大蛇长
	int const nSnakeLen = 10;
	//存储蛇身体
	sPos arrSnake[nSnakeLen];
	//当前蛇长
	int nCurSnakeLen = 2;
	//蛇头的位置
	arrSnake[0].nRow = 5;
	arrSnake[0].nCol = 10;
	//添加一个蛇身体
	arrSnake[1].nRow = 5;
	arrSnake[1].nCol = 11;
	
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
		//避免与蛇重叠
		bool bRetry = false;
		for (int i = 0; i < nCurSnakeLen; i++) {
			if (food.nRow == arrSnake[i].nRow && food.nCol == arrSnake[i].nCol) {
				bRetry = true; //需要重新生成
				break;
			}
		}
		if (!bRetry){
				break;
		}
	}

	//游戏状态标志
	bool isGameOver = false;
	bool isWin = false;
	while (!isGameOver) {
		system("cls");

		//备份蛇头坐标
		for (int i = 0; i < nCurSnakeLen; i++){
			arrSnake[i].nRowBk = arrSnake[i].nRow;
			arrSnake[i].nColBk = arrSnake[i].nCol;
		}

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
		bool bMoved = false;
		switch (mvDir) {
			case E_NULL:
				break;
			case E_UP:
				arrSnake[0].nRow--;
				bMoved = true;
				break;
			case E_DOWN:
				arrSnake[0].nRow++;
				bMoved = true;
				break;
			case E_LEFT:
				arrSnake[0].nCol--;
				bMoved = true;
				break;
			case E_RIGHT:
				arrSnake[0].nCol++;
				bMoved = true;
				break;
			default:
				break;
		}

		//撞墙判断
		for (int row = 0; row < iMapRow; row++) {
			for (int col = 0; col < iMapCol; col++) {
				if (1 == arrMap[row][col]
					&& (arrSnake[0].nRow == row && arrSnake[0].nCol == col)) { //蛇头撞墙了
					//还原蛇头坐标
					arrSnake[0].nRow = arrSnake[0].nRowBk;
					arrSnake[0].nCol = arrSnake[0].nColBk;
					bMoved = false;
				}
			}
		}

		//吃到食物
		if (arrSnake[0].nRow == food.nRow && arrSnake[0].nCol == food.nCol) {
			nCurSnakeLen++;
			if (nCurSnakeLen >= nSnakeLen) {
				isWin = true;
				isGameOver = true;
			}
			if (!isGameOver) {
				//重新生成食物（copy 前面的生成代码）
				while (true) {
					//食物位置在地图空白处随机
					food.nRow = rand() % (iMapRow - 2) + 1; //rand() % (15 - 2) + 1
					food.nCol = rand() % (iMapCol - 2) + 1; //rand() % (20 - 2) + 1
					//避免与蛇重叠
					bool bRetry = false;
					for (int i = 0; i < nCurSnakeLen; i++) {
						if (food.nRow == arrSnake[i].nRow && food.nCol == arrSnake[i].nCol) {
							bRetry = true; //需要重新生成
							break;
						}
					}
					if (!bRetry) {
						break;
					}
				}
			}
		}


		//移动蛇身体
		if (bMoved) {
			for (int i = nCurSnakeLen - 1; i > 0; i--) {
				arrSnake[i].nRow = arrSnake[i - 1].nRowBk;
				arrSnake[i].nCol = arrSnake[i - 1].nColBk;
			}
		}


		//画地图
		for (int row = 0; row < iMapRow; row++) {
			for (int col = 0; col < iMapCol; col++) {
				if (1 == arrMap[row][col]) {
					cout << "■";
				}
				else {
					bool bDrawSnakebody = false;
					for (int i = 1; i < nCurSnakeLen; i++)
					{
						if (arrSnake[i].nRow == row && arrSnake[i].nCol == col) {
							bDrawSnakebody = true;
							break;
						}
					}
					if (food.nRow == row && food.nCol == col) { //绘制食物
						cout << "△";
					}else if (arrSnake[0].nRow == row && arrSnake[0].nCol == col) { //绘制蛇头
						cout << "☆";
					}
					else if (bDrawSnakebody) { //绘制蛇头
						cout << "○";
					}
					else {
						cout << "  ";
					}
				}
			}
			cout << endl;
		}
	}

	if (isWin) {
		cout << "Win!" << endl;
	}
	else {
		cout << "Fail" << endl;
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

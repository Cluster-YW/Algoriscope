#ifndef RENDER_H
#define RENDER_H

#include "shader.h"
#include "vector2.h"
#include "color.h"

namespace Algoriscope {
	class Render {
		private:
			vector2 size;//画布/场景尺寸
		public:
			//构造函数，进行相关初始化。
			Render() {

			}

			//析构函数，进行收尾工作
			~Render() {

			}
			//负责帧的更新
			int update() {

			}

			//检测按键是否按下
			//key - 按下哪个键
			//options - 检测功能键（如ctrl,shift）等
			bool isKeyDown(const char& key, const char* options = "") const {

			}

			//画直线
			//pos1 - 起点位置
			//pos2 - 终点位置
			//color - 线的颜色
			int drawLine(const vector2& pos1, const vector2& pos2, const color& col) {

			}

			//画三角形
			//3个点+颜色
			int drawTri(const vector2& pos1, const vector2& pos2, const vector2& pos3, const color& col) {

			}

			//画矩形
			// pos - 起始点
			// size - 尺寸（宽和高）
			// color - 颜色
			int drawRect(const vector2& pos, const vector2& size, const color& col) {

			}

			int drawText(const vector2& pos, const char*)

	};
}

#endif

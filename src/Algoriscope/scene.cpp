#include "scene.h"


namespace Algoriscope {
	Scene::Scene(int x, int y, int _FPS):
		size(x, y), render(x, y), FPS(_FPS), background("#222222") {
		root = new Object;
	}

	int Scene::setTitle(const char*name) {
		render.setTitle(name);
		return 0;
	}

	void Scene::debug_info_draw(int i) {
		string key_change_string = "";
		render.drawLine(Vector2(-size.x, 0), Vector2(size.x, 0), Color("#0000FF"));
		render.drawLine(Vector2(0, -size.y), Vector2(0, size.y), Color("#FF0000"));
		render.drawText(Vector2(size.x * 0.5f - 20, 15), 5,
		                util::Format("{0}", size.x * 0.5f), "#0000FF");
		render.drawText(Vector2(20, size.y * 0.5f - 15), 5,
		                util::Format("{0}", size.y * 0.5f), "#FF0000");
		//绘制坐标轴

		render.drawText(Vector2(-size.x * 0.5f + 30, size.y * 0.5f - 30.0f), 5, "#" + to_string(i), "#FFFFFF", "l");
		//绘制帧序号


		Color mouse_line_color("lightgrey");
		if (input.mouse_left_down) {
			mouse_line_color = "#FF0000";
			if (input.mouse_right_down)
				mouse_line_color = "#00FF00";
		} else if (input.mouse_right_down) {
			mouse_line_color = "#0000FF";
		}
		auto &mousepos = input.mousepos;
		render.drawLine(Vector2(-size.x, mousepos.y), Vector2(size.x, mousepos.y), mouse_line_color, 2);
		render.drawLine(Vector2(mousepos.x, -size.y), Vector2(mousepos.x, size.y), mouse_line_color, 2);
		render.drawText(mousepos + Vector2(5, 5), 3,
		                util::Format("({0},{1})", mousepos.x, mousepos.y), "white", "ld");
		//绘制鼠标位置


		string key_string = "KEYBOARD:";
		for (auto c : input.key_all) {
			if (input.key_down[(int)c]) key_string += c;
			if (input.key_change[(int)c] == 1) key_change_string += c, key_change_string += "_";
			if (input.key_change[(int)c] == -1) key_change_string += c, key_change_string += "^";
		}
		render.drawText(Vector2(-size.x * 0.5f + 30, size.y * 0.5f - 60.0f), 5, key_string, "#FFFFFF", "l");
		render.drawText(Vector2(-size.x * 0.5f + 30, size.y * 0.5f - 90.0f), 5, key_change_string, "#FFFFFF", "l");
		//绘制键盘事件
	}

	int Scene::run(int time, bool canbreak) {

		float timer = 0.0f;
		clock_t last, now;
		last = now = clock();

		auto i = 0;
		while (running) {
			glfwPollEvents();
			now = clock();
			if (now - last < CLOCKS_PER_SEC / FPS) {
				continue;
			}

			float deltatime = 1.0f / FPS;

			if (!paused) {
				timer += 1000.0f * (now - last) / CLOCKS_PER_SEC;
				this->timer += 1000.0f * (now - last) / CLOCKS_PER_SEC;
				i++;
			}
			last = now;// 稳定帧率


			if (time > 0) {
				if (timer > time) {
					break;
				}
			}

			processInput();

			render.update(background);

			if (!paused)
				root->update(deltatime, input);

			root->draw(render);

			if (debug_mode) {
				debug_info_draw(i);

				root -> debug_draw(render);
			}

			if (paused) {
				render.drawText(Vector2(0, size.y * 0.4f), 10, "PAUSED", "#FFFFFF", "m");
			}//输出暂停标志


			if (input.key_change[' '] == 1) {
				break;
			}
			if (input.key_down['\n']) {
				break;
			}
			if (input.key_change[GLFW_KEY_F12] == -1) {
				debug_mode = !debug_mode;
			}
			if (glfwWindowShouldClose(render.getw())) {
				running = 0 ;
				break;
			}
			if (input.key_change['P'] == 1) {
				paused = !paused;
			}

			if (debug_function != nullptr)
				debug_function(this, &render, input);
		}
		cout << "loopend" << endl;
		return 0;
	}
	void Scene::processInput() {
		auto window = render.getw();

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		input.mousepos_screen = Vector2(xpos, ypos);
		input.mousepos = Vector2(input.mousepos_screen[0] - size[0] * 0.5f, -input.mousepos_screen[1] + size[1] * 0.5f);
		input.mouse_left_down = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS ? 1 : 0;
		input.mouse_right_down = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS ? 1 : 0;
		// 鼠标输入获取

		auto &key_all = input.key_all;
		auto &key_down = input.key_down;
		auto &key_change = input.key_change;

		for (auto k : key_all) {
			auto now_state = glfwGetKey(window, k);
			if (k == '\n')
				now_state = glfwGetKey(window, GLFW_KEY_ENTER);
			if (now_state > key_down[(int)k]) key_change[(int)k] = 1;
			else if (now_state < key_down[(int)k]) key_change[(int)k] = -1;
			else key_change[(int)k] = 0;
			key_down[(int)k] = now_state;
		}
		for (auto k = GLFW_KEY_F1; k <= GLFW_KEY_F14; k++) {
			auto now_state = glfwGetKey(window, k);
			if (now_state > key_down[(int)k]) key_change[(int)k] = 1;
			else if (now_state < key_down[(int)k]) key_change[(int)k] = -1;
			else key_change[(int)k] = 0;
			key_down[(int)k] = now_state;
		}
		// 键盘输入获取
	}
}



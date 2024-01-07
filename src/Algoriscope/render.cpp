#include "render.h"
#define  MAX_CHAR 128
namespace Algoriscope {
	Render::Render() : size (800.0f,600.0f) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		window = glfwCreateWindow(size.x, size.y, "Computer Graphics", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glewExperimental = true;
		glewInit();
		glViewport(0, 0, size.x, size.y);
	}
	
	//析构函数，进行收尾工作
	Render::~Render() {
		glfwTerminate();
	}
	//负责帧的更新
	int Render::update() {
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.init("vertexShaderDrawLines.glsl","fragmentShader_frag=vertexDrawLines.glsl");
		shader.use();

		return 0;
	}
	
	//检测按键是否按下
	//key - 按下哪个键
	//options - 检测功能键（如ctrl,shift）等
	bool Render::isKeyDown(const char& key, const char* options) const {
		
		return 0;
	}
	
	//画直线
	//pos1 - 起点位置
	//pos2 - 终点位置
	//color - 线的颜色
	int Render::drawLine(const Vector2& pos1, const Vector2& pos2, const Color& col) {
		glLineWidth(10.0f);
		const float line[] = {
			pos1.x,pos1.y,0.0,
			pos2.x,pos2.y,0.0
//			0.0f, 0.0f, 0.0f,
//			0.2f, 0.5f, 0.0f
		};
		GLuint vertex_array_object;//VAO,使用核心模式，只需调用一次
		glGenVertexArrays(1, &vertex_array_object);//先生成
		glBindVertexArray(vertex_array_object);//再绑定
		
		GLuint vertex_buffer_object;//VBO
		glGenBuffers(1, &vertex_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object); //将顶点数据绑定至当前默认的缓冲中
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //设置顶点属性指针//试着去了解各个参数的意义
		glEnableVertexAttribArray(0);//开启通道
		
		glBindVertexArray(vertex_array_object);
		
		shader.setFloat4("inputColor",col.getRf(),col.getGf(),col.getBf(),col.getAf());
		
		glDrawArrays(GL_LINES, 0, 2);

		return 1;
	}
	
	//画三角形
	//3个点+颜色
	int Render::drawTri(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Color& col) {
		const float vertices[] = {
			pos1.x,pos1.y,0.0,
			pos2.x,pos2.y,0.0,
			pos3.x,pos3.y,0.0,
		};
		GLuint VAO,VBO,EBO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO); 
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(VAO);
		shader.setFloat4("inputColor",col.getRf(),col.getGf(),col.getBf(),col.getAf());
		glDrawArrays(GL_TRIANGLES, 0, 6);
		return 0;
	}
	
	//画矩形
	// pos - 起始点
	// size - 尺寸（宽和高）
	// color - 颜色
	int Render::drawRect(const Vector2& pos, const Vector2& size, const Color& col) {
		const float vertices[] = {
			pos.x,pos.y,0.0,
			pos.x+size.x,pos.y,0.0,
			pos.x,pos.y+size.y,0.0,
			pos.x+size.x,pos.y+size.y,0.0
		};
		unsigned int indices[] = { 
			0, 1, 2, 
			1, 2, 3 
		}; 
		GLuint VAO,VBO,EBO;
		glGenVertexArrays(1, &VAO); 
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO); 
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(VAO);
		shader.setFloat4("inputColor",col.getRf(),col.getGf(),col.getBf(),col.getAf());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		return 0;
	}
	
	int Render::drawRectBorder(const Vector2& pos, const Vector2& size, const Color&col, const float width)
	{
		glLineWidth(width);
		const float line[] = {
			pos.x,pos.y,0.0,
			pos.x+size.x,pos.y,0.0,
			pos.x+size.x,pos.y,0.0,
			pos.x+size.x,pos.y+size.y,0.0,
			pos.x+size.x,pos.y+size.y,0.0,
			pos.x,pos.y+size.y,0.0,
			pos.x,pos.y,0.0,
			pos.x,pos.y+size.y,0.0
		};
		GLuint vertex_array_object;//VAO,使用核心模式，只需调用一次
		glGenVertexArrays(1, &vertex_array_object);//先生成
		glBindVertexArray(vertex_array_object);//再绑定
		GLuint vertex_buffer_object;//VBO
		glGenBuffers(1, &vertex_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object); //将顶点数据绑定至当前默认的缓冲中
		glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //设置顶点属性指针//试着去了解各个参数的意义
		glEnableVertexAttribArray(0);//开启通道
		glBindVertexArray(vertex_array_object);
		shader.setFloat4("inputColor",col.getRf(),col.getGf(),col.getBf(),col.getAf());
		glDrawArrays(GL_LINES, 0, 8);
		return 0;
	}

	int Render::drawText(Vector2& pos,GLfloat scale ,std::string text,Color iColor){
		glm::vec3 color(iColor.getRf(),iColor.getGf(),iColor.getBf());
		GLuint WIDTH = 800, HEIGHT = 600;
		struct Character {
			GLuint TextureID;   // 字形纹理ID
			glm::ivec2 Size;    // 字形大小
			glm::ivec2 Bearing;  // 字形基于基线和起点的位置？
			GLuint Advance;    // 起点到下一个字形起点的距离？
		};
		std::map<GLchar, Character> Characters;
		GLuint VAO, VBO;
		
		
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Compile and setup the shader
		Shader shader("shaders/text.vs", "shaders/text.fs");
		glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));
		shader.use();
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		
		FT_Face face;
		if (FT_New_Face(ft, "fonts/font.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

		FT_Set_Pixel_Sizes(face, 0, 48);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
		for (GLubyte c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
				);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			Characters.insert(std::pair<GLchar, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		// Destroy FreeType once we're finished
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		

		
		glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);
		
		// Iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++) 
		{
			Character ch = Characters[*c];
			
			GLfloat xpos = pos.x + ch.Bearing.x * scale;
			GLfloat ypos = pos.y - (ch.Size.y - ch.Bearing.y) * scale;
			
			GLfloat w = ch.Size.x * scale;
			GLfloat h = ch.Size.y * scale;
			// Update VBO for each character
			GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },            
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }           
			};
			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			pos.x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
//		
		return 0;
	}

};

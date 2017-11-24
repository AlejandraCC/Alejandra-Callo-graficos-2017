
#include <iostream>

using namespace std;

#include <GL/glew.h>
#include <GL/glut.h>
#define GLEW_STATIC




const GLint width = 1200, height = 800;

const char *vertexShaderSource = "#version 410 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 r;\n"
"mat3 scale = mat3(0.08, 0.0, 0.0, 0.0, 0.08, 0.0, 0.0, 0.0, 0.08);\n"
"float rx = r.x;"
"float ry = r.y;"
"mat3 Rx = mat3(vec3(1, 0, 0),\n"
"              vec3(0, cos(rx), sin(rx)),\n"
"              vec3(0, -sin(rx), cos(rx)));\n"
"mat3 Ry = mat3(vec3(cos(ry), 0, -sin(ry)),\n"
"               vec3(0, 1, 0),\n"
"               vec3(-sin(ry), 0, cos(ry)));\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"vec3 po2=Rx * Ry * scale * aPos; \n"
"   gl_Position = vec4( po2.x, po2.y, po2.z, 1.0);\n"
"}\0";

const char *fragmentShaderSource = "#version 410 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor =vec4(1.000, 0.078, 0.576, 1.0f);\n"

"}\n\0";

unsigned int VBO, VAO, EBO;
int shaderProgram;
int vertexShader;
int fragmentShader;

static int ejex = 0, ejey = 0;
static int estado = 0;
static float rotarx = 0.0f, rotary = 0.0f;


float vertices[] = {
	//A-----------
	 2,0,1 , 
	 2,0,3 ,
	 4,2,1 , 
	 4,2,3 ,
	5,0,1 , 
	5,0,3 ,
	 4.5,1,1 ,
	 4.5,1,3 ,
	 3.0,1,1 , 
	 3.0,1,3 ,
	//c------------
	 1,2,1 ,
	 1,2,3 ,
	 -1,2,1,
	 -1,2,3,
	 -1,0,1 ,
	 -1,0,3 ,
	 1,0,1 ,
	 1,0,3 ,
	 //c------------
	-3,2,1 ,
	-3,2,3 ,
	-5,2,1,
	-5,2,3,
	-5,0,1 ,
	-5,0,3 ,
	-3,0,1 ,
	-3,0,3,
	//A-----------
	-10,0,1 ,
	-10,0,3 ,
	-8,2,1 ,
	-8,2,3 ,
	-7,0,1 ,
	-7,0,3 ,
	-8.5,1,1 ,
	-8.5,1,3 ,
	-9.0,1,1 ,
	-9.0,1,3 ,

	
};
unsigned int indices[] = {  // note that we start from 0!
	0,1,3,2,
	2,3,5,4,
	4,5,7,6,
	6,7,9,8,


	
	10,11,13,12,
	12,13,15,14,
	14,15,17,16,
	//2,3,4,5
	
	18,19,21,20,
	20, 21,23,22,
	22,23,25,24,

	26,27,29,28,
	28,29,31,30,
	30,31,33,32,
	32,33,35,34,

};

void init() {
	// ------------------------------------
	// vertex shader
	 vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// comprobamos si hay errores de compilacion

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// comprobamos si hay errores de compilacion
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	 shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//comprobando errores check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO); //buffer del indice
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


	glUseProgram(shaderProgram);

}
void dibujar() {
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	// 
	// ---------------------------
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	// render the triangle
	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS,56, GL_UNSIGNED_INT, 0);

	

	glutSwapBuffers();

}


void mousefunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			estado = 1;
		}
		else {
			estado = 0;
		}
	}
}

void motionfunc(int x, int y)
{
	if (estado>0) {
		if (estado>1) {
			rotarx += 2.0f*(x - ejex) / width;
			rotary += 2.0f*(y - ejey) / height;
		}

		ejex = x;
		ejey = y;
		glUseProgram(shaderProgram);
		glVertexAttrib2f(1, rotary, -rotarx);
		

		estado = 2;
	}
	//vector<GLfloat [3]> v;
}

void keyboardfunc(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 27) exit(0);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Practica 1");
	if (glewInit()!=GLEW_OK) {
		cout << "error XD" << endl;
	}
	init();

	glutDisplayFunc(dibujar);
	glutMouseFunc(mousefunc);
	glutMotionFunc(motionfunc);
	glutKeyboardFunc(keyboardfunc);
	glutIdleFunc(dibujar);
	glutMainLoop();

	
	

	return 0;
}
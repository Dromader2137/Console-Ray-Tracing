#include "Vector3f.h"
#include "Rendering.h"
#include "Shapes.h"

#include <Windows.h>


#define WIDTH 115
#define HEIGTH 60

int main()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	Camera camera(WIDTH, HEIGTH, .60f);
	camera.position = Vector3f(0, 0, -2);
	Light light(Vector3f(16, 0, -6));

	std::vector<Sphere> spheres;
	spheres.push_back(Sphere(Vector3f(0, 0, 6), .8f));
	spheres.push_back(Sphere(Vector3f(), .2f));
	spheres.push_back(Sphere(Vector3f(), .4f));
	spheres.push_back(Sphere(Vector3f(), .1f));
	spheres.push_back(Sphere(Vector3f(), .5f));

	float t = 0;

	char prevBuff[WIDTH][HEIGTH];
	std::memset(&prevBuff, 0, WIDTH * HEIGTH);
	char frameCB[WIDTH][HEIGTH];

	while (true)
	{
		// PER FRAME LOGIC

		t += .016f;
		spheres[1].position = Vector3f(sin(t * 2), sin(t * 2) * -0.2, cos(t * 2)) * 1.4f + Vector3f(0, 0, 6);
		spheres[2].position = Vector3f(sin(t), sin(t) * 0.3, cos(t)) * 2.3f + Vector3f(0, 0, 6);
		spheres[3].position = Vector3f(sin(t * 3) * 0.8, sin(t * 3), cos(t * 3)) * 1.05f + Vector3f(0, 0, 6);
		spheres[4].position = Vector3f(sin(t / 2), sin(t / 2) * 0.1, cos(t / 2)) * 3.2f + Vector3f(0, 0, 6);

		// RENDERING

		std::string frame = camera.Render(&spheres, &light);
		for (short int y = 0; y < HEIGTH; ++y)
		{
			for (short int x = 0; x < WIDTH; ++x)
			{
				frameCB[x][y] = frame[y * WIDTH + x];

				if (frameCB[x][y] == prevBuff[x][y]) {
					continue;
				}
				
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(x * 2), y});
				std::cout << frameCB[x][y];
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(x * 2 + 1), y});
				std::cout << frameCB[x][y];
			}
		}
		std::cout.flush();
		std::memcpy(&prevBuff, &frameCB, WIDTH * HEIGTH);

		// 60 FPS LIMITER

		Sleep(16);
	}
}
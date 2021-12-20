#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// these macros are not correct!!!
#define GLFW_JOYSTICK_BTN_DOWN 0			    //   A
#define GLFW_JOYSTICK_BTN_RIGHT 1				//   B
#define GLFW_JOYSTICK_BTN_LEFT 2                //   X
#define GLFW_JOYSTICK_BTN_UP 3                  //   Y   
#define GLFW_JOYSTICK_SHOULDER_LEFT 4           //   LB
#define GLFW_JOYSTICK_SHOULDER_RIGHT 5          //   RB
#define GLFW_JOYSTICK_TRIGGER_LEFT 6            //   RS
#define GLFW_JOYSTICK_TRIGGER_RIGHT 7           //   LT
#define GLFW_JOYSTICK_SELECT 8                  //   Address
#define GLFW_JOYSTICK_START 9                   //   Menu
#define GLFW_JOYSTICK_LEFT_STICK 10             //   LS
#define GLFW_JOYSTICK_RIGHT_STICK 11            //   RS
#define GLFW_JOYSTICK_HOME 12                   //   Home
#define GLFW_JOYSTICK_CLICK 13                  //   n/a
#define GLFW_JOYSTICK_DPAD_UP 14                //   Dpad up
#define GLFW_JOYSTICK_DPAD_RIGHT 15             //   Dpad right
#define GLFW_JOYSTICK_DPAD_DOWN 16              //   Dpad down
#define GLFW_JOYSTICK_DPAD_LEFT 17              //   Dpad left

// axes
#define GLFW_JOYSTICK_AXES_LEFT_STICK_X 0
#define GLFW_JOYSTICK_AXES_LEFT_STICK_Y 1
#define GLFW_JOYSTICK_AXES_RIGHT_STICK_X 2
#define GLFW_JOYSTICK_AXES_RIGHT_STICK_Y 3
#define GLFW_JOYSTICK_AXES_LEFT_TRIGGER 4
#define GLFW_JOYSTICK_AXES_RIGHT_TRIGGER 5


class Joystick {
public:
	Joystick(int i);

	void update();

	float axesState(int axis);
	unsigned char buttonState(int button);

	int getAxesCount();
	int getButtonCount();

	bool isPresent();
	const char* getName();

	static int getId(int i);

private:
	int present;

	int id;

	const char* name;

	int axesCount;
	const float* axes;

	int buttonCount;
	const unsigned char* buttons;


};

#endif // !JOYSTICK_H

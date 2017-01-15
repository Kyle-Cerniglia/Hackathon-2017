/**********************************************************************************/

#include <math.h>

/**********************************************************************************/

void getDestination(float& angle, int& xFin, int& yFin);

void goStraight();
void turnRight(char& dir);
void turnLeft(char& dir);

bool canTurnRight(int& xPos, int& yPos, char& dir);
bool canGoStraight(int& xPos, int& yPos, char& dir);

void keepRight(int& xPos, int& yPos, char& dir);

/**********************************************************************************/

bool grid[32][32];

int main(){

	int xPos = 0, yPos = 0;
	int xFin = 31, yFin = 31;
	float angle = 0;
	char dir = 'r';

	for (int i = 0; i < 31; i++)
		for (int j = 0; j <31; j++)
			grid[i][j] = true;

	getDestination(angle, xFin, yFin);

	while (xPos != xFin && yPos != yFin)
		keepRight(xPos, yPos, dir);

	return 0;
}

/**********************************************************************************/

void keepRight(int& xPos, int& yPos, char& dir) {

	if (canTurnRight(xPos, yPos, dir)) {
		turnRight(dir);
		goStraight();
	}

	else if (canGoStraight(xPos, yPos, dir))
		goStraight();

	else
		turnLeft(dir);

	return;
}

/**********************************************************************************/

void goStraight() {

	//Move for x milliseconds
	return;
}

void turnRight(char& dir) {

	switch(dir) {
		case 'r':
			dir = 'd';
			break;
		case 'l':
			dir = 'u';
			break;
		case 'u':
			dir = 'r';
			break;
		case 'd':
			dir = 'l';
			break;
		}

	//Turn for x milliseconds
	return;
}

void turnLeft(char& dir) {

	switch(dir) {
		case 'r':
			dir = 'u';
			break;
		case 'l':
			dir = 'd';
			break;
		case 'u':
			dir = 'l';
			break;
		case 'd':
			dir = 'r';
			break;
		}

	//Turn for x milliseconds
	return;
}

bool canTurnRight(int& xPos, int& yPos, char& dir) {

	switch(dir) {
		case 'r':
			if (yPos != 0 && grid[xPos][yPos - 1] != false)
				return true;
			break;
		case 'l':
			if (yPos != 31 && grid[xPos][yPos + 1] != false)
				return true;
			break;
		case 'u':
			if (xPos != 31 && grid[xPos + 1][yPos] != false)
				return true;
			break;
		case 'd':
			if (xPos != 0 && grid[xPos - 1][yPos] != false)
				return true;
			break;
	}

	return false;
}

bool canGoStraight(int& xPos, int& yPos, char& dir) {

	switch(dir) {
		case 'r':
			if (xPos != 31 && grid[xPos + 1][yPos] != false)
				return true;
			break;
		case 'l':
			if (xPos != 0 && grid[xPos - 1][yPos] != false)
				return true;
			break;
		case 'u':
			if (yPos != 31 && grid[xPos][yPos + 1] != false)
				return true;
			break;
		case 'd':
			if (yPos != 0 && grid[xPos][yPos - 1] != false)
				return true;
			break;
	}

	return false;
}

void getDestination(float& angle, int& xFin, int& yFin) {

	if(angle > 45){
		angle = angle * 3.14159265358979 / 180;
		//If the angle is more than 45, that means that it is on the axis y = 16.
		yFin = 31;
		//Now, we use a Taylor Series Approximation to calculate thing instead of using tangent inverse.
        xFin = int(31/tan(angle));
	}

	else if (angle < 45){
		angle = angle * 14159265358979 / 180;
		//If the angle is less than 45, that means that it is on the axis x = 16.
		xFin = 31;
		yFin = int(31*tan(angle));
	}

	//If we reach here, that means that the angle must be 45 degrees, which means that the point is (16, 16).
	else{
		xFin = 31;
		yFin = 31;
	}

	return;
}

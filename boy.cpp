// The boy model. 
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <GL/glu.h>
#include "modelerglobals.h"
#include "camera.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include<chrono>

#define STB_IMAGE_IMPLEMENTATION
//int frameall = 0;
// To make a SampleModel, we inherit off of ModelerView
class Boy : public ModelerView
{
public:
    Boy(int x, int y, int w, int h, char* label)
        : ModelerView(x, y, w, h, label) {
		
	}

    virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char* label)
{
    return new Boy(x, y, w, h, label);
}
int getTime() {
	using namespace std::chrono;
	auto now = system_clock::now();
	auto integral_duration = now.time_since_epoch().count();
	return integral_duration;
}

//GLuint loadBMP_custom(const char* imagepath) {
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	return textureID;
//}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void Boy::draw()
{
	int level = VAL(LEVEL);
	int color = VAL(COLOR);
	float lightIntensity = VAL(LIGHT);
	int mine = VAL(LANDMINE);
	float color1[4] = {0.0,1.0,0.0,1.0};
	float color2[4] = {1.0,0.0,0.0,1.0};
	float color3[4] = {0.0,0.0,1.0,0.0};
	
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...

	//ModelerView::draw();
	GLfloat lightPosition0[] = { 4, 2, -4, 0 };
	GLfloat lightDiffuse0[] = { lightIntensity,lightIntensity,lightIntensity,1 };
	GLfloat lightPosition1[] = { -2, 1, 5, 0 };
	GLfloat lightDiffuse1[] = { lightIntensity, lightIntensity, lightIntensity, 1 };

	if (!valid())
	{
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_NORMALIZE);
	}

	glViewport(0, 0, w(), h());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, float(w()) / float(h()), 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//if (VAL(FRAMEALL) != frameall) {
		//frameall = VAL(FRAMEALL);
	
		//m_camera->setEye(2 * m_camera->getEye());
		
	//}
	//else {
		//m_camera->applyViewingTransform();
	//}
	m_camera->applyViewingTransform();
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse1);
	
	GLuint image = loadBMP_custom("ferry.bmp");
	
	
	if (mine == 1) {
		//draw complex shape
		setDiffuseColor(0.75f, 0.5f, .0f);

		glBegin(GL_QUADS);
		glVertex3d(0, 0, 5);
		glVertex3d(0, 0, 6);
		glVertex3d(1, 0, 6);
		glVertex3d(1, 0, 5);


		glEnd();

		glBegin(GL_TRIANGLES);
		setDiffuseColor(0.75f, 0.5f, 0.0f);

		glVertex3d(0, 1, 6);glVertex3d(1, 1, 6);glVertex3d(0.5, 2, 5.5);
		glVertex3d(0, 1, 6);glVertex3d(1, 1, 5);glVertex3d(0.5, 2, 5.5);
		glVertex3d(0, 1, 5);glVertex3d(1, 1, 5);glVertex3d(0.5, 2, 5.5);
		glVertex3d(1, 1, 5);glVertex3d(1, 1, 6);glVertex3d(0.5, 2, 5.5);

		//setDiffuseColor(0.0f, 0.5f, 0.0f);
		setDiffuseColor(0.75f, 0.5f, .0f);
		glVertex3d(0, 1, 6);glVertex3d(1, 1, 6);glVertex3d(0.5, 0.5, 8);
		glVertex3d(0, 1, 6);glVertex3d(0, 0, 6);glVertex3d(0.5, 0.5, 8);
		glVertex3d(0, 0, 6);glVertex3d(1, 0, 6);glVertex3d(0.5, 0.5, 8);
		glVertex3d(1, 0, 6);glVertex3d(1, 1, 6);glVertex3d(0.5, 0.5, 8);

		glVertex3d(0, 0, 5);glVertex3d(0, 0, 6);glVertex3d(-2, 0.5, 5.5);
		glVertex3d(0, 0, 6);glVertex3d(0, 1, 6);glVertex3d(-2, 0.5, 5.5);
		glVertex3d(0, 1, 6);glVertex3d(0, 1, 5);glVertex3d(-2, 0.5, 5.5);
		glVertex3d(0, 1, 5);glVertex3d(0, 0, 5);glVertex3d(-2, 0.5, 5.5);

		glVertex3d(1, 0, 6);glVertex3d(1, 0, 5);glVertex3d(3, 0.5, 5.5);
		glVertex3d(1, 0, 5);glVertex3d(1, 1, 5);glVertex3d(3, 0.5, 5.5);
		glVertex3d(1, 1, 5);glVertex3d(1, 1, 6);glVertex3d(3, 0.5, 5.5);
		glVertex3d(1, 1, 6);glVertex3d(1, 0, 6);glVertex3d(3, 0.5, 5.5);

		glVertex3d(0, 0, 5);glVertex3d(1, 0, 5);glVertex3d(0.5, 0.5, 3);
		glVertex3d(1, 0, 5);glVertex3d(1, 1, 5);glVertex3d(0.5, 0.5, 3);
		glVertex3d(1, 1, 5);glVertex3d(0, 1, 5);glVertex3d(0.5, 0.5, 3);
		glVertex3d(0, 1, 5);glVertex3d(0, 0, 5);glVertex3d(0.5, 0.5, 3);
		glEnd();
	}
	//surrender
	if (VAL(SURRENDER) == 1) {
		setDiffuseColor(1.0f,1.0f,1.0f);

		glBegin(GL_QUADS);
		glVertex3d(-4, 0, 5.5);
		glVertex3d(-4.1, 0, 5.5);
		glVertex3d(-4.1, 2, 5.5);
		glVertex3d(-4, 2, 5.5);

		glVertex3d(-4.1, 0, 5.5);
		glVertex3d(-4.1, 0, 5.6);
		glVertex3d(-4.1, 2, 5.6);
		glVertex3d(-4.1, 2, 5.5);

		glVertex3d(-4, 0, 5.6);
		glVertex3d(-4.1, 0, 5.6);
		glVertex3d(-4.1, 2, 5.6);
		glVertex3d(-4, 2, 5.6);

		glVertex3d(-4, 0, 5.5);
		glVertex3d(-4, 2, 5.5);
		glVertex3d(-4, 2, 5.6);
		glVertex3d(-4, 0, 5.6);

		glVertex3d(-4, 1, 5.5);
		glVertex3d(-4, 2, 5.5);
		glVertex3d(-3, 2, 5.5);
		glVertex3d(-3, 1, 5.5);


		glEnd();
	}
	// draw the model
	setAmbientColor(.0f, .0f, .0f);
	switch (color) {
		case 0:
			setDiffuseColor(1.0f, 0.0f, 0.0f);
			break;
		case 1:
			setDiffuseColor(0.0f, 0.0f, 1.0f);
			break;
		case 2:
			setDiffuseColor(1.0f, 1.0f, 0.0f);
			break;
		case 3:
			setDiffuseColor(COLOR_GREEN);
			break;
	}
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

	glPushMatrix();
	glTranslated(-1.5, 0, -2);
	glScaled(3, 5, 4);
	drawBox(1, 1, 1);
	glPopMatrix();

	/*GLuint image = loadBMP_custom("ferry.bmp");
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glNormal3d(0.0, 0.0, -1.0);
	glTexCoord2f(0.0, 0.0); glVertex3d(-1.5, 0, 2.0);
	glTexCoord2f(1.0, 0.0); glVertex3d(1.5, 0, 2.0);
	glTexCoord2f(1.0, 1.0); glVertex3d(1.5, 5, 2.0);
	glTexCoord2f(0.0, 1.0); glVertex3d(-1.5, 5, 2.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);*/

	// draw wheel
	if (level >= 1) {
		switch (color) {
		case 0:
			setDiffuseColor(0.0f, 1.0f, 0.0f);
			break;
		case 1:
			setDiffuseColor(1.0f, 0.0f, 0.0f);
			break;
		case 2:
			setDiffuseColor(0.0f, 0.0f, 1.0f);
			break;
		case 3:
			setDiffuseColor(1.0f,1.0f,0.0f);
			break;
		}
		glPushMatrix();
		glTranslated(-1.5, 0.2, -1.7);
		glRotated(-90, 0.0, 1.0, 0.0);
		drawCylinder(1, 0.1, 0.1);
		if (level >= 2) {
			switch (color) {
			case 0:
				setDiffuseColor(1.0f, 1.0f, 0.0f);
				break;
			case 1:
				setDiffuseColor(0.0f, 1.0f, 0.0f);
				break;
			case 2:
				setDiffuseColor(1.0f, 0.0f, 0.0f);
				break;
			case 3:
				setDiffuseColor(0.0f, 0.0f, 1.0f);
				break;
			}
			glPushMatrix();
			glTranslated(0, 0, 0.3);
			drawCylinder(1, 1, 1);
			glPopMatrix();
		}
		setDiffuseColor(color1[color], color2[color], color3[color]);
		glTranslated(3.4, 0, 0);
		drawCylinder(1, 0.1, 0.1);
		if (level >= 2) {
			switch (color) {
			case 0:
				setDiffuseColor(1.0f, 1.0f, 0.0f);
				break;
			case 1:
				setDiffuseColor(0.0f, 1.0f, 0.0f);
				break;
			case 2:
				setDiffuseColor(1.0f, 0.0f, 0.0f);
				break;
			case 3:
				setDiffuseColor(0.0f, 0.0f, 1.0f);
				break;
			}
			glPushMatrix();
			glTranslated(0, 0, 0.3);
			drawCylinder(1, 1, 1);
			glPopMatrix();
		}
		setDiffuseColor(color1[color], color2[color], color3[color]);
		glRotated(180, 0.0, 1.0, 0.0);
		glTranslated(0, 0, 3);
		drawCylinder(1, 0.1, 0.1);
		if (level >= 2) {
			switch (color) {
			case 0:
				setDiffuseColor(1.0f, 1.0f, 0.0f);
				break;
			case 1:
				setDiffuseColor(0.0f, 1.0f, 0.0f);
				break;
			case 2:
				setDiffuseColor(1.0f, 0.0f, 0.0f);
				break;
			case 3:
				setDiffuseColor(0.0f, 0.0f, 1.0f);
				break;
			}
			glPushMatrix();
			glTranslated(0, 0, 0.3);
			drawCylinder(1, 1, 1);
			glPopMatrix();
		}
		setDiffuseColor(color1[color], color2[color], color3[color]);
		glTranslated(3.4, 0, 0);
		drawCylinder(1, 0.1, 0.1);
		if (level >= 2) {
			switch (color) {
			case 0:
				setDiffuseColor(1.0f, 1.0f, 0.0f);
				break;
			case 1:
				setDiffuseColor(0.0f, 1.0f, 0.0f);
				break;
			case 2:
				setDiffuseColor(1.0f, 0.0f, 0.0f);
				break;
			case 3:
				setDiffuseColor(0.0f, 0.0f, 1.0f);
				break;
			}
			glPushMatrix();
			glTranslated(0, 0, 0.3);
			drawCylinder(1, 1, 1);
			glPopMatrix();
		}
		glPopMatrix();

		// draw cannon
		setDiffuseColor(color1[color], color2[color], color3[color]);
		glPushMatrix();
		glRotated(VAL(TOPHANGLE), 0.0, 1.0, 0.0);
		glTranslated(0, 5, 0);
			glPushMatrix();
				glTranslated(1, 0, 1);
				glRotated(-90, 1.0, 0.0, 0.0);
				drawBox(0.1, 2, 1);
			glPopMatrix();

			glPushMatrix();
				glTranslated(-1, 0, -1);
				glRotated(-90, 1.0, 0.0, 0.0);
				drawBox(-0.1, -2, 1);
			glPopMatrix();
		if (level >= 2) {
			switch (color) {
			case 0:
				setDiffuseColor(1.0f, 1.0f, 0.0f);
				break;
			case 1:
				setDiffuseColor(0.0f, 1.0f, 0.0f);
				break;
			case 2:
				setDiffuseColor(1.0f, 0.0f, 0.0f);
				break;
			case 3:
				setDiffuseColor(0.0f, 0.0f, 1.0f);
				break;
			}
			glPushMatrix();
				glTranslated(1, 0.5, 0);
				glRotated(-90, 0.0, 1.0, 0.0);
				drawCylinder(2, 0.1, 0.1);
			glPopMatrix();

			glPushMatrix();
			switch (color) {
			case 0:
				setDiffuseColor(0.0f, 0.0f, 1.0f);
				break;
			case 1:
				setDiffuseColor(1.0f, 1.0f, 0.0f);
				break;
			case 2:
				setDiffuseColor(0.0f, 1.0f, 0.0f);
				break;
			case 3:
				setDiffuseColor(1.0f, 0.0f, 0.0f);
				break;
			}
				glTranslated(0, 1, 0);
				drawSphere(1);
			if (level >= 3) {
				
				if (VAL(AIM) == 0) {
					if (VAL(ANIMATE) == 1) {
						int time = getTime();
						double angle = abs(time % 40000000) * 0.000009;
						if (angle < 180) {
							glRotated(angle - 90, 1.0, 0.0, 0.0);
						}
						else {
							glRotated(360-angle - 90, 1.0, 0.0, 0.0);
						}
						glRotated(-90, 1.0, 0.0, 0.0);
						drawCylinder(2, 1, 1);
					}
					else {
						glRotated(VAL(TOPVANGLE), 1.0, 0.0, 0.0);
						glRotated(-90, 1.0, 0.0, 0.0);
						drawCylinder(2, 1, 1);
					}
				}
				else {
					glRotated(-90, 1.0, 0.0, 0.0);
					glRotated(VAL(AIM) * 90 / 100, 1.0, 0.0, 0.0);
					drawCylinder(2, 1, 1);
				}
			}
			glPopMatrix();
		}
		glPopMatrix();
		setDiffuseColor(color1[color], color2[color], color3[color]);
		glPushMatrix();
			glTranslated(0, 3.5, 0);
			glPushMatrix();
				glTranslated(-1.5, 0, 0);
				glRotated(-90, 0.0, 1.0, 0.0);
				drawCylinder(VAL(LEFTGAP), 0.1, 0.1);
				if (level >= 2) {
					switch (color) {
					case 0:
						setDiffuseColor(1.0f, 1.0f, 0.0f);
						break;
					case 1:
						setDiffuseColor(0.0f, 1.0f, 0.0f);
						break;
					case 2:
						setDiffuseColor(1.0f, 0.0f, 0.0f);
						break;
					case 3:
						setDiffuseColor(0.0f, 0.0f, 1.0f);
						break;
					}
					glTranslated(0, 0, VAL(LEFTGAP));
					drawSphere(1);
					
					
					if (level >= 3) {
						
						glRotated(90, 0.0, 1.0, 0.0);
						if (VAL(AIM) == 0) {
							glRotated(-VAL(LEFTHANGLE), 0.0, 1.0, 0.0);
							glRotated(VAL(LEFTVANGLE), 1.0, 0.0, 0.0);
						}
						else {
							glRotated(90, 1.0, 0.0, 0.0);
							glRotated(-VAL(AIM) * 90 / 100, 1.0, 0.0, 0.0);
							glRotated(VAL(AIM) * 15 / 100, 0.0, 1.0, 0.0);
						}
						drawCylinder(3, 1, 1);
						if (level >= 4) {
							switch (color) {
							case 0:
								setDiffuseColor(1.0f, 0.0f, 0.0f);
								break;
							case 1:
								setDiffuseColor(0.0f, 0.0f, 1.0f);
								break;
							case 2:
								setDiffuseColor(1.0f, 1.0f, 0.0f);
								break;
							case 3:
								setDiffuseColor(0.0f, 1.0f, 0.0f);
								break;
							}
							glTranslated(0, 0, 3);
							if (VAL(AIM) == 0) {
								drawCylinder(VAL(LEFTGLENGTH), 0.5, 0.5);
							}
							else {
								drawCylinder(VAL(AIM) * 3 / 100, 0.5, 0.5);
							}
						}
					}
				}
			glPopMatrix();
			setDiffuseColor(color1[color], color2[color], color3[color]);
			glPushMatrix();
				glTranslated(1.5, 0, 0);
				glRotated(90, 0.0, 1.0, 0.0);
				drawCylinder(VAL(RIGHTGAP), 0.1, 0.1);
				glTranslated(0, 0, VAL(RIGHTGAP));
				if (level >= 2) {
					switch (color) {
					case 0:
						setDiffuseColor(1.0f, 1.0f, 0.0f);
						break;
					case 1:
						setDiffuseColor(0.0f, 1.0f, 0.0f);
						break;
					case 2:
						setDiffuseColor(1.0f, 0.0f, 0.0f);
						break;
					case 3:
						setDiffuseColor(0.0f, 0.0f, 1.0f);
						break;
					}
					drawSphere(1);
					if (level >= 3) {
						
						glRotated(-90, 0.0, 1.0, 0.0);
						if (VAL(AIM) == 0) {
							glRotated(VAL(RIGHTHANGLE), 0.0, 1.0, 0.0);
							glRotated(VAL(RIGHTVANGLE), 1.0, 0.0, 0.0);
						}
						else {
							glRotated(90, 1.0, 0.0, 0.0);
							glRotated(-VAL(AIM) * 90 / 100, 1.0, 0.0, 0.0);
							glRotated(-VAL(AIM) * 15 / 100, 0.0, 1.0, 0.0);
						}
						drawCylinder(3, 1, 1);
						if (level >= 4) {
							switch (color) {
							case 0:
								setDiffuseColor(1.0f, 0.0f, 0.0f);
								break;
							case 1:
								setDiffuseColor(0.0f, 0.0f, 1.0f);
								break;
							case 2:
								setDiffuseColor(1.0f, 1.0f, 0.0f);
								break;
							case 3:
								setDiffuseColor(0.0f, 1.0f, 0.0f);
								break;
							}
							glTranslated(0, 0, 3);
							if (VAL(AIM) == 0) {
								drawCylinder(VAL(RIGHTGLENGTH), 0.5, 0.5);
							}
							else {
								drawCylinder(VAL(AIM) * 3 / 100, 0.5, 0.5);
							}
						}
					}
				}
			glPopMatrix();
		glPopMatrix();
	}
	glPopMatrix();
}

int main()
{
	
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.01f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.01f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.01f, 0);
	controls[TOPHANGLE] = ModelerControl("Top Gun Horizontal Angle", -135, 135, 1, 0);
	controls[TOPVANGLE] = ModelerControl("Top Gun Vertical Angel", -90, 90, 1, 0);
	controls[LEFTGAP] = ModelerControl("Left Gun Gap", 2, 3, 0.01f, 2.5);
	controls[LEFTHANGLE] = ModelerControl("Left Gun Horizontal Angel", 0, 180, 1, 0);
	controls[LEFTVANGLE] = ModelerControl("Left Gun Vertical Angel", -90, 90, 1, 90);
	controls[LEFTGLENGTH] = ModelerControl("Left Inner Gun Legnth", 0, 3, 0.01f, 0);
	controls[RIGHTGAP] = ModelerControl("Right Gun Gap", 2, 3, 0.01f, 2.5);
	controls[RIGHTHANGLE] = ModelerControl("Right Gun Horizontal Angel", 0, 180, 1, 0);
	controls[RIGHTVANGLE] = ModelerControl("Right Gun Vertical Angel", -90, 90, 1, 90);
	controls[RIGHTGLENGTH] = ModelerControl("Right Inner Gun Legnth", 0, 3, 0.01f, 0);
	controls[AIM] = ModelerControl("Aim", 0, 100, 1, 0);
	controls[LEVEL] = ModelerControl("Change the level of detail", 0, 4, 1, 4);
	controls[COLOR] = ModelerControl("Change the color", 0, 3, 1, 3);
	controls[LIGHT] = ModelerControl("Change the light intensity", 0, 5, 0.01f, 1);
	controls[ANIMATE] = ModelerControl("Enable animate", 0, 1, 1, 0);
	controls[LANDMINE] = ModelerControl("Lay mine", 0, 1, 1, 1);
	controls[SURRENDER] = ModelerControl("Surrender", 0, 1, 1, 0);
	controls[FRAMEALL] = ModelerControl("change value to frame", 0, 1, 1, 0);

	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}

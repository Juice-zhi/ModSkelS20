// The boy model. 
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <GL/glu.h>
#include "modelerglobals.h"
#include "camera.h"

// To make a SampleModel, we inherit off of ModelerView
class Boy : public ModelerView
{
public:
    Boy(int x, int y, int w, int h, char* label)
        : ModelerView(x, y, w, h, label) { }

    virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char* label)
{
    return new Boy(x, y, w, h, label);
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void Boy::draw()
{
	int level = VAL(LEVEL);
	int color = VAL(COLOR);
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...

	//ModelerView::draw();
	static GLfloat lightPosition0[] = { 4, 2, -4, 0 };
	static GLfloat lightDiffuse0[] = { 10,10,10,1 };
	static GLfloat lightPosition1[] = { -2, 1, 5, 0 };
	static GLfloat lightDiffuse1[] = { 1, 1, 1, 1 };

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
	m_camera->applyViewingTransform();

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse1);
	// draw the floor
	/*setAmbientColor(.0f, .0f, .0f);
	setDiffuseColor(COLOR_BLUE);
	glPushMatrix();
	glTranslated(-5, 0, -5);
	drawBox(10, 0.01f, 10);
	glPopMatrix();*/

	// draw the sample model
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
	
	// draw wheel
	if (level >= 1) {
		glPushMatrix();
		glTranslated(-1.5, 0.2, -1.7);
		glRotated(-90, 0.0, 1.0, 0.0);
		drawCylinder(1, 0.1, 0.1);
		if (level >= 2) {
			glPushMatrix();
			glTranslated(0, 0, 0.3);
			drawCylinder(1, 1, 1);
			glPopMatrix();
		}
		glTranslated(3.4, 0, 0);
		drawCylinder(1, 0.1, 0.1);
		if (level >= 2) {
			glPushMatrix();
			glTranslated(0, 0, 0.3);
			drawCylinder(1, 1, 1);
			glPopMatrix();
		}

		glRotated(180, 0.0, 1.0, 0.0);
		glTranslated(0, 0, 3);
		drawCylinder(1, 0.1, 0.1);
		if (level >= 2) {
			glPushMatrix();
			glTranslated(0, 0, 0.3);
			drawCylinder(1, 1, 1);
			glPopMatrix();
		}

		glTranslated(3.4, 0, 0);
		drawCylinder(1, 0.1, 0.1);
		if (level >= 2) {
			glPushMatrix();
			glTranslated(0, 0, 0.3);
			drawCylinder(1, 1, 1);
			glPopMatrix();
		}
		glPopMatrix();

		// draw cannon

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
			glPushMatrix();
			glTranslated(1, 0.5, 0);
			glRotated(-90, 0.0, 1.0, 0.0);
			drawCylinder(2, 0.1, 0.1);
			glPopMatrix();

			glPushMatrix();
			glTranslated(0, 1, 0);
			drawSphere(1);
			if (level >= 3) {
				glRotated(VAL(TOPVANGLE), 1.0, 0.0, 0.0);
				glRotated(-90, 1.0, 0.0, 0.0);
				drawCylinder(2, 1, 1);
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();
		glTranslated(0, 2.5, 0);
			glPushMatrix();
			glTranslated(-1.5, 0, 0);
			glRotated(-90, 0.0, 1.0, 1.0);
			drawCylinder(3, 0.1, 0.1);
			glTranslated(0, 0, 2);
			drawSphere(2);
			glRotated(90, 0.0, 1.0, 0.0);
			glRotated(-VAL(LEFTHANGLE), 0.0, 1.0, 0.0);
			glRotated(VAL(LEFTHANGLE), 1.0, 0.0, 0.0);
			drawCylinder(3, 2, 2);
			glTranslated(0, 0, 3);
			drawCylinder(VAL)
			glPopMatrix();

			glPushMatrix();
			glPopMatrix();
		glPopMatrix();
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
	controls[LEFTHANGLE] = ModelerControl("Left Gun Horizontal Angel", 0, 180, 1, 0);
	controls[LEFTVANGLE] = ModelerControl("Left Gun Vertical Angel", -90, 90, 1, 0);
	controls[LEFTGLENGTH] = ModelerControl("Left Inner Gun Legnth", -90, 90, 1, 0);
	controls[LEVEL] = ModelerControl("Change the level of detail", 0, 3, 1, 3);
	controls[COLOR] = ModelerControl("Change the color", 0, 3, 1, 3);

	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}

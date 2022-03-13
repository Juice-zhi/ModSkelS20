// The boy model. 
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

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
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();

	// draw the floor
	/*setAmbientColor(.0f, .0f, .0f);
	setDiffuseColor(COLOR_BLUE);
	glPushMatrix();
	glTranslated(-5, 0, -5);
	drawBox(10, 0.01f, 10);
	glPopMatrix();*/

	// draw the sample model
	setAmbientColor(.0f, .0f, .0f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		glPushMatrix();
		glTranslated(-1.5, 0, -2);
		glScaled(3, 5, 4);
		drawBox(1, 1, 1);
		glPopMatrix();

		// draw wheel
		glPushMatrix();
		glTranslated(-1.4, 0.2, -1.7);
		glRotated(-90, 0.0, 1.0, 0.0);
		drawCylinder(1, 0.1, 0.1);
			glPushMatrix();
			glTranslated(0, 0, 0.3);
			drawCylinder(1, 1, 1);
			glPopMatrix();

		glTranslated(3.4, 0, 0);
		drawCylinder(1, 0.1, 0.1);
			glPushMatrix();
			glTranslated(0, 0, 0.3);
			drawCylinder(1, 1, 1);
			glPopMatrix();

		glRotated(180, 0.0, 1.0, 0.0);
		glTranslated(0, 0, 2.8);
		drawCylinder(1, 0.1, 0.1);
			glPushMatrix();
			glTranslated(0, 0, 0.3);
			drawCylinder(1, 1, 1);
			glPopMatrix();

		glTranslated(3.4, 0, 0);
		drawCylinder(1, 0.1, 0.1);
			glPushMatrix();
			glTranslated(0, 0, 0.3);
			drawCylinder(1, 1, 1);
			glPopMatrix();
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

			glPushMatrix();
			glTranslated(1, 0.5, 0);
			glRotated(-90, 0.0, 1.0, 0.0);
			drawCylinder(2, 0.1, 0.1);
			glPopMatrix();

			glPushMatrix();
			glTranslated(0, 1, 0);
			drawSphere(1);
			glRotated(VAL(TOPVANGLE), 1.0, 0.0, 0.0);
			glRotated(-90, 1.0, 0.0, 0.0);
			drawCylinder(2, 1, 1);
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

	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}

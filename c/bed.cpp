#include <GL/gl.h>
#include <GL/glut.h>
#include <unistd.h>

static float Vertices[][3] = {
    {1,-1,-1},
    {1,1,-1},
    {-1,1,-1},
    {-1,-1,-1},
    {1,-1,1},
    {1,1,1},
    {-1,-1,1},
    {-1,1,1}
    };
static int Edges[][2] = {
        {0,1},
        {0,3},
        {0,4},
        {2,1},
        {2,3},
        {2,7},
        {6,3},
        {6,4},
        {6,7},
        {5,1},
        {5,4},
        {5,7}
    };

void setMaterial ( GLfloat ambientR, GLfloat ambientG, GLfloat ambientB, 
         GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB, 
         GLfloat specularR, GLfloat specularG, GLfloat specularB,
         GLfloat shininess ) {

    GLfloat ambient [ ] = { ambientR, ambientG, ambientB    };
    GLfloat diffuse [ ] = { diffuseR, diffuseG, diffuseB    };
    GLfloat specular[ ] = { specularR, specularG, specularB };

    glMaterialfv ( GL_FRONT_AND_BACK,GL_AMBIENT,ambient     );
    glMaterialfv ( GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse     );
    glMaterialfv ( GL_FRONT_AND_BACK,GL_SPECULAR,specular   );
    glMaterialf  ( GL_FRONT_AND_BACK,GL_SHININESS,shininess );
}

void Cube (void)
{
   int i,j;
   glBegin(GL_LINES);
   for(i=0;i<(sizeof(Edges)/sizeof(Edges[0]));i++)
      for(j=0;j<(sizeof(Edges[0])/sizeof(Edges[0][0]));j++)
         glVertex3fv(Vertices[Edges[i][j]]);
   glEnd         (                                       );
   glPushMatrix  (                                       );
   setMaterial   ( 0.0,0.5,1.0,0.0,0.5,1.0,1.0,1.0,1.0,1 );
   glutSolidCube ( 1                                     );
}
void Reshape ( int width, int height ) {

    /* define the viewport transformation */
    glViewport(0,0,width,height);
}
void Animate (void)
{
   glRotatef         ( 2,1,0,1 );
   glutPostRedisplay (         );
}

void Display () {

   glClear         ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   Cube            (                                           );
   glutSwapBuffers (                                           );
}

void Bed (int* argc,char* argv[]) {

    /* initialize GLUT, using any commandline parameters passed to the 
       program */
   glutInit(argc,argv);

   /* setup the size, position, and display mode for new windows */
   glutInitWindowSize     ( 500,500              );
   glutInitWindowPosition ( 0,0                  );
   glutInitDisplayMode    ( GLUT_RGB|GLUT_DOUBLE );
//
//   /* create and set up a window */
   glutCreateWindow ( "hello cube"    );
   gluPerspective   ( 45,1, 0.1, 50.0 );
   glTranslatef     ( 0.0,0.0,-15     );
   Cube             (                 );
   glutDisplayFunc  ( Display         );
   glutIdleFunc     ( Animate         );
   glutReshapeFunc  ( Reshape         );

   /* set up lights */

   GLfloat lightpos  [ ] = { 0.0, 15.0, 15.0 };
   GLfloat lightcolor[ ] = { 0.5, 0.5, 0.5   };
   GLfloat ambcolor  [ ] = { 0.2, 0.2, 0.0   };

   glEnable(GL_LIGHTING);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambcolor);

   glEnable  ( GL_LIGHT0                        );
   glLightfv ( GL_LIGHT0,GL_POSITION,lightpos   );
   glLightfv ( GL_LIGHT0,GL_AMBIENT,lightcolor  );
   glLightfv ( GL_LIGHT0,GL_DIFFUSE,lightcolor  );
   glLightfv ( GL_LIGHT0,GL_SPECULAR,lightcolor );

   /* define the projection transformation */
   glMatrixMode   ( GL_PROJECTION );
   glLoadIdentity (               );
   gluPerspective ( 40,1,4,20     );

   /* define the viewing transformation */
   glMatrixMode   ( GL_MODELVIEW                        );
   glLoadIdentity (                                     );
   gluLookAt      ( 5.0,5.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0 );


   glutMainLoop();
}

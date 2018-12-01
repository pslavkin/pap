#ifndef TRESD
#define TRESD

class TresD_Class {
   public:
      TresD_Class ( void                  );
      void Bed    ( int* argc,char** argv );
      void Rti    ( void                  );
   private:
      static void setMaterial ( GLfloat ambientR, GLfloat ambientG, GLfloat ambientB,
         GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB,
         GLfloat specularR, GLfloat specularG, GLfloat specularB,
         GLfloat shininess );
      static void Cube    ( void );
      static void Animate ( void );
      static void Display ( void );
      struct timespec Rti_Delay= { 0, 10000000}; //   5 milis
   private:
};

#endif


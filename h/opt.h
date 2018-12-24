#define SERIAL_MANAGER_RTI      20000000
#define SERIAL_OPEN_PORT_DELAY 900000000
#define MAX_SERIAL_PORTS        2


#define TRESD_RTI              200000000
#define GANTRY_RTI              50000000
#define MAX_XY_SCALE_INDEX       1000000
#define MAX_Z_SCALE_INDEX          10000
#define MAX_PATH                 5000000
#define MAX_Z_TABLE           (50*Z_SCALE) //para definir el color mas oscuro.. supongo que z puede subir 25mm max, desde cero..  //para definir el color mas oscuro.. supongo que z puede subir 25mm max, desde cero..  //para definir el color mas oscuro.. supongo que z puede subir 25mm max, desde cero..
#define MIN_Z_TABLE           (-50*Z_SCALE) //para definir el color mas oscuro.. supongo que z puede subir 25mm max, desde cero..  //para definir el color mas oscuro.. supongo que z puede subir 25mm max, desde cero..  //para definir el color mas oscuro.. supongo que z puede subir 25mm max, desde cero..

#define MIN_COLOUR_PAIR  16
#define MAX_COLOUR_PAIR  255
#define MAX_BASIC_COLORS 8


#define MAX_SPEED_LIMIT         500
#define MAX_SPEED_SCALE         100
#define SCREEN_UPDATE_RTI       20000000
#define HISTOGRAMS_RTI          50000000
#define SENDER_RTI              30000000
#define EXEC_LINE_POS 3    //posicion de la linea en ejecucion
#define MAX_ANS_SIZE             255

#define COORDS_RTI    50000000
#define MAX_JOG_SPEED 100
#define X_SCALE       600  // micropasos por mm
#define Y_SCALE       600  // micropasos por mm
#define Z_SCALE       2560 // micropasos por mm
#define MICROSTEP     128


#define MAX_ACC   ((59000*MICROSTEP)/Z_SCALE)
#define MAX_DEC   ((59000*MICROSTEP)/Z_SCALE)
#define MIN_ACC   ((15*MICROSTEP)/X_SCALE)
#define MIN_DEC   ((15*MICROSTEP)/X_SCALE)
#define ACC_STEP  100

#define PLOT_STEP 100
#define PLOT_MAX  100000


#define DEFAULT_GCODE_FILE_NAME "gcodes/route.nc"
#define MAX_SENDER_QUEUE  200

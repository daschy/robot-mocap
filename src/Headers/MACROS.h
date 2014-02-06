#define minVALUE 0.0
#define MAXVALUE 255.0
#define PI 3.14159265358979323846264338327
//280 teorico
//gap inizio ~25 gradi
//gap fine ~28 gradi
#define MAXANGLE 222.5
#define VALUETODEGREE(value) value*0.88
#define DEGREETOVALUE(degree) degree*MAXVALUE/MAXANGLE

#define DEGREETORADIANTS(degree) degree*PI/180.0
#define DEGREETOURADIANTS(degree) (degree*(PI)/180.0)*1000000.0
#define RADIANTSTODEGREE(radiants) (radiants*180.0)/(PI)
#define URADIANTSTODEGREE(uradiants) ((uradiants/1000000.0)*180.0)/(PI)

#define VALUETORADIANTS(value) VALUETODEGREE(value)*(PI)/(180.0)
#define VALUETOURADIANTS(value) (VALUETODEGREE(value)*(PI)/(180.0))*1000000.0

#define RADIANTSTOVALUE(radiants) DEGREETOVALUE(RADIANTSTODEGREE(radiants))
#define URADIANTSTOVALUE(uradiants) DEGREETOVALUE(RADIANTSTODEGREE(radiants))*1000000.0

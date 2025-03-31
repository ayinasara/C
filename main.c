#include <stdio.h>
#define Pi 3.142
#define Area(r) (Pi*r*r)
#define SA(r,h) (2*Pi*r*(r+h))

int main()
{
    float r,h,area,surface;
    printf("enter radius of cylinder");
    scanf("%f",&r);
    printf("enter height");
    scanf("%f",&h);
    area=Area(r);
    printf("the area is %f",area);
    surface=SA(r,h);
    printf("the surface area is %f",SA(r,h));


    return 0;
}

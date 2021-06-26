#include <stdio.h>  

#include<conio.h>  

#include<graphics.h>  

#include<stdlib.h>  

#include <math.h>



#define Aralik 4 //ekrana cizilen koordinat sistemi aralıklarını ifade eder

#define  NOKTA_SAYISI 3	//dosyadan kac tane nokta oldugunu ifade eder





//Point structı bir nokta icin x ve y kordinatı icerir

typedef struct Point {

    double x;

    double y;

};



//cizilecek cemberin merkez noktasını ve yarıcapını icerir

typedef struct Circle {

    Point center;

    double radius;

};





//iki nokta arası mesafeyi hesaplar

double point_distance (Point &point_1, Point &point_2) {

    return sqrt(pow(point_1.x - point_2.x, 2) + pow(point_2.y - point_1.y, 2));

}



//noktanın cember icinde olup olmadıgını kontrol eder

bool point_in_circle (Circle &circle, Point &point) {

    return pow(point.x - circle.center.x, 2) + pow(point.y - circle.center.y, 2) <= pow(circle.radius, 2);

}



//iki nokta arasındaki minumum cemberi bulur

Circle min_circle(Point &point_1, Point &point_2) {

   //burda cemberin merkezi iki noktanın ortası olarak kabul edilir

    Point init_center = {

            (point_1.x + point_2.x) / 2,

            (point_1.y + point_2.y) / 2

    };

    double distance = point_distance(point_1, point_2);

    

    //yarıcapta ikisi arası mesafenin yarısı olarak ele alınır boylece iki noktayı da tam iceren minumum cember bulunur

    Circle circle = {

            init_center,

            distance / 2

    };

  

  

    return circle;

}



//3 noktayı cevreleyen cember 2 nokta olursa 3. cü 0 alınır

Circle circumcircle (Point &point_1, Point &point_2, Point &point_3) {

    double a = point_distance(point_1, point_2);

    double b = point_distance(point_2, point_3);

    double c = point_distance(point_3, point_1);



    double P = a + b + c;



    Point center = {

            (a * point_1.x + b * point_2.x + c * point_3.x) / P,

            (a * point_1.y + b * point_2.y + c * point_3.y) / P

    };

    double radius = point_distance(center, point_1);



    Circle circle = {

            center,

            radius

    };



    return circle;

}



Circle min_disc_with_two_points(struct Point points[] , Point &point_1, Point &point_2) {

   //gelen  iki noktadan bir cember cizlir

    Circle circle = min_circle(point_1, point_2);

    

    for (int i=0;i<NOKTA_SAYISI;i++) {

    	//diğer noktalardan struct array dizinden bakılır icinde olup olmamması na gore yeni cember cizilir

         if (!point_in_circle(circle, points[i])) {

            circle = circumcircle(points[i], point_1, point_2);

        }

    }

    return circle;

}





//noktalar cemberde mi değil mi bakar değilse 2 nokta alacak şekilde bakar

Circle min_disc_with_points (struct Point points[], Point &point) {

    Circle circle = min_circle(points[0], point);



    for (int i = 1; i < NOKTA_SAYISI; i++) {

        Point pnt = points[i];

  //cember değilse 2 noktayı ayrı ayrı alıp diğer fonksiyonda bakılır

        if (!point_in_circle(circle, pnt)) {

            circle = min_disc_with_two_points(points, pnt, point);

        }

    }

    return circle;

}





//bütün noktaları cevreleyen cemberi bulma

Circle min_disc (struct Point points[]) {

   

   //nokta sayısı ikiyse diğer fonksiyonlara gitmez

    Circle circle = min_circle(points[0], points[1]);

     

     

if(NOKTA_SAYISI>=2) //2 den büyükse

{

	//struct dizisindeki her bir nokta alınır 

    for (int i = 2; i <NOKTA_SAYISI; i++) {

        Point point = points[i];

         //cemberin icinde değilse nokta noktalar arası min mesafa bulan fonksiyona gonderilir

        if (!point_in_circle(circle, point)) {

            circle = min_disc_with_points(points, point);

        }

    }

}



    return circle;

}





//global olarak tanımlanan değişken ekranın gosterimidir 

double xm,ym;



//graphic.h başlangıc tanımlamalamarını icerir

void map()  

{  

    int gd=DETECT, gm;  

    initgraph (&gd, &gm, "");  

    

    //yazının boyutunu ve stylei gösterir

    settextstyle(2,HORIZ_DIR,(4));

        

}  



//Erkana başlangıc cizimleri kordinat sistemi ve nokta yazımları işlemlerini gerçekleştirme

void graph()  

{  

    xm=getmaxx();  

    ym=getmaxy();  

  

    //x ve y ekseni cizimleri

    line (xm, 0, xm, 2 * ym);  

    line (0, ym, 2 * xm, ym);  

     setcolor(GREEN); 

    

    

    char str[10]; 

    

   //yukarıda define la tanımlanan aralık kadar her bir eksen bolunur.

	for(int i=1;i<Aralik;i++)

	{	    

	//moveto x ekseninde -10 birim eksiye line to da +10 gider boylece 20 piksellik bir cizgi cizilir bunun üstünede

	//noktalar yazılır burda aralık 4 oldugu icin noktalar 3 tane 10 20 30 seklnde yazılır

	moveto(xm-10,ym-i*ym/(Aralik-1)); 

	lineto(xm+10, ym -i*ym/(Aralik-1)); 

	sprintf(str,"%d",i*10);

    outtextxy(xm-10,ym-i*ym/(Aralik-1) ,str);

   }

   

   //aynı işlemler diğer tafarlara da yapılır yani x ekseni sol sağ y ekseni sol sağına 4 tane

   

   	for(int i=1;i<Aralik;i++)

	{	

	moveto(xm+i*xm/(Aralik-1),ym-5); 

	lineto(xm+i*xm/(Aralik-1), ym +5); 

    sprintf(str,"%d",i*10);

    outtextxy(xm+i*xm/(Aralik-1),ym-10 ,str);

    

    

   }

   

   

   	for(int i=1;i<Aralik;i++)

	{	

	moveto(xm-10,ym+i*ym/5); 

	lineto(xm+10, ym +i*ym/5); 

	sprintf(str,"%d",i*10);

    outtextxy(xm+10,ym+i*ym/5 ,str);

  

   }

   

   	for(int i=1;i<Aralik;i++)

	{	

	moveto(xm-i*xm/(Aralik-1),ym-5); 

	lineto(xm-i*xm/(Aralik-1), ym +5); 

    

    sprintf(str,"%d",i*10);

    outtextxy(xm-i*xm/(Aralik-1),ym+10 ,str);

   }





}

  

int main ()  

{  

  //graph initialize edilir

    map();  

    graph();  

     char str[300];  

  int boyut=3;    

     

     



//dosyadan alınan x ve y değerleri points structına atılır

   FILE* Kordinat;

    double xcor;

    double ycor;



 struct Point points[NOKTA_SAYISI];

  

   Kordinat = fopen("a.txt", "r");

   int i=0;

    while(fscanf(Kordinat,"%lf %lf",&xcor, &ycor)>0) {

       

       points[i].x=xcor;

       points[i].y=ycor;

       i++;

    }



  fclose(Kordinat);







//oncelikle points den alınan x ve y kordinatları ekranda gostermek gerekir

//burda yalnızca soyle bir sey vardır aralık kac alındaysa onun bir eksiği nin 10 carpılmışı kadar her bir piksel bi seye tekabül eder

//yani mesela xm 600 ise ve aralık 4 ise bir xm ekseni 6 ya bolunup her biri 10 luk sekilde ayrılmıştır yani 600 gosterimde 60 a gelmiştir

//burda soyle bir orantı olur 600 60 lıksa bir x noktası neye denk gelir 

// points[i].x*xm/((Aralik-1)*10)+xm   soyle bir hesaplama dogru olacaktır

  

  for (int i=0;i<NOKTA_SAYISI;i++)

  {

  	    moveto(points[i].x*xm/((Aralik-1)*10)+xm,ym-points[i].y*ym/((Aralik-1)*10));

  	    //burda cizilen cember 3 piksel yarıcaplık kücük noktalar belli olsun diye yapılmış cemberdir

  	    

  	    circle (points[i].x*xm/((Aralik-1)*10)+xm, ym-points[i].y*ym/((Aralik-1)*10), 3); 

		 int a=	points[i].x;

		 int b=points[i].y;

  	    sprintf(str,"%d,%d",a,b);

 	    outtextxy(points[i].x*xm/((Aralik-1)*10)+xm, ym-points[i].y*ym/((Aralik-1)*10) ,str);

  }

  



    //cember hesaplanır

    Circle min_circle = min_disc(points);

    moveto(min_circle.center.x *xm/((Aralik-1)*10)+xm,ym-min_circle.center.y*ym/((Aralik-1)*10));

    //cember cizilir

    circle(min_circle.center.x *xm/((Aralik-1)*10)+xm, ym-min_circle.center.y*ym/((Aralik-1)*10), min_circle.radius*xm/((Aralik-1)*10));   

   	sprintf(str,"Minimal circle, x: %.1lf y:%.1lf radius :%.2lf  ", min_circle.center.x ,min_circle.center.y , min_circle.radius);

 

    outtextxy(10,50 ,str);

    

    delay(5000);

	//bu cember cizme ekranı kapatılır

	closegraph();



   outtextxy(10,50 ,"Spline");



//yeni bir line ekranı cizilir





double t,put_x,put_y;

  map();

  graph();  

  

  

   //yine  noktalar ekranda gosterilir

  for (int i=0;i<NOKTA_SAYISI;i++)

  {

  	    moveto(points[i].x*xm/((Aralik-1)*10)+xm, ym-points[i].y*ym/((Aralik-1)*10));

  	    circle (points[i].x*xm/((Aralik-1)*10)+xm, ym-points[i].y*ym/((Aralik-1)*10), 3); 

		 int a=	points[i].x;

		 int b=points[i].y;

  	    sprintf(str,"%d,%d",a,b);

 	    outtextxy(points[i].x*xm/((Aralik-1)*10)+xm, ym-points[i].y*ym/((Aralik-1)*10) ,str);

  }

 

 

 

  //bir moveto yapılarak gerekli yere gidilir

  	int x0=points[0].x*xm/((Aralik-1)*10)+xm;

 	int y0=ym-points[0].y*ym/((Aralik-1)*10);

 	moveto(x0,y0);



//line cizerken temel mantık piksel piksel cizmektir

//linenin bir spline olması ıstendiginden belli bir denklem kullanıldı



  for(int i=0;i<NOKTA_SAYISI-1;i++){

 //burda iki nokta alınır ard arda gelen struct arrayde

 //x0 ,y0  ilkinin noktalarıdır x4 ,y4 ikincinin noktalarıdır

  int x0=points[i].x*xm/((Aralik-1)*10)+xm;

  int y0=ym-points[i].y*ym/((Aralik-1)*10);

  int x4=points[i+1].x*xm/((Aralik-1)*10)+xm;

  int y4=ym-points[i+1].y*ym/((Aralik-1)*10);

    moveto(x0,y0);

    

    for(t=0.0;t<1.0;t=t+0.001)

  {

  //burdaki t  ifadesi bize splinein curve olmasını sağlıyor

  //x ve y noktası aynı mantıkla belirlenir

  //t ye bağlı bir denklem oluşturulup x0 dan x4 e y0 dan y4 e bir tane curve yapılır

  	put_x=pow(1-t,3)*x0+3*t*pow(1-t,2)*(x0+100)+3*t*t*(1-t)*(x0+100)+pow(t,3)*x4;

    put_y=pow(1-t,3)*y0+3*t*pow(1-t,2)*(y0+100)+3*t*t*(1-t)*(y0+100)+pow(t,3)*y4;

    moveto(put_x,put_y);

  	putpixel(put_x,put_y,WHITE);

  

  }

   

}

  

     getch();

    closegraph();

    

   

    

    

	return 0; 

}  


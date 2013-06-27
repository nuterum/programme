#include <stdio.h>
#include <stdlib.h>
#include <RT_ARDrone/RT_ARDrone.h>
#include </home/camelin/labo/RT_ARDrone/tools/drone_videostream/src/glwindow.h>

//librairie pour la commande sleep
#include <unistd.h>

unsigned char* conv( YUV420Image* img) 
{
  	int  i,j;
  	int res;
  	unsigned char* pix;
	int cpt = 0;
	int startU = 640*360;
	int startV = 640*360 * 5 /4;
	
	pix = ( unsigned char*) malloc (img->height * img->width * 3) ;
/*
			
			// print the first Y
			Y1 =img->pixels[nblin * 640 + cpt1];	
			Y2 =img->pixels[nblin * 640 + cpt1 +1];
			Y641 =img->pixels[(nblin+1) * 640 + cpt1];
			Y642 =img->pixels[(nblin+1) * 640 + cpt1+1];
			
			// print the first U
			U1 = img->pixels[startU];
			U2 = img->pixels[startU];
			U641 = img->pixels[startU];						
			U642 = img->pixels[startU];						
			startU++;

			// print the first V
			V1 = img->pixels[startV];
			V2 = img->pixels[startV];
			V641 = img->pixels[startV];
			V642 = img->pixels[startV];
			startV++*/
	
	res=-1;		
	for(i=0;i<360;i=i+2)
	{
		for(j=0;j<640;j=j+2)
		{
			if(i==0 && j!=0)
			{
				res=j;
			}
			else
			{
				if(j==0)
				{
					res=res+1;
				}
				else
				{
					res=i*j;
				}
			}
			//D'abord les Y
			pix[cpt] =img->pixels[res];	
			pix[cpt+3] =img->pixels[res+1];	
			pix[cpt+640] =img->pixels[res+640];
			pix[cpt+643] =img->pixels[res+641];
			//puis les U
			pix[cpt+1]=img->pixels[startU];
			pix[cpt+4]=img->pixels[startU];
			pix[cpt+641]=img->pixels[startU];
			pix[cpt+644]=img->pixels[startU];
			startU++;
			//et enfin les V
			pix[cpt+2]=img->pixels[startV];
			pix[cpt+5]=img->pixels[startV];
			pix[cpt+642]=img->pixels[startV];
			pix[cpt+645]=img->pixels[startV];
			startV++;
			//prochain groupe
			cpt=cpt+6;
		}
	}
	
  	return pix;
}


int main ( int argc, char** argv, char** envv ) {

	ARDrone* bob ;
	GLWindow*   win ;
	YUV420Image* img ;
	unsigned char* picture;

	img = YUV420Image_new(640,360) ; // ou 480
	bob = ARDrone_new( "192.168.1.1" ) ;

	ARDrone_connect( bob ) ;
		
	ARDrone_trim ( bob ) ;
	
	sleep(2);

	ARDrone_zap_camera ( bob, 2 ) ;

	sleep(1);
	
	win = GLWindow_new ( "glview", 640, 360, 0 ) ;

	while(1) 
	{		

		ARDrone_get_YUV420Image ( bob, img ) ;
		
		picture=conv( img );
		
		GLWindow_draw_rgb(win,picture );
		
		GLWindow_swap_buffers(win);
		
		XEvent event;

		while ( GLWindow_next_event( win, &event ) ) 
		{

			GLWindow_process_events( win, event );
		
		}

		usleep( 50000 ) ;
	}

	ARDrone_free( bob ) ;
	free(picture);


	return 0 ;

}

#include <stdio.h>
#include <stdlib.h>
#include <RT_ARDrone/RT_ARDrone.h>
#include <RT_ARDrone_VideoStream/glwindow.h>

//librairie pour la commande sleep
#include <unistd.h>

unsigned char* convYUV( YUV420Image* img) 
{
  	int  i,j;
  	int res;
  	unsigned char* pix;
	int cpt = 0;
	//int startU = 640*364;
	//int startV = 640*364* 5 /4;
	
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
	
		
	for(i=0;i<364;i=i+2)
	{
		for(j=0;j<640;j=j+2)
		{
			res=i*j*3;
			//D'abord les Y
			pix[cpt] =img->pixels[res];	
			pix[cpt+3] =img->pixels[res+1];	
			pix[cpt+640] =img->pixels[res+2];
			pix[cpt+643] =img->pixels[res+3];
			//puis les U
			pix[cpt+1]=img->pixels[res+4];
			pix[cpt+4]=img->pixels[res+4];
			pix[cpt+641]=img->pixels[res+4];
			pix[cpt+644]=img->pixels[res+4];
			//et enfin les V
			pix[cpt+2]=img->pixels[res+5];
			pix[cpt+5]=img->pixels[res+5];
			pix[cpt+642]=img->pixels[res+5];
			pix[cpt+645]=img->pixels[res+5];
			//prochain groupe
			cpt=cpt+6;
		}
	}
	
  	return pix;
}

unsigned char* convYUVtoRGB( unsigned char* picture) 
{
	int i;
	int j;
	int res;
	unsigned char* img ;
	
	img=( unsigned char*) malloc (364 * 640 * 3) ;
	
	for(i=0;i<364;i++)
		{
			for(j=0;j<640;j=j++)
			{
				res=i*j*3;
				img[res]=picture[res];
				img[res+1]=picture[res+1];
				img[res+2]=picture[res+2];
			} 
		}
	
	return img;
}

int main ( int argc, char** argv, char** envv ) {

	ARDrone* bob ;
	GLWindow*   win ;
	YUV420Image* img ;
	RGB24Image* img2 ;
	unsigned char* picture;
	unsigned char* stream;
	//int i;

	img = YUV420Image_new(640,364) ; // ou 480
	img2 = RGB24Image_new(640,360);
	
	bob = ARDrone_new( "192.168.1.1" ) ;

	ARDrone_connect( bob ) ;
		
	ARDrone_trim ( bob ) ;
	
	sleep(2);

	ARDrone_zap_camera ( bob, 2 ) ;

	sleep(1);
	
	win = GLWindow_new ("glview", 640, 364, 0 ) ;

	while(1) 
	{		

		ARDrone_get_YUV420Image ( bob, img ) ;
		
		picture=convYUV( img );
		stream=convYUVtoRGB(picture) ;
		//for(i=0;i<30;i++)
		//{
		//	printf("%d ",picture[i]);
		//}
		
		ARDrone_get_RGB24Image ( bob, img2 ) ;
		
		GLWindow_draw_rgb(win,stream ); //img2->pixels
		
		GLWindow_swap_buffers(win);
		
		XEvent event;

		while ( GLWindow_next_event( win, &event ) ) 
		{

			GLWindow_process_events( win, event );
		
		}

		//printf("\n\n");
		usleep( 50000 ) ;
		//sleep(8);
	}

	ARDrone_free( bob ) ;
	//free(picture);
	//free(stream);


	return 0 ;

}

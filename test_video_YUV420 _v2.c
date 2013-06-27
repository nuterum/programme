#include <stdio.h>
#include <RT_ARDrone/RT_ARDrone.h>

//librairie pour la commande sleep
#include <unistd.h>

void conv( YUV420Image* img) 
{

  	int  i,j;
  	unsigned char* pix;
  
	pix = ( unsigned char*) malloc (img->height * img->width * 3) ;
	int cpt = 0;
	int cpt1=0;
	
	int nblin = 0;
	int startU = 640*360;
	int startV = 640*360 * 5 /4;

			
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
  
  	free(pix);
}


int main ( int argc, char** argv, char** envv ) {

	int iFrame ;
	//int i;
	//int j;
	//int res;
	ARDrone* bob ;
	YUV420Image* img ;

	img = YUV420Image_new(640,480) ;
	bob = ARDrone_new( "192.168.1.1" ) ;

	ARDrone_connect( bob ) ;
		
	ARDrone_trim ( bob ) ;
	
	sleep(2);

	ARDrone_zap_camera ( bob, 2 ) ;

	sleep(1);
	
	iFrame = 0 ;

	//while(iFrame<200) {
	while(1) {		

		ARDrone_get_YUV420Image ( bob, img ) ;
		
		SaveFrame( img, iFrame ) ;
		iFrame++ ;

		usleep( 50000 ) ;
		/*printf("width: %i et height: %i \n",img->width,img->height);
		sleep(5);
		//SaveFrame( img, iFrame ) ;
		iFrame++ ;
		usleep( 50000 ) ;
		res=0;
		for(i=0;i<360;i++)
		{
			for(j=0;j<640;j++)
			{
				printf("pixel- %i: %i \n",res,img->pixels[res]);
				res++;
			}
		}
		printf("U ou V \n\n");
		for(i=0;i<180;i++)
		{
			for(j=0;j<320;j++)
			{
				printf("pixel- %i: %i \n",res,img->pixels[res]);
				res++;
			}
		}
		printf("U hou V \n\n"); //faute volontaire
		for(i=0;i<180;i++)
		{
			for(j=0;j<320;j++)
			{
				printf("pixel- %i: %i \n",res,img->pixels[res]);
				res++;
			}
		}
		printf("fin\n");
		iFrame=0;*/
	}

	ARDrone_free( bob ) ;


	return 0 ;

}

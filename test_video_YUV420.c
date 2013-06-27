#include <stdio.h>
#include <RT_ARDrone/RT_ARDrone.h>

//librairie pour la commande sleep
#include <unistd.h>

void SaveFrame( YUV420Image* img, int iFrame) {

	FILE *pFile;
	char szFilename[32];
  	int  x,y;
  	unsigned char* pix;
  	int res;
  
   // Open file
  
  	sprintf(szFilename, "frame%d.ppm", iFrame);
  
 // 	pFile=fopen(szFilename, "wb");
//  	if(pFile==NULL)
 //   		return;
  
  // Write header 
  //"P5" is header for PGM (grayscale), "P6" is header for PPM (color)
  	
//	fprintf(pFile, "P6\n%d %d\n255\n", 640, 360);
	pix = ( unsigned char*) malloc (img->height * img->width * 3) ;
	res=-1;
	int cpt = 0;
	int cpt1=0;
	
	int nblin = 0;
	int startU = 640*360;
	int startV = 640*360 * 5 /4;
//  	for (y=0; y<360; y++ ) 
	{
//		for (x=0; x<6; x++ ) 
		{
			//if(y==0 && x!=0)
			//{
				//res=y+x;
			//}
			//else
			//{
				//if(x==0)
				//{
					//res=res+1;
				//}
				//else
				//{
					//res=x*y;
				//}
			//}
			//pix[(res*3)]=img->pixels[(res)-(2*x)];
			//pix[(res*3)+1]=img->pixels[(res)-(2*x)];
			//pix[(res*3)+2]=img->pixels[(res)-(2*x)];
			
			// print the first Y
			Y1 = printf("%d ",img->pixels[nblin * 640 + cpt1]);
			
			Y2 = printf("%d ",img->pixels[nblin * 640 + cpt1 +1]);
			
			Y3 = printf("%d ",img->pixels[(1+nblin) * 640 + cpt1]);
			Y4 = printf("%d ",img->pixels[(1+nblin) * 640 + cpt1+1]);
			
			U = 
			// print the first U
			U1 = printf("%d ",img->pixels[startU + 320 * (nblin/2) +cpt1/2]);
			U1 = printf("%d ",img->pixels[startU + 320 * (nblin/2) +cpt1/2]);
			U1 = printf("%d ",img->pixels[startU + 320 * (nblin/2) +cpt1/2]);						
			U1 = printf("%d ",img->pixels[startU + 320 * (nblin/2) +cpt1/2]);						

			startU++;

			
			V = 
			// print the first V
			printf("%d ",img->pixels[640*360 + (640*360/4)+cpt1/2]);
			
			pix[cpt++]=img->pixels[cpt1++];
			pix[cpt++]=0;
			pix[cpt++]=0;
			
		}
	}
	printf("\r");
  
  // Write pixel data
  
	/*res=-1;
	for (y=0; y<img->height; y++ ) 
	{
		for (x=0; x<img->width; x++ ) 
		{
			if(y==0 && x!=0)
			{
				res=y+x;
			}
			else
			{
				if(x==0)
				{
					res=res+1;
				}
				else
				{
					res=x*y;
				}
			}
			fprintf(pFile, "%d ", pix[res] ) ;

		}

		fprintf(pFile, "\n" ) ;
	}*/

	//for(y=0; y<360; y++)
//		fwrite((pix), 1, 360*640*3, pFile ) ;

  // Close file
  
//  	fclose(pFile);
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

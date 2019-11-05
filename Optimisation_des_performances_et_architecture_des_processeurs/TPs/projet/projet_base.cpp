/*
 * Fichier source pour le projet d'unité
 *  INF-4101C
 *---------------------------------------------------------------------------------------------------
 * Pour compiler : g++ `pkg-config --cflags opencv` projet.cpp `pkg-config --libs opencv` -o projet
 *---------------------------------------------------------------------------------------------------
 * auteur : Eva Dokladalova 09/2015
 * modification : Eva Dokladalova 10/2017
 */


/* 
 * Libraries stantards 
 *
 */ 
#include <stdio.h>
#include <stdlib.h>

/* 
 * Libraries OpenCV "obligatoires" 
 *
 */


#include "opencv2/highgui/highgui_c.h"
#include "opencv2/core/cvstd.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include  "sobel.cpp"
#include  "median.cpp"

/* 
 * Définition des "namespace" pour évite cv::, std::, ou autre
 *
 */  
using namespace std;
using namespace cv;
using std::cout;

/*
 * Some usefull defines
 * (comment if not used)
 */
#define PROFILE
#define VAR_KERNEL
#define N_ITER 100

#ifdef PROFILE
#include <time.h>
#include <sys/time.h>
#endif


/*
 *
 *--------------- MAIN FUNCTION ---------------
 *
 */
int main () {

  
//----------------------------------------------
// Video acquisition - opening
//----------------------------------------------
  VideoCapture cap(0); // le numéro 0 indique le point d'accès à la caméra 0 => /dev/video0
  if(!cap.isOpened()){
    cout << "Errore"; return -1;
  }

//----------------------------------------------
// Déclaration des variables - imagesize
// Mat - structure contenant l'image 2D niveau de gris
// Mat3b - structure contenant l'image 2D en couleur (trois cannaux)
//
  Mat3b frame; // couleur
  Mat frame1; // niveau de gris 
  Mat frame1_base; // niveau de gris 
  Mat frame_gray; // niveau de gris 
  Mat grad_x;
  Mat grad_y;
  Mat abs_grad_y;
  Mat abs_grad_x;
  Mat grad;

// variable contenant les paramètres des images ou d'éxécution  
  int ddepth = CV_16S;
  int scale = 1;
  int delta = 0;	
  unsigned char key = '0';

 #define PROFILE
  
#ifdef PROFILE
// profiling / instrumentation libraries
#include <time.h>
#include <sys/time.h>
#endif
  
//----------------------------------------------------
// Création des fenêtres pour affichage des résultats
// vous pouvez ne pas les utiliser ou ajouter selon ces exemple
// 
  //cvNamedWindow("Video input", WINDOW_AUTOSIZE);
  //cvNamedWindow("Video gray levels", WINDOW_AUTOSIZE);
  cvNamedWindow("Video Mediane base", WINDOW_AUTOSIZE);
  cvNamedWindow("Video Mediane custom", WINDOW_AUTOSIZE);
  cvNamedWindow("Video Edge detection", WINDOW_AUTOSIZE);
// placement arbitraire des  fenêtre sur écran 
// sinon les fenêtres sont superposée l'une sur l'autre
  //cvMoveWindow("Video input", 10, 30);
  //cvMoveWindow("Video gray levels", 800, 30);
  cvMoveWindow("Video Mediane custom", 10, 0);
  cvMoveWindow("Video Edge detection", 800, 0);
  
  
// --------------------------------------------------
// boucle infinie pour traiter la séquence vidéo  
//
  int iter_count = 1;
  double sobel_time_sum = 0;
  while(key!='q'){
  //	  
  // acquisition d'une trame video - librairie OpenCV
    cap.read(frame);
  //conversion en niveau de gris - librairie OpenCV
    cvtColor(frame, frame_gray, CV_BGR2GRAY);

	
   // image smoothing by median blur
   // 
 int n = 17;
 int k = 1;  
 #ifdef PROFILE
 struct timeval start, end;
 double starting_date;
 double e;
 double s;
 for (k;k<n;k+=2)
 { 
#endif
   printf("MEDIAN k=%d\n", k);
   gettimeofday(&start, NULL);
   medianBlur(frame_gray, frame1_base, k);
   gettimeofday(&end, NULL);
   e = ((double) end.tv_sec * 1000000.0 + (double) end.tv_usec);
   s = ((double) start.tv_sec * 1000000.0 + (double) start.tv_usec);
   printf("       OPENCV: %0.lf µs\n", e-s);


   starting_date = ((double) start.tv_sec * 1000000.0 + (double) start.tv_usec);
   gettimeofday(&start, NULL);
   //medianBlur(frame_gray, frame1, k);
   median_blur(frame_gray, frame1, k);
#ifdef PROFILE 
   gettimeofday(&end, NULL);
   e = ((double) end.tv_sec * 1000000.0 + (double) end.tv_usec);
   s = ((double) start.tv_sec * 1000000.0 + (double) start.tv_usec);
   printf("       CUSTOM: %0.lf µs\n", e-s);
 }
 printf("MEDIAN TOTAL TIME: %0.lf µs\n\n", e-starting_date);
 #endif
    
 gettimeofday(&start, NULL);
 sobel_opt( frame1, grad, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
 gettimeofday(&end, NULL);
 e = ((double) end.tv_sec * 1000000.0 + (double) end.tv_usec);
 s = ((double) start.tv_sec * 1000000.0 + (double) start.tv_usec);
 sobel_time_sum+= (e-s);
   printf("SOBEL iteration: %d    time: %0.lf µs    mean time: %0.lf µs\n\n", iter_count, (e - s), sobel_time_sum/((double) iter_count));


    // ------------------------------------------------
	// calcul du gradient- librairie OpenCV
 /// Gradient Y
 
    
    // -------------------------------------------------
	// visualisation
	// taille d'image réduite pour meuilleure disposition sur écran
    //    resize(frame, frame, Size(), 0.5, 0.5);
    //    resize(frame_gray, frame_gray, Size(), 0.5, 0.5);
    //    resize(grad, grad, Size(), 0.5, 0.5);
    
    //imshow("Video input",frame);
    //imshow("Video gray levels",frame_gray);
    imshow("Video Mediane custom",frame1);    
    imshow("Video Mediane base",frame1_base);    
    imshow("Video Edge detection",grad);  
    
    
    key=waitKey(5);
    iter_count++;
  }
}

    

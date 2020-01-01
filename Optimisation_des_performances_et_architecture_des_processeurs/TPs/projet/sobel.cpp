#include<deque>


int
abs(int a)
{
  if (a < 0)
    return -a;
  else
    return a;
}

// cuisant échec (apparement peu aisé de faire un SLA)
int
abs_opt(int a)
{
  int comp = a < 0;
  return a ^ ((comp << 16) >> 16) ;
}


// 374349
/*
void
sobel_opt(cv::InputArray src,
      cv::OutputArray dst,
      int ddepth,
      int dx,
      int dy,
      int ksize=3,
      double scale=1,
      double delta=0,
      int borderType=cv::BORDER_DEFAULT)
{
  assert(src.isMat());

  
  ushort *vec;

  cv::MatIterator_<ushort> it;
  
  auto mat_in = src.getMat();
  auto el_size = 1;
  auto h = mat_in.size[0];
  auto w = mat_in.size[1];
  std::cout << w << " " << h << std::endl;
  auto mat_out = cv::Mat(h, w, mat_in.type());

  auto length = h*w*el_size;

  auto ptr_in = mat_in.data;
  auto ptr_out = mat_out.data;
  auto histograms = std::vector<std::deque<ushort>>(w);
  //initialisation des histogrammes
  for (int i = 0; i < w; ++i)
  {
    histograms[i].push_front(0); // pour l'init
    histograms[i].push_front(ptr_in[i]);
    histograms[i].push_front(ptr_in[i+w]);
  }


  histograms[0].pop_back();
  histograms[0].push_front(w*2);

  histograms[1].pop_back();
  histograms[1].push_front(w*2+1);

  //algo
  for (int y = 1; y < h-1; y++)
  {
    for (int x = 1; x < w-1; x++)
    {
      auto i = x+w*y;
      
      ptr_out[i] = 
	abs(- histograms[x-1][0] + histograms[x+1][0]
	    - 2*histograms[x-1][1] + 2*histograms[x+1][1]
	    - histograms[x-1][2] + histograms[x+1][2])
	+
	abs(- histograms[x-1][0] - 2*histograms[x][0] - histograms[x+1][0]
	    + histograms[x-1][2] + 2*histograms[x][2] + histograms[x+1][2]);
    }
    for (int x = 0; x < w; ++x)
    {
      histograms[x].pop_back();
      histograms[x].push_front(ptr_in[(y+2)*w + x]); // on se décale d'une ligne

    }
  }
  dst.assign(mat_out);
  
}
*/









// moyenne: 17646 - 18733 µs
void
sobel(cv::InputArray src,
      cv::OutputArray dst,
      int ddepth,
      int dx,
      int dy,
      int ksize=3,
      double scale=1,
      double delta=0,
      int borderType=cv::BORDER_DEFAULT)
{  
  auto mat_in = src.getMat();
  auto el_size = 1;
  auto h = mat_in.size[0];
  auto w = mat_in.size[1];
  auto mat_out = cv::Mat(h, w, mat_in.type());

  auto length = h*w*el_size;

  auto ptr_in = mat_in.data;
  auto ptr_out = mat_out.data;

    for (int i = w+1; i < length-w; ++i)
    {
      ptr_out[i] = (
		    abs(2*(ptr_in[i+1] - ptr_in[i-1])
			+ ptr_in[i+1-w] - ptr_in[i-1-w]
			+ ptr_in[i+1+w] - ptr_in[i-1+w]) +
		    
		    abs(2*(ptr_in[i+w] - ptr_in[i-w])
			+ ptr_in[i+w-1] - ptr_in[i-w-1]
			+ ptr_in[i+w+1] - ptr_in[i-w+1])
		    )/2;
    }
    dst.assign(mat_out);
  
}

// 14828 µs
void
sobel_opt(cv::InputArray src,
	  cv::OutputArray dst,
	  int ddepth,
	  int dx,
	  int dy,
	  int ksize=3,
	  double scale=1,
	  double delta=0,
	  int borderType=cv::BORDER_DEFAULT)
{
  
  auto mat_in = src.getMat();
  auto el_size = 1;
  auto h = mat_in.size[0]; // height
  auto w = mat_in.size[1]; // width
  auto mat_out = cv::Mat(h, w, mat_in.type()); // tableau de sortie

  auto length = h*w*el_size;

  auto ptr_in = mat_in.data; // pointeur vers les données du tableau d'entrée
  auto ptr_out = mat_out.data; // pointeur vers les données du tableau de sortie
  auto ptr_avant = ptr_in - w; // ligne d'avant dans tableau d'entrée
  auto ptr_apres = ptr_in + w; // ligne d'après dans tableau de sortie

  int i = w+1;
  auto gauche = i-1;
  auto droite = i+1;
   
  auto c0 = ptr_avant[i];
  auto c1 = ptr_in[i];
  auto c2 = ptr_apres[i];
  auto g0 = ptr_avant[gauche];
  auto g1 = ptr_in[gauche];
  auto g2 = ptr_apres[gauche];
  auto d0 = ptr_avant[droite];
  auto d1 = ptr_in[droite];
  auto d2 = ptr_apres[droite];
  for  (i = w+1; i < length-w-32;)
  {
    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;










    //////////////////////////////////////////////////////////////////////////////////
    gauche = i-1;
    droite = i+1;
    

    ptr_out[i] = (
		  abs((d1 - g1)*2
		      + d0 - g0
		      + d2 - g2) +
		  
		  abs((c2 - c0)*2
		      + g2 - g0
		      + g2 - g0)
		  )/2;
    
    
    g0 = c0; // On décale le kernel de gauche à droite
    g1 = c1;
    g2 = c2;
    c0 = d0;
    c1 = d1;
    c2 = d2;
    d0 = ptr_avant[droite];
    d1 = ptr_in[droite];
    d2 = ptr_apres[droite];
    ++i;












    
  }
  dst.assign(mat_out);
  
}

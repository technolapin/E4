#pragma once

const unsigned MAX_UNSIGNED = 65535;



// la fonction de distance map générique
template<int dim, typename Box>
NImage<dim, unsigned, Box>
distance_map(const NImage<dim, unsigned, Box> &img)
{
  auto output = NImage<dim, unsigned, Box>(img);

  // les pixels en cours de calculs
  auto heads = std::queue<NPoint<dim>>();

  auto iter = img.iterator();
  auto nei_iter = img.neighboor_iterator();

  // on ajoute tous les pixels non-nuls à heads
  // et on donne comme valeurs au pixel sur l'image de sortie 0 si ajouté à head et MAX_UNSIGNED sinon
  for (iter.start(); iter.is_valid(); iter.next())
  {
    auto pt = iter.value();
    auto pix = img.get_pixel(pt).value();

    if (pix != 0)
    {
      heads.push(pt);
      output.set_pixel(pt, 0);
    }
    else
    {
      output.set_pixel(pt, MAX_UNSIGNED);
    }
  }

  //chaque pixels non-déjà calculé adjacent à un élément de heads va prendre pour valeur la valeur du pixel élément de heads plus 1, puis sera ajouté à heads lui aussi.
  // la structure de file garantie que les valeures des pixels traîtés seront croissantes.
  while (!heads.empty())
  {
    auto head = heads.front();
    heads.pop();
    auto dist_head = output.get_pixel(head).value();

    for (nei_iter.start(head);
	 nei_iter.is_valid();
	 nei_iter.next())
    {
      auto pt_nei = nei_iter.value();
      
      // si le pixel n'est pas déjà exploré
      if (output.get_pixel(pt_nei).value() == MAX_UNSIGNED)
      {
	output.set_pixel(pt_nei, dist_head+1);
	heads.push(pt_nei);
      }
    }
  }
  
  return output;
}




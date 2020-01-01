image="PS5-Images/cil.pgm"
threshold=105
area=300
volume=100
erosion=7

pink_bin/seuil $image $threshold pb2_thresholded.pgm
pink_bin/areaopening $image 8 $area pb2_by_area.pgm
pink_bin/seuil pb2_by_area.pgm $threshold pb2_area_and_threshold.pgm



pink_bin/erosball pb2_area_and_threshold.pgm $erosion pb2_eroded.pgm
pink_bin/geodilat pb2_eroded.pgm pb2_area_and_threshold.pgm 8 $erosion pb2_geoeros.pgm

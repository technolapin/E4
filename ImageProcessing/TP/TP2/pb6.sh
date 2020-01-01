
ngh="4"


pink_bin/erosion $1 gray_ese.pgm TMP_AEZALBEAZL
pink_bin/geodilat TMP_AEZALBEAZL $1 $ngh -1 TMP_AEZALBEAZL_fix


pink_bin/dilation TMP_AEZALBEAZL_fix gray_ese_neuuman_2.pgm TMP_AEZALBEAZL_fix_dil
pink_bin/geoeros TMP_AEZALBEAZL_fix_dil TMP_AEZALBEAZL_fix $ngh -1 $2

rm TMP_AEZALBEAZL

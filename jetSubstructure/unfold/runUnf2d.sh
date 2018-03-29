#void unfold1D(int kSample = kPP, int optX =1, double radius= 0.4, int nIter=1) {
cp unfold2D.cxx temp.cxx
more temp.cxx | sed s/unfold2D/unfold2D_matrixWeight0/g | sed s/'int matrixWeight = 1'/'int matrixWeight = 0'/g >& unfold2D_matrixWeight0.cxx
rm temp.cxx


root -l <<EOF
gSystem->Load("libRooUnfold");
.L unfold2D.cxx++
.L unfold2D_matrixWeight0.cxx++
EOF

for kSample in 1 0 # 0 = pp,  1 = pbpb
do
    for optX in 1  # 1
    do
	for optY in 2  # 1
	do
	    for radius in 0.4
	    do
		for specRwt in 1 0
		do
		    root -l -b -q  'unfold2D.cxx+('$kSample','$optX','$optY','$radius','$specRwt')'
   	            root -l -b -q  'unfold2D_matrixWeight0.cxx+('$kSample','$optX','$optY','$radius','$specRwt')'
		done
	    done
	done
    done
done

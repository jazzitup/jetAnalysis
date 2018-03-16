#void unfold1D(int kSample = kPP, int optX =1, double radius= 0.4, int nIter=1) {
root -l <<EOF
gSystem->Load("libRooUnfold");
.L unfold2D.cxx++
.L unfold2D_matrixWeight0.cxx++
EOF

for kSample in 1 # 0 = pp,  1 = pbpb
do
    for optX in 1  # 1
    do
	for optY in 2  # 1
	do
	    for radius in 0.4
	    do
		for specRwt in 0 1
		do
		    root -l -b -q  'unfold2D.cxx+('$kSample','$optX','$optY','$radius','$specRwt')'
   	            root -l -b -q  'unfold2D_matrixWeight0.cxx+('$kSample','$optX','$optY','$radius','$specRwt')'
		done
	    done
	done
    done
done

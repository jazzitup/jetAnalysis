
root -l <<EOF
gSystem->Load("libRooUnfold");
.L unfold2D.cxx++
.L unfold2D_matrixWeight0.cxx++
EOF

optX=1 
optY=2 


for kSample in 0 1  # 0 = pp,  1 = pbpb
do
    for etaBin in 0 1 2
    do
	for specRwt in 1
	do
	    root -l -b -q  'unfold2D.cxx+('$kSample','$optX','$optY','$etaBin','$specRwt')'
	done
    done
done

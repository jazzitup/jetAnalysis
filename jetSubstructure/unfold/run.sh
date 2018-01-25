root -l <<EOF
gSystem->Load("libRooUnfold");
.L unfoldPtMass.cxx+
EOF

for optX in 1  
do
    for optY in 1 2
    do
	for radius in 0.4
	do
	    for niter in 6 8 # 10 12 14 20
	    do
		root -l -b -q  'unfoldPtMass.cxx+('$optX','$optY','$radius','$niter')'
	    done
	done
    done
done




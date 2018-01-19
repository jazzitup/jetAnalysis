root -l <<EOF
gSystem->Load("libRooUnfold");
.L unfoldPtMass.cxx+
EOF

for optX in 1  
do
    for optY in 2
    do
	for radius in 0.4
	do
	    for niter in 4 8 12 20 30 40 50 60 70 100 200 1000 
	    do
		root -l -b -q  'unfoldPtMass.cxx+('$optX','$optY','$radius','$niter')'
	    done
	done
    done
done




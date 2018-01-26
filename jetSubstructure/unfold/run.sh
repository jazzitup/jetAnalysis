root -l <<EOF
gSystem->Load("libRooUnfold");
.L unfoldPtMass.cxx+
EOF

for kSample in 1  # 0 = pp,  1 = pbpb
do
    for optX in 1  
    do
	for optY in 1 2
	do
	    for radius in 0.4
	    do
		for niter in 2 4 6 8 10 # 10 12 14 20
		do
		    root -l -b -q  'unfoldPtMass.cxx+('$kSample','$optX','$optY','$radius','$niter')'
		done
	    done
	done
    done
done


root -l <<EOF
gSystem->Load("libRooUnfold");
.L unfoldPtMass.cxx+
EOF

for kSample in  0  # 0 = pp,  1 = pbpb
do
    for optX in 1  # 1
    do
	for optY in 2 
	do
	    for radius in 0.4
	    do
		root -l -b -q  'unfoldPtMass.cxx+('$kSample','$optX','$optY','$radius')'
	    done
	done
    done
done


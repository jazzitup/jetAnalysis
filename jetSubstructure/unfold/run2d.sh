root -l <<EOF
gSystem->Load("libRooUnfold");
.L makeUnfMatrix2D.cxx++
EOF

for kSample in 1 0  # 0 = pp,  1 = pbpb
do
    for doReweight in 1 0 
    do
	for optX in 1  # 1
	do
	    for optY in 2 # 1
	    do
		for radius in 0.4
		do
		    root -l -b -q  'makeUnfMatrix2D.cxx+('$kSample','$optX','$optY','$radius','$doReweight')'
		done
	    done
	done
    done
done


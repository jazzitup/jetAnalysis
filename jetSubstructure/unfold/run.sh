root -l <<EOF
gSystem->Load("libRooUnfold");
.L unfoldPtMass.cxx+
EOF

for optX in 1
do
    for optY in 1
    do
	root -l  'unfoldPtMass.cxx+('$optX','$optY',0.4)'
    done
done




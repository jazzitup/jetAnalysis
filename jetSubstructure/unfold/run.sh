root -l <<EOF
gSystem->Load("libRooUnfold");
.L unfoldPtMass.cxx+
EOF

for optX in 1
do
    for optY in 1
    do
	root -l  'unfoldPtMass.cxx+('$optX','$optY',"jetSubstructure_Data_HION9_v4.7_v1_Jan7")'
    done
done



